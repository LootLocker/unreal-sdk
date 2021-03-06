// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAPI/LLDropTablesRequestHandler.h"

ULootLockerHttpClient* ULLDropTablesRequestHandler::HttpClient = nullptr;

ULLDropTablesRequestHandler::ULLDropTablesRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULLDropTablesRequestHandler::ComputeAndLockDropTable(int TableId, const FLootLockerComputeAndLockDropTableResponseBP& OnCompletedRequestBP, const FLootLockerComputeAndLockDropTableResponseDelegate& OnCompletedRequest)
{
	FString ContentString;
	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FLootLockerComputeAndLockDropTableResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerComputeAndLockDropTableResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
				ResponseStruct.success = true;
			}
			else {
				ResponseStruct.success = false;
				UE_LOG(LogTemp, Error, TEXT("Update character failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});

	FLootLockerEndPoints endpoint = ULootLockerGameEndpoints::ComputeAndLockDropTable;

	FString newEndpoint = FString::Format(*endpoint.endpoint, { TableId });
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(endpoint.requestMethod));
	HttpClient->SendApi(newEndpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULLDropTablesRequestHandler::PickDropsFromDropTable(const FLootLockerPickDropsFromDropTableRequest& request, int TableId, const FFLootLockerPickDropsFromDropTableResponseBP& OnCompletedRequestBP, const FFLootLockerPickDropsFromDropTableResponseDelegate& OnCompletedRequest)
{
	FString ContentString;
	FJsonObjectConverter::UStructToJsonObjectString(FLootLockerPickDropsFromDropTableItem::StaticStruct(), &request, ContentString, 0, 0);

	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FLootLockerPickDropsFromDropTableResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerPickDropsFromDropTableResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
				ResponseStruct.success = true;
			}
			else {
				ResponseStruct.success = false;
				UE_LOG(LogTemp, Error, TEXT("Update character failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});

	FLootLockerEndPoints endpoint = ULootLockerGameEndpoints::ComputeAndLockDropTable;

	FString newEndpoint = FString::Format(*endpoint.endpoint, { TableId });
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(endpoint.requestMethod));
	HttpClient->SendApi(newEndpoint, requestMethod, ContentString, sessionResponse, true);
}
