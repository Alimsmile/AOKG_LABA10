#include "glew.h"

#include <windows.h>
#include <iostream>
#include <vector>
#include <ctime> // для функции time()

#include <string>
#include <stdio.h>
#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IL/il.h"
#include "IL/ilu.h"
#include "IL/ilut.h"

#include "Data.h"
#include "Display.h"
#include "Simulation.h"

// используем пространство имен стандартной библиотеки
using namespace std;


int main(int argc, char **argv)
{
	setlocale(LC_ALL, "ru");

	// инициализация библиотеки GLUT
	glutInit(&argc, argv);
	// инициализация дисплея (формат вывода)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	// СОЗДАНИЕ ОКНА:
	// 1. устанавливаем верхний левый угол окна
	glutInitWindowPosition(200, 200);
	// 2. устанавливаем размер окна
	glutInitWindowSize(800, 600);
	// 3. создаем окно
	glutCreateWindow("Laba_10");

	// инициализация GLEW
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		printf("Error: %s\n", glewGetErrorString(err));
	}
	printf("Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
	// проверка поддержки расширения для работы с буфером VBO
	if (GLEW_ARB_vertex_buffer_object) {
		printf("VBO is supported\n");
	};

	// инициализация библиотеки DevIL для загрузки изображений
	ilInit();
	iluInit();
	ilutInit();

	// функция для инициализации всех общих данных (камера, объекты и т.д.)
	initData();
	// устанавливаем значение системных часов в качестве стартового числа
	srand(static_cast<unsigned int>(time(0))); 

	// УСТАНОВКА ФУНКЦИЙ ОБРАТНОГО ВЫЗОВА
	// устанавливаем функцию, которая будет вызываться для перерисовки окна
	glutDisplayFunc(display);
	// устанавливаем функцию, которая будет вызываться при изменении размеров окна
	glutReshapeFunc(reshape);
	// устанавливаем функцию, которая будет 
	glutIdleFunc(simulation);
	// основной цикл обработки сообщений ОС
	glutMainLoop();
};