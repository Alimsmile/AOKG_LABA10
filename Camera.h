#pragma once

#include <windows.h>
#include <iostream>
#include <vector>

#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;
// КЛАСС ДЛЯ РАБОТЫ С КАМЕРОЙ
class Camera
{
public:
	// конструкторы
	Camera();
	Camera(vec3 position);
	Camera(float x, float y, float z);

	// установка и получение позиции камеры
	void setPosition(vec3 position);
	vec3 getPosition();

	//функции для перемещения камеры
	void rotateLeftRight(float degree);
	void rotateUpDown(float degree);
	void zoomInOut(float distance);

	// функция для установки матрицы камеры
	void apply();

private:
	// перерасчет позиции камеры после поворотов
	void recalculatePosition();

private:
	// радиус и углы поворота
	float r;
	float angleX;
	float angleY;

	// позиция камеры
	vec3 position;
};