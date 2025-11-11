#include "GameObject.h"
#include "SphereCollider.h"
#include <Windows.h>

GameObject::GameObject()
	:pParent_(nullptr)
{
}

GameObject::GameObject(GameObject* parent, const string& name)
	:pParent_(parent), objectName_(name), isDead_(false)
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

	RoundRobin(GetRootJob());
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

void GameObject::AddCollider(SphereCollider* pCollider)
{
	pCollider_ = pCollider;
}

void GameObject::Collision(GameObject* pTarget)
{
	// this->pColliderとpTarget->pColliderの当たり判定を行う
	// 閾値＝お互いの半径+半径
	float thisR = this->pCollider_->GetRadius();
	float tgtR = pTarget->pCollider_->GetRadius();
	float thre = (thisR + tgtR) * (thisR + tgtR); // 閾値の二乗
	// 1.2つのコライダーの距離計算
	XMFLOAT3 thisP = this->transform_.position_;
	XMFLOAT3 tgtP = pTarget->transform_.position_;
	float dist = (thisP.x - tgtP.x) * (thisP.x - tgtP.x) +
		         (thisP.y - tgtP.y) * (thisP.y - tgtP.y) +
				 (thisP.z - tgtP.z) * (thisP.z - tgtP.z);
	// 2.コライダー同士が交差していたら
	if (dist <= thre)
	{
		OnCollision(pTarget);
	}
}

void GameObject::RoundRobin(GameObject* pTarget)
{
	// 1.自分にコライダーが無かったらretrun 
	if (pCollider_ == nullptr)
	{
		return;
	}
	// 2.自分とターゲット自体のコライダーの当たり判定
	if (pTarget->pCollider_ == nullptr)
	{
		return;
	}
	Collision(pTarget);
	// 3.再帰的な奴でターゲットの子オブジェクトを当たり判定していく
	for (auto child : pTarget->childList_)
	{
		RoundRobin(child);
	}
}