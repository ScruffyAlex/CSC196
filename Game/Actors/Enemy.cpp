#include "Enemy.h"
#include "Math/Math.h"

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
	if (actor->GetType() == Actor::eType::PROJECTILE);
	{
		m_destroy = true;
		//m_scene->RemoveActor(actor);
	}
}

