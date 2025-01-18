#pragma once

#include "gameobject.h"
#include <iostream>

class Rectangle2D : public GameObject
{
private:
	int mWidth;
	int mHeight;
	Color mColor;
public:

	Rectangle2D(int width, int height, Color color, Vector2 position)
		: mWidth(width)
		, mHeight(height)
		, mColor(color)
		, GameObject(position)
	{

	}

	void Draw() override
	{
		Vector2 relative_position;
		relative_position.x = mPosition.x - mWidth * mPivot.x;
		relative_position.y = mPosition.y - mHeight * mPivot.y;

		DrawRectangle(relative_position.x, relative_position.y, mWidth, mHeight, mColor);
		GameObject::Draw();
	}

	void Update() override
	{
		GameObject::Update();
	}
};
