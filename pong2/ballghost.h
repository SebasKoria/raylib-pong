#pragma once
#include "gameobject.h"
#include "raytween.h"

class BallGhost : public GameObject
{
private:
	int mRadius;
	int mTransparency;
	float mLifetime;
	Color mColor;
public:
	BallGhost(int radius, float lifetime, Color color, Vector2 position)
		: mRadius(radius)
		, mLifetime(lifetime)
		, mColor(color)
		, GameObject(position)
	{
		mTransparency = mColor.a;

		Raytween::Value(mTransparency, 0, mLifetime, EASE_LINEAR)
			->SetOnUpdate([this](float value)
				{
					mTransparency = value;
				})
			->SetOnComplete([this]()
				{
					Destroy();
				});
	}

	void Draw() override
	{
		mColor.a = mTransparency;
		DrawCircle(mPosition.x, mPosition.y, mRadius, mColor);
	}

	void Update() override
	{

	}
};
