#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "ALiftTrigger.generated.h"

UCLASS()
class ALiftTriggerBox : public ATriggerBox
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	
public:
	ALiftTriggerBox();
	
	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);
	
	UFUNCTION()
	void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);
};
