#include "PlayScene.h"
#include "Player.h"
#include "ChildOden.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

PlayScene::PlayScene(GameObject* parent) : GameObject(parent, "PlayScene")
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
	Instantiate<Player>(this);
}

void PlayScene::Update()
{
	// スペースキーでシーン遷移
	if (Input::IsKeyDown(DIK_SPACE))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TEST);
	}
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}
