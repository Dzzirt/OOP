#include "stdafx.h"
#include "DrawVisitor.h"
#include "LineSegment.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Circle.h"

void CDrawVisitor::Visit(CLineSegment & line)
{
	auto leftPoint = sf::Vector2f((float)line.GetFirstPoint().GetPosition().x,
		(float)line.GetFirstPoint().GetPosition().y);
	auto rightPoint = sf::Vector2f((float)line.GetSecondPoint().GetPosition().x,
		(float)line.GetSecondPoint().GetPosition().y);
	auto visualLine = sf::VertexArray(sf::Lines, 2);
	visualLine[0].position = leftPoint;
	visualLine[1].position = rightPoint;
	visualLine[0].color = sf::Color(line.GetBorderColor().r, line.GetBorderColor().g, line.GetBorderColor().b);
	visualLine[1].color = sf::Color(line.GetBorderColor().r, line.GetBorderColor().g, line.GetBorderColor().b);
	m_drawable.push_back(std::make_unique<sf::VertexArray>(visualLine));
}

void CDrawVisitor::Visit(CTriangle & triangle)
{
	auto visualShape = std::make_unique<sf::ConvexShape>();
	visualShape->setPointCount(3);
	auto leftPoint = sf::Vector2f((float)triangle.GetLeftVertex().GetPosition().x,
		(float)triangle.GetLeftVertex().GetPosition().y);
	auto middlePoint = sf::Vector2f((float)triangle.GetMiddleVertex().GetPosition().x,
		(float)triangle.GetMiddleVertex().GetPosition().y);
	auto rightPoint = sf::Vector2f((float)triangle.GetRightVertex().GetPosition().x,
		(float)triangle.GetRightVertex().GetPosition().y);
	visualShape->setPoint(0, leftPoint);
	visualShape->setPoint(1, middlePoint);
	visualShape->setPoint(2, rightPoint);
	visualShape->setOutlineThickness(1);
	visualShape->setFillColor(sf::Color(triangle.GetFillColor().r, triangle.GetFillColor().g, triangle.GetFillColor().b));
	visualShape->setOutlineColor(sf::Color(triangle.GetBorderColor().r, triangle.GetBorderColor().g, triangle.GetBorderColor().b));
	m_drawable.push_back(std::move(visualShape));
}

void CDrawVisitor::Visit(CRectangle & rectangle)
{
	auto visualRect = std::make_unique<sf::RectangleShape>();
	visualRect->setPosition((float)rectangle.GetPosition().x, (float)rectangle.GetPosition().y);
	visualRect->setSize(sf::Vector2f((float)rectangle.GetWidth(), (float)rectangle.GetHeight()));
	visualRect->setOutlineThickness(1);
	visualRect->setFillColor(sf::Color(rectangle.GetFillColor().r, rectangle.GetFillColor().g, rectangle.GetFillColor().b));
	visualRect->setOutlineColor(sf::Color(rectangle.GetBorderColor().r, rectangle.GetBorderColor().g, rectangle.GetBorderColor().b));
	m_drawable.push_back(std::move(visualRect));
}

void CDrawVisitor::Visit(CCircle & circle)
{
	auto visualShape = std::make_unique<sf::CircleShape>();
	visualShape->setRadius(static_cast<float>(circle.GetRadius()));
	visualShape->setPosition(sf::Vector2f(static_cast<float>(circle.GetCenter().GetPosition().x), 
		static_cast<float>(circle.GetCenter().GetPosition().y)));
	visualShape->setFillColor(sf::Color(circle.GetFillColor().r, circle.GetFillColor().g, circle.GetFillColor().b));
	visualShape->setOutlineThickness(1);
	visualShape->setOutlineColor(sf::Color(circle.GetBorderColor().r, circle.GetBorderColor().g, circle.GetBorderColor().b));
	visualShape->setOrigin(sf::Vector2f(static_cast<float>(circle.GetRadius()), static_cast<float>(circle.GetRadius())));
	m_drawable.push_back(std::move(visualShape));
}

void CDrawVisitor::Draw(sf::RenderWindow & window)
{
	for (auto & shape : m_drawable)
	{
		window.draw(*shape);
	}
}
