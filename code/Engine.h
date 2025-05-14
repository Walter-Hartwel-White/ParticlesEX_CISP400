#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include "Particle.h"
using namespace sf;
using namespace std;

int const NUM_PARTICLES = 5;

class Engine
{
private:
	// A regular RenderWindow
	RenderWindow m_Window;

	//vector for Particles
	vector<Particle> m_particles;
	vector<Sprite> graphics;

	// Private functions for internal use only
	void input();
	void update(float dtAsSeconds);
	void draw();
	void particlePopulator(int x, int y);

public:
	// The Engine constructor
	Engine();

	// Run will call all the private functions
	void run();

};