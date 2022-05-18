#pragma once

#include "Vehicle.h"
#include "Target.h"
#include "Vector2D.h"

class Sketch
{
public:
	Sketch();
	void update();
	void draw(SDL_Renderer* renderer);

private:
	Vehicle* pursuer;
	Target* target;

	Vector2D* steering;
	Vector2D* d;

	float d_value;
};