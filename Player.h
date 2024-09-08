#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Player
{
private:
	sf::RectangleShape _Shape;

	sf::Texture _Texture;

	float _MovementSpeed;
	int _Hp;
	int _MaxHp;

	void InitVariables();
	void InitShape();

public:
	Player(float x = 0.f, float y = 0.f);
	~Player();

	sf::RectangleShape GetShape() const;
	const int& GetHp() const;
	const int& GetHpMax() const;

	void TakeDamage(const int damage);
	void GainHealth(const int health);

	void InitTextures();
	void UpdateInput();
	void UpdateWindowBoundsCollision(const sf::RenderTarget* target);
	void Update(const sf::RenderTarget* target);
	void Render(sf::RenderTarget* target);
};

