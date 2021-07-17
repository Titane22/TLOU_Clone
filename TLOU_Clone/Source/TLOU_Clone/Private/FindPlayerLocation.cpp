// Fill out your copyright notice in the Description page of Project Settings.


#include "FindPlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "ModularAIController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "blackboard_keys.h"


UFindPlayerLocation::UFindPlayerLocation(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Find Player Location");
}

EBTNodeResult::Type UFindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//�÷��̾� ��ü ��������
	ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	//��Ʈ�ѷ� ��������
	auto const cont = Cast<AModularAIController>(OwnerComp.GetAIOwner());

	//�÷��̾� ��ġ ��������
	FVector const player_location = player->GetActorLocation();

	if (search_random)
	{
		FNavLocation loc;

		//����ý���, ������ġ
		UNavigationSystemV1* const nav_sys = UNavigationSystemV1::GetCurrent(GetWorld());
		if (nav_sys->GetRandomPointInNavigableRadius(player_location, search_radius, loc, nullptr))
		{
			cont->get_blackboard()->SetValueAsVector(bb_keys::target_location, loc.Location);
		}
	} 
	else
	{
		cont->get_blackboard()->SetValueAsVector(bb_keys::target_location, player_location);
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
