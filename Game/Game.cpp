
#include "core.h"
#include "Color.h"
#include "Math/Random.h"
//#include "Math/Vector2.h"
#include "Math/Math.h"
#include "Color.h"
#include "Math/Transform.h"
#include "Graphics/Shape.h"
#include <iostream>
#include <string>


nc::Shape ship;
nc::Transform transform{ {400,300},4,0 };

DWORD prevTime;
DWORD deltaTime;


float t{ 0 };

float speed = 200.0f;

float frametime;
float roundTime{ 0 };
bool gameOver{ false };



bool Update(float dt)// delta time (60 fps) (1/60 = 0.016)
{

	DWORD time = GetTickCount();
	deltaTime = time - prevTime; // current time frame - previous time frame
	prevTime = time;

	t = t + dt*5;

	frametime = dt;
	roundTime += dt;
	if (roundTime >= 5.0f) gameOver = true;

	dt = dt * 2.0f;
	

	if (gameOver) dt = dt * 0.5f;

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	int x;
	int y;
	Core::Input::GetMousePos(x, y);


	nc::Vector2 force{ 0,0 };
	if (Core::Input::IsPressed('W')) { force = nc::Vector2::forward * speed * dt; }
	nc::Vector2 direction = force;
	direction = nc::Vector2::Rotate(direction, transform.angle);
	transform.position = transform.position + direction;

	//rotate
	if (Core::Input::IsPressed('A')) { transform.angle = transform.angle - (nc::DegreesToRadians(360.0f)*dt); }
	if (Core::Input::IsPressed('D')) { transform.angle = transform.angle + (nc::DegreesToRadians(360.0f)*dt); }

	//keep within borders
	transform.position = nc::Clamp(transform.position, { 0,0 }, { 800,600 });

	return quit;
}

void Draw(Core::Graphics& graphics)
{	
	graphics.DrawString(10, 10, std::to_string(frametime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f/frametime).c_str());
	graphics.DrawString(10, 30, std::to_string(deltaTime/1000.0f).c_str());

	float v = (std::sin(t) + 1.0f); // -1 <-> 1 | 0 - 2

	nc::Color c = nc::Lerp(nc::Color{0,0,1}, nc::Color{1,0,0},v);
	graphics.SetColor(c);
	
	nc::Vector2 p = nc::Lerp(nc::Vector2{400,300}, nc::Vector2{100,100},v);
	graphics.DrawString(p.x,p.y,"Pew Pew Boi");

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


