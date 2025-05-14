#include "Engine.h"
#include "Particle.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

void Engine::particlePopulator(int x, int y) {
	Vector2i coor;
	coor.x = x; coor.y = y;

	for (int i = 0; i < NUM_PARTICLES; i++) {
		Particle particle(m_Window, rand() % 50 + 25, coor);
		m_particles.push_back(particle);
	}
}

Engine::Engine() {
	VideoMode vm(sf::VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height);
	m_Window.create(vm, "wowzers", Style::Default);
}

void Engine::run() {
	sf::Clock clock;
	float dt;
	Particle particle();

	Texture textureBackground;
	textureBackground.loadFromFile("graphics/Heimerdingus.png"); //"C:/Users/mxleo/source/repos/Particles/graphics/Heimerdingus.png");

	Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);
	spriteBackground.setPosition(46, -46);
	graphics.push_back(spriteBackground);

	Texture textureKeys;
	textureKeys.loadFromFile("graphics/BIG_ARROW_KESY.png");
	Sprite arrowKeys;
	arrowKeys.setTexture(textureKeys);
	arrowKeys.setPosition(700, 20);
	graphics.push_back(arrowKeys);

	//moving arrow keys
	Texture mapText;
	mapText.loadFromFile("graphics/part1.png");
	Sprite map;
	map.setTexture(mapText);
	map.setPosition(700, 525);
	graphics.push_back(map);

	float mapSpeed = 197.0;

	//music
	sf::Music music;
	music.openFromFile("sound/A Big Upgrade.wav");
	music.play();

	//unit testing
		std::cout << "Starting Particle unit tests..." << endl;
		Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
		p.unitTests();
		std::cout << "Unit tests complete.  Starting engine..." << endl;

	while (m_Window.isOpen()) {
		sf::Time dt = clock.restart();

		graphics.at(2).setPosition(
			graphics.at(2).getPosition().x,
			graphics.at(2).getPosition().y - (mapSpeed * dt.asSeconds()));

		input();
		update(dt.asSeconds());
		draw();
	}
}

void Engine::input() {
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		m_Window.close();
	}

	Event event;
	while (m_Window.pollEvent(event)) {
		if (event.type == Event::Closed) m_Window.close();

		if (event.type == Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == Mouse::Left) {
				particlePopulator(event.mouseButton.x, event.mouseButton.y);
			}
			//cout << event.mouseButton.x << " " << event.mouseButton.y << endl;
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
			particlePopulator(1163, 89);
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
			particlePopulator(752, 89);
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
			particlePopulator(1018, 89);
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) {
			particlePopulator(899, 89);
		}
	}
}

void Engine::update(float dtAsSeconds) {
	for (auto thingers = m_particles.begin(); thingers != m_particles.end(); ) {
		if ((*thingers).getTTL() > 0.0) {
			(*thingers).update(dtAsSeconds);
			++thingers;
		}
		else {
			thingers = m_particles.erase(thingers);
		}
	}
}

void Engine::draw() {
	m_Window.clear();
	for (Sprite s : graphics) {
		m_Window.draw(s);
	}

	for (int i = 0; i < m_particles.size(); i++) m_Window.draw(m_particles.at(i));
	m_Window.display();
}