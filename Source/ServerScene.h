#pragma once
#include "MyLibrary/Scene.h"

class Server;

class ServerScene : public Scene
{
public:
	ServerScene();
	~ServerScene() override;
	void Update() override;

private:
	enum STATE
	{
		MAKE_ROOM,		// •”‰®‚ğì‚é
		MAKE_NAME,		// –¼‘O‚ğŠm”F‚·‚é
		WAIT_ANSWER,	// “š‚¦‚ğ‘Ò‚Â
		SEND_ANSWER,	// “š‚¦‚ğ‘—‚é
		MAX_STATE,
	};

	Server* server_;
	STATE state_;

};