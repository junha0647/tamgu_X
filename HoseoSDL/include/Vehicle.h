#pragma once

#include "Vector2D.h"
#include "main.h"

class Vehicle
{
public:
	Vehicle(float x, float y);
	Vector2D arrive(Vector2D* target);
	Vector2D seek(Vector2D* target, bool arrival);
	void applyForce(Vector2D* force);
	void edges();
	Vector2D rotate(float _x, float _y, float rad);
	void update();
	void show(SDL_Renderer* renderer);

private:
	Vector2D* pos;
	Vector2D* vel;
	Vector2D* acc;
	float maxSpeed;
	float maxForce;
	float r;

	double radian;
	Vector2D* m_xy1;
	Vector2D* m_xy2;
	Vector2D* m_xy3;

	Vector2D* force;
	float desiredSpeed;
	int slowRadius;
	float distance;
};