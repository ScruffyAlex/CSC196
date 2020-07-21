#pragma once
#include "Object/Actor.h"


namespace nc
{
	class Player : public nc::Actor

	{
	public:

		virtual eType GetType() { return eType::PLAYER; }

		virtual bool Load(const std::string& filename) override;

		virtual void Update(float dt) override;

	protected:
		float m_thrust;
		float r_rotation;
		float m_fireRate{ 0.2f };
		float m_fireTimer{0.0f};
		nc::Vector2 m_velocity;
	};

};