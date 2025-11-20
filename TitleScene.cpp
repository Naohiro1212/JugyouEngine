#include "TitleScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

TitleScene::TitleScene(GameObject* parent) : GameObject(parent, "TitleScene"), titlePict_(-1)
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	titlePict_ = Model::Load("title.fbx");
	assert(titlePict_ >= 0);
}

void TitleScene::Update()
{
	if (Input::IsKeyDown(DIK_SPACE))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
}

void TitleScene::Draw()
{
	Transform titleTransform;
	titleTransform.position_ = { 0.0f, 0.0f, 0.0f };
	titleTransform.scale_ = { 1.0f, 1.0f, 1.0f };
	titleTransform.rotate_ = { 10.0f, 5.0f, 0.0f };
	Model::SetTransform(titlePict_, titleTransform);
	Model::Draw(titlePict_);
}

void TitleScene::Release()
{
}
