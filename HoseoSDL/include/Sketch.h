#pragma once

#include "Vehicle.h"
#include "Vector2D.h"

class Sketch
{
public:
	Sketch();
	void update();
	void draw(SDL_Renderer* renderer);

private:
	Vector2D* target;
	Vehicle* vehicle;

	Vector2D* steering;
};