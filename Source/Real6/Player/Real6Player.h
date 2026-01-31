// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "Real6/Real6.h"
#include "Real6Player.generated.h"

class ACameraRail;
class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeathSignature, ACharacter*, Player);

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

	UPROPERTY(BlueprintAssignable)
	FOnDeathSignature OnDeathDelegate;

	UPROPERTY(BlueprintReadWrite)
	FTransform LastCheckpoint = FTransform::Identity;
protected:
	virtual void BeginPlay() override;

	void InitCameraRail();
	void MoveCameraOnRail(float DeltaTime);

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
	FVector MovementForwardAxis = FVector(-1, 0, 0);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Movement)
	FVector MovementRightAxis = FVector(0, 1, 0);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Power)
	EPowerType CurrentPower = EPowerType::None;

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
};
