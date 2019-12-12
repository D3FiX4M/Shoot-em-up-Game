#include "global_variable.h"
#include "Entity.h"
#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "Background.h"
#include "Counter.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <random>
using namespace sf;


int menu(RenderWindow &Game, Counter &counter)
{
	// ���� ������������ �� ������� ������� ������ ������ �����
	Clock clock;

	// ������ ������ � � �������������
	Sprite play;
	play.setTexture(texture);
	play.setTextureRect(IntRect(2, 936, 392, 90));
	play.setPosition(W/2  - play.getGlobalBounds().width/2, H/2 - play.getGlobalBounds().height);
	
	// ������ ����� � � �������������
	Sprite exit;
	exit.setTexture(texture);
	exit.setTextureRect(IntRect(397, 936, 392, 90));
	exit.setPosition(W / 2 - exit.getGlobalBounds().width / 2, H / 2 + exit.getGlobalBounds().height);

	// ���������  ����, ������ ��� ��� ����
	background bg("background.jpg");



	while (Game.isOpen())
	{
		// ��������� �������� ������� ���������� �� ����
		float time = clock.restart().asMicroseconds();
		time /= 800;

		// �������� ��� ������� ��������� � ����� ���������
		Event event;
		while (Game.pollEvent(event))
		{
			if (event.type == Event::MouseButtonPressed)
				if (event.key.code == Mouse::Left)
				{
					// �������� ���������� ����� ������������ ���� ����
					Vector2i mousePosition = Mouse::getPosition(Game);
					// ���� ������ �� ������ ������
					if (play.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
					{
						// ��������� �������� screen ��������������� ������ ����
						return 1;
					}
					// ���� ������ �� ������ �����
					if (exit.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
					{
						// ��������� �������� screen ��������������� ������ �� ����
						return -2;
					}
				}
			if (event.type == Event::Closed) // ��������� �������� screen ��������������� ������ �� ����
				return -2;

		}
		bg.update(time);

		Game.clear();
		Game.draw(bg);
		Game.draw(play);
		Game.draw(exit);
		Game.draw(counter.getMaxCount());
		Game.display();
	}

	return -2;
	//something
}

int level(RenderWindow &Game, Counter &counter)
{
	// ���� ������������ �� ������� ������� ������ ������ �����
	Clock clock;

	// ���� ������������ �� ������� ������� � ������� ��������� ���������� �����
	Clock en;
	// ����� � �������� �� ��������� ���������� ����������
	float createEnemy = 2;

	
	// �������������� ��������� ��������� ����� � ������ ��������� ��� ����
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(100, W - 200);

	// ���������� ������, ������� ������ ��������� �� �������
	int countEnemies = 27;
	
	// ����, � ������� �� ������ ������, ������� ��������� � ������ ������ � ����
	std::list<Enemy*> enemies;

	// ������������� ������ ������
	// � setOutline() ���������� ���������� �����, ����������� ������� ������� �������
	Player player(IntRect(1, 130, 128, 117));
	player.setOutline({ Vector2f(117, 49), Vector2f(102, 46), Vector2f(84, 28), Vector2f(77, 15), Vector2f(66, 0), Vector2f(61, 0), Vector2f(50, 15), Vector2f(43, 28), Vector2f(25, 46), Vector2f(10, 49), Vector2f(0, 60), Vector2f(0, 102), Vector2f(32, 102), Vector2f(40, 116), Vector2f(64, 88), Vector2f(87, 116), Vector2f(95, 102), Vector2f(127, 102), Vector2f(127, 60), Vector2f(117, 49) });
	player.setPosition(W / 2 - 64, H - 200);

	// ������. ������ ������ ��� ����������� ����
	background bg("background.jpg");

	// ����� ��������� � ���������� ��������� 
	float timeAfterAcceleration = 0;

	// ����������� ������ � SFML
	while (Game.isOpen())
	{
		// ��������� �������� ������� ���������� �� ����
		float time = clock.restart().asMicroseconds();
		timeAfterAcceleration += time;
		time /= 800;

		// �������� ��� ������� ��������� � ����� ���������
		Event event;
		while (Game.pollEvent(event))
		{
			if (event.type == Event::Closed) // ��������� �������� screen ��������������� ������ �� ����
				return -2;
		}

		// ��������� ������ �������
		if (timeAfterAcceleration >= 1000000)
		{
			bg.addSpeed();
			timeAfterAcceleration = 0;
		}

		// ��������� ���������� � ����(������ ���), ���� �� ��� �� ������� ���� ��������� ����������� 
		// � ������ ���������� ������� � �������� ����������� ����������
		if (countEnemies > 0 && en.getElapsedTime().asSeconds() >= createEnemy)
		{
			// ������������� ����
			en.restart();
			// ��������� ����� �� ��������� ����� ����������
			createEnemy -= 0.1;
			// ��������� ���-�� ������������� ����������� �� ���� ������
			countEnemies--;

			if (countEnemies == 0)
			{
				countEnemies = 27;
				createEnemy = 3;
			}

			// ������ ������ �� ������ ������ ����������, ������� � ����������� ������ � �������� ��������� ���������
			// ������� �� ��������
			enemies.push_back(new Enemy (IntRect(0, 0, 112, 116), bg.getSpeed()));

			// ���������� ������� � ������� ���������
			(*enemies.back()).setOutline({ Vector2f(90, 48), Vector2f(111, 0), Vector2f(60, 11), Vector2f(51, 11), Vector2f(0, 0), Vector2f(21, 49), Vector2f(50, 114), Vector2f(61, 114), Vector2f(90, 48) });
			(*enemies.back()).setPosition(dist(gen), -(*enemies.back()).getHeight()/**-enemy_size.y**/);
			
		}

		// ���������� �� ������ ��������� �����������
		for (std::list<Enemy*>::iterator e = enemies.begin(); e != enemies.end(); e++)
		{
			// ��� ������� ���������� ���������� �� ������ ���� ���������� ����
			for (std::list<Bullet*>::iterator bu = player.bullets.begin(); bu != player.bullets.end(); bu++)
			{
				// ���� ������� ������� ���� � ������� ���������� �����������
				if ((*e)->intersects((*bu)->getOutline()))
				{
					// ��������� ��������� � ��������� ������
					(*e)->blowUp();
					
						

					// ���� ������������
					(*bu)->die();
					// ���� �������������
					counter.addCount();
				}
			}
			// ��� �������� ���������� ��������� ������������ �� �� � �������
			if ((*e)->intersects(player.getOutline()))
			{
				// ��������� ��������� � ��������� ������
				(*e)->blowUp();
		
				// ����� ��������� � ��������� ������
				player.blowUp();
			}
		}

		// ��������� ������, ��� � �������
		player.control(time);
		bg.update(time);
		counter.update();

		// ���� ����� ���� - ������� � ����
		if (!player.isLife())
		{
			counter.currentCountClear();
			return -1;
		}
			


		// ������� ������ �������
		Game.clear();
		// ������ ���
		Game.draw(bg);
		// ������ ������
		Game.draw(player);
		// �������� �� ����� ����, ��������� �� � �������������
		for (std::list<Bullet*>::iterator it = player.bullets.begin(); it != player.bullets.end();)
		{
			// ���������� � ����������
			(*it)->update(time);
			Game.draw(**it);

			// ���� ���� ��� �� ���� ��� ��� ���� �� ������� ����
			if (!(*it)->isLife() || (*it)->getPosition().y + (*it)->getHeight() < 0)
			{
				// ������� ������ ������ ����
				delete *it;
				// ������� ��������� �� ������ ������ ���� � ������� �������� ��������� �� ������� ����
				it = player.bullets.erase(it);
			}
			else // ����� ��������� � ��������� ����
				it++;

			// ���� �� ������� ����, � ��� ���� ��������� - ������� �� �����
			if (player.bullets.empty()) break;
		}
		// �������� ��������, ����������� ��������� � �����
		for (std::list<Enemy*>::iterator it = enemies.begin(); it != enemies.end();)
		{
			(*it)->update(time);
			Game.draw(**it);
			if (!(*it)->isLife() || (*it)->getPosition().y > H)
			{
				delete *it;
				it = enemies.erase(it);
			}
			else
				it++;

			if (enemies.empty()) { break; }
		}
		// �������� ������� ����
		Game.draw(counter.getCurrentCount());

		// ������� ��, ��� ���������� �� �����
		Game.display();
	}
	return -2;
}




int main()
{	
	// ���������� ����������� � ���������� 
	Image image;
	image.loadFromFile("images\\TileSet.png");

	// ������ �������� �� ������ ������� ����������� 
	texture.loadFromImage(image);

	Counter counter("9303.ttf");

	// �������������� ���� ����
	RenderWindow Game(VideoMode(W, H), "CosmoStriker");

	/*����: -1; ����: 1; �����: -2;*/
	int screen = -1;

		
	Music music;//������� ������ ������
	music.openFromFile("music.ogg");//��������� ����
	music.setVolume(7);
	music.play();//������������� ������



	// � ������� ������� ����� ������������ ������������ ����� ���� � �����
	// ������� menu() � level() ���������� ��������, ������� ������������ ����, ���� ����� ������� ������������
	// (��. ����������� � screen)
	while (screen != -2)
		switch (screen)
		{
		case -1:
			screen = menu(Game, counter);
			break;
		case 1:
			screen = level(Game, counter);
			break;
		default:
			break;
		}
	
	// �������� ��� � ������, ���� �� ����� �� �����
	if (Game.isOpen())
		Game.close();

	return 0;
}