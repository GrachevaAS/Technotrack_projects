#include <SFML/Audio.hpp>
#include <limits>
#include <iostream>
//#include <SFML/Time.hpp>
#include<math.h>

int main() {
	sf::SoundBuffer buffer;
	const _int16 INF = INT16_MAX;
	const double PI = 3.1415926535897932384626433832795;
	_int16* awfulNoise = new _int16[100000];
	for (int i = 0; i < 100000; i++) {
		awfulNoise[i] = static_cast<_int16>(round(sin((i % 100) / 100.0 * 2 * PI) * INF));
	}
	buffer.loadFromSamples(const_cast<const _int16*>(awfulNoise), 100000, 1, 44100);
	std::cout << buffer.getDuration().asSeconds();
	sf::Sound sound1;
	sound1.setBuffer(buffer);
	sound1.play();
	system("pause");
}

//#include <SFML/Graphics.hpp>
//
//int main()
//{
//	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
//	sf::CircleShape shape(100.f);
//	shape.setFillColor(sf::Color::Green);
//
//	while (window.isOpen())
//	{
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//				window.close();
//		}
//
//		window.clear();
//		window.draw(shape);
//		window.display();
//	}
//
//	return 0;
//}