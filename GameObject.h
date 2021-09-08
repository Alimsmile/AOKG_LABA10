#pragma once
#include <windows.h>
#include <vector>

#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GraphicObject.h"

// класс-перечисление для указания направления перемещения
enum class MoveDirection { STOP, LEFT, RIGHT, UP, DOWN };

// КЛАСС ДЛЯ ПРЕДСТАВЛЕНИЯ ИГРОВОГО ОБЪЕКТА
class GameObject
{
public:
	// конструктор
	GameObject();

	// установка используемого графического объекта
	// происходит копирование переданного объекта для последующего использования
	void setGraphicObject(const GraphicObject & graphicObject);

	// установка логических координат (два перегруженных метода для удобства)
	void setPosition(int x, int y);
	void setPosition(ivec2 position);

	// получение текущих логических координат
	ivec2 getPosition();

	// начать движение в выбранном направлении с указанной скоростью
	// скорость передвижения определяется количеством клеток в секунду
	void move(MoveDirection direction, float speed = 3.0f);

	// проверка на то, что объект в настоящий момент движется
	bool isMoving();

	// симуляция игрового объекта (плавное перемещение объекта)
	// метод вызывается непрерывно в функции simulation
	void simulate(float sec);

	// вывод игрового объекта на экран
	void draw(void);
private:
	// логические координаты игрового объекта
	glm::ivec2 position;
	// графический объект (для вывода на экран)
	GraphicObject graphicObject;
	// состояние объекта (заданное направление перемещения)
	MoveDirection sost;
	// прогресс в перемещении (от 0.0 до 1.0)
	float progress;
	// скорость перемещения
	float speed;
};

