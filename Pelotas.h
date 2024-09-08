#pragma once

#include <SFML/Graphics.hpp>

enum PelotasTypes { DEFAULT = 0, DAMAGING, HEALING, NROFTYPES };

class Pelotas
{
private:
	sf::CircleShape _Shape;
	int _Type;

	void InitShape(const sf::RenderWindow& window);

public:
	Pelotas(const sf::RenderWindow& window, int type);

	const sf::CircleShape GetShape() const;
	const int& getType() const;

	void SetTexture(sf::Texture* texture);

	void Render(sf::RenderTarget* target);
};
