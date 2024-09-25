#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Recorder.generated.h"



/// <summary>
/// First Proto for Ghost
/// 
/// Record All player states and pass it to a ghost,
/// ghost play all record information to imitates player actions
/// 
/// whats good ?
/// fidelity of movement whith hight register rate,
/// simple
/// easy to set up and use
/// lag proof
/// 
/// whats wrong ?
/// a lot of data register and play
/// need hight rate to seem natural movement
/// 
/// 
/// can be use for small level
/// for wider levels, too many data will be register, and can cause latency
/// 
/// 
/// </summary>

class ACheckPoint;


#define LOG_WARNING(string) UE_LOG(LogTemp, Warning, TEXT(string));
#define LOG_ERROR(string) UE_LOG(LogTemp, Error, TEXT(string));

USTRUCT()
struct FRecorderData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = floatData)
	float recordRate = 0.1f;
	UPROPERTY(EditAnywhere, Category = floatData)
	float timeBeforePlaying = 10.f;
	UPROPERTY(EditAnywhere, Category = floatData)
	float interpSpeed = 300.f;


	UPROPERTY(EditAnywhere, Category = ActorPtr)
	TObjectPtr<AActor> cameraView;



	UPROPERTY(VisibleAnywhere, Category = ActorPtr)
	TObjectPtr<AActor> playerActor;
	UPROPERTY(EditAnywhere, Category = ActorPtr)
	TObjectPtr<AActor> ghostActor;
	UPROPERTY(EditAnywhere, Category = ActorPtr)
	TObjectPtr<ACheckPoint > start;
	UPROPERTY(EditAnywhere, Category = ActorPtr)
	TObjectPtr<ACheckPoint> end;

};



/// <summary>
/// Struct with all player data need to replay actions
/// </summary>
USTRUCT()
struct FPlayerData
{

	/// TODO Upgrade for animatons
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	TArray<FVector> locations;

	inline void AddLocation(FVector _location)
	{
		locations.Add(_location);
	}

	inline void ClearLocation()
	{
		locations.Empty();
	}


};

UCLASS()
class GHOSTPROTO_API ARecorder : public AActor
{
	GENERATED_BODY()
	
public:
	/// <summary>
	/// Recorder Main Data
	/// </summary>
	UPROPERTY(EditAnywhere)
	FRecorderData recorderData = FRecorderData();
	/// <summary>
	/// Player Data record 
	/// </summary>
	UPROPERTY(EditAnywhere)
	FPlayerData playData = FPlayerData();

private:
	FTimerHandle timer;
	int playIndex = 0;
	//TODO on pawn
	FVector targetLocation;

public:	
	ARecorder();


protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/// <summary>
	/// Register all player locations,
	/// Not really optiise, lot of datas are save
	/// 
	/// Register data -> Player Location at timeStamp based on recordRate
	/// </summary>
	UFUNCTION()
	void RegisterLocation();


	/// <summary>
	/// browse locations list,
	/// Hight cost
	/// 
	/// browse all location register, and set target for ghost actor
	/// </summary>
	UFUNCTION()
	void Play();


private:

	/// <summary>
	/// Begin recorder timer at Rate (recorderRate -> recorderData)
	/// </summary>
	/// <param name="_overlappedActor"></param>
	/// <param name="_otherActor"></param>
	UFUNCTION()
	void BeginRecord(AActor* _overlappedActor, AActor* _otherActor);


	/// <summary>
	/// End Record and clear timer
	/// Init BeginPlayingRecord
	/// </summary>
	/// <param name="_overlappedActor"></param>
	/// <param name="_otherActor"></param>
	UFUNCTION()
	void EndRecord(AActor* _overlappedActor, AActor* _otherActor);


	/// <summary>
	/// Set up timer, location and cameraView
	/// Init Play
	/// </summary>
	void BeginPlayingRecord();

	/// <summary>
	/// Clear all
	/// </summary>
	void EndPlayingRecord();


	/// <summary>
	/// Switch Collision to True / false
	/// Use to switch start and end collision to prevent loop
	/// </summary>
	/// <param name="_switchToTrue"></param>
	/// <param name="_switchToFalse"></param>
	inline void SwitchCollision(AActor* _switchToTrue, AActor* _switchToFalse)
	{
		_switchToTrue->SetActorEnableCollision(true);
		_switchToFalse->SetActorEnableCollision(false);
	}
};
