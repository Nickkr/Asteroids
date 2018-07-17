#include "gameState.h"
#include "gameSettings.inl"
#include "collision.h"
#include <random>
#include <algorithm>



void gameState::setup()
{
	area = rect{ { -1, -1 }, { 1, 1 } };
	ship.getBody()->setLinearDamping(0.8f);
	ship.getBody()->setMaxLinearVelocity(maxLinearVelocity);

	addAsteroid();
	spawnUfo();

}

void gameState::spawnUfo()
{
	vec2 ufoForwardDirection = { cosf(ufoHeading), sinf(ufoHeading) };
	ufo.getBody()->setLinearVelocity(ufoForwardDirection * (maxLinearVelocity / 3));
	ufo.getBody()->setPos({ -0.9f , 0.5f });
}


void gameState::shootBullet()
{
	if (ship.isAlive())
	{
		auto bullet = std::make_unique<gameObject>(gameObjectType::bullet, 0.003f);
		float travelHeading = ship.getBody()->getAngle();
		vec2 shipForwardDirection = { cosf(travelHeading), sinf(travelHeading) };
		bullet->getBody()->setLinearVelocity(shipForwardDirection * maxLinearVelocity * 2);
		bullet->getBody()->setPos(ship.getBody()->getPos());
		bullets.push_back(std::move(bullet));
	}
}

void gameState::ufoAttack()
{
	auto ufoBullet = std::make_unique<gameObject>(gameObjectType::ufoBullet, 0.003f);
	float travelHeading = rand() % 360 / 180.0f * pi;
	vec2 ufoForwardDirection = { cosf(travelHeading), sinf(travelHeading) };
	ufoBullet->getBody()->setLinearVelocity(ufoForwardDirection * (maxLinearVelocity / 2));
	ufoBullet->getBody()->setPos(ufo.getBody()->getPos());
	ufoBullets.push_back(std::move(ufoBullet));
}

void gameState::addAsteroid()
{
	auto asteroid = std::make_unique<gameObject>(gameObjectType::asteroid, 0.09f);
	asteroid->getBody()->setAngularVelocity(angularVelocity / 30);
	float travelHeading = rand() % 360 / 180.0f * pi; //0-359 degrees in radian fly direction
	vec2 asteroidForwardDirection = { cosf(travelHeading), sinf(travelHeading) };
	asteroid->getBody()->setLinearVelocity(asteroidForwardDirection * (maxLinearVelocity / 3));
	asteroid->getBody()->setPos(asteroidSpawnCoords[spawnCoordCounter % 4]);
	asteroids.push_back(std::move(asteroid));
	++spawnCoordCounter; //next asteroid spawns at next position defined in vector
}

// dt float time since last update call
void gameState::update(float dt)
{
	gameTime += dt;
	ship.getBody()->resetForceAndTorque();

	updateControls();

	if (enableMomentum)
	{
		ship.getBody()->update(dt);
	}
	else
	{
		// Rotate the velocity vector along with the ship for snappier controls
		float oldHeading = ship.getBody()->getAngle();
		ship.getBody()->update(dt);
		float newHeading = ship.getBody()->getAngle();
		float rotation = newHeading - oldHeading;
		vec2 shipVelocity = ship.getBody()->getLinearVelocity();
		vec2 rotatedShipVelocity = {
			cosf(rotation) * shipVelocity.x - sinf(rotation) * shipVelocity.y,
			cosf(rotation) * shipVelocity.y + sinf(rotation) * shipVelocity.x
		};
		ship.getBody()->setLinearVelocity(rotatedShipVelocity);
	}
	ship.getBody()->confineTo(area);

	for (auto& asteroid : asteroids)
	{
		asteroid->getBody()->update(dt);
		asteroid->getBody()->confineTo(area);
	}

	eraseOutOfRange(bullets);
	eraseOutOfRange(ufoBullets);

	for (auto& bullet : bullets)
	{
		bullet->getBody()->update(dt);
	}

	for (auto& ufoBullet : ufoBullets)
	{
		ufoBullet->getBody()->update(dt);
	}

	ufo.getBody()->update(dt);
	ufo.getBody()->confineTo(area);


	if (!ufo.isAlive() && gameTime > (ufoKilledTime + ufoSpawnInterval))
	{
		vec2 currentUfoPos = ufo.getBody()->getPos();
		//UFO respawns on the left edge with a random y axis between -1 and 1
		ufo.getBody()->setPos({ -1, (rand() / ((float)RAND_MAX) - (float)(RAND_MAX / 2)) });
		ufo.revive();
	}

	if (!ship.isAlive())
	{
		if (shipStateTimeStamp == 0)
		{
			shipStateTimeStamp = gameTime + respawnTimer;
		}
		else if (gameTime > shipStateTimeStamp)
		{
			shipStateTimeStamp = 0;
			ship.respawn();
		}
	}

	float gameDifficultyAdjustment = std::pow(0.9f, (playerScore / 1000));

	if (ufo.isAlive() && (gameTime > (lastUfoBulletTime + ufoShootInterval * gameDifficultyAdjustment)))
	{
		ufoAttack();
		lastUfoBulletTime = gameTime;
	}

	if (gameTime > (lastAsteroidSpawn + asteroidSpawnInterval * gameDifficultyAdjustment))
	{
		addAsteroid();
		lastAsteroidSpawn = gameTime;
	}

	if (ship.isInvincible())
	{
		if (shipStateTimeStamp == 0)
		{
			shipStateTimeStamp = gameTime + invincibleAfterSpawnTimer;
		}
		else if (gameTime > shipStateTimeStamp)
		{
			shipStateTimeStamp = 0;
			ship.setInvincible(false);
		}
	}
	else
		//check collision between ship and ufobullets, ufo, asteroid game objects
	{
		this->collision = (ufo.isAlive() && checkCollision(ufo, ship)); //checkcollision is only called if ufo is alive
		for (auto& asteroid : asteroids)
		{
			if (asteroid->isAlive() && checkCollision(*asteroid, ship))
			{
				this->collision = true;
				break;
			}
		}
		for (auto& ufoBullet : ufoBullets)
		{
			if (checkCollision(*ufoBullet, ship))
			{
				this->collision = true;
				break;
			}
		}
		if (this->collision)
		{
			printf("Player score: %d \n", playerScore);
		}

	}
	//check collision between bullets fired from ship and asteroids, ufo
	for (auto& bullet : bullets)
	{
		if (ufo.isAlive() && checkCollision(*bullet, ufo))
		{
			playerScore += 50;
			ufoKilledTime = gameTime;
		}
		for (auto& asteroid : asteroids)
		{
			if (asteroid->isAlive() && checkCollision(*bullet, *asteroid))
			{
				playerScore += 30;
			}
		}
	}
}

void gameState::eraseOutOfRange(std::vector<std::unique_ptr<gameObject>>& objects)
{
	objects.erase(std::remove_if(objects.begin(), objects.end(), [](auto&& object)
	{
		return object->getBody()->getPos().x > 1
			|| object->getBody()->getPos().x < -1
			|| object->getBody()->getPos().y > 1
			|| object->getBody()->getPos().y < -1;
	}), objects.end());
}

// TODO: Move to controller
void gameState::updateControls()
{
	float shipAngularVelocity = 0;
	if (turnLeft)
	{
		shipAngularVelocity += angularVelocity;
	}
	if (turnRight)
	{
		shipAngularVelocity -= angularVelocity;
	}

	float shipAcceleration = 0;
	if (boostingForward)
	{
		shipAcceleration += linearAcceleration;
	}
	if (boostingBackward)
	{
		shipAcceleration += -linearAcceleration;
	}
	float shipHeading = ship.getBody()->getAngle();
	vec2 shipForwardDirection = { cosf(shipHeading), sinf(shipHeading) };
	vec2 shipForce = shipForwardDirection * shipAcceleration;

	ship.getBody()->applyForce(shipForce);
	ship.getBody()->setAngularVelocity(shipAngularVelocity);
}
