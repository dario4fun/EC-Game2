#include "Pelotas.h"

void Pelotas::InitShape(const sf::RenderWindow& window)
{

	this->_Shape.setRadius(static_cast<float>(rand() % 10 + 10));

	sf::Color _Color;

	switch (this->_Type) {

		case DEFAULT:
			_Color = sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
			break;
		case DAMAGING:
			_Color = sf::Color::Red;
			this->_Shape.setOutlineColor(sf::Color::White);
			this->_Shape.setOutlineThickness(2.f);
			break;
		case HEALING:
			_Color = sf::Color::Green;
			this->_Shape.setOutlineColor(sf::Color::White);
			this->_Shape.setOutlineThickness(2.f);
			break;


	}

	this->_Shape.setFillColor(_Color);
	this->_Shape.setPosition(sf::Vector2f(
		static_cast<float>(rand() % window.getSize().x - this->_Shape.getGlobalBounds().width),
		static_cast<float>(rand() % window.getSize().y - this->_Shape.getGlobalBounds().height)
	));
}

Pelotas::Pelotas(const sf::RenderWindow& window, int type) : _Type(type)
{
	_Type = type;
	InitShape(window);
}


const sf::CircleShape Pelotas::GetShape() const
{
	return this->_Shape;
}

const int& Pelotas::getType() const
{
	return this->_Type;
}

void Pelotas::SetTexture(sf::Texture* texture)
{
	_Shape.setTexture(texture);
}

void Pelotas::Render(sf::RenderTarget* target)
{
	target->draw(this->_Shape);
}

