#include "Simulation.h"

int main()
{
	sf::Vector2u screenSize(800, 600);
	Simulation sim(screenSize);
	sim.run();
	return 0;
}