#include "gameobject.h"

GameObject::GameObject(Vector2 position)
	: mPosition(position)
{
	mPivot = { 0, 0 };
	mOnCompleteCallback = [](std::shared_ptr<GameObject> pointer){};
}

void GameObject::Draw() 
{
	for (auto pChild : mChildren)
	{
		pChild->Draw();
	}
}

void GameObject::Update()
{
	for (auto pChild : mChildren)
	{
		pChild->Update();
	}
}

void GameObject::AddChild(std::shared_ptr<GameObject> pChild) 
{
	mChildren.push_back(pChild);
}

void GameObject::RemoveChild(std::shared_ptr<GameObject> pChild)
{
	mChildren.erase(std::remove_if(mChildren.begin(), mChildren.end(), [pChild](std::shared_ptr<GameObject> pointer) {
		return pointer == pChild;
		}));
}

void GameObject::SetParent(std::shared_ptr<GameObject> pParent) 
{
	mParent = pParent;
	pParent->AddChild(shared_from_this());
}
void GameObject::SetPivot(Vector2 pivot) { mPivot = pivot; }
void GameObject::SetOnCompleteCallback(std::function<void(std::shared_ptr<GameObject>)> onCompleteCallback) { mOnCompleteCallback = onCompleteCallback; }

void GameObject::Destroy()
{
	mOnCompleteCallback(shared_from_this());
}