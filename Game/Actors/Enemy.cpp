#include "Enemy.h"
#include "Math/Math.h"
#include "Graphics/ParticleSystem.h"

bool nc::Enemy::Load(const std::string& filename)
{
	bool success = false;

	std::ifstream stream(filename);
	if (stream.is_open())
	{
		success = true;
		Actor::Load(stream);

		stream >> m_thrust;

		stream.close();
	}

	return success;
}

void nc::Enemy::Update(float dt)
{
	nc::Vector2 direction = m_target->GetTransform().position - m_transform.position;
	m_transform.angle = std::atan2(direction.y, direction.x) + nc::DegreesToRadians(90.0f);
	nc::Vector2 velocity = direction.Normalized() * 0;
	direction.Normalize();
	m_velocity = direction * m_thrust;
	m_transform.position += m_velocity * dt;
	

	m_transform.Update();
}

void nc::Enemy::OnCollision(Actor* actor)
{
	if (actor->GetType() == eType::PROJECTILE);
	{
		m_destroy = true;
		nc::Color colors[] = { nc::Color::purple,nc::Color::green,nc::Color::white };
		nc::Color color = colors[rand() % 3];

		g_particleSystem.Create(m_transform.position, 0, 180, 30, color, 1, 100, 200);

		
		//m_scene->RemoveActor(actor);
	}
}

