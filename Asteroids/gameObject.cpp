#include "gameObject.h"
#include <thread>
#include <chrono>

gameObject::gameObject(gameObjectType type, float radius)
	: type(type), shape(radius)
{
	setBody(&body);
	setShape(&shape);
}

void gameObject::onCollisionWith(gameObject& other)
{
	if (this->type == gameObjectType::ship)
	{
		if (other.type == gameObjectType::asteroid
			|| other.type == gameObjectType::ufo)
		{
			kill();
			std::thread t(&gameObject::respawn, this);
			t.detach();
		}
	}

	if (this->type == gameObjectType::asteroid
		|| this->type == gameObjectType::ufo)
	{
		if (other.type == gameObjectType::bullet)
		{
			kill();
		}
	}
}
void gameObject::respawn()
{
	this->revive();
	this->getBody()->setPos({ 0,0 });
	this->getBody()->setLinearVelocity({ 0,0 });
	this->invincible = true;
	printf("invincible for 2s");
	std::this_thread::sleep_for(std::chrono::seconds(2));
	this->invincible = false;
	printf("invincibility gone");
}