
#include "core.h"
#include "Color.h"
#include "Math/Random.h"
#include "Math/Vector2.h"
#include "Math/Math.h"
#include "Color.h"
#include "Math/Transform.h"
#include "Graphics/Shape.h"
#include "Graphics/ParticleSystem.h"
#include "Object/Actor.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Object/Scene.h"
#include <iostream>
#include <string>
#include <list>
#include <vector>

nc::Scene scene;
nc::ParticleSystem particlesystem;

float t{ 0 };

float frametime;
float spawntimer{ 0 };

bool Update(float dt)// delta time (60 fps) (1/60 = 0.016)
{
	frametime = dt;

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	if (Core::Input::IsPressed(VK_SPACE))
	{
		//scene.Shutdown();

	}

	

	spawntimer += dt;

	if (spawntimer >= 3.0f)
	{
		spawntimer = 0.0f;

		////add enemy to scene
		nc::Enemy* actor = new nc::Enemy;
		actor->Load("enemytr.txt");
		actor->SetTarget(scene.GetActor<nc::Player>());
		actor->GetTransform();
		actor->GetTransform().position = nc::Vector2{ nc::random(0,800), nc::random(0,600) };
		actor->SetThrust(nc::random(50, 100));
		scene.AddActor(actor);
	}

	nc::Player* player = scene.GetActor<nc::Player>();
	particlesystem.Create(player->GetTransform().position, player->GetTransform().angle + nc::PI, 20, 1, nc::Color{1,1,1},1,100,200);

	particlesystem.Update(dt);
	scene.Update(dt);
	return quit;
}

void Draw(Core::Graphics& graphics)
{	
	graphics.DrawString(10, 10, std::to_string(frametime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f/frametime).c_str());

	float v = (std::sin(t) + 1.0f); // -1 <-> 1 | 0 - 2

	nc::Color c = nc::Lerp(nc::Color{0,0,1}, nc::Color{1,0,0},v);
	graphics.SetColor(c);

	particlesystem.Draw(graphics);
	scene.Draw(graphics);

}

int main()
{
	scene.Startup();
	particlesystem.Startup();


	DWORD ticks = GetTickCount();
	std::cout << ticks/1000/60/60 << std::endl;

	nc::Player* player = new nc::Player;
	player->Load("playertr.txt");
	scene.AddActor(player);
	//actors.push_back(player);

	for (int i = 0; i < 10; i++)
	{
		nc::Actor* enemy = new nc::Enemy;
		enemy->Load("enemytr.txt");
		dynamic_cast<nc::Enemy*>(enemy)->SetTarget(player);
		enemy->GetTransform().position = nc::Vector2{ nc::random(0,800), nc::random(0,600) };
		dynamic_cast<nc::Enemy*>(enemy)->SetThrust(nc::random(50,100));

		scene.AddActor(enemy);
	}

	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();

	scene.Shutdown();
	particlesystem.Shutdown();
}


