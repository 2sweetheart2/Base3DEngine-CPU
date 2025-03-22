#include "MathUtils.h"



int main()
{
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antiAliasingLevel = 3;
	settings.majorVersion = 3;
	settings.minorVersion = 0;
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode({ 800, 600 }), "Rotating Cube", sf::State::Windowed, settings);
	sf::Vector2i windowCenter(window.getSize().x / 2, window.getSize().y / 2);

	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	Cube cube;
	Vector3 v;
	v = v * 3;
	

	while (window.isOpen()) {
	
	
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) window.close();
		}		
		
		window.clear(sf::Color(100, 100, 100));

		cube.Draw(window);

		window.display();
	}
	return 0;
}
