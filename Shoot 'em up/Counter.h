#include <SFML/Graphics.hpp>
#include <sstream>
using namespace sf;


class Counter {
private:
	Font font;
	Text text;

	// ���� ����� � ����
	int currentCount;
	// ������ ����
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
		// ���� ������� ������ �������������
		if (currentCount > maxCount)
			// ������������ �������������
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
		// L ��������� �� ��, ��� ��� Unicode ������
		String str = L"������� ���������: " + ss.str();
		text.setString(str);
		return text;
	}
};
