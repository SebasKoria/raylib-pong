#pragma once
#include "gameobject.h"
#include "paddle.h"
#include "cpuPaddle.h"
#include "collisionglow.h"
#include "ballghost.h"
#include <raymath.h>
#include <math.h>

Color Yellow = Color{ 243, 213, 91, 255 };
Color Dark_Yellow = Color{ 194, 145, 54, 255 };

class Ball : public GameObject
{
private:
	int mRadius;
	float mStartSpeed;
	float mSpeedLimit;
	float mCurrentSpeed;
	float mAngle;
	float mGhostTimer;
	float mCreateGhostInterval;
	Vector2 mDirection;
	Color mColor;
	std::shared_ptr<Paddle> mPaddle;
	std::shared_ptr<CpuPaddle> mCpuPaddle;
public:
	Ball(int radius, float startSpeed, float speedLimit, Color color, std::shared_ptr<Paddle> paddle, std::shared_ptr<CpuPaddle> cpuPaddle, Vector2 position)
		: mRadius(radius)
		, mStartSpeed(startSpeed)
		, mSpeedLimit(speedLimit)
		, mColor(color)
		, mPaddle(paddle)
		, mCpuPaddle(cpuPaddle)
		, GameObject(position)
	{
		mGhostTimer = 0;
		mCreateGhostInterval = 0.1;

		ShootInRandomDirection();
	}

	void Draw() override
	{
		GameObject::Draw();
		DrawCircle(mPosition.x, mPosition.y, mRadius, mColor);
	}

	void Update() override
	{
		mDirection.x = cosf(mAngle);
		mDirection.y = sinf(mAngle);

		mPosition.x += mDirection.x * mCurrentSpeed;
		mPosition.y += mDirection.y * mCurrentSpeed;

		CheckCollisionWithPaddle(mPaddle);
		CheckCollisionWithPaddle(mCpuPaddle);

		CheckBoundaries();

		mCpuPaddle->SetBallYPosition(mPosition.y);
		mCpuPaddle->SetBallXDirection(mDirection.x);

		mGhostTimer += GetFrameTime();
		if (mGhostTimer >= mCreateGhostInterval)
		{
			CreateGhost();
			mGhostTimer = fmod(mGhostTimer, mCreateGhostInterval);
		}

		GameObject::Update();
	}

	void ShootInRandomDirection() {
		mPosition = Vector2{ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
		mCurrentSpeed = mStartSpeed;

		mAngle = ((GetRandomValue(550, 706) - (GetRandomValue(0, 1) == 0 ? 314 : 0)) % 628) / 100.0;
	}

	void CheckBoundaries()
	{
		if (mPosition.y + mRadius > GetScreenHeight())
		{
			mPosition.y = GetScreenHeight() - mRadius;
			mAngle = 2 * acosf(-1) - mAngle;
			CreateGlow();
		}
		if (mPosition.y - mRadius < 0)
		{
			mPosition.y = mRadius;
			mAngle = 2 * acosf(-1) - mAngle;
			CreateGlow();
		}
		if (mPosition.x - mRadius > GetScreenWidth())
		{
			mCpuPaddle->IncreaseScore();
			ShootInRandomDirection();
		}
		if (mPosition.x + mRadius < 0)
		{
			mPaddle->IncreaseScore();
			ShootInRandomDirection();
		}
	}

	bool CheckCollisionWithPaddle(std::shared_ptr<Paddle> paddle)
	{
		Rectangle rec = paddle->GetRectangle();

		int top = rec.y;
		int bottom = rec.y + rec.height;
		int left = rec.x;
		int right = rec.x + rec.width;

		if (CheckCollisionCircleRec(mPosition, mRadius, rec))
		{
			if (mPosition.x < left) 
			{
				mAngle = fmodf(3 * acosf(-1) - mAngle, 2 * acosf(-1));
				mPosition.x = left - mRadius;

				if (mPosition.y <= top + rec.height * 0.25f) {
					mAngle = std::min(mAngle + 0.349066f, 3.92699f); // rotate angle 20 degrees counter-clockwise, clamp to 225 degrees
				}
				else if (mPosition.y >= bottom - rec.height * 0.25f)
				{
					mAngle = std::max(mAngle - 0.349066f, 2.35619f); // rotate angle 20 degrees clockwise, clamp to 135 degrees
				}
			}
			else if (mPosition.x > right)
			{
				mAngle = fmodf(3 * acosf(-1) - mAngle, 2 * acosf(-1));
				mPosition.x = right + mRadius;
			}
			else if (mPosition.y < top)
			{
				mAngle = fmodf(2 * acosf(-1) - mAngle, 2 * acosf(-1));
				mPosition.y = top - mRadius;
			}
			else if (mPosition.y > bottom)
			{
				mAngle = fmodf(2 * acosf(-1) - mAngle, 2 * acosf(-1));
				mPosition.y = bottom + mRadius;
			}

			mCurrentSpeed = std::min(mCurrentSpeed + 0.5f, mSpeedLimit);

			CreateGlow();
			return true;
		}
		return false;
	}

	void CreateGlow()
	{
		auto collisionGlow = GameObject::Create<CollisionGlow>(0.5, mPosition);
		collisionGlow->SetParent(shared_from_this());
		collisionGlow->SetOnCompleteCallback([this](std::shared_ptr<GameObject> pointer)
			{
				RemoveChild(pointer);
			});
	}

	void CreateGhost()
	{
		auto ghost = GameObject::Create<BallGhost>(mRadius - 5, 0.5f, Yellow, mPosition);
		ghost->SetParent(shared_from_this());
		ghost->SetOnCompleteCallback([this](auto pointer)
			{
				RemoveChild(pointer);
			});
	}
};
