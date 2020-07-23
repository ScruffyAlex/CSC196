#include "pch.h"
#include "Shape.h"
#include "Math/Matrix33.h"
#include <fstream>

bool nc::Shape::Load(const std::string& filename)
{

	bool success = false;

	std::ifstream stream(filename);
	if (stream.is_open())
	{
		success = true;

		//read color {stream >> m_color}

		//get color
		stream >> m_color;

		//get num of points
		std::string line;
		std::getline(stream, line);
		size_t size = stoi(line);

		//read points
		for (size_t i = 0; i < size; i++)
		{
			Vector2 v;
			stream >> v;
			m_points.push_back(v);
		}

		//read points
		
		stream.close();
	}

	//get radius
	for (size_t i = 0; i < m_points.size(); i++)
	{
		nc::Vector2 p1 = m_points[i];

		float length = p1.Length();
		if (length > m_radius) m_radius = length;
	}
	return success;
}

void nc::Shape::Draw(Core::Graphics& graphics, nc::Vector2 position, float scale, float angle)
{
	graphics.SetColor(m_color);

	Matrix33 mxs;
	mxs.Scale(scale);

	Matrix33 mxr;
	mxr.Rotate(angle);

	nc::Matrix33 mxt;
	mxt.Translate(position);

	Matrix33 mx = mxs * mxr * mxt;

	for (size_t i = 0; i < m_points.size() - 1; i++)
	{
		//local / object space spoints
		nc::Vector2 p1 = m_points[i];
		nc::Vector2 p2 = m_points[i + 1];

		p1 = p1 * mx;
		p2 = p2 * mx;

		graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}
}

void nc::Shape::Draw(Core::Graphics& graphics, const Transform& transform)
{
	graphics.SetColor(m_color);

	for (size_t i = 0; i < m_points.size() - 1; i++)
	{
		//local / object space spoints
		nc::Vector2 p1 = m_points[i];
		nc::Vector2 p2 = m_points[i + 1];

		p1 = p1 * transform.matrix;
		p2 = p2 * transform.matrix;

		graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}
}
