// Fill out your copyright notice in the Description page of Project Settings.


#include "Real6Player.h"

#include "CameraRail.h"
#include "Interact_Item.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SplineComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Real6/Enemy.h"
#include "Real6/Interactable.h"


AReal6Player::AReal6Player()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArmComponent);
	
	bUseControllerRotationYaw = false;
}

void AReal6Player::Die()
{
	OnDeathDelegate.Broadcast(this);
	UE_LOG(LogTemp, Log, TEXT("Player has died."))
	GEngine->AddOnScreenDebugMessage(66, 5.f, FColor::Red, TEXT("You Died!"));
	CurrentStatus = EPlayerStatus::Dead;

	GetCharacterMovement()->DisableMovement();
	PlayerRotationTarget = FRotator(180, 0, 0);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
	{
		Respawn();
	}, 3.0f, false);
}

void AReal6Player::CheckpointReached(FTransform NewCheckpoint)
{
	LastCheckpoint = NewCheckpoint;
}

void AReal6Player::GoalReached()
{
	UE_LOG(LogTemp, Log, TEXT("Player goal reached."))
	GEngine->AddOnScreenDebugMessage(33, 10.f, FColor::Green, TEXT("You win!!!"));
}

void AReal6Player::StealMask(AEnemy* InEnemy)
{
	if (!IsValid(InEnemy))
	{
		UE_LOG(LogTemp, Warning, TEXT("Tried to steal mask, but enemy is invalid."))
		return;
	}

	if (CurrentPower != EPowerType::None) return;

	// TODO play animation here too.
	UAnimInstance* AnimInstance = GetMesh() ? GetMesh()->GetAnimInstance() : nullptr;
	if (!(AnimInstance && StealMaskMontage)) return;
	float Duration = AnimInstance->Montage_Play(StealMaskMontage);

	GetCharacterMovement()->DisableMovement();

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, InEnemy]()
	{
		if (CurrentStatus != EPlayerStatus::Alive) return;
		GetCharacterMovement()->SetMovementMode(MOVE_Walking);
		
		LOG_ARGS(Log, "Stealing mask from %s", *InEnemy->GetName())
		// Activate new power
		// TODO: play sound
		USkeletalMesh* EnemyMesh = InEnemy->GetMesh()->GetSkeletalMeshAsset();
		if (EnemyMesh && InEnemy->EnemyPowerType != EPowerType::None)
		{
			CurrentPower = InEnemy->EnemyPowerType;
			GetMesh()->SetSkeletalMesh(EnemyMesh, true);
			if (AnimationBlueprintMap.Contains(CurrentPower))
			{
				GetMesh()->SetAnimInstanceClass(AnimationBlueprintMap.FindRef(CurrentPower));
			}
		}
	}, 0.3, false);
}

void AReal6Player::OnStealMaskMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	
}

void AReal6Player::BeginPlay()
{
	Super::BeginPlay();

	if (UWorld*	World = GetWorld())
	{
		// Set Interact timer
		World->GetTimerManager().SetTimer(
			InteractTimerHandle, this, &ThisClass::InteractTimerEvent, InteractTimerSpeed, true
		);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("World was not found so we couldn't initialize interact timer!"));
	}

	// Set last checkpoint to the starting position.
	LastCheckpoint = GetActorTransform();
	StartPoint = LastCheckpoint;
}

void AReal6Player::Move_Implementation(const FInputActionValue& Value)
{
	if (CurrentStatus == EPlayerStatus::Dead)
	{
		return;
	}
	
	const FVector2D MovementValue = Value.Get<FVector2D>();
	// AddMovementInput(GetActorRightVector(), -MovementValue.X);
	// AddMovementInput(GetActorForwardVector(), MovementValue.Y);
	
	// Constrict movement to world axis
	AddMovementInput(MovementRightAxis, MovementValue.X);
	AddMovementInput(MovementForwardAxis, MovementValue.Y);

	FVector MoveDirection = MovementRightAxis * MovementValue.X + MovementForwardAxis * MovementValue.Y;
	if (!MoveDirection.IsNearlyZero())
	{
		// Convert movement direction to rotation (yaw only)
		PlayerRotationTarget = UKismetMathLibrary::MakeRotFromX(MoveDirection);
		PlayerRotationTarget.Pitch = 0.f;
		PlayerRotationTarget.Roll = 0.f;
	}
}

void AReal6Player::InitCameraRail()
{
	// Keep checking for camera rail until we get one.
	if (!IsValid(CameraRail))
	{
		TArray<AActor*> OutRails;
		UGameplayStatics::GetAllActorsOfClass(this, ACameraRail::StaticClass(), OutRails);
		// Assume there is only 0 or 1 rail

		if (OutRails.Num() > 0)
		{
			CameraRail = Cast<ACameraRail>(OutRails[0]);
		}
		
		if (CameraRail)
		{
			UE_LOG(LogTemp, Log, TEXT("CameraRail found"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("CameraRail doesn't exist in level!"));
		}
	}
}

void AReal6Player::MoveCameraOnRail(float DeltaTime)
{
	if (!IsValid(CameraRail)) return;

	USplineComponent* Spline = CameraRail->CameraSpline;
	float InputKey = Spline->FindInputKeyClosestToWorldLocation(GetActorLocation() + CameraRail->GetDistanceOffset());
	float SplineDistance = Spline->GetDistanceAlongSplineAtSplineInputKey(InputKey);
	FVector TargetLocation = Spline->GetLocationAtDistanceAlongSpline(
		SplineDistance, ESplineCoordinateSpace::World);
	
	FVector CurrentLocation = SpringArmComponent->GetComponentLocation();
	FVector NewCamLocation = UKismetMathLibrary::VInterpTo(
		CurrentLocation, TargetLocation, DeltaTime, SplineRailInterpSpeed);
	SpringArmComponent->SetWorldLocation(NewCamLocation);

	FVector PlayerLoc = GetActorLocation();
	FVector CameraLoc = Camera->GetComponentLocation();
	
	// Look at player
	FRotator LookAt = UKismetMathLibrary::FindLookAtRotation(CameraLoc, PlayerLoc);
	FRotator FinalRot = FMath::RInterpTo(
		Camera->GetComponentRotation(),
		LookAt,
		DeltaTime,
		CameraRotationSpeed
	);
	Camera->SetWorldRotation(FinalRot);
}

void AReal6Player::Respawn()
{
	SetActorTransform(LastCheckpoint);
	CurrentStatus = EPlayerStatus::Alive;
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	PlayerRotationTarget = FRotator::ZeroRotator;
	SetActorRotation(PlayerRotationTarget);
	DoTransform();
}

void AReal6Player::DoTransform_Implementation()
{
	if (!AnimationBlueprintMap.Contains(EPowerType::None)) return;
	if (!PlayerMesh) return;
	GetMesh()->SetSkeletalMesh(PlayerMesh);
	GetMesh()->SetAnimInstanceClass(AnimationBlueprintMap.FindRef(EPowerType::None));
	CurrentPower = EPowerType::None;
}

void AReal6Player::DoJump_Implementation(const FInputActionValue& Value)
{
	if (CurrentPower != EPowerType::Jump) return;
	
	// TODO. check if we have the right mask
	if (GetCharacterMovement()->IsMovingOnGround())
	{
		Jump();
	}
}

void AReal6Player::DoInteract_Implementation(const FInputActionValue& Value)
{
	if (HeldItem)
	{
		DropItem();
		return;
	}
	
	if (IsValid(InteractedObject) && InteractedObject->Implements<UInteractable>())
	{
		IInteractable::Execute_Interact(InteractedObject, this);
	}
}

void AReal6Player::InteractTimerEvent()
{
	FVector Start = GetActorLocation() + (GetActorForwardVector()*StartInteractDistance);
	FVector End = GetActorLocation() + (GetActorForwardVector()*EndInteractDistance);

	FHitResult OutHit;

	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(this);

	UKismetSystemLibrary::SphereTraceSingle(this, Start, End, InteractRadius,
		UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_GameTraceChannel1),
		false, IgnoreActors, bShowInteractTrace ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None,
		OutHit, true
	);

	if (OutHit.bBlockingHit && OutHit.GetActor())
	{
		// FString HitString = FString::Printf(TEXT("Hit Object %s"), *OutHit.GetActor()->GetName());
		// GEngine->AddOnScreenDebugMessage(99, 5.f, FColor::Magenta, HitString);
		InteractedObject = OutHit.GetActor();
	}
	else
	{
		InteractedObject = nullptr;
	}
}

void AReal6Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Rotate player
	FRotator CurrentRotation = GetActorRotation();
	FRotator NewRotation = UKismetMathLibrary::RInterpTo(CurrentRotation,
		PlayerRotationTarget, DeltaTime, PlayerRotationRate);
	SetActorRotation(NewRotation);
	
	InitCameraRail();
	MoveCameraOnRail(DeltaTime);
}

void AReal6Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ThisClass::DoInteract);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ThisClass::DoJump);
		EnhancedInputComponent->BindAction(TransformAction, ETriggerEvent::Started, this, &ThisClass::DoTransform);
	}
}

void AReal6Player::PickupItem(AInteract_Item* Item) {
	if ( !Item ) return;

	if ( HeldItem ) return; // すでに持っているなら拾えない

	// ソケットにアタッチ
	Item->AttachToComponent(
		GetMesh( ),                               // キャラクターメッシュ
		FAttachmentTransformRules::SnapToTargetNotIncludingScale,
		FName( "ItemSocket" )                       // ソケット名
	);

	Item->SetActorRelativeLocation( FVector::ZeroVector ); // 必要ならオフセット調整

	HeldItem = Item;
}

void AReal6Player::DropItem( ) {
	if ( !HeldItem ) return;

	// ドロップ処理
	HeldItem->OnDropped( );

	// プレイヤー前方に置く
	FVector CapsuleOffset = FVector(0, 0, GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
	FVector DropLocation = (GetActorLocation( ) - CapsuleOffset) + GetActorForwardVector( ) * 150.f;
	HeldItem->SetActorLocation( DropLocation );
	HeldItem->SetActorRotation(FRotator::ZeroRotator);

	// アタッチ解除
	HeldItem->DetachFromActor( FDetachmentTransformRules::KeepWorldTransform );

	HeldItem = nullptr;
}