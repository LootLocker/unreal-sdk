// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HttpModule.h"
#include "LootLockerConfig.generated.h"

USTRUCT(BlueprintType)
struct FLootLockerResponse
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	bool success;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	bool ServerCallHasError;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	int ServerCallStatusCode;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString FullTextFromServer;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString ServerError;
};

UENUM(BlueprintType)
enum class ELootLockerHTTPMethod : uint8
{
	GET = 0         UMETA(DisplayName = "GET"),
	POST = 1        UMETA(DisplayName = "POST"),
	DELETE = 2      UMETA(DisplayName = "DELETE"),
	PUT = 3         UMETA(DisplayName = "PUT"),
	HEAD = 4        UMETA(DisplayName = "HEAD"),
	CREATE = 5      UMETA(DisplayName = "CREATE"),
	OPTIONS = 6     UMETA(DisplayName = "OPTIONS"),
	PATCH = 7       UMETA(DisplayName = "PATCH"),
	UPLOAD = 8      UMETA(DisplayName = "UPLOAD")
};

UENUM(BlueprintType)
enum class ELootLockerPlatformType : uint8
{
	Android = 0				UMETA(DisplayName = "Android"),
	Ios = 1					UMETA(DisplayName = "Ios"),
	Steam = 2				UMETA(DisplayName = "Steam"),
	NintendoSwitch = 3		UMETA(DisplayName = "NintendoSwitch"),
	EpicStore = 3			UMETA(DisplayName = "EpicStore"),
	PlayStationNetwork = 3  UMETA(DisplayName = "PlayStationNetwork"),
	Xbox = 3				UMETA(DisplayName = "Xbox"),
	GoG = 3					UMETA(DisplayName = "GoG")
};

USTRUCT(BlueprintType)
struct FLootLockerEndPoints
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString endpoint;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	ELootLockerHTTPMethod requestMethod;
};

USTRUCT(BlueprintType)
struct FLootLockerGetRequests
{
	GENERATED_BODY()
	TArray<FStringFormatArg> args;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FResponseCallbackBP, FLootLockerResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerResponseCallback, FLootLockerResponse, Response);
DECLARE_DELEGATE_OneParam(FResponseCallback, FLootLockerResponse);

UCLASS(Config = LootLockerSDK)
class LOOTLOCKERSDK_API ULootLockerConfig : public UObject
{
	GENERATED_BODY()
public:
	static FString GetEnum(const TCHAR* Enum, int32 EnumValue);
    static inline FString GetRequestMethodString(ELootLockerHTTPMethod RequestMethod)
    {
        return GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(RequestMethod));
    }
public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString LootLockerGameKey;
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	ELootLockerPlatformType Platform;
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString GameVersion;
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	bool OnDevelopmentMode;
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	bool AllowTokenRefresh;

};
