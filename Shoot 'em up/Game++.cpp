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
	// Часы ответсвенные за подсчёт времени работы одного кадра
	Clock clock;

	// Кнопка играть и её инициализация
	Sprite play;
	play.setTexture(texture);
	play.setTextureRect(IntRect(2, 936, 392, 90));
	play.setPosition(W/2  - play.getGlobalBounds().width/2, H/2 - play.getGlobalBounds().height);
	
	// Кнопка выход и её инициализация
	Sprite exit;
	exit.setTexture(texture);
	exit.setTextureRect(IntRect(397, 936, 392, 90));
	exit.setPosition(W / 2 - exit.getGlobalBounds().width / 2, H / 2 + exit.getGlobalBounds().height);

	// Обявление  фона, только уже для меню
	background bg("background.jpg");



	while (Game.isOpen())
	{
		// Обновляем значение времени прошедшего за кадр
		float time = clock.restart().asMicroseconds();
		time /= 800;

		// Проходим пул событий связанный с окном программы
		Event event;
		while (Game.pollEvent(event))
		{
			if (event.type == Event::MouseButtonPressed)
				if (event.key.code == Mouse::Left)
				{
					// Проучаем координаты мышки относительно окна игры
					Vector2i mousePosition = Mouse::getPosition(Game);
					// если нажали на кнопку играть
					if (play.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
					{
						// возращаем занчение screen соответствующее началу игры
						return 1;
					}
					// если нажали на кнопку выход
					if (exit.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
					{
						// возращаем занчение screen соответствующее выходу из игры
						return -2;
					}
				}
			if (event.type == Event::Closed) // возращаем занчение screen соответствующее выходу из игры
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
	// Часы ответсвенные за подсчёт времени работы одного кадра
	Clock clock;

	// Часы ответсвенные за подсчёт времени с момента генерации последнего врага
	Clock en;
	// Время в секундах до появления следующего противника
	float createEnemy = 2;

	
	// Инициализируем генератор случайных чисел и создаём дистанцию для него
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(100, W - 200);

	// Количество врагов, которое должно появиться за уровень
	int countEnemies = 27;
	
	// Лист, в котором мы храним врагов, которые находятся В ДАННЫЙ МОМЕНТ в игре
	std::list<Enemy*> enemies;

	// Инициализация самого игрока
	// в setOutline() передаются координаты точек, описывающий границы спрайта объекта
	Player player(IntRect(1, 130, 128, 117));
	player.setOutline({ Vector2f(117, 49), Vector2f(102, 46), Vector2f(84, 28), Vector2f(77, 15), Vector2f(66, 0), Vector2f(61, 0), Vector2f(50, 15), Vector2f(43, 28), Vector2f(25, 46), Vector2f(10, 49), Vector2f(0, 60), Vector2f(0, 102), Vector2f(32, 102), Vector2f(40, 116), Vector2f(64, 88), Vector2f(87, 116), Vector2f(95, 102), Vector2f(127, 102), Vector2f(127, 60), Vector2f(117, 49) });
	player.setPosition(W / 2 - 64, H - 200);

	// иницил. объект класса для движущегося фона
	background bg("background.jpg");

	// Время прошедшее с последнего ускорения 
	float timeAfterAcceleration = 0;

	// подключение оконки в SFML
	while (Game.isOpen())
	{
		// Обновляем значение времени прошедшего за кадр
		float time = clock.restart().asMicroseconds();
		timeAfterAcceleration += time;
		time /= 800;

		// Проходим пул событий связанный с окном программы
		Event event;
		while (Game.pollEvent(event))
		{
			if (event.type == Event::Closed) // возращаем занчение screen соответствующее выходу из игры
				return -2;
		}

		// ускорение каждую секунду
		if (timeAfterAcceleration >= 1000000)
		{
			bg.addSpeed();
			timeAfterAcceleration = 0;
		}

		// Добавляем противника в лист(создаём его), если мы ещё не создали всех возможных противников 
		// и прошло достаточно времени с создания предыдущего противника
		if (countEnemies > 0 && en.getElapsedTime().asSeconds() >= createEnemy)
		{
			// Перезапускаем часы
			en.restart();
			// Уменьшаем время до появления новго противника
			createEnemy -= 0.1;
			// Уменьшаем кол-во потенциальных противников на этом уровне
			countEnemies--;

			if (countEnemies == 0)
			{
				countEnemies = 27;
				createEnemy = 3;
			}

			// создаём ссылку на объект класса противника, передав в конструктор класса в качестве параметра положение
			// спрайта на тайлсете
			enemies.push_back(new Enemy (IntRect(0, 0, 112, 116), bg.getSpeed()));

			// Выставляем контуры и позицию противнка
			(*enemies.back()).setOutline({ Vector2f(90, 48), Vector2f(111, 0), Vector2f(60, 11), Vector2f(51, 11), Vector2f(0, 0), Vector2f(21, 49), Vector2f(50, 114), Vector2f(61, 114), Vector2f(90, 48) });
			(*enemies.back()).setPosition(dist(gen), -(*enemies.back()).getHeight()/**-enemy_size.y**/);
			
		}

		// Проходимся по списку созданных противников
		for (std::list<Enemy*>::iterator e = enemies.begin(); e != enemies.end(); e++)
		{
			// для каждого противника проходимся по списку всех выпущенных пуль
			for (std::list<Bullet*>::iterator bu = player.bullets.begin(); bu != player.bullets.end(); bu++)
			{
				// Если контуры спрайта пули и спрайта противника пересеклись
				if ((*e)->intersects((*bu)->getOutline()))
				{
					// противник переходит в состояние взрыва
					(*e)->blowUp();
					
						

					// Пуля уничтожается
					(*bu)->die();
					// счёт увеличивается
					counter.addCount();
				}
			}
			// для каждлого противника проверяем пересекается ли он с игроком
			if ((*e)->intersects(player.getOutline()))
			{
				// Противник переходит в состояние взрыва
				(*e)->blowUp();
		
				// игрок переходит в состояние взрыва
				player.blowUp();
			}
		}

		// Обновляем игрока, фон и счётчик
		player.control(time);
		bg.update(time);
		counter.update();

		// Если игрок умер - выходим в меню
		if (!player.isLife())
		{
			counter.currentCountClear();
			return -1;
		}
			


		// Очищаем старые рисунки
		Game.clear();
		// Рисуем фон
		Game.draw(bg);
		// Рисуем игрока
		Game.draw(player);
		// Проходим по листу пуль, обновляем их и прорисовываем
		for (std::list<Bullet*>::iterator it = player.bullets.begin(); it != player.bullets.end();)
		{
			// обновление и прорисовка
			(*it)->update(time);
			Game.draw(**it);

			// Если пуля уже не жива или она вшла за границы окна
			if (!(*it)->isLife() || (*it)->getPosition().y + (*it)->getHeight() < 0)
			{
				// Удаляем объект данной пули
				delete *it;
				// удаляем указатель на объект данной пули и передаём итератор следующей по порядку пуле
				it = player.bullets.erase(it);
			}
			else // иначе переходим к следующей пуле
				it++;

			// если мы удалили пулю, а она была последней - выходим из цикла
			if (player.bullets.empty()) break;
		}
		// Проводим децствия, анологичные действиям с пулей
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
		// выводлим текущий счёт
		Game.draw(counter.getCurrentCount());

		// Выводим всё, что нарисовали на экран
		Game.display();
	}
	return -2;
}




int main()
{	
	// Подгружаем изображение с текстурами 
	Image image;
	image.loadFromFile("images\\TileSet.png");

	// создаём текстуру на основе данного изображения 
	texture.loadFromImage(image);

	Counter counter("9303.ttf");

	// Инициализируем окно игры
	RenderWindow Game(VideoMode(W, H), "CosmoStriker");

	/*Меню: -1; Игра: 1; Выход: -2;*/
	int screen = -1;

		
	Music music;//создаем объект музыки
	music.openFromFile("music.ogg");//загружаем файл
	music.setVolume(7);
	music.play();//воспроизводим музыку



	// С помощью данного цикла реализованно переключение между меню и игрой
	// Функции menu() и level() возвращают значение, которое соответсвует тому, куда хочет перейти пользователь
	// (см. комментарий к screen)
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
	
	// закрытие она в случае, если мы вышли из цикла
	if (Game.isOpen())
		Game.close();

	return 0;
}