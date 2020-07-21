#include "Projectile.h"
#include "Math/Math.h"

bool Projectile::Load(const std::string& filename)
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

void Projectile::Update(float dt)
{
	nc::Vector2 direction = nc::Vector2::Rotate(nc::Vector2::forward , m_transform.angle);
	nc::Vector2 velocity = direction * m_thrust;
	m_transform.position = m_transform.position + velocity * dt;
	/*nc::Vector2 direction = m_target->GetTransform().position - m_transform.position;
	direction.Normalize();
	m_velocity = direction * m_thrust;
	m_transform.position += m_velocity * dt;
	m_transform.angle = std::atan2(direction.y, direction.x) + nc::DegreesToRadians(90.0f);*/

	m_transform.Update();
}

void Projectile::OnCollision(Actor* actor)
{
	if (actor->GetType()== eType::ENEMY) 
	{
		m_destroy = true;
	}
}


