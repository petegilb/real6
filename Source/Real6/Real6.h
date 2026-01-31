// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// Powers that the player can steal from enemies.
// Not every interactable will have a power type.
UENUM(BlueprintType)
enum class EPowerType : uint8
{
	None        UMETA(DisplayName = "No Power"),
	Carry       UMETA(DisplayName = "Carry Power"),
	Jump        UMETA(DisplayName = "Jump Power"),
	Max         UMETA(Hidden) // Used for counting, not shown in UI
};

#define LOG_ARGS(LogLevel, Message, ...) UE_LOG(LogTemp, LogLevel, TEXT(Message), __VA_ARGS__)
