#pragma once
#include "DxLib.h"
#include <string>

class Scene;

namespace SceneMaster
{
	void CreateFirst();
	void ChangeScene(const std::string& name);
	void Init();
	void Update();
	void Draw();
	void Release();
}

class Scene
{
public:
	Scene() {};
	virtual ~Scene() {};
	virtual void Update() {};
	virtual void Draw() {};
};
