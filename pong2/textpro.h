#pragma once
#include "gameobject.h"
#include "raytween.h"

class TextPro : public GameObject
{
private:
	std::string mText;
	int mFontSize;
	int mTransparency;
	Color mColor;
public:
	TextPro(int fontSize, Color color, Vector2 position)
		: mFontSize(fontSize)
		, mColor(color)
		, GameObject(position)
	{
		mText = "";
		mTransparency = mColor.a;
	}

	void Draw() override
	{
		Vector2 relativePos;
		Vector2 textMeasure = MeasureTextEx(GetFontDefault(), mText.c_str(), mFontSize, 0);

		relativePos.x = mPosition.x - textMeasure.x * mPivot.x;
		relativePos.y = mPosition.y - textMeasure.y * mPivot.y;

		mColor.a = mTransparency;
		DrawText(mText.c_str(), relativePos.x, relativePos.y, mFontSize, mColor);
	}

	void Update() override
	{

	}

	void SetText(std::string text) { mText = text; }

	void PopAnimation()
	{
		Raytween::Value(mFontSize, mFontSize + 100, 0.15, EASE_OUT_CUBIC)
			->SetOnUpdate([this](float value)
				{
					mFontSize = value;
				})
			->SetOnComplete([this]()
				{
					Raytween::Value(mFontSize, mFontSize - 100, 0.15, EASE_IN_CUBIC)
						->SetOnUpdate([this](float value)
							{
								mFontSize = value;
							});
				});
		Raytween::Value(mTransparency, mTransparency + 100, 0.15, EASE_OUT_CUBIC)
			->SetOnUpdate([this](float value)
				{
					mTransparency = value;
				})
			->SetOnComplete([this]()
				{
					Raytween::Value(mTransparency, mTransparency - 100, 0.15, EASE_IN_CUBIC)
						->SetOnUpdate([this](float value)
							{
								mTransparency = value;
							});
				});
	}
};
