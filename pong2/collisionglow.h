#pragma once
#include "gameobject.h"
#include "raytween.h"

class CollisionGlow : public GameObject
{
private:
	float mMagnitude;
	int mRadius;
	int mTransparency;
public:
	CollisionGlow(float magnitude, Vector2 position)
		: mMagnitude(magnitude)
		, GameObject(position)
	{
		mRadius = 0;
		mTransparency = 255;

		Raytween::Value(255, 0, mMagnitude, EASE_IN_CUBIC)
			->SetOnUpdate([this](float value) 
				{
					mTransparency = (int)value;
					mRadius += 5;
				})
			->SetOnComplete([this]()
				{
					Destroy();
				});
	}

	void Draw() override
	{
		// DrawCircleLinesV(mPosition, mRadius, Color{ 255, 255, 255, (unsigned char)mTransparency });
		DrawPolyLinesEx(mPosition, 100, mRadius, 0, 4, Color{ 255, 255, 255, (unsigned char)mTransparency });
	}

	void Update() override
	{

	}
};
