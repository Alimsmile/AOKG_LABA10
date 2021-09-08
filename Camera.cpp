#include "Camera.h"

// ��������� ������� ������
void Camera::setPosition(vec3 position)
{
	// ���������� ������ - ���������� �� ������ ������� ��������� �� �������� �������
	r = length(position);
	// ���������� ������������ ����:
	// ��� ���� ����� �������� �� ������ ��������� � ����������� (v1)
	// � ��������� ����� ������� �� �������������� ��������� (v2)
	// ��� ����������� ���� ������������ ��������� ������������ ��������������� ��������
	vec3 v1 = position;
	vec3 v2 = vec3(v1.x, 0, v1.z);
	float cos_y = dot(normalize(v1), normalize(v2));
	angleY = degrees(acos(cos_y));
	// ����������� ������� ���������� �������������� ����:
	// ��� ���� ����� ��������� (v2) � ��������� �������� ����� ��� Ox
	float cos_x = dot(normalize(v2), glm::vec3(1, 0, 0));
	angleX = degrees(acos(cos_x));
	// ������������� ������� (��� ������������� ������ ����������)
	recalculatePosition();
}

// ��������� ������� ������
vec3 Camera::getPosition()
{
	return position;
}

// ������� ��� ��������� ������� ������
void Camera::apply()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(position.x, position.y, position.z, 0, 0, 0, 0, 1, 0);
}

// ������������
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

// ���������� ������� ������ ����� ���������
void Camera::recalculatePosition()
{
	position.x = r * cos(radians(angleX)) * sin(radians(angleY));
	position.z = r * sin(radians(angleX)) * sin(radians(angleY));
	position.y = r * cos(radians(angleY));
}

//������� ��� ����������� ������
void Camera::rotateLeftRight(float degree)
{ 
	angleX = angleX + degree;
	recalculatePosition();
}

void Camera::rotateUpDown(float degree)
{
	const float maxUpDegree = 85.0; // ������������ ���� �������
	const float minDownDegree = 5.0; // ����������� ���� �������

	angleY = angleY + degree;

	// �������� �����������
	if (angleY <= minDownDegree) angleY = minDownDegree;
	if (angleY >= maxUpDegree) angleY = maxUpDegree;

	recalculatePosition();
}

void Camera::zoomInOut(float distance)
{
	const float maxDist = 50.0; // ������������ ����������
	const float minDist = 1.0; // ����������� ����������

	r = r + distance;

	// �������� �����������
	if (r <= minDist) r = minDist;
	if (r >= maxDist) r = maxDist;

	recalculatePosition();
}