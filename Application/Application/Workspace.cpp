#include "WorkSpace.h"

Workspace::Workspace(const sf::Vector2f & pos, sf::Vector2f & size)
{
	m_canvasVisual.setPosition(pos);
	m_canvasVisual.setFillColor(sf::Color::White);
	m_canvasVisual.setOutlineThickness(1.f);
	m_canvasVisual.setOutlineColor(sf::Color::Black);
	m_canvasVisual.setSize(size);
}

Workspace::Workspace()
{
}

Workspace::~Workspace()
{
}

void Workspace::AddShape(std::shared_ptr<ShapeVisual> & shape, size_t index)
{
	shape->SetIndex(index);
	m_shapesVisual.push_back(shape);
}

void Workspace::RemoveSelectedShape()
{
	for (size_t i = 0; i < m_shapesVisual.size(); i++)
	{
		break;
	}
}

void Workspace::RemoveShape(size_t index)
{
	m_shapesVisual.erase(m_shapesVisual.begin() + index);
}

void Workspace::Draw(sf::RenderWindow & window)
{
	window.draw(m_canvasVisual);
	for (auto & shape : m_shapesVisual)
	{
		shape->Draw(window);
	}
}

size_t Workspace::GetShapesCount()
{
	return m_shapesVisual.size();
}

std::vector<std::shared_ptr<ShapeVisual>>& Workspace::GetShapesVisual()
{
	return m_shapesVisual;
}

sf::RectangleShape& Workspace::GetCanvasVisual()
{
	return m_canvasVisual;
}

void Workspace::ProcessEvents(sf::Event event)
{
	sf::Vector2f mousePos = sf::Vector2f(float(event.mouseButton.x), float(event.mouseButton.y));
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_canvasVisual.getGlobalBounds().contains(mousePos))
	{
		HandleClick();
	}
	for_each(m_shapesVisual.begin(), m_shapesVisual.end(), [&](std::shared_ptr<ShapeVisual> & shapeVisual) 
	{
		shapeVisual->ProcessEvents(event);
	});
}

boost::signals2::connection Workspace::DoOnClick(const WorkSpaceClickSignal::slot_type & handler)
{
	return m_onClick.connect(handler);
}

void Workspace::HandleClick()
{
	m_onClick();
}