// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "IWebSocket.h"
#include "MyTestGameInstance.generated.h"


/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWebSocketMessageDelegate, const FString&, Nessage);

UCLASS(Blueprintable)
class TESTPROJECT_API UMyTestGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	
	virtual void Init() override;
	
	virtual void Shutdown() override;

	
public:

	TSharedPtr<IWebSocket> WebSocket;
	
	UPROPERTY(BlueprintAssignable)
	FWebSocketMessageDelegate OnMessageRecieved;

	UFUNCTION(BlueprintCallable)
	void Send_WS_Message (const FString Message);

	UFUNCTION(BlueprintCallable)
	void CreateSocket(const FString URL);

	UFUNCTION(BlueprintCallable)
	void ConnectToWS();

	UFUNCTION(BlueprintPure)
	bool IsConnected();
	
	UFUNCTION(BlueprintCallable)
	void SendMessage(FString Message);
};


