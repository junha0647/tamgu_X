#include "Sketch.h"
#include "InputHandler.h"

Sketch::Sketch()
{
	target = new Vector2D(0, 0);
	vehicle = new Vehicle(100, 100);

	steering = new Vector2D(0, 0);
}

void Sketch::update()
{
	target = TheInputHandler::Instance()->getMousePosition();

	*steering = vehicle->arrive(target);
	vehicle->applyForce(steering);
	vehicle->update();
}

void Sketch::draw(SDL_Renderer* renderer)
{
	filledCircleColor(renderer,
		target->getX(), target->getY(), 16,
		0xFF0000FF);

	vehicle->show(renderer);
}