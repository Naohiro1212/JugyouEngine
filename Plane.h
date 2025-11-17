#pragma once
#include "Engine/GameObject.h"

class Plane : public GameObject
{
public:
	Plane(GameObject* parent);
	~Plane();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

private:
	int planeModel_;
};