#include "GameObject.h"

// �����������
GameObject::GameObject()
{
	position = ivec2(0, 0);
	sost = MoveDirection::STOP;
	progress = 0.0;
}

// ��������� ������������� ������������ �������
// ���������� ����������� ����������� ������� ��� ������������ �������������
void GameObject::setGraphicObject(const GraphicObject& graphicObject)
{
	this->graphicObject = graphicObject;
}

// ��������� ���������� ��������� (��� ������������� ������ ��� ��������)
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

// ��������� ������� ���������� ���������
ivec2 GameObject::getPosition()
{
	return position;
}

// ������ �������� � ��������� ����������� � ��������� ���������
// �������� ������������ ������������ ����������� ������ � �������
void GameObject::move(MoveDirection direction, float speed)
{
	if (progress != 0) return;
	sost = direction;
	this->speed = speed;

}

	// �������� �� ��, ��� ������ � ��������� ������ ��������
bool GameObject::isMoving()
{
	return ((sost != MoveDirection::STOP) || (progress != 0));
}

// ��������� �������� ������� (������� ����������� �������)
// ����� ���������� ���������� � ������� simulation
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
		// ��������� ����� ���������� ���������
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

// ����� �������� ������� �� �����
void GameObject::draw(void)
{
	graphicObject.draw();
}