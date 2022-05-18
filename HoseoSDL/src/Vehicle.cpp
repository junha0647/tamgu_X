#include "Vehicle.h"

// 이 부분 수정해야 함
const int WIDTH = 600;
const int HEIGHT = 400;

Vehicle::Vehicle(float x, float y)
{
	pos = new Vector2D(x, y);
	vel = new Vector2D(0, 0);
	acc = new Vector2D(0, 0);
	maxSpeed = 4;
	maxForce = 0.25f;
	r = 16;

	pursuit = new Vector2D(0, 0);

	save_vehicle = new Vector2D(0, 0);
	target = new Vector2D(0, 0);
	prediction = new Vector2D(0, 0);
	v3 = new Vector2D(0, 0);

	force = new Vector2D(0, 0);



	radian = 0;
	m_xy1 = new Vector2D(0, 0);
	m_xy2 = new Vector2D(0, 0);
	m_xy3 = new Vector2D(0, 0);
}

/*
Vector2D Vehicle::evade(Vehicle* vehicle)
{
	*pursuit = pursue(vehicle);
	*pursuit *= -1;

	return *pursuit;
}
*/

Vector2D Vehicle::pursue(Vehicle* vehicle)
{
	*save_vehicle = *vehicle->pos;

	*target = *vehicle->pos;
	*prediction = *vehicle->vel;

	*v3 = *target - *pos;
	float v3_mag = v3->length();
	*prediction *= v3_mag / 10;

	*target += *prediction;
	/*
	stroke(255);
    line(vehicle.pos.x, vehicle.pos.y, target.x, target.y);
    fill(127);
    circle(target.x, target.y, 16);
	*/

	return seek(target);
}

Vector2D Vehicle::flee(Vector2D* target)
{
	return seek(target) * -1;
}

Vector2D Vehicle::seek(Vector2D* target)
{
	*force = *target - *pos;
	force->normalize();
	*force *= maxSpeed;
	*force -= *vel;
	force->limit(maxForce);

	return *force;
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
	*vel += *acc;
	vel->limit(maxSpeed);
	*pos += *vel;
	*acc *= 0;

	edges();
	radian = atan2(vel->getY(), vel->getX());
	*m_xy1 = rotate(-r, -r / 2, radian);
	*m_xy2 = rotate(-r, r / 2, radian);
	*m_xy3 = rotate(r, 0, radian);
}

void Vehicle::draw(SDL_Renderer* renderer)
{
	filledTrigonRGBA(renderer,
		m_xy1->getX() + pos->getX(), m_xy1->getY() + pos->getY(),
		m_xy2->getX() + pos->getX(), m_xy2->getY() + pos->getY(),
		m_xy3->getX() + pos->getX(), m_xy3->getY() + pos->getY(),
		255, 255, 255, 255);

	lineRGBA(renderer,
		save_vehicle->getX(), save_vehicle->getY(),
		target->getX(), target->getY(),
		255, 255, 255, 255);
	lineRGBA(renderer, 
		pos->getX(), pos->getY(), 
		target->getX(), target->getY(), 0, 255, 0, 255);

	filledCircleRGBA(renderer,
		target->getX(), target->getY(),
		16,
		128, 128, 128, 255);
}