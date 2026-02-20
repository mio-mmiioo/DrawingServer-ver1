#include "Scene.h"

// 各シーン
#include "../ServerScene.h"

namespace SceneMaster
{
	Scene* current;
}

void SceneMaster::CreateFirst()
{
	current = new ServerScene();
}

void SceneMaster::ChangeScene(const std::string& name)
{
	Scene* prev = current;
	if (name == "SERVER")
	{
		current = new ServerScene();
	}
	else
	{
		// シーンが切り替わらない
	}
	prev->~Scene();
}

void SceneMaster::Init()
{
	CreateFirst();
}

void SceneMaster::Update()
{
	current->Update();
}

void SceneMaster::Draw()
{
	current->Draw();
}

void SceneMaster::Release()
{
	current->~Scene();
}

