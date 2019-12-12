#include <SFML/Graphics.hpp>
#include <sstream>
using namespace sf;


class Counter {
private:
	Font font;
	Text text;

	// счёт прямо в игре
	int currentCount;
	// Лучший счёт
	int maxCount;
public:
	Counter(std::string path) {
		font.loadFromFile("fonts\\" + path);
		text.setFont(font);
		text.setPosition(10, 5);
		text.setCharacterSize(30);
		text.setFillColor(Color::Red);
		text.setStyle(Text::Bold);

		currentCount = 0;
		maxCount = 0;
	}

	void addCount() {
		currentCount++;
	}
	void update() {
		// Если текущий больше максимального
		if (currentCount > maxCount)
			// максимальный увеличивается
			maxCount = currentCount;
	}

	void currentCountClear() {
		currentCount = 0;
	}

	Text getCurrentCount() {
		std::stringstream ss;
		ss << currentCount;
		text.setString(ss.str());
		return text;
	}

	Text getMaxCount() {
		std::stringstream ss;
		ss << maxCount;
		// L указывает на то, что это Unicode строка
		String str = L"Прошлый результат: " + ss.str();
		text.setString(str);
		return text;
	}
};
