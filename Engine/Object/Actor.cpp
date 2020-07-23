#include "pch.h"
#include "Actor.h"
#include "../Math/Transform.h"
#include <iostream>
#include <string>

using std::string;

namespace nc 
{

    bool Actor::Load(const std::string& filename)
    {
        bool success = false;

        std::ifstream stream(filename); // open stream
         // check if stream is open
        if (stream.is_open())
        {
            success = true;  // set success to true

            Load(stream);

            stream.close();

           // stream >> m_transform;
           //string name;
            //stream >> name;
            //m_shape.Load(name);

        }

       
        return success;
    }

	void Actor::Load(std::istream& stream)
	{
        stream >> m_transform;

        std::string shapename;
        stream >> shapename;
        m_shape.Load(shapename);
	}

    void Actor::Update(float dt)
    {
       
    }

    void Actor::Draw(Core::Graphics& graphics)
    {
        m_shape.Draw(graphics, m_transform);
    }

	float Actor::GetRadius()
	{
        return m_shape.GetRadius() * m_transform.scale;
	}

    
}


