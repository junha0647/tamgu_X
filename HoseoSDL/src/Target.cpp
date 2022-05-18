#include "Target.h"
#include <random>

const int WIDTH = 600;
const int HEIGHT = 400;

Target::Target(float x, float y) : Vehicle(x, y)
{
	maxSpeed = 4;
}

void Target::edges()
{
	if (pos->getX() > WIDTH - r)
	{
		vel->setX(vel->getX() * -1);
		pos->setX(WIDTH - r);
	}
	else if (pos->getX() < r)
	{
		vel->setX(vel->getX() * -1);
		pos->setX(r);
	}

	if (pos->getY() > HEIGHT - r)
	{
		vel->setY(vel->getY() * -1);
		pos->setY(HEIGHT - r);
	}
	else if (pos->getY() < r)
	{
		vel->setY(vel->getY() * -1);
		pos->setY(r);
	}
}

void Target::applyForce(Vector2D* force)
{
	Vehicle::applyForce(force);
}

void Target::update()
{
	*vel *= 4;

	edges();
	Vehicle::update();
}

void Target::draw(SDL_Renderer* renderer)
{
	filledCircleRGBA(renderer,
		pos->getX(), pos->getY(),
		r * 2,
		255, 255, 0, 128);
}