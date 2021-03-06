// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerConfig.h"
#include "JsonObjectConverter.h"
#include "LootLockerHttpClient.h"
#include "LootLockerAssetInstancesRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FLootLockerAssetInstanceStorageItem {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString key;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString value;
};

USTRUCT(BlueprintType)
struct FLootLockerAssetInstanceStorageResponseItem : public FLootLockerAssetInstanceStorageItem {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int id;
};

USTRUCT(BlueprintType)
struct FLootLockerAssetInstanceStorageItems {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerAssetInstanceStorageItem> storage;
};

USTRUCT(BlueprintType)
struct FLootLockerAssetInstanceStorageItemsResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerAssetInstanceStorageResponseItem> storage;
};

USTRUCT(BlueprintType)
struct FLootLockerLootBoxItem {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int asset_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int asset_variation_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int asset_rental_option_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int weight;
};

USTRUCT(BlueprintType)
struct FLootLockerLootBoxContentResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerLootBoxItem> contents;
};

USTRUCT(BlueprintType)
struct FLootLockerOpenLootBoxResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool check_grant_notifications;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FAssetInstanceStorageItemsResponseDelegateBP, FLootLockerAssetInstanceStorageItemsResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootBoxContentResponseDelegateBP, FLootLockerLootBoxContentResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOpenLootBoxResponseDelegateBP, FLootLockerOpenLootBoxResponse, Response);
DECLARE_DELEGATE_OneParam(FAssetInstanceStorageItemsResponseDelegate, FLootLockerAssetInstanceStorageItemsResponse);
DECLARE_DELEGATE_OneParam(FLootBoxContentResponseDelegate, FLootLockerLootBoxContentResponse);
DECLARE_DELEGATE_OneParam(FOpenLootBoxResponseDelegate, FLootLockerOpenLootBoxResponse);

UCLASS()
class LOOTLOCKERSDK_API ULootLockerAssetInstancesRequestHandler : public UObject
{
public:
    GENERATED_BODY()
    
    static void GetAllKeyValuePairsForAssetInstance(const FAssetInstanceStorageItemsResponseDelegateBP& OnCompletedRequestBP = FAssetInstanceStorageItemsResponseDelegateBP(), const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest = FAssetInstanceStorageItemsResponseDelegate());

    static void GetAllKeyValuePairsToAnInstanceForAssetInstance(int AssetInstanceId, const FAssetInstanceStorageItemsResponseDelegateBP& OnCompletedRequestBP = FAssetInstanceStorageItemsResponseDelegateBP(), const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest = FAssetInstanceStorageItemsResponseDelegate());
    
    static void GetAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegateBP& OnCompletedRequestBP = FAssetInstanceStorageItemsResponseDelegateBP(), const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest = FAssetInstanceStorageItemsResponseDelegate());
    
    static void CreateAKeyValuePairForAssetInstance(int AssetInstanceId, const FLootLockerAssetInstanceStorageItem& Item, const FAssetInstanceStorageItemsResponseDelegateBP& OnCompletedRequestBP = FAssetInstanceStorageItemsResponseDelegateBP(), const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest = FAssetInstanceStorageItemsResponseDelegate());
    
    static void UpdateOneOrMoreKeyValuePairForAssetInstance(int AssetInstanceId, const TArray<FLootLockerAssetInstanceStorageItem>& Items, const FAssetInstanceStorageItemsResponseDelegateBP& OnCompletedRequestBP = FAssetInstanceStorageItemsResponseDelegateBP(), const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest = FAssetInstanceStorageItemsResponseDelegate());
    
    static void UpdateAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FLootLockerAssetInstanceStorageItem Item, const FAssetInstanceStorageItemsResponseDelegateBP& OnCompletedRequestBP = FAssetInstanceStorageItemsResponseDelegateBP(), const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest = FAssetInstanceStorageItemsResponseDelegate());
    
    static void DeleteAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegateBP& OnCompletedRequestBP = FAssetInstanceStorageItemsResponseDelegateBP(), const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest = FAssetInstanceStorageItemsResponseDelegate());
    
    static void InspectLootBox(int AssetInstanceId, const FLootBoxContentResponseDelegateBP& OnCompletedRequestBP = FLootBoxContentResponseDelegateBP(), const FLootBoxContentResponseDelegate& OnCompletedRequest = FLootBoxContentResponseDelegate());
    
    static void OpenLootBox(int AssetInstanceId, const FOpenLootBoxResponseDelegateBP& OnCompletedRequestBP = FOpenLootBoxResponseDelegateBP(), const FOpenLootBoxResponseDelegate& OnCompletedRequest = FOpenLootBoxResponseDelegate());
    
public:
    ULootLockerAssetInstancesRequestHandler();

    static ULootLockerHttpClient* HttpClient;
};
