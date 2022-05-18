#pragma once

#include "Vector2D.h"
#include "main.h"

class Vehicle
{
public:
	Vehicle(float x, float y);
	//Vector2D evade(Vehicle* vehicle);
	Vector2D pursue(Vehicle* vehicle);
	Vector2D flee(Vector2D* target);
	Vector2D seek(Vector2D* target);
	void applyForce(Vector2D* force);
	void edges();
	void update();
	void draw(SDL_Renderer* renderer);

	Vector2D getPos() { return *pos; }
	float getR() { return r; }



	Vector2D rotate(float _x, float _y, float rad);

protected:
	Vector2D* pos;
	Vector2D* vel;
	Vector2D* acc;
	float maxSpeed, maxForce, r;

	Vector2D* pursuit;

	Vector2D* save_vehicle;
	Vector2D* target;
	Vector2D* prediction;
	Vector2D* v3;

	Vector2D* force;



	double radian;
	Vector2D* m_xy1;
	Vector2D* m_xy2;
	Vector2D* m_xy3;
};