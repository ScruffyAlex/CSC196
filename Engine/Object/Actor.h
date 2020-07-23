#pragma once
#include "Math/Transform.h"
#include "Graphics/Shape.h"


namespace nc

{

	class Scene;

	class Actor
	{
	public:
		enum class eType
		{
			PLAYER,
			ENEMY,
			PROJECTILE
		};

	public:
		Actor() = default;
		Actor(const Transform& transform, const Shape& shape); // make sure to initialize m_transform and m_shape
		virtual ~Actor() {}

		virtual eType GetType() = 0;

		virtual bool Load(const std::string& filename);
		virtual void Load(std::istream& stream);

		virtual void Update(float dt);
		virtual void Draw(Core::Graphics& graphics);

		virtual void OnCollision(Actor* actor) {}

		float GetRadius();

		void SetScene(Scene* scene) { m_scene = scene; }
		Transform& GetTransform() {return m_transform;}// return the transform
		Shape& GetShape(){return m_shape;}// return the shape
		void SetDestroy(bool destroy = true) { m_destroy = true; }
		bool IsDestroy() { return m_destroy; }

	protected:
		bool m_destroy{false};
		Scene* m_scene{ nullptr };
		Transform m_transform;
		Shape m_shape;
	};
}
