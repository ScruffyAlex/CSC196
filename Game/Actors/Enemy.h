#pragma once
#include "Object/Actor.h"

namespace nc 
{

	class Enemy : public nc::Actor
	{
	public:
		Enemy() = default;
		virtual ~Enemy() {}

		virtual eType GetType() { return eType::ENEMY;}

		virtual bool Load(const std::string& filename) override;
		virtual void Update(float dt) override;

		virtual void OnCollision(Actor* actor);

		void SetThrust(float thrust) { m_thrust = thrust; };

		void SetTarget(Actor* actor) { m_target = actor; }

	protected:
		nc::Vector2 m_velocity;
		float m_thrust{ 0.0f };
		Actor* m_target{ nullptr };

	};
};
