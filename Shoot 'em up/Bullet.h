#include <SFML/Graphics.hpp>
using namespace sf;

class Bullet : public Entity {
private:
	// Скорость пули
	float speed = -0.5;

public:
	Bullet(IntRect rect) : Entity(rect) {
	}
	~Bullet() {
	}

	// функция обновления пули
	void update(float time) {
		move(0, speed * time);
	}
};
