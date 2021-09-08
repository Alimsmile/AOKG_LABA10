#include "Light.h"

// конструкторы
Light::Light()
{

};

Light::Light(vec3 position)
{
	this->position = vec4(position, 1.0);
};

Light::Light(float x, float y, float z)
{
	position = vec4(x, y, z, 1.0);
};

// задание различных параметров источника света
void Light::setPosition(vec3 position)
{
	this->position = vec4(position,1.0);
};

void Light::setAmbient(vec4 color)
{
	ambient = color;
};

void Light::setDiffuse(vec4 color)
{
	diffuse = color;
};

void Light::setSpecular(vec4 color)
{
	specular = color;
};

// установка всех параметров источника света с заданным номером
// данная функция должна вызываться после установки камеры,
// т.к. здесь устанавливается позиция источника света
void Light::apply(GLenum LightNumber)
{
	glEnable(LightNumber);
	glLightfv(LightNumber, GL_AMBIENT, value_ptr(ambient));
	glLightfv(LightNumber, GL_DIFFUSE, value_ptr(diffuse));
	glLightfv(LightNumber, GL_SPECULAR, value_ptr(specular));		
	glLightfv(LightNumber, GL_POSITION, value_ptr(position));
};