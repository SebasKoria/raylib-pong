#pragma once
#include "gameobject.h"
#include "textpro.h"

class Paddle : public GameObject
{
protected:
	float mWidth;
	float mHeight;
	int mSpeed;
	int mScore;
	Color mColor;
	std::shared_ptr<TextPro> mScoreLabel;
public:
	Paddle(float width, float height, int speed, Color color, std::shared_ptr<TextPro> scoreLabel, Vector2 position)
		: mWidth(width)
		, mHeight(height)
		, mSpeed(speed)
		, mColor(color)
		, mScoreLabel(scoreLabel)
		, GameObject(position)
	{
		mScore = 0;
	}

	void Draw() override
	{
		DrawRectangleRounded(Rectangle{ mPosition.x, mPosition.y, mWidth, mHeight }, 0.8, 2, mColor);
	}

	virtual void Update() override
	{
		if (IsKeyDown(KEY_UP))
		{
			mPosition.y -= mSpeed;
		}
		if (IsKeyDown(KEY_DOWN))
		{
			mPosition.y += mSpeed;
		}

		CheckLimits();
	}

	void CheckLimits() {
		if (mPosition.y + mHeight > GetScreenHeight())
		{
			mPosition.y = GetScreenHeight() - mHeight;
		}
		if (mPosition.y < 0)
		{
			mPosition.y = 0;
		}
	}

	Rectangle GetRectangle()
	{
		return Rectangle{ mPosition.x, mPosition.y, mWidth, mHeight };
	}

	void IncreaseScore()
	{
		mScoreLabel->SetText(TextFormat("%i", ++mScore)); 
		mScoreLabel->PopAnimation();
	}
	int GetScore() { return mScore; }
};
