#include "ClearScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/Model.h"

ClearScene::ClearScene(GameObject* parent) : GameObject(parent, "ClearScene"), clearPict_(-1)
{
}

ClearScene::~ClearScene()
{
}

void ClearScene::Initialize()
{
	clearPict_ = Model::Load("clear.fbx");
	assert(clearPict_ >= 0);
}

void ClearScene::Update()
{
	// スペースキーでシーン遷移
	if (Input::IsKeyDown(DIK_SPACE))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}
}

void ClearScene::Draw()
{
	Transform clearTransform;
	clearTransform.position_ = { 0.0f, 0.0f, 0.0f };
	clearTransform.scale_ = { 1.0f, 1.0f, 1.0f };
	clearTransform.rotate_ = { 10.0f, 5.0f, 0.0f };
	Model::SetTransform(clearPict_, clearTransform);
	Model::Draw(clearPict_);
}

void ClearScene::Release()
{
}
