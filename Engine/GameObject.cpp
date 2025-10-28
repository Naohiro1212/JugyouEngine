#include "GameObject.h"

GameObject::GameObject()
	:pParent_(nullptr)
{
}

GameObject::GameObject(GameObject* parent, const string& name)
	:pParent_(parent), objectName_(name)
{
	if (pParent_)
	{
		transform_.pParent_ = &(parent->transform_);
	}
}

GameObject::~GameObject()
{
}

void GameObject::DrawSub()
{
	//0. 自分を描画
	//1. 子オブジェクトを描画 childList_の各要素に対してDrawを呼ぶ
	this->Draw();
	for (auto child : childList_)
	{
		child->DrawSub();
	}
}

void GameObject::UpdateSub()
{
	transform_.Calculation();
	this->Update();
	for (auto child : childList_)
	{
		child->UpdateSub();
	}

	for (auto itr = childList_.begin(); itr != childList_.end(); )
	{
		if ((*itr)->isDead_)
		{
			(*itr)->ReleaseSub();
			delete (*itr);
			itr = childList_.erase(itr);
		}
		else
		{
			++itr;
		}
	}
}

void GameObject::ReleaseSub()
{
	this->Release();
	for (auto child : childList_)
	{
		child->ReleaseSub();
	}
}

void GameObject::SetPosition(XMFLOAT3 position)
{
	transform_.position_ = position;
}

void GameObject::SetPosition(float x, float y, float z)
{
	transform_.position_ = XMFLOAT3(x, y, z);
}

void GameObject::KillMe()
{
	isDead_ = true;
}

GameObject* GameObject::GetRootJob()
{
	if (pParent_ == nullptr)
	{
		return this;
	}
	else
	{
		return pParent_->GetRootJob();
	}
}

GameObject* GameObject::FindChildObject(const string& name)
{
	if (this->objectName_ == name)
	{
		return this; 
	}
	else
	{
		for (auto child : childList_)
		{
			GameObject* result = child->FindChildObject(name);
			if (result != nullptr)
			{
				return result;
			}
		}
		return nullptr;
	}
}

GameObject* GameObject::FindObject(const string& name)
{
	GameObject* rootJob = GetRootJob();
	GameObject* result = rootJob->FindChildObject(name);
	return result;
}
