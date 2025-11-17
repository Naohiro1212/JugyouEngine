#include "Plane.h"
#include "Engine/Model.h"

Plane::Plane(GameObject* parent)
	:GameObject(parent, "Plane"), planeModel_(-1)
{
}

Plane::~Plane()
{
}

void Plane::Initialize()
{
	planeModel_ = Model::Load("Stage_t.fbx");
	assert(planeModel_ >= 0);
	transform_.scale_ = { 1.0f, 1.0f, 1.0f };
	transform_.position_ = { 0.0f, 0.0f, 0.0f };
}

void Plane::Update()
{
}

void Plane::Draw()
{
	Model::SetTransform(planeModel_, transform_);
	Model::Draw(planeModel_);
}

void Plane::Release()
{
}
