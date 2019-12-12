#include <SFML/Graphics.hpp>
using namespace sf;

class background : public Drawable, public Transformable {
private:
	// ����������� ����� draw, ����� �������� ���� �������, � �� �� �������
	virtual void draw(RenderTarget& target, RenderStates states) const
	{
		states.transform *= getTransform();
		states.texture = &back;
		target.draw(m_vertices, states);
	}

	// ������ � ��������� ������ ����
	VertexArray m_vertices;
	// �������� ����
	Texture back;

	// ������� ���� � �������� ��������� �����
	float currentFrame = 0;
	float speed_scrolling = 0.15;

public:
	// ����������� ������
	background(std::string path) {
		// ��������� ��������
		back.loadFromFile("images\\" + path);
		// �������������� ������ ����� ���, ����� ��� ��������� 2 �������������� (8 �����)
		m_vertices.setPrimitiveType(Quads);
		m_vertices.resize(8);


		// ������������� �������� ������� ��������������, ��� ���� ���
		m_vertices[0].texCoords = Vector2f(0, 0);
		m_vertices[1].texCoords = Vector2f(back.getSize().x, 0);
		m_vertices[2].texCoords = Vector2f(back.getSize().x, back.getSize().y);
		m_vertices[3].texCoords = Vector2f(0, back.getSize().y);
		// ������������� � �� ������ �� ���� ������
		m_vertices[0].position = Vector2f(0, 0);
		m_vertices[1].position = Vector2f(back.getSize().x, 0);
		m_vertices[2].position = Vector2f(back.getSize().x, back.getSize().y);
		m_vertices[3].position = Vector2f(0, back.getSize().y);

		// ������������� �������� ������� ��������������, ��� ���� ���
		m_vertices[4].texCoords = Vector2f(0, back.getSize().y);
		m_vertices[5].texCoords = Vector2f(back.getSize().x, back.getSize().y);
		m_vertices[6].texCoords = Vector2f(back.getSize().x, back.getSize().y);
		m_vertices[7].texCoords = Vector2f(0, back.getSize().y);
		// ������������� � �� ������ ������� � ������� �������������� ����� ���� � ���� ����� ������� 0
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

		// ��������� ������ �������� ������� �������������� �� ������ �������� ����� � ������������ ��������� ��� ������ � ���� �� ����� �� ��������
		m_vertices[2].texCoords = Vector2f(back.getSize().x, back.getSize().y - int(currentFrame));
		m_vertices[3].texCoords = Vector2f(0, back.getSize().y - int(currentFrame));

		m_vertices[0].position = Vector2f(0, int(currentFrame));
		m_vertices[1].position = Vector2f(back.getSize().x, int(currentFrame));


		// ������������� �������� 2��� ��������������, ��� ������ ������� currentFrame, ������� �� ������� ���� �������� ����� ����
		m_vertices[4].texCoords = Vector2f(0, back.getSize().y - int(currentFrame));
		m_vertices[5].texCoords = Vector2f(back.getSize().x, back.getSize().y - int(currentFrame));
		// ����������� ������ ���� �������� � ���� ���, ����� ��� ����� ��� �� currentFrame
		m_vertices[6].position = Vector2f(back.getSize().x, int(currentFrame));
		m_vertices[7].position = Vector2f(0, int(currentFrame));

		// �������� �������� �������� �����
		if (currentFrame <= back.getSize().y)
			currentFrame = currentFrame + speed_scrolling * time;
		else
			currentFrame = 0;
	}
};
