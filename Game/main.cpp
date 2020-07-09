
#include "core.h"
#include "Color.h"
#include "Math/Random.h"
//#include "Math/Vector2.h"
#include "Color.h"
#include "Math/Transform.h"
#include "Graphics/Shape.h"
#include <iostream>
#include <string>


nc::Shape ship;

const size_t NUM_POINTS = 40;
float speed = 300.0f;

//std::vector<nc::Vector2> points = { { 0, -3 }, { 3, 3 }, { 0, 1 }, { -3, 3 }, { 0, -3 } };

nc::Transform transform{ {400,300},4,0 };

float frametime;
float roundTime{ 0 };
bool gameOver{ false };

DWORD prevTime;
DWORD deltaTime;


bool Update(float dt)// delta time (60 fps) (1/60 = 0.016)
{

	DWORD time = GetTickCount();
	deltaTime = time - prevTime; // current time frame - previous time frame
	prevTime = time;

	frametime = dt;
	roundTime += dt;
	if (roundTime >= 5.0f) gameOver = true;

	dt = dt * 2.0f;
	

	if (gameOver) dt = dt * 0.5f;

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	int x;
	int y;
	Core::Input::GetMousePos(x, y);



	nc::Vector2 force;
	if (Core::Input::IsPressed('W')) { force = nc::Vector2::forward * speed * dt; }
	nc::Vector2 direction = force;
	direction = nc::Vector2::Rotate(direction, transform.angle);
	transform.position = transform.position + direction;

	if (Core::Input::IsPressed('A')) { transform.angle = transform.angle - (dt * 3.0f); }
	if (Core::Input::IsPressed('D')) { transform.angle = transform.angle + (dt * 3.0f); }

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	
	
	graphics.DrawString(10, 10, std::to_string(frametime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f/frametime).c_str());
	graphics.DrawString(10, 30, std::to_string(deltaTime/1000.0f).c_str());

	if (gameOver) graphics.DrawString(400, 300, "Game Over");

	ship.Draw(graphics, transform);
	
	

}

int main()
{



	DWORD ticks = GetTickCount();
	std::cout << ticks/1000/60/60 << std::endl;
	prevTime = GetTickCount();

	ship.Load("aship.txt");


	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
}


