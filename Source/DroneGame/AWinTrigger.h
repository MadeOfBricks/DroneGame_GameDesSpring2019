#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "AWinTrigger.generated.h"

UCLASS()
class AWinTriggerBox : public ATriggerBox
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	
public:
	AWinTriggerBox();
	
	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);
	
	UFUNCTION()
	void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);
};

