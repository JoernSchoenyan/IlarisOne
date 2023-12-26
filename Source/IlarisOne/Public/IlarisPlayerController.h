// CC-BY-NC-4.0

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "IlarisPlayerController.generated.h"

/**
 * BP_PlayerController is derived from this class
 */
UCLASS()
class ILARISONE_API AIlarisPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
};
