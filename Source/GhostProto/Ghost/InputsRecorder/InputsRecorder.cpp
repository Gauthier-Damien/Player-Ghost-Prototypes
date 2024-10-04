#include "../../Ghost/InputsRecorder/InputsRecorder.h"
#include "../GhostCharacter.h"


// stick -> Angle 
// action true/false
// 
//---------------------------------------
//|	Time	|	Action	 |	stick angle	|
//---------------------------------------
//|	10s		|	   A	 |	    360		|
//---------------------------------------
//
// retrib :
// call action func corresponding  Action in Angle on Time 
//


AInputsRecorder::AInputsRecorder()
{
	PrimaryActorTick.bCanEverTick = true;
	

}

void AInputsRecorder::BeginPlay()
{
	Super::BeginPlay();
	SetUpRegisterParameters();

}

void AInputsRecorder::Tick(float _deltatime)
{
	Super::Tick(_deltatime);
}


#pragma region Recording
void AInputsRecorder::SetUpRegisterParameters()
{
	enhancedInputComponent = GetWorld()->GetFirstPlayerController()->GetPawn()->GetComponentByClass<UEnhancedInputComponent>();

	if (!enhancedInputComponent || actions.IsEmpty()) return;

	//UE_LOG(LogTemp, Warning, TEXT("Set Up Parameters"));


	FTimerDelegate Delegate;
	Delegate.BindUFunction(this, "Play");


	GetWorld()->GetTimerManager().SetTimer(timer, Delegate, recordTime, false);




	for (UInputAction* _currentAction : actions)
	{


		//UE_LOG(LogTemp, Warning, TEXT("Set up : %s"), *_currentAction->GetName());

		//for (UInputTrigger* _trigger : _currentAction->Triggers)
		//{
		//	ETriggerType _type = _trigger->GetTriggerType();
		//	//UE_LOG(LogTemp, Warning, TEXT("Register new input type"));
		//}

		enhancedInputComponent->BindAction(_currentAction, ETriggerEvent::Triggered, this, &AInputsRecorder::RecordValue, _currentAction);


	}

}

void AInputsRecorder::RecordValue(const FInputActionValue& _value, UInputAction* _action)
{
	//UE_LOG(LogTemp, Warning, TEXT("Record %s"), *_action->GetName());

	data.dataAction.Add(FDataAction(GetWorld()->GetTimerManager().GetTimerElapsed(timer), _action, _value, GetWorld()->GetFirstPlayerController()->GetControlRotation()));
}

#pragma endregion Recording


#pragma region Playing
void AInputsRecorder::Play()
{

	if (GetWorld()->GetFirstPlayerController() && cameraView)
		GetWorld()->GetFirstPlayerController()->SetViewTarget(cameraView);

	GetWorld()->GetTimerManager().ClearTimer(timer);



	//TODO Warning : can break if ghost is scoreboard and not pre-registered => ptr* action / schearch a way to do it with FName
	for (int i = 0; i < data.dataAction.Num(); i++)
	{
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "InjectInputToCharacter", data.dataAction[i].timeStamp, data.dataAction[i].action, data.dataAction[i].value, data.dataAction[i].rotation);
		FTimerHandle _handle = GetWorld()->GetTimerManager().GenerateHandle(i);
		GetWorld()->GetTimerManager().SetTimer(_handle, Delegate, data.dataAction[i].timeStamp, false);
	}


}

void AInputsRecorder::InjectInputToCharacter(float _time, UInputAction* _action, const FInputActionValue& _value, const FRotator& _rotation)
{
	if (!ghostCharacter)
		return;
	ghostCharacter->InjectInput(_time, _action->GetName(), _value, _rotation);

}
#pragma endregion Playing

