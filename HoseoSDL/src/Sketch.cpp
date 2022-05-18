#include "Sketch.h"
#include <random>

#include <iostream>

const int WIDTH = 600;
const int HEIGHT = 400;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> _x(0, 600);
std::uniform_int_distribution<int> _y(0, 400);

Sketch::Sketch()
{
	pursuer = new Vehicle(50, 50);
	target = new Target(WIDTH - 50, HEIGHT - 50);

	steering = new Vector2D(0, 0);
	d = new Vector2D(0, 0);

	d_value = 0;
}

void Sketch::update()
{
	*steering = pursuer->pursue(target);
	pursuer->applyForce(steering);

	*d = pursuer->getPos() - target->getPos();
	d_value = d->length();

	if (d_value < pursuer->getR() + target->getR())
	{
		target = new Target(_x(gen), _y(gen));
		// pursuer.pos.set(width / 2, height / 2);
	}

	pursuer->update();

	target->update();
	target->applyForce(steering);
}

void Sketch::draw(SDL_Renderer* renderer)
{
	pursuer->draw(renderer);
	target->draw(renderer);
}