#include "Player.h"

void Player::InitVariables()
{
	
	this->_MovementSpeed = 10.f;
	this->_Hp = 10;
	this->_MaxHp = 10;
}

void Player::InitShape()
{
	this->_Shape.setSize(sf::Vector2f(50.f, 50.f));
	_Shape.setTexture(&_Texture);
}

Player::Player(float x, float y) {

	this->_Shape.setPosition(x, y);

	this->InitVariables();
	InitTextures();
	this->InitShape();
	
	
}

Player::~Player()
{
	
}

sf::RectangleShape Player::GetShape() const
{
	return this->_Shape;
}

const int& Player::GetHp() const
{
	return this->_Hp;
}

const int& Player::GetHpMax() const
{
	return this->_MaxHp;
}

void Player::TakeDamage(const int damage)
{
	if (this->_Hp > 0) this->_Hp -= damage;

	if (this->_Hp <= 0) this->_Hp = 0;
}

void Player::GainHealth(const int health)
{
	if (this->_Hp < this->_MaxHp) this->_Hp += health;

	if (this->_Hp >= this->_MaxHp) this->_Hp = this->_MaxHp;
}

void Player::InitTextures()
{
	if (!_Texture.loadFromFile("./Resources/Player.png")) {

		std::cout << "Error al cargar la imagen del background" << " \n";
	}
}

void Player::UpdateInput()
{

	// Keyboard input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {

		this->_Shape.move(-this->_MovementSpeed, 0.f);

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {

		this->_Shape.move(this->_MovementSpeed, 0.f);

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {

		this->_Shape.move(0.f, -this->_MovementSpeed);

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {

		this->_Shape.move(0.f, this->_MovementSpeed);

	}

}

void Player::UpdateWindowBoundsCollision(const sf::RenderTarget* target)
{

	//Left/Rigth Window Limits
	if (this->_Shape.getGlobalBounds().left <= 0.f) {

		this->_Shape.setPosition(0.f, this->_Shape.getGlobalBounds().top);

	}
	else if (this->_Shape.getGlobalBounds().left + this->_Shape.getGlobalBounds().width >= target->getSize().x) {

		this->_Shape.setPosition(target->getSize().x - this->_Shape.getGlobalBounds().width, this->_Shape.getGlobalBounds().top);
	}

	//Top/Bottom Window Limits
	if (this->_Shape.getGlobalBounds().top <= 0.f) {

		this->_Shape.setPosition(this->_Shape.getGlobalBounds().left, 0.f);

	}
	else if (this->_Shape.getGlobalBounds().top + this->_Shape.getGlobalBounds().height >= target->getSize().y) {

		this->_Shape.setPosition(this->_Shape.getGlobalBounds().left, target->getSize().y - this->_Shape.getGlobalBounds().height);
	}

}

void Player::Update(const sf::RenderTarget* target)
{

	this->UpdateInput();
	this->UpdateWindowBoundsCollision(target);

}

void Player::Render(sf::RenderTarget* target)
{
	target->draw(this->_Shape);
}
