#include <SFML/Graphics.hpp>
using namespace sf;

class background : public Drawable, public Transformable {
private:
	// виртуальный метод draw, чтобы рисовать сами объекты, а не их спрайты
	virtual void draw(RenderTarget& target, RenderStates states) const
	{
		states.transform *= getTransform();
		states.texture = &back;
		target.draw(m_vertices, states);
	}

	// Массив с контурами блоков фона
	VertexArray m_vertices;
	// Текстура фона
	Texture back;

	// текущий кадр и скорость прокрутки карты
	float currentFrame = 0;
	float speed_scrolling = 0.15;

public:
	// конструктор класса
	background(std::string path) {
		// Загружаем тектсуру
		back.loadFromFile("images\\" + path);
		// инициализируем массив точек так, чтобы они описывали 2 прямоугольника (8 точек)
		m_vertices.setPrimitiveType(Quads);
		m_vertices.resize(8);


		// Устанавливаем текстуру первого прямоугольника, как весь фон
		m_vertices[0].texCoords = Vector2f(0, 0);
		m_vertices[1].texCoords = Vector2f(back.getSize().x, 0);
		m_vertices[2].texCoords = Vector2f(back.getSize().x, back.getSize().y);
		m_vertices[3].texCoords = Vector2f(0, back.getSize().y);
		// Устанавливаем её на экране во весь размер
		m_vertices[0].position = Vector2f(0, 0);
		m_vertices[1].position = Vector2f(back.getSize().x, 0);
		m_vertices[2].position = Vector2f(back.getSize().x, back.getSize().y);
		m_vertices[3].position = Vector2f(0, back.getSize().y);

		// Устанавливаем текстуру второго прямоугольника, как весь фон
		m_vertices[4].texCoords = Vector2f(0, back.getSize().y);
		m_vertices[5].texCoords = Vector2f(back.getSize().x, back.getSize().y);
		m_vertices[6].texCoords = Vector2f(back.getSize().x, back.getSize().y);
		m_vertices[7].texCoords = Vector2f(0, back.getSize().y);
		// Устанавливаем её на экране впритык к верхней горизонтальной линии окна в виде линии шириной 0
		m_vertices[4].position = Vector2f(0, 0);
		m_vertices[5].position = Vector2f(back.getSize().x, 0);
		m_vertices[6].position = Vector2f(back.getSize().x, 0);
		m_vertices[7].position = Vector2f(0, 0);
	}

	void addSpeed() {
		speed_scrolling = speed_scrolling + 0.003;
	}

	float getSpeed()
	{
		return speed_scrolling;
	}

	void update(float time) {

		// Уменьшаем высоту текстуру первого прямоугольника на размер текущего кадра и одновременно уменьшаем его высоту в окне на такую же величину
		m_vertices[2].texCoords = Vector2f(back.getSize().x, back.getSize().y - int(currentFrame));
		m_vertices[3].texCoords = Vector2f(0, back.getSize().y - int(currentFrame));

		m_vertices[0].position = Vector2f(0, int(currentFrame));
		m_vertices[1].position = Vector2f(back.getSize().x, int(currentFrame));


		// устанавливаем текстуру 2ого прямоугольника, как полосу шириной currentFrame, начиная от нижнего края текстуры всего фона
		m_vertices[4].texCoords = Vector2f(0, back.getSize().y - int(currentFrame));
		m_vertices[5].texCoords = Vector2f(back.getSize().x, back.getSize().y - int(currentFrame));
		// Увеличиваем высоту этой текстуры в окне так, чтобы она стала так же currentFrame
		m_vertices[6].position = Vector2f(back.getSize().x, int(currentFrame));
		m_vertices[7].position = Vector2f(0, int(currentFrame));

		// Изменяем значение текущего кадра
		if (currentFrame <= back.getSize().y)
			currentFrame = currentFrame + speed_scrolling * time;
		else
			currentFrame = 0;
	}
};
