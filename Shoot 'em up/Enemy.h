#include <SFML/Graphics.hpp>
using namespace sf;

class Enemy : public Entity {
private:
	// �������� �������� ����������
	float speed = 0.1;

	// ������ ����������, ������������ ���������� �� ������
	bool explodes = false;

public:
	Enemy(IntRect rect, float newSpeed) : Entity(rect) {
		speed = newSpeed - 0.05;
	}
	~Enemy() {
	}

	void setSpeed(float speed) {
		this->speed = speed;
	}

	// ����� ���������� ���������� 
	void update(float time) {
		if (!explodes)
			move(0, speed*time);
		else
			explosion(time);
	}

	// ��������� - ���������� �� � ������ ������?
	const bool isExplodes() const {
		return explodes;
	}

	// ������ ���������� � ��������� ������ (����������)
	void blowUp() {
		explodes = true;
	}
};
