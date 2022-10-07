#include "ArtilleryGame.h"
#include <iostream>			// cout
#include "AssetInfo.h"

#define DEBUG_LOG_ENABLED
#ifdef DEBUG_LOG_ENABLED
#define DEBUG_PRINT(x, ...) printf(x, __VA_ARGS__)
#else
#define DEBUG_PRINT(x)
#endif

// Ids preloaded in the main.cpp to be referenced when
// creating specific game objects for your game.
// - EnemyTank, PlayerTank, and Bullet
unsigned int TankModelId;
unsigned int ProjectileModelId;
unsigned int PlayerMaterialId;
unsigned int EnemyMaterialId;
unsigned int BulletMaterialId;

// TODO:
// #include "YourPhysicsClass.h"
#include "source/PhysicEngine.h"

PhysicEngine PlayerObj;
PhysicEngine EnemyObj;
PhysicEngine BulletObj;

/// <summary>
/// Default constructor
/// Set all class variables to the desired default state
/// </summary>
ArtilleryGame::ArtilleryGame()
	: m_PlayerTank(nullptr)
	, m_EnemyTank(nullptr)
	, m_Bullet(nullptr) 
{
	DEBUG_PRINT("ArtilleryGame::ArtilleryGame\n");
	// DO NOTHING!!!!!!!!
}

/// <summary>
/// Default destructor
/// </summary>
ArtilleryGame::~ArtilleryGame()
{
	DEBUG_PRINT("ArtilleryGame::~ArtilleryGame\n");
	// DO NOTHING!!!!!!!!
}
/// <summary>
/// Create everything needed for your game here
/// such as memory allocation calls
/// </summary>
void ArtilleryGame::Initialize()
{
	DEBUG_PRINT("ArtilleryGame::Initialize\n");
	// TODO:
	// - Create a Player Tank GameObject
	// - Create an Enemy Tank GameObject
	// - Create projectile(s)
	m_PlayerTank = CreateGameObjectByType("Player");
	m_EnemyTank = CreateGameObjectByType("Enemy");
	m_Bullet = CreateGameObjectByType("Bullet");

	m_PlayerTank->Position = glm::vec3(-10, 0, -10);
	m_EnemyTank->Position = glm::vec3(10, 0, 10);
	m_Bullet->Position = glm::vec3(10, 2, 0);

	StartNewGame();
}

/// <summary>
/// Handle everything that needs to be destroyed
/// such as memory de-allocation.
/// </summary>
void ArtilleryGame::Destroy()
{
	DEBUG_PRINT("ArtilleryGame::Destroy\n");
	// TODO:
}

/// <summary>
/// StartNewGame
/// 1. Randomly place the enemy tank at a random valid location 
///    on the map
/// 2. Randomly place the player tank at a random valid location
///    on the map
/// 3. Reset the bullet(s)
/// </summary>
void ArtilleryGame::StartNewGame()
{
	DEBUG_PRINT("ArtilleryGame::StartNewGame\n");
	// TODO:

	//PhysicEngine PlayerPos;
	//PhysicEngine EnemyPos;
	//PhysicEngine BulletPos;

	//random player and enemy tanks
	srand((unsigned)time(NULL));
	PlayerObj.RandPos();
	EnemyObj.RandPos();

	//reset bullet to player tank position
	BulletObj.Pos = PlayerObj.Pos;

	//draw
	m_PlayerTank->Position = glm::vec3(PlayerObj.Pos.get_X(), 0, PlayerObj.Pos.get_Z());
	m_EnemyTank->Position = glm::vec3(EnemyObj.Pos.get_X(), 0, EnemyObj.Pos.get_Z());
	m_Bullet->Position = glm::vec3(BulletObj.Pos.get_X(), 0, BulletObj.Pos.get_Z());
}

/// <summary>
/// Update all bullets here
/// - Call your Physics class to update all projectiles
/// Check for bullet collision (position.y <= 0, hit ground)
/// Check for User input:
/// >>> GDP_IsKeyPressed, GDP_IsKeyHeldDown <-- Case Sensitive
/// >>> example: if (GDP_IsKeyPressed('n') || GDP_IsKeyPressed('N'))
/// - Input for changing the bullet direction	(wasd, etc)
/// - Input to change the projectile type		(1,2,3,4,5)
/// - Input to fire a projectile				(space)
/// - Input to start a new game					(n)
/// </summary>
void ArtilleryGame::GameUpdate()
{
	//DEBUG_PRINT("ArtilleryGame::GameUpdate\n");
	// TODO:
	if (GDP_IsKeyReleased('n') || GDP_IsKeyReleased('N'))
	{
		StartNewGame();
		//DisplayTextToUser("test");
	}
	if (GDP_IsKeyPressed('w') || GDP_IsKeyPressed('W')) //||GDP_IsKeyHeldDown('w') || GDP_IsKeyHeldDown('W'))
	{
		Move(UP);
	}
	if (GDP_IsKeyPressed('a') || GDP_IsKeyPressed('A')) //|| GDP_IsKeyHeldDown('a') || GDP_IsKeyHeldDown('A'))
	{
		Move(LEFT);
	}
	if (GDP_IsKeyPressed('s') || GDP_IsKeyPressed('S')) //|| GDP_IsKeyHeldDown('s') || GDP_IsKeyHeldDown('S'))
	{
		Move(DOWN);
	}
	if (GDP_IsKeyPressed('d') || GDP_IsKeyPressed('D')) //|| GDP_IsKeyHeldDown('d') || GDP_IsKeyHeldDown('D'))
	{
		Move(RIGHT);
	}
	if (GDP_IsKeyPressed('1'))
	{
		SetProjectileType(1);
	}
	if (GDP_IsKeyPressed('2'))
	{
		SetProjectileType(2);
	}
	if (GDP_IsKeyPressed('3'))
	{
		SetProjectileType(3);
	}
	if (GDP_IsKeyPressed('4'))
	{
		SetProjectileType(4);
	}
	if (GDP_IsKeyPressed('5'))
	{
		SetProjectileType(5);
	}
	if (GDP_IsKeyPressed(KEY_DOWN))
	{
		SetFireDirection(vector3(0, 0, -1));
		m_PlayerTank->Rotation = RotationCal(PlayerObj.FireDirection);
		m_Bullet->Rotation = RotationCal(BulletObj.FireDirection);
	}
	if (GDP_IsKeyPressed(KEY_LEFT))
	{
		SetFireDirection(vector3(1, 0, 0));
		m_PlayerTank->Rotation = RotationCal(PlayerObj.FireDirection);
		m_Bullet->Rotation = RotationCal(BulletObj.FireDirection);
	}
	if (GDP_IsKeyPressed(KEY_UP))
	{
		SetFireDirection(vector3(0, 0, 1));
		m_PlayerTank->Rotation = RotationCal(PlayerObj.FireDirection);
		m_Bullet->Rotation = RotationCal(BulletObj.FireDirection);
	}
	if (GDP_IsKeyPressed(KEY_RIGHT))
	{
		SetFireDirection(vector3(-1, 0, 0));
		m_PlayerTank->Rotation = RotationCal(PlayerObj.FireDirection);
		m_Bullet->Rotation = RotationCal(BulletObj.FireDirection) + glm::quat();
	}
	if (GDP_IsKeyPressed(KEY_SPACEBAR))
	{
		fire();
	}
	if (BulletObj.isFire)
	{
		BulletObj.TrajectoryCal();
		m_Bullet->Position = glm::vec3(BulletObj.Pos.get_X(), BulletObj.Pos.get_Y(), BulletObj.Pos.get_Z());
	}
	else
	{
		BulletObj.Pos = PlayerObj.Pos;
		m_Bullet->Position = glm::vec3(BulletObj.Pos.get_X(), BulletObj.Pos.get_Y(), BulletObj.Pos.get_Z());
	}
	if (BulletObj.isHitGround)
	{
		if (HitCheck())
		{
			DisplayTextToUser("Hit!!");
			m_EnemyTank->Rotation = glm::quat(1, 0, 1, 0);
			DisplayTextToUser("Press \'n\' to restart a game");
		}
		else
		{
			DisplayTextToUser("Miss!! Hit a ground at");
			std::cout << "x:" << m_Bullet->Position.x << "\ny: " << m_Bullet->Position.y << "\nz: " << m_Bullet->Position.z<<"\n";
		}
		BulletObj.isHitGround = false;
	}
}

/// <summary>
/// Print provided text to the console for the user
/// </summary>
/// <param name="text"></param>
void ArtilleryGame::DisplayTextToUser(const std::string& text)
{
	std::cout << text << "\n";
}

void ArtilleryGame::Move(int Dir)
{

	switch (Dir)
	{
	case(UP):
		if (m_PlayerTank->Position.z < MaxPos)
		{
			PlayerObj.Pos += vector3(0, 0, 1);
			m_PlayerTank->Position = glm::vec3(PlayerObj.Pos.get_X(), 0, PlayerObj.Pos.get_Z());
			//m_PlayerTank->Rotation = glm::quat(0.7f, 0, 0.7f, 0);
			m_PlayerTank->Rotation = RotationCal(90);	
			PlayerObj.FireDirection = vector3(0,0,1);
			BulletObj.FireDirection = PlayerObj.FireDirection;
			if (!BulletObj.isFire)
			{
				BulletObj.Pos = PlayerObj.Pos;
				m_Bullet->Position = glm::vec3(BulletObj.Pos.get_X(), BulletObj.Pos.get_Y(), BulletObj.Pos.get_Z());
				//m_Bullet->Rotation = glm::quat(1, 0, 0, 0);
				m_Bullet->Rotation = RotationCal(90);
			}
		}
		break;
	case(DOWN):
		if (m_PlayerTank->Position.z > MinPos)
		{
			PlayerObj.Pos += vector3(0, 0, -1);
			m_PlayerTank->Position = glm::vec3(PlayerObj.Pos.get_X(), 0, PlayerObj.Pos.get_Z());
			//m_PlayerTank->Rotation = glm::quat(0.7f, 0, -0.7f, 0);
			m_PlayerTank->Rotation = RotationCal(270);
			PlayerObj.FireDirection = vector3(0, 0, -1);
			BulletObj.FireDirection = PlayerObj.FireDirection;
			if (!BulletObj.isFire)
			{
				BulletObj.Pos = PlayerObj.Pos;
				m_Bullet->Position = glm::vec3(BulletObj.Pos.get_X(), BulletObj.Pos.get_Y(), BulletObj.Pos.get_Z());
				//m_Bullet->Rotation = glm::quat(0, 0, 1, 0);
				m_Bullet->Rotation = RotationCal(270);
			}
		}
		break;
	case(LEFT):
		if (m_PlayerTank->Position.x < MaxPos)
		{
			PlayerObj.Pos += vector3(1, 0, 0);
			m_PlayerTank->Position = glm::vec3(PlayerObj.Pos.get_X(), 0, PlayerObj.Pos.get_Z());
			//m_PlayerTank->Rotation = glm::quat(0, 0, 1, 0);
			m_PlayerTank->Rotation = RotationCal(180);
			PlayerObj.FireDirection = vector3(1, 0, 0);
			BulletObj.FireDirection = PlayerObj.FireDirection;
			if (!BulletObj.isFire)
			{
				BulletObj.Pos = PlayerObj.Pos;
				m_Bullet->Position = glm::vec3(BulletObj.Pos.get_X(), BulletObj.Pos.get_Y(), BulletObj.Pos.get_Z());
				//m_Bullet->Rotation = glm::quat(0.7f, 0, 0.7f, 0);
				m_Bullet->Rotation = RotationCal(180);
			}
		}
		break;
	case(RIGHT):
		if (m_PlayerTank->Position.x > MinPos)
		{
			PlayerObj.Pos += vector3(-1, 0, 0);
			m_PlayerTank->Position = glm::vec3(PlayerObj.Pos.get_X(), 0, PlayerObj.Pos.get_Z());
			//m_PlayerTank->Rotation = glm::quat(1, 0, 0, 0);
			m_PlayerTank->Rotation = RotationCal(0);
			PlayerObj.FireDirection = vector3(-1, 0, 0);
			BulletObj.FireDirection = PlayerObj.FireDirection;
			if (!BulletObj.isFire)
			{
				BulletObj.Pos = PlayerObj.Pos;
				m_Bullet->Position = glm::vec3(BulletObj.Pos.get_X(), BulletObj.Pos.get_Y(), BulletObj.Pos.get_Z());
				//m_Bullet->Rotation = glm::quat(0.7f, 0, -0.7f, 0);
				m_Bullet->Rotation = RotationCal(0);
			}
		}
		break;
	default:
		break;
	}
}

void ArtilleryGame::SetProjectileType(int type)
{
	BulletObj.ProjectileType = (float) type;
	
}

void ArtilleryGame::SetFireDirection(vector3 Direction)
{
	PlayerObj.FireDirection += Direction;
	BulletObj.FireDirection = PlayerObj.FireDirection;
}

void ArtilleryGame::fire()
{
	//float Radian_XZ = glm::atan((BulletObj.FireDirection.get_Z()) / (BulletObj.FireDirection.get_X()));
	//float V_X = BulletObj.ProjectileType * BASE_VELOCITY * sin(Radian_XZ);
	//float V_Z = BulletObj.ProjectileType * BASE_VELOCITY * cos(Radian_XZ);
	BulletObj.isFire = true;
	BulletObj.Velocity.set_Y(BulletObj.ProjectileType * BASE_VELOCITY);
	//BulletObj.Velocity = vector3(V_X,BulletObj.ProjectileType * BASE_VELOCITY,V_Z);
	//BulletObj.Pos.set_Y(1);
}

glm::quat ArtilleryGame::RotationCal(float degree)
{
	float radians = glm::radians(degree);
	float w = cos(radians /2);
	float y = sin(radians / 2);
	return glm::quat(w, 0, y, 0);
}

glm::quat ArtilleryGame::RotationCal(vector3 Direction)
{
	float radians = glm::atan(Direction.get_Z(), -Direction.get_X());
	float w = cos(radians / 2);
	float y = sin(radians / 2);
	return glm::quat(w, 0, y, 0);
}

bool ArtilleryGame::HitCheck()
{
	int x = (int)round(abs(m_Bullet->Position.x - m_EnemyTank->Position.x));
	int y = (int)round(abs(m_Bullet->Position.y - m_EnemyTank->Position.y));
	int z = (int)round(abs(m_Bullet->Position.z - m_EnemyTank->Position.z));
	if ((x <= 1) && (y <= 1) && (z <= 1))
	{
		return true;
	}

	return false;
}

GameObject* ArtilleryGame::CreateGameObjectByType(const std::string& type)
{
	DEBUG_PRINT("ArtilleryGame::CreateGameObjectByType(%s)\n", type.c_str());

	if (type.compare("Player") == 0) {
		DEBUG_PRINT("Create player!\n");
		GameObject* go = GDP_CreateGameObject();
		go->Renderer.ShaderId = 1;
		go->Renderer.MeshId = TankModelId;
		go->Renderer.MaterialId = PlayerMaterialId;
		return go;
	}
	if (type.compare("Enemy") == 0) {
		DEBUG_PRINT("Create Enemy!\n");
		GameObject* go = GDP_CreateGameObject();
		go->Renderer.ShaderId = 1;
		go->Renderer.MeshId = TankModelId;
		go->Renderer.MaterialId = EnemyMaterialId;
		return go;
	}
	if (type.compare("Bullet") == 0) {
		DEBUG_PRINT("Create Bullet!\n");
		GameObject* go = GDP_CreateGameObject();
		go->Renderer.ShaderId = 1;
		go->Renderer.MeshId = ProjectileModelId;
		go->Renderer.MaterialId = BulletMaterialId;
		go->Position = glm::vec3(0, 0, 0);
		return go;
	}

	// Invalid game object type, return nullptr
	return nullptr;
}