#include "ChildOden.h"
#include "Engine/Fbx.h"

ChildOden::ChildOden(GameObject* parent)
	:GameObject(parent, "ChildOden"), pFbx_(nullptr)
{
}

ChildOden::~ChildOden()
{
}

void ChildOden::Initialize()
{
	pFbx_ = new Fbx;
	pFbx_->Load("oden.fbx");
	transform_.scale_ = { 0.3f, 0.3f, 0.3f };
}

void ChildOden::Update()
{
	transform_.rotate_.y += 1.0f;
}

void ChildOden::Draw()
{
	if(pFbx_)
	{
		pFbx_->Draw(transform_);
	}
}

void ChildOden::Release()
{
	if (pFbx_)
	{
		pFbx_->Release();
		delete pFbx_;
		pFbx_ = nullptr;
	}
}
