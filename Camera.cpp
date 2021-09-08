#include "Camera.h"

// установка позиции камеры
void Camera::setPosition(vec3 position)
{
	// определяем радиус - расстояние от начала системы координат до заданной позиции
	r = length(position);
	// определяем вертикальный угол:
	// это угол между вектором из начала координат к наблюдателю (v1)
	// и проекцией этого вектора на горизонтальную плоскость (v2)
	// для определения угла используется скалярное произведение нормализованных векторов
	vec3 v1 = position;
	vec3 v2 = vec3(v1.x, 0, v1.z);
	float cos_y = dot(normalize(v1), normalize(v2));
	angleY = degrees(acos(cos_y));
	// аналогичным образом определяем горизонтальный угол:
	// это угол между проекцией (v2) и единичным вектором вдоль оси Ox
	float cos_x = dot(normalize(v2), glm::vec3(1, 0, 0));
	angleX = degrees(acos(cos_x));
	// пересчитываем позицию (для корректировок ошибок округления)
	recalculatePosition();
}

// получение позиции камеры
vec3 Camera::getPosition()
{
	return position;
}

// функция для установки матрицы камеры
void Camera::apply()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(position.x, position.y, position.z, 0, 0, 0, 0, 1, 0);
}

// конструкторы
Camera::Camera()
{
	position.x = 0;
	position.y = 0;
	position.z = 0;
	setPosition(position);
}

Camera::Camera(vec3 position)
{
	this->position = position;
	setPosition(this->position);
}

Camera::Camera(float x, float y, float z)
{
	position = vec3(x, y, z);
	setPosition(position);
}

// перерасчет позиции камеры после поворотов
void Camera::recalculatePosition()
{
	position.x = r * cos(radians(angleX)) * sin(radians(angleY));
	position.z = r * sin(radians(angleX)) * sin(radians(angleY));
	position.y = r * cos(radians(angleY));
}

//функции для перемещения камеры
void Camera::rotateLeftRight(float degree)
{ 
	angleX = angleX + degree;
	recalculatePosition();
}

void Camera::rotateUpDown(float degree)
{
	const float maxUpDegree = 85.0; // максимальный угол подъема
	const float minDownDegree = 5.0; // минимальный угол подъема

	angleY = angleY + degree;

	// проверка ограничений
	if (angleY <= minDownDegree) angleY = minDownDegree;
	if (angleY >= maxUpDegree) angleY = maxUpDegree;

	recalculatePosition();
}

void Camera::zoomInOut(float distance)
{
	const float maxDist = 50.0; // максимальное расстояние
	const float minDist = 1.0; // минимальное расстояние

	r = r + distance;

	// проверка ограничений
	if (r <= minDist) r = minDist;
	if (r >= maxDist) r = maxDist;

	recalculatePosition();
}