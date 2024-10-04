// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "InputsRecorder.generated.h"

class AGhostCharacter;


USTRUCT()
struct FDataAction
{

	GENERATED_BODY()
public:
	float timeStamp;
	UInputAction* action;
	FInputActionValue value;
	FRotator rotation;
	//ETriggerEvent eventType;
};



USTRUCT()
struct FData
{

	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere)
	TArray<FDataAction> dataAction;
};



UCLASS()
class GHOSTPROTO_API AInputsRecorder : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Ghost Character")
	TObjectPtr<AGhostCharacter> ghostCharacter = NULL;

	UPROPERTY(VisibleAnywhere, Category = "Datas")
	FData data = FData();

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Record")
	TArray<UInputAction*> actions = TArray<UInputAction*>();

	UPROPERTY(EditAnywhere, Category = "Record")
	float recordTime = 5.f;


	UPROPERTY(EditAnywhere, Category = "ActorPtr")
	TObjectPtr<AActor> cameraView;

	UPROPERTY(VisibleAnywhere)
	UEnhancedInputComponent* enhancedInputComponent = NULL;

	UPROPERTY()
	FTimerHandle timer;

public:
	AInputsRecorder();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float _deltatime) override;


#pragma region Recording
private:
	void SetUpRegisterParameters();
public:
	/// <summary>
	/// Record input value
	/// </summary>
	/// <param name="_value"></param>
	/// <param name="_action"></param>
	UFUNCTION()
	void RecordValue(const FInputActionValue& _value, UInputAction* _action);
#pragma endregion Recording


#pragma region Playing
public:
	/// <summary>
	/// Return a list of action to record
	/// </summary>
	/// <returns></returns>
	FORCEINLINE TArray<UInputAction*> GetActionsList() const
	{
		return actions;
	}


	/// <summary>
	///  set timers to inject at timestamp, recorded inputs to Ghost character
	/// </summary>
	UFUNCTION()
	void Play();
	/// <summary>
	/// Function call by timmers sets in Play
	/// </summary>
	/// <param name="_time"></param>
	/// <param name="_action"></param>
	/// <param name="_value"></param>
	/// <param name="_rotation"></param>
	UFUNCTION()
	void InjectInputToCharacter(float _time, UInputAction* _action, const FInputActionValue& _value, const FRotator& _rotation);

#pragma endregion Playing

};
