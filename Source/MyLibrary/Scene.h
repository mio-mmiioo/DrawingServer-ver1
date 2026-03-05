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

// 各シーンを制作するときの親クラス
class Scene
{
public:
	Scene() {};
	virtual ~Scene() {};
	virtual void Update() {};
	virtual void Draw() {};
};
