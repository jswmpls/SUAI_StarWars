#include "Player.h"
#include "Obstacles.h"

#include <SFML/Graphics.hpp>
#include <Math.h>

using namespace sf;
using namespace std;

int main()
{
	RenderWindow window(VideoMode(700, 900), L"Звёздный защитник!"); //Создание окна
	Image icon; //Установка иконки для окна
	icon.loadFromFile("Image/icon.png");
	window.setIcon(33, 32, icon.getPixelsPtr());

	//Фон
	Texture textureSpace;
	textureSpace.loadFromFile("Image/kosmo.png");
	RectangleShape gamingBackground(Vector2f(700, 900));
	gamingBackground.setTexture(&textureSpace);

	//космический корабль
	Player player (330, 500, "Image/ship.png");
	Obstacles obstacles(330, 500, "Image/obstacles.png");

	//Bullets
	vector<CircleShape> bullets;
	vector<float> angles;

	Clock clock;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds(); //Время 
		time /= 800;
		clock.restart();

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)) //Закрытие окна
				window.close();
		}

		if (Mouse::isButtonPressed(Mouse::Left)) {
			bullets.push_back(CircleShape());
			bullets.back().setRadius(5);
			bullets.back().setOrigin(5, 5);
			bullets.back().setPosition(player.sprite.getPosition().x + 50, player.sprite.getPosition().y);

			angles.push_back(atan2(Mouse::getPosition(window).y - player.sprite.getPosition().y, 
								   Mouse::getPosition(window).x - player.sprite.getPosition().x));

			
		}

		//Фон
		window.clear();
		window.draw(gamingBackground);

		//Персонаж 
		player.playerMove(time);
		window.draw(player.sprite); //Rendering

		for (int i = 0; i < bullets.size(); i++) {
			window.draw(bullets[i]);
			bullets[i].move(0, 5 * sin(angles[i]));
		}

		obstacles.update(player, window, time);

		window.display();
	}

	return 0;
}