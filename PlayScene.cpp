#include "PlayScene.h"
#include "Player.h"
#include "PlayerBullet.h"
#include "Enemy.h"
#include "Plane.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/GameTime.h"
#include <vector>

PlayScene::PlayScene(GameObject* parent) : GameObject(parent, "PlayScene")
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
	GameTime::Initialize();
	Instantiate<Player>(this);
	Instantiate<Plane>(this);
	// 敵を複数配置　座標も入れる
	for (int i = 0; i < 5; i++)
	{
		Enemy* enemy = Instantiate<Enemy>(this);
		enemy->SetPosition(-10.0f + i * 5.0f, 0.0f, 45.0f);
		enemies.push_back(enemy);
	}
}

void PlayScene::Update()
{
	GameTime::Update();
	// スペースキーでシーン遷移
	if (Input::IsKeyDown(DIK_SPACE))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_CLEAR);
	}
	
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}