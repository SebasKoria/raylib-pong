#pragma once

#include "raylib.h"
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <functional>

class GameObject : public std::enable_shared_from_this<GameObject>
{
private:
	std::function<void(std::shared_ptr<GameObject>)> mOnCompleteCallback;
protected:
	GameObject(Vector2 position);
	Vector2 mPosition;
	Vector2 mPivot;
	std::vector<std::shared_ptr<GameObject>> mChildren;
	std::shared_ptr<GameObject> mParent;
public:
	virtual void Draw();
	virtual void Update();
	void AddChild(std::shared_ptr<GameObject> pChild);
	void RemoveChild(std::shared_ptr<GameObject> pChild);
	void SetParent(std::shared_ptr<GameObject> pParent);
	void SetPivot(Vector2 pivot);
	void SetOnCompleteCallback(std::function<void(std::shared_ptr<GameObject>)> onCompleteCallback);

	template <typename T, typename... Args>
	static std::shared_ptr<T> Create(Args&&... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
	void Destroy();
};
