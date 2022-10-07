#pragma once

#include <gdp/Engine.h>
#include <string>
#include "source/vector3.h"

using namespace gdp; 

#define UP		1
#define DOWN	2
#define RIGHT	3
#define LEFT	4
#define MaxPos	20
#define MinPos	-20
#define KEY_UP			'i'
#define KEY_DOWN		'k'
#define KEY_LEFT		'j'
#define KEY_RIGHT		'l'
#define KEY_SPACEBAR	0x20
#define BASE_VELOCITY	3


class ArtilleryGame {
public:
	ArtilleryGame();
	~ArtilleryGame();

	void Initialize();
	void Destroy();

	void StartNewGame();
	void GameUpdate();
	void DisplayTextToUser(const std::string& text);

	void Move(int Dir);
	void SetProjectileType(int type);
	void SetFireDirection(vector3 Direction);
	void fire();
	glm::quat RotationCal(float degree);
	glm::quat RotationCal(vector3 Direction);
	bool HitCheck();

private:
	GameObject* CreateGameObjectByType(const std::string& type);

	GameObject* m_PlayerTank;
	GameObject* m_EnemyTank;
	GameObject* m_Bullet;
};