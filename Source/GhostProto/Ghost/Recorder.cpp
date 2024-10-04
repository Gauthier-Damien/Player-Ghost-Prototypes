

#include "../Ghost/Recorder.h"
#include "CheckPoint.h"
#include "Components/BoxComponent.h"


ARecorder::ARecorder()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ARecorder::BeginPlay()
{
	Super::BeginPlay();
	

	if (!recorderData.start || !recorderData.end) return;
	recorderData.start->OnActorBeginOverlap.AddDynamic(this, &ARecorder::BeginRecord);
	recorderData.end->OnActorBeginOverlap.AddDynamic(this, &ARecorder::EndRecord);

	playData.locations = TArray<FVector>();
	if(!recorderData.playerActor) recorderData.playerActor = (AActor*)GetWorld()->GetFirstPlayerController()->GetPawn();

	SwitchCollision(recorderData.start, recorderData.end);

}

void ARecorder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//TODO on pawn
	if(recorderData.ghostActor && recorderData.ghostActor->GetActorLocation() != targetLocation)
		recorderData.ghostActor->SetActorLocation(FMath::VInterpConstantTo(recorderData.ghostActor->GetActorLocation(), targetLocation,DeltaTime, recorderData.interpSpeed));
}

void ARecorder::RegisterLocation()
{
	if (!recorderData.playerActor) return;

	LOG_WARNING("Record");
	playData.AddLocation(recorderData.playerActor->GetActorLocation());

}


void ARecorder::Play()
{
	if (!recorderData.ghostActor || playIndex >= playData.locations.Num()) 
	{
		EndPlayingRecord();
		return;
	}

	LOG_WARNING("Play Record");

	targetLocation = FVector(playData.locations[playIndex].X, playData.locations[playIndex].Y - 1600 , playData.locations[playIndex].Z);
	playIndex++;

}

void ARecorder::BeginRecord(AActor* _overlappedActor, AActor* _otherActor)
{

	LOG_ERROR("Begin Recording");

	GetWorld()->GetTimerManager().SetTimer(timer, this, &ARecorder::RegisterLocation, recorderData.recordRate, true, 0.f);
	SwitchCollision(recorderData.end, recorderData.start);

}

void ARecorder::EndRecord(AActor* _overlappedActor, AActor* _otherActor)
{
	LOG_ERROR("End Record");

	SwitchCollision(recorderData.start, recorderData.end);

	GetWorld()->GetTimerManager().ClearTimer(timer);
	GetWorld()->GetTimerManager().SetTimer(timer, this, &ARecorder::Play, recorderData.recordRate, true, recorderData.timeBeforePlaying);

	BeginPlayingRecord();

}

void ARecorder::BeginPlayingRecord()
{

	LOG_ERROR("Begin Playing Record");

	if (GetWorld()->GetFirstPlayerController() && recorderData.cameraView)
		GetWorld()->GetFirstPlayerController()->SetViewTarget(recorderData.cameraView);

	recorderData.ghostActor->SetActorLocation(FVector(playData.locations[0].X, playData.locations[0].Y - 1600, playData.locations[0].Z));
	playIndex++;
	if (recorderData.ghostActor) targetLocation = recorderData.ghostActor->GetActorLocation();

}

void ARecorder::EndPlayingRecord()
{
	LOG_ERROR("End Playing Record");

	GetWorld()->GetTimerManager().ClearTimer(timer);
	playData.ClearLocation();
}

