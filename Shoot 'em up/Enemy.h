#include <SFML/Graphics.hpp>
using namespace sf;

class Enemy : public Entity {
private:
	// Скорость движения противника
	float speed = 0.1;

	// Булева переменная, определяющая взрывается ли объект
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

	// метод обновления противника 
	void update(float time) {
		if (!explodes)
			move(0, speed*time);
		else
			explosion(time);
	}

	// Проверить - взрывается ли в данный момент?
	const bool isExplodes() const {
		return explodes;
	}

	// Первод противника в состояние подбит (взрывается)
	void blowUp() {
		explodes = true;
	}
};
