// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProjectEXInteractionPromptWidget.generated.h"

class UTextBlock;

/**
 *  Centered interaction prompt. Built in C++ so it shows without a widget Blueprint.
 *  Assign a Blueprint subclass on the interaction component to restyle it later.
 */
UCLASS()
class PROJECTEX_API UProjectEXInteractionPromptWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetPromptText(const FText& InPromptText);

protected:

	virtual TSharedRef<SWidget> RebuildWidget() override;

private:

	void BuildLayout();

	UPROPERTY(Transient)
	TObjectPtr<UTextBlock> PromptTextBlock;

	FText PromptText;
};
