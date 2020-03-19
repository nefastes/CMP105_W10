#include "Player.h"
Player::Player()
{
	//Walk
	walk.addFrame(sf::IntRect(0, 0, 64, 64));
	walk.addFrame(sf::IntRect(64, 0, 64, 64));
	walk.setFrameSpeed(1.f / 10.f);

	//Idle
	idle.addFrame(sf::IntRect(0, 0, 64, 64));
	idle.addFrame(sf::IntRect(128, 0, 64, 64));
	idle.setFrameSpeed(1.f / 10.f);

	//Physics
	sScale = 40.f;
	gravity = sf::Vector2f(0, 9.8 * sScale);
	stepVelocity = sf::Vector2f(0, 0);

	//Others
	isMoving = false;
	isOnGround = false;
	prevTime = 0;
	window = nullptr;
}

Player::~Player()
{

}

void Player::update(float dt)
{
	//Animation
	if (isMoving)
	{
		walk.animate(dt);
		setTextureRect(walk.getCurrentFrame());
	}
	else
	{
		idle.animate(dt);
		setTextureRect(idle.getCurrentFrame());
	}

	//Physics
	sf::Vector2f pos = stepVelocity * dt + 0.5f * gravity * dt;
	stepVelocity += gravity * dt;
	setPosition(getPosition() + pos);

	//default reset pos
	if (getPosition().y > window->getSize().y + getSize().y) setPosition(sf::Vector2f(300, 100));
}

void Player::handleInput(float dt)
{
	prevTime += dt;
	if (input->isKeyDown(sf::Keyboard::Right) || input->isKeyDown(sf::Keyboard::D))
	{
		//walk
		isMoving = true;
		move(velocity.x * dt, 0);
		walk.setFlipped(true);
		idle.setFlipped(true);
	}
	else if (input->isKeyDown(sf::Keyboard::Left) || input->isKeyDown(sf::Keyboard::A))
	{
		//walk but reversed
		isMoving = true;
		move(-velocity.x * dt, 0);
		walk.setFlipped(false);
		idle.setFlipped(false);
	}
	else
	{
		//idle
		isMoving = false;
	}

	if (input->isKeyDown(sf::Keyboard::Space) && isOnGround)
	{
		stepVelocity = sf::Vector2f(0, -600.f);
	}
}

void Player::collisionResponse(GameObject* collider)
{
	if (std::abs((collider->getPosition().x + collider->getSize().x / 2) - getPosition().x) < std::abs((collider->getPosition().y + collider->getSize().y / 2) - getPosition().y))
	{
		if (collider->getPosition().x + collider->getSize().x != getPosition().x)
		{
			velocity.y = 0;
			setPosition(sf::Vector2f(getPosition().x, collider->getPosition().y - getSize().y));
		}
	}
	else
	{
		if ((collider->getPosition().x + collider->getSize().x) - getPosition().x < 0)
		{
			setPosition(sf::Vector2f(collider->getPosition().x + collider->getSize().x, getPosition().y));
		}
		else
		{
			setPosition(sf::Vector2f(collider->getPosition().x - getSize().x, getPosition().y));
		}
	}
}