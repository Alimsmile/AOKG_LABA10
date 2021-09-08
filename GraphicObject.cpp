#include "GraphicObject.h"

// установка позиции
void GraphicObject::setPosition(vec3 position)
{
	this->position = position;
	recalculateModelMatrix();
}

vec3 GraphicObject::getPosition()
{
	return position;
}

void GraphicObject::setAngle(float grad)
{
	angle = radians(grad);
	recalculateModelMatrix();
}

float GraphicObject::getAngle()
{
	return glm::degrees(angle);
}

void GraphicObject::setColor(vec3 color)
{
	this->color = color;
}

vec3 GraphicObject::getColor()
{
	return color;
}

// ”становка используемого материала
void GraphicObject::setMaterial(std::shared_ptr<Material> material)
{
	this->material = material;
}

// ”становка используемого меша
void GraphicObject::setMesh(std::shared_ptr<Mesh> mesh)
{
    this->mesh = mesh;
}

// расчет матрицы modelMatrix на основе position и angle
void GraphicObject::recalculateModelMatrix()
{
	modelMatrix[ 0] = cos(angle);	modelMatrix[ 1] = 0;			modelMatrix[ 2] = sin(angle);		modelMatrix[ 3] = 0; // ось Ox
	modelMatrix[ 4] = 0;			modelMatrix[ 5] = 1;			modelMatrix[ 6] = 0;				modelMatrix[ 7] = 0; // ось Oy
	modelMatrix[ 8] = -sin(angle);	modelMatrix[ 9] = 0;			modelMatrix[10] = cos(angle);		modelMatrix[11] = 0; // ось Oz
	modelMatrix[12] = position.x;	modelMatrix[13] = position.y;	modelMatrix[14] = position.z;		modelMatrix[15] = 1; // позици¤ объекта (начало системы координат)
}

// вывести объект
void GraphicObject::draw()
{
	if (material != nullptr)
	{
		material->apply();
	}
	glPushMatrix();
	glMultMatrixf(modelMatrix);
	if (mesh != nullptr)
	{
		mesh->draw();
	}
	glPopMatrix();
}