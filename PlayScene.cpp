#include "PlayScene.h"
#include "Player.h"
#include "ChildOden.h"

PlayScene::PlayScene(GameObject* parent)
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
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}
