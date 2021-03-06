// Copyright 2019 ayumax. All Rights Reserved.
#include "TextureUtil.h"
#include "Engine/Texture2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "UnrealClient.h"

UTextureUtil::UTextureUtil()
{
}

UTextureUtil::~UTextureUtil()
{
}

UTexture2D* UTextureUtil::CreateTexture(int32 Width, int32 Height)
{
	auto Texture = UTexture2D::CreateTransient(Width, Height, PF_B8G8R8A8);
	Texture->UpdateResource();

	return Texture;
}

void UTextureUtil::UpdateTexture(UTexture2D* Texture, const TArray<uint8>& PixelsBuffer)
{
	auto Region = new FUpdateTextureRegion2D(0, 0, 0, 0, Texture->GetSizeX(), Texture->GetSizeY());
	Texture->UpdateTextureRegions(0, 1, Region, 4 * Texture->GetSizeX(), 4, (uint8*)PixelsBuffer.GetData());
}

void UTextureUtil::GetPixelBufferFromRenderTarget(UTextureRenderTarget2D* TextureRenderTarget, TArray<uint8>& Buffer)
{
	TArray<FColor> SurfData;
	FRenderTarget* RenderTarget = TextureRenderTarget->GameThread_GetRenderTargetResource();
	RenderTarget->ReadPixels(SurfData);
	
	FMemory::Memcpy(Buffer.GetData(), SurfData.GetData(), Buffer.Num());
}

