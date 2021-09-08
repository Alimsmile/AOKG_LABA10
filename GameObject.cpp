#include "GameObject.h"

// конструктор
GameObject::GameObject()
{
	position = ivec2(0, 0);
	sost = MoveDirection::STOP;
	progress = 0.0;
}

// установка используемого графического объекта
// происходит копирование переданного объекта дл€ последующего использовани€
void GameObject::setGraphicObject(const GraphicObject& graphicObject)
{
	this->graphicObject = graphicObject;
}

// установка логических координат (два перегруженных метода дл€ удобства)
void GameObject::setPosition(int x, int y)
{
	if (x < 21 && y < 21)
	{
		position = ivec2(x, y);
		graphicObject.setPosition(vec3(-10 + position.x, 0.5, -10 + position.y));
	}
}

void GameObject::setPosition(ivec2 position)
{
	if (position.x < 21 && position.y < 21)
	{
		this->position = position;
		graphicObject.setPosition(vec3(-10 + this->position.x, 0.5, -10 + this->position.y));
	}
}

// получение текущих логических координат
ivec2 GameObject::getPosition()
{
	return position;
}

// начать движение в выбранном направлении с указанной скоростью
// скорость передвижени€ определ€етс€ количеством клеток в секунду
void GameObject::move(MoveDirection direction, float speed)
{
	if (progress != 0) return;
	sost = direction;
	this->speed = speed;

}

	// проверка на то, что объект в насто€щий момент движетс€
bool GameObject::isMoving()
{
	return ((sost != MoveDirection::STOP) || (progress != 0));
}

// симул€ци€ игрового объекта (плавное перемещение объекта)
// метод вызываетс€ непрерывно в функции simulation
void GameObject::simulate(float sec)
{
	float dx = 0.0;
	float dy = 0.0;

	switch (sost)
	{
	case MoveDirection::STOP:
	{
		return;
	}; break;
	case MoveDirection::LEFT:
	{
		dx = -progress;
	}; break;
	case MoveDirection::RIGHT:
	{
		dx = progress;
	}; break;
	case MoveDirection::UP:
	{
		dy = -progress;
	}; break;
	case MoveDirection::DOWN:
	{
		dy = progress;
	}; break;
	default:
	{
		std::cout << "Error GameObject::simulate(0)!" << std::endl;
	}
	break;
	}
	progress += sec * speed;
	if (progress >= 1.0)
	{
		// ”становка новых логических координат
		switch (sost)
		{
		case MoveDirection::LEFT:
		{
			position = ivec2(getPosition().x - 1, getPosition().y);
		}; break;
		case MoveDirection::RIGHT:
		{
			position = ivec2(getPosition().x + 1, getPosition().y);
		}; break;
		case MoveDirection::UP:
		{
			position = ivec2(getPosition().x, getPosition().y - 1);
		}; break;
		case MoveDirection::DOWN:
		{
			position = ivec2(getPosition().x, getPosition().y + 1);
		}; break;
		default:
		{
			std::cout << "Error GameObject::simulate(1)!" << std::endl;
		}
		break;
		}
		progress = 0.0;
		sost = MoveDirection::STOP;
		setPosition(position);
	}
	else
	{
		graphicObject.setPosition(vec3(-10 + position.x + dx, 0.5, -10 + position.y + dy));
	}
}

// вывод игрового объекта на экран
void GameObject::draw(void)
{
	graphicObject.draw();
}