// CC-BY-NC-4.0

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "PlayerPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class ILARISONE_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> ZoomAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> CameraMovementAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> CameraRotateRightAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> CameraRotateLeftAction;

	UPROPERTY(EditAnywhere, Category = Input)
	float MaxSpringArmLength = 5000.0f;

	UPROPERTY(EditAnywhere, Category = Input)
	float MinSpringArmLength = 100.0f;

	UPROPERTY(EditAnywhere, Category = Input)
	float ZoomSpeedFactor = 100.0f;

	UPROPERTY(BlueprintReadOnly, Category = Input)
	FRotator DesiredRotation;

	void Zoom(const FInputActionValue& Value);
	void MoveCamera(const FInputActionValue& Value);
	void RotateCameraRight(const FInputActionValue& Value);
	void RotateCameraLeft(const FInputActionValue& Value);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
