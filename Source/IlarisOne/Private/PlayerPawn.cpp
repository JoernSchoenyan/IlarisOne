// CC-BY-NC-4.0

// BP_PlayerPawn is derived from this class

#include "PlayerPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Math/UnrealMathUtility.h"
#include "IlarisOne/DebugMacros.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->TargetArmLength = 700.0f;
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->bEnableCameraLag = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void APlayerPawn::Zoom(const FInputActionValue &Value)
{
	const float DirectionValue = Value.Get<float>();

	if (GetController() && (DirectionValue != 0.0f))
	{
		float NewTargetArmLength = SpringArmComponent->TargetArmLength - DirectionValue * ZoomSpeedFactor;
		SpringArmComponent->TargetArmLength = FMath::Clamp(NewTargetArmLength, MinSpringArmLength, MaxSpringArmLength);
	}
}

void APlayerPawn::MoveCamera(const FInputActionValue &Value)
{
    const FVector2D DirectionValue = Value.Get<FVector2D>();

    if (GetController())
    {
        FVector NewLocation = GetActorLocation();

        // Erhalten Sie die Vorwärts- und Rechtsvektoren des Pawns
        FVector ForwardDirection = GetActorForwardVector();
        FVector RightDirection = GetActorRightVector();

        // Passen Sie die Position basierend auf der Eingabe und der Drehung des Pawns an
        NewLocation += (ForwardDirection * DirectionValue.X) + (RightDirection * DirectionValue.Y);

        SetActorLocation(NewLocation);
    }
}

void APlayerPawn::RotateCameraRight(const FInputActionValue &Value)
{
	FRotator NewRotation = GetActorRotation() + FRotator(0.0f, -45.0f, 0.0f);

	SetActorRotation(NewRotation);
}

void APlayerPawn::RotateCameraLeft(const FInputActionValue &Value)
{
	FRotator NewRotation = GetActorRotation() + FRotator(0.0f, 45.0f, 0.0f);

	SetActorRotation(NewRotation);
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &APlayerPawn::Zoom);
		EnhancedInputComponent->BindAction(CameraMovementAction, ETriggerEvent::Triggered, this, &APlayerPawn::MoveCamera);
		EnhancedInputComponent->BindAction(CameraRotateRightAction, ETriggerEvent::Triggered, this, &APlayerPawn::RotateCameraRight);
		EnhancedInputComponent->BindAction(CameraRotateLeftAction, ETriggerEvent::Triggered, this, &APlayerPawn::RotateCameraLeft);
	}
}
