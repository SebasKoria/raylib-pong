#pragma once
#include "paddle.h"

class CpuPaddle : public Paddle
{
private:
	int mBallYPosition;
	float mBallXDirection;
public:
	CpuPaddle(float width, float height, int speed, Color color, std::shared_ptr<TextPro> scoreLabel, Vector2 position)
		: Paddle(width, height, speed, color, scoreLabel, position)
	{
		mBallYPosition = 0;
		mBallXDirection = 0;
	}

	void Update() override
	{
		// some AI (really?) stuff
		if (mBallXDirection < 0)
		{
			if (mBallYPosition < mPosition.y + mHeight / 2) mPosition.y -= std::min(mSpeed, (int)(mPosition.y + mHeight / 2) - mBallYPosition);
			else mPosition.y += std::min(mSpeed, mBallYPosition - (int)(mPosition.y + mHeight / 2));
		}
		else {
			if (mPosition.y + mHeight / 2 < GetScreenHeight() / 2) mPosition.y += std::min(mSpeed, GetScreenHeight() / 2 - (int)(mPosition.y + mHeight / 2));
			else mPosition.y -= std::min(mSpeed, (int)(mPosition.y + mHeight / 2) - GetScreenHeight() / 2);
		}

		CheckLimits();
	}

	void SetBallYPosition(int yPosition) { mBallYPosition = yPosition; }
	void SetBallXDirection(float xDirection) { mBallXDirection = xDirection; }
};
