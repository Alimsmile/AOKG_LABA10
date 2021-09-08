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

class Light
{
public:
	// конструкторы
	Light();
	Light(vec3 position);
	Light(float x, float y, float z);

	// задание различных параметров источника света
	void setPosition(vec3 position);
	void setAmbient(vec4 color);
	void setDiffuse(vec4 color);
	void setSpecular(vec4 color);

	// установка всех параметров источника света с заданным номером
	// данна¤ функци¤ должна вызыватьс¤ после установки камеры,
	// т.к. здесь устанавливаетс¤ позици¤ источника света
	void apply(GLenum LightNumber = GL_LIGHT0);

private:
	// позици¤ источника света
	vec4 position;
	// фонова¤ составл¤юща¤ источника света
	vec4 ambient;
	// диффузна¤ составл¤юща¤
	vec4 diffuse;
	// зеркальна¤ составл¤юща¤
	vec4 specular;
};