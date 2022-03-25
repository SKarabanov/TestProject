// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTestGameInstance.h"
#include "WebSocketsModule.h"



void UMyTestGameInstance::Init()
{
	Super::Init();
	
}

void UMyTestGameInstance::Shutdown()
{
	Super::Shutdown();

	if (WebSocket->IsConnected())
	{
		WebSocket->Close();
	}
	
}

void UMyTestGameInstance::Send_WS_Message(const FString Message)
{
	WebSocket->Send(Message);
}

bool UMyTestGameInstance::IsConnected()
{
	return WebSocket->IsConnected();
}

void UMyTestGameInstance::SendMessage(FString Message)
{
}

void UMyTestGameInstance::CreateSocket(const FString URL)
{
	if (!FModuleManager::Get().IsModuleLoaded("WebSockets"))
	{
		FModuleManager::Get().LoadModule("WebSockets");
	};
	
	WebSocket=FWebSocketsModule::Get().CreateWebSocket(URL);
}


void UMyTestGameInstance::ConnectToWS()
{
	WebSocket->OnConnected().AddLambda([]()
	{
		GEngine->AddOnScreenDebugMessage(-1,15.0f,FColor::Green,"Successfully Connected");
	});

	WebSocket->OnConnectionError().AddLambda([](const FString& Error)
	{
		GEngine->AddOnScreenDebugMessage(-1,150.0f,FColor::Red,Error);
	});

	WebSocket->OnClosed().AddLambda([](int32 StatusCode, const FString& Reason, bool WasClean)
	{
		GEngine->AddOnScreenDebugMessage(-1,150.0f,WasClean ?FColor::Green : FColor::Red ,"Connection Closed: "+Reason);
	});

	WebSocket->OnMessage().AddLambda([&](FString MessageString)
{
	GEngine->AddOnScreenDebugMessage(-1,150.0f,FColor::Cyan,"Received message: "+MessageString);
		OnMessageRecieved.Broadcast(MessageString);
});

	WebSocket->OnMessageSent().AddLambda([](const FString& MessageString)
{
	GEngine->AddOnScreenDebugMessage(-1,150.0f,FColor::Yellow,"Sent message: "+MessageString);
		//OnMessageRecieved.Broadcast(MessageString);
});

	WebSocket->Connect();
}