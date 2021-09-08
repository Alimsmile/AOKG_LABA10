#pragma once

#include <windows.h>
#include <iostream>
#include <vector>

#include <string>
#include <stdio.h>
#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Data.h"




// ������� ��� �������� FPS
unsigned int getFPS();

// �������, ���������� ��� ��������� �������� ����
void reshape(int, int);

// ������� ���������� ��� ����������� ����
// � ��� ����� � �������������, �� �������� glutPostRedisplay
void display(void);