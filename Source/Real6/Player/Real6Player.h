// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "Real6/Real6.h"
#include "Real6Player.generated.h"

class AEnemy;
class ACameraRail;
class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;

UENUM(BlueprintType)
enum class EPlayerStatus : uint8
{
	Alive,
	Dead,
	Max
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeathSignature, ACharacter*, Player);
class AInteract_Item;
UCLASS()
class REAL6_API AReal6Player : public ACharacter
{
	GENERATED_BODY()

public:
	AReal6Player();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InteractAction;

	// Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Components)
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Components)
	TObjectPtr<UCameraComponent> Camera;

	UFUNCTION(BlueprintCallable, Category = Player)
	void Die();

	UFUNCTION(BlueprintCallable, Category = "Player")
	void CheckpointReached(FTransform NewCheckpoint);

	UFUNCTION(BlueprintCallable, Category = "Player")
	void GoalReached();

	UFUNCTION(BlueprintCallable, Category = "Player")
	void StealMask(AEnemy* InEnemy);

	UPROPERTY(BlueprintAssignable)
	FOnDeathSignature OnDeathDelegate;

	UPROPERTY(BlueprintReadWrite)
	FTransform StartPoint = FTransform::Identity;

	UPROPERTY(BlueprintReadWrite)
	FTransform LastCheckpoint = FTransform::Identity;

	UPROPERTY(BlueprintReadWrite)
	EPlayerStatus CurrentStatus = EPlayerStatus::Alive;
	
	UFUNCTION( BlueprintCallable )
	void PickupItem(AInteract_Item* Item);

	UFUNCTION( BlueprintCallable )
	void DropItem( );
protected:
	virtual void BeginPlay() override;

	void InitCameraRail();
	void MoveCameraOnRail(float DeltaTime);

	void Respawn();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Player)
	void Move(const FInputActionValue& Value);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Player)
	void DoInteract(const FInputActionValue& Value);

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<ACameraRail> CameraRail;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Camera)
	float SplineRailInterpSpeed = 20.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Camera)
	float CameraRotationSpeed = 10.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Movement)
	float PlayerRotationRate = 10.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Movement)
	FRotator PlayerRotationTarget = FRotator::ZeroRotator;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Movement)
	FVector MovementForwardAxis = FVector(-1, 0, 0);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Movement)
	FVector MovementRightAxis = FVector(0, 1, 0);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Power)
	EPowerType CurrentPower = EPowerType::None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Power)
	UAnimMontage* StealMaskMontage = nullptr;

	UFUNCTION()
	void OnStealMaskMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	// Interact
	UPROPERTY()
	AActor* InteractedObject = nullptr;
	
	FTimerHandle InteractTimerHandle;
	
	void InteractTimerEvent();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Interact)
	float InteractTimerSpeed = .1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Interact)
	float InteractRadius = 200.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Interact)
	float StartInteractDistance = 50.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Interact)
	float EndInteractDistance = 50.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Interact)
	bool bShowInteractTrace = true;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Interact" )
	AInteract_Item* HeldItem;
};
