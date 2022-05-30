#include "Vehicle.h"
#include <math.h>
#include <iostream>

const int WIDTH = 600;
const int HEIGHT = 400;

enum deceleration
{
	FAST = 1,
	NORMAL = 2,
	SLOW = 3
};

Vehicle::Vehicle(float x, float y)
{
	pos = new Vector2D(x, y);
	vel = new Vector2D(0, 0);
	acc = new Vector2D(0, 0);
	maxSpeed = 6;
	maxForce = 0.4f;
	r = 16;

	radian = 0;
	m_xy1 = new Vector2D(0, 0);
	m_xy2 = new Vector2D(0, 0);
	m_xy3 = new Vector2D(0, 0);

	force = new Vector2D(0, 0);
	desiredSpeed = 0;
	slowRadius = 100;
	distance = 0;
}

Vector2D Vehicle::arrive(Vector2D* target)
{
	return seek(target, true);
}

Vector2D Vehicle::seek(Vector2D* target, bool arrival)
{
	/*
	*force = *target - *pos;
	desiredSpeed = maxSpeed;
	if (arrival)
	{
		distance = force->length();
		if (distance < slowRadius)
		{
			// desiredSpeed = map(distance, 0, slowRadius, 0, this.maxSpeed);
			desiredSpeed = std::min(0, slowRadius);
		}
	}
	force->normalize();
	*force *= desiredSpeed;
	*force -= *vel;
	force->limit(maxForce);
	return *force;
	*/

	* force = *target - *pos;
	double dist = force->length();
	if (dist > 0)
	{
		const double DecelerationTweaker = 0.3f;
		//double speed = dist / ((double)deceleration * DecelerationTweaker);
		double speed = dist / (50 * DecelerationTweaker);
		speed = std::min(speed, (double)maxSpeed);
		*force *= speed / dist;
		Vector2D DesiredVelocity = *force;

		return DesiredVelocity - *vel;
	}

	return Vector2D(0, 0);
}

void Vehicle::applyForce(Vector2D* force)
{
	*acc += *force;
}

void Vehicle::edges()
{
	if (pos->getX() > WIDTH + r)
	{
		pos->setX(-r);
	}
	else if (pos->getX() < -r)
	{
		pos->setX(WIDTH + r);
	}

	if (pos->getY() > HEIGHT + r)
	{
		pos->setY(-r);
	}
	else if (pos->getY() < -r)
	{
		pos->setY(HEIGHT + r);
	}
}

Vector2D Vehicle::rotate(float _x, float _y, float rad)
{
	Vector2D tmp(0, 0);

	tmp.setX(cos(rad) * _x - sin(rad) * _y);
	tmp.setY(sin(rad) * _x + cos(rad) * _y);

	return tmp;
}

void Vehicle::update()
{
	edges();

	*vel += *acc;
	vel->limit(maxSpeed);
	*pos += *vel;
	*acc *= 0;

	radian = atan2(vel->getY(), vel->getX());
	*m_xy1 = rotate(-r, -r / 2, radian);
	*m_xy2 = rotate(-r, r / 2, radian);
	*m_xy3 = rotate(r, 0, radian);
}

void Vehicle::show(SDL_Renderer* renderer)
{
	filledTrigonColor(renderer,
		m_xy1->getX() + pos->getX(), m_xy1->getY() + pos->getY(),
		m_xy2->getX() + pos->getX(), m_xy2->getY() + pos->getY(),
		m_xy3->getX() + pos->getX(), m_xy3->getY() + pos->getY(),
		0xFFFFFFFF);
}