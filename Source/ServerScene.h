#pragma once
#include "MyLibrary/Scene.h"
#include <vector>

class Server;

class ServerScene : public Scene
{
public:
	ServerScene();
	~ServerScene() override;
	void Update() override;

private:
	Server* server_;

	std::vector<int> useNumber;
};