#include "stdafx.h"
#include "Rectangle.h"
#include <cassert>



CRectangle::CRectangle(CPoint upperLeft, double width, double height)
	: m_upperLeftCorner(upperLeft), m_width(width), m_height(height)
{
	if (width < 0 || height < 0)
	{
		throw std::invalid_argument("Width and height should have positive values");
	};
}

double CRectangle::GetArea() const
{
	return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
	return (m_width + m_height) * 2;
}

CColorRGB CRectangle::GetBorderColor() const
{
	return m_borderColor;
}

double CRectangle::GetWidth() const
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}

std::pair<double, double> CRectangle::GetPosition() const
{
	return m_upperLeftCorner.GetPosition();
}

void CRectangle::SetBorderColor(CColorRGB const& color)
{
	m_borderColor = color;
}

std::string CRectangle::ToString() const
{
	std::string output = "Rectangle ";
	output += "\n";
	output += "pos: ";
	output += m_upperLeftCorner.ToString();
	output += "\n";
	output += "S: " + std::to_string(GetArea());
	output += "\n";
	output += "P: ";
	output += std::to_string(GetPerimeter());
	output += "\n";
	output += "Border Color: ";
	output += std::to_string(GetBorderColor().r);
	output += " ";
	output += std::to_string(GetBorderColor().g);
	output += " ";
	output += std::to_string(GetBorderColor().b);
	output += "\n";
	output += "Fill Color: ";
	output += std::to_string(GetFillColor().r);
	output += " ";
	output += std::to_string(GetFillColor().g);
	output += " ";
	output += std::to_string(GetFillColor().b);
	output += "\n";
	output += "=============================";
	return output;
}

CColorRGB CRectangle::GetFillColor() const
{
	return m_fillColor;
}

void CRectangle::SetFillColor(CColorRGB const& color)
{
	m_fillColor = color;
}


Shapes CRectangle::GetType() const
{
	return RECTANGLE;
}
