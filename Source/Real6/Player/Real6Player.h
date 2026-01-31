// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "Real6Player.generated.h"

class ACameraRail;
class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;

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

	// Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Components)
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Components)
	TObjectPtr<UCameraComponent> Camera;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Player)
	void Move(const FInputActionValue& Value);

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<ACameraRail> CameraRail;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Camera)
	float SplineRailInterpSpeed = 20.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Movement)
	FVector MovementForwardAxis = FVector(-1, 0, 0);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Movement)
	FVector MovementRightAxis = FVector(0, 1, 0);
};
