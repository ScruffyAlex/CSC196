#include "Player.h"
#include "Projectile.h"
#include "Math/Vector2.h"
#include "Math/Math.h"
#include "Object/Scene.h"

namespace nc {

	bool Player::Load(const std::string& filename)
	{
		bool success = false;
		std::ifstream stream(filename);

		if (stream.is_open())
		{
			success = true;
			Actor::Load(stream);

			stream >> m_thrust;
			stream >> r_rotation;


			stream.close();
		}
		return success;
	}

	void Player::Update(float dt)
	{

		m_fireTimer += dt;

		if (Core::Input::IsPressed(VK_SPACE) && m_fireTimer >= m_fireRate)
		{
			m_fireTimer = 0;
			//add enemy to scene
			Projectile* projectile = new Projectile;
			projectile->Load("projectile.txt");
			projectile->GetTransform().position = m_transform.position;
			projectile->GetTransform().angle = m_transform.angle;
			m_scene->AddActor(projectile);
		}

		//position
		nc::Vector2 force;
		if (Core::Input::IsPressed('W')) { force = nc::Vector2::forward * m_thrust; }
		force = nc::Vector2::Rotate(force, m_transform.angle);

		//force = force + nc::Vector2{ 0,100 };

		m_velocity = m_velocity + (force * dt);
		m_velocity = m_velocity * 0.98f;

		m_transform.position += m_velocity * dt;

		//direction = nc::Vector2::Rotate(direction, transform.angle);
		//transform.position = transform.position + direction;

		//rotate
		if (Core::Input::IsPressed('A')) {m_transform.angle -= nc::DegreesToRadians(r_rotation) * dt; }
		if (Core::Input::IsPressed('D')) {m_transform.angle += nc::DegreesToRadians(r_rotation) * dt; }

		//keep within borders

		/*if (m_transform.position.x > 800) m_transform.position.x = 0;
		if (m_transform.position.x < 0) m_transform.position.x = 800;
		if (m_transform.position.y > 600) m_transform.position.y = 0;
		if (m_transform.position.y < 0) m_transform.position.y = 600;*/

		m_transform.position = nc::Clamp(m_transform.position, {0,0}, {800,600});
		m_transform.Update();

	}

}

