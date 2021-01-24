// Copyright (c) 2021 LootLocker

#include "GameAPI/PurchasesRequestHandler.h"

#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "LootLockerGameEndpoints.h"

UHttpClient* UPurchasesRequestHandler::HttpClient = nullptr;

UPurchasesRequestHandler::UPurchasesRequestHandler()
{
    HttpClient = NewObject<UHttpClient>();
}

void UPurchasesRequestHandler::PurchaseAssets(const TArray<FAssetPurchaseData>& PurchaseData, const FPurchaseResponseDelegateBP& OnCompletedRequestBP, const FPurchaseResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FPurchaseResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FPurchaseResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("PurchaseAssets failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    TArray<TSharedPtr<FJsonValue>> ItemsJsonArray;
    for (auto Item : PurchaseData)
    {
        TSharedRef<FJsonObject> ItemJson = MakeShareable(new FJsonObject());
        if (FJsonObjectConverter::UStructToJsonObject(FAssetPurchaseData::StaticStruct(), &Item, ItemJson, 0, 0))
        {
            ItemsJsonArray.Push(MakeShareable(new FJsonValueObject(ItemJson)));
        }
    }

    FString ContentString;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&ContentString);
    FJsonSerializer::Serialize(ItemsJsonArray, Writer);
    
    const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
    FEndPoints Endpoint = LootLockerGameEndpoints::PurchaseEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    HttpClient->SendApi(Endpoint.endpoint, requestMethod, ContentString, sessionResponse, true);
}

void UPurchasesRequestHandler::PurchaseAssetsAndroid(const TArray<FAndroidAssetPurchaseData>& PurchaseData, const FPurchaseResponseDelegateBP& OnCompletedRequestBP, const FPurchaseResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FPurchaseResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FPurchaseResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("PurchaseAssets failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    TArray<TSharedPtr<FJsonValue>> ItemsJsonArray;
    for (auto Item : PurchaseData)
    {
        TSharedRef<FJsonObject> ItemJson = MakeShareable(new FJsonObject());
        if (FJsonObjectConverter::UStructToJsonObject(FAndroidAssetPurchaseData::StaticStruct(), &Item, ItemJson, 0, 0))
        {
            ItemsJsonArray.Push(MakeShareable(new FJsonValueObject(ItemJson)));
        }
    }

    FString ContentString;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&ContentString);
    FJsonSerializer::Serialize(ItemsJsonArray, Writer);
    
    const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
    FEndPoints Endpoint = LootLockerGameEndpoints::PurchaseEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    HttpClient->SendApi(Endpoint.endpoint, requestMethod, ContentString, sessionResponse, true);
}

void UPurchasesRequestHandler::PurchaseAssetsIOS(const TArray<FVerifyPurchaseIosData>& PurchaseData, const FPurchaseResponseDelegateBP& OnCompletedRequestBP, const FPurchaseResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FPurchaseResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FPurchaseResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("VerifyPurchaseIos failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    TArray<TSharedPtr<FJsonValue>> ItemsJsonArray;
    for (auto Item : PurchaseData)
    {
        TSharedRef<FJsonObject> ItemJson = MakeShareable(new FJsonObject());
        if (FJsonObjectConverter::UStructToJsonObject(FVerifyPurchaseIosData::StaticStruct(), &Item, ItemJson, 0, 0))
        {
            ItemsJsonArray.Push(MakeShareable(new FJsonValueObject(ItemJson)));
        }
    }

    FString ContentString;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&ContentString);
    FJsonSerializer::Serialize(ItemsJsonArray, Writer);
    
    const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
    FEndPoints Endpoint = LootLockerGameEndpoints::IOSPurchaseEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    HttpClient->SendApi(Endpoint.endpoint, requestMethod, ContentString, sessionResponse, true);
}

void UPurchasesRequestHandler::PollingOrderStatus(int PurchaseId, const FPurchaseStatusResponseDelegateBP& OnCompletedRequestBP, const FPurchaseStatusResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FPurchaseStatusResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FPurchaseStatusResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("PollPurchaseStatus failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
    FEndPoints Endpoint = LootLockerGameEndpoints::PollingOrderStatusEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { PurchaseId });
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}

void UPurchasesRequestHandler::ActivateRentalAsset(int AssetId, const FActivateRentalAssetResponseDelegateBP& OnCompletedRequestBP, const FActivateRentalAssetResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FActivateRentalAssetResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FActivateRentalAssetResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("ActivateRentalAsset failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
    FEndPoints Endpoint = LootLockerGameEndpoints::ActivateRentalAssetEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { AssetId });
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}
