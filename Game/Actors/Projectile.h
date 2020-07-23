#pragma once
#include "Object/Actor.h"
#include "Math/Math.h"



	class Projectile : public nc::Actor
	{
	public:

		virtual eType GetType() { return eType::PROJECTILE; }

		virtual bool Load(const std::string& filename) override;
		virtual void Update(float dt) override;

		void SetThrust(float thrust) { m_thrust = thrust; };

		virtual void OnCollision(Actor* actor) override;


	protected:
		float m_thrust{ 0.0f };
		float m_lifetime{3.0f};

	};
