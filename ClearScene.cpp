#include "ClearScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

ClearScene::ClearScene(GameObject* parent) : GameObject(parent, "ClearScene")
{
}

ClearScene::~ClearScene()
{
}

void ClearScene::Initialize()
{
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
}

void ClearScene::Release()
{
}
