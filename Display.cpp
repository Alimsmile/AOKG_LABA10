#include "Display.h"
#include "Simulation.h"

// функция для подсчета FPS
unsigned int getFPS()
{
	static unsigned int count = 0, FPS;
	static LARGE_INTEGER timeOld, perfomanceFrenquency;
	LARGE_INTEGER timeNew;
	float value;
	static bool flag = true;

	count++;
	if (flag)
	{
		QueryPerformanceCounter(&timeOld);
		QueryPerformanceFrequency(&perfomanceFrenquency);		
		flag = false;
	}
	QueryPerformanceCounter(&timeNew);
	
	value = float((timeNew.QuadPart - timeOld.QuadPart) / perfomanceFrenquency.QuadPart);
	
	if (value >= 1.0) {
		FPS = count / value;
		flag = true;
		count = 0;
	}

	return FPS;
}

// функция, вызываемая при изменении размеров окна
void reshape(int w, int h)
{
	// установить новую область просмотра, равную всей области окна
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	// установить матрицу проекции с правильным аспектом
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};

// функция вызывается при перерисовке окна
// в том числе и принудительно, по командам glutPostRedisplay
void display(void)
{
	// отчищаем буфер цвета и буфер глубины
	glClearColor(0.00, 0.00, 0.00, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// включаем тест глубины
	glEnable(GL_DEPTH_TEST);

	// включаем режим расчета освещения
	glEnable(GL_LIGHTING);

	// установка камеры
	camera.apply();

	// установка источника света с заданным номером
	light.apply(GL_LIGHT0);

	// выводим все игровые объекты
	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			if (mapObjects[i][j] != nullptr)
			{
				mapObjects[i][j]->draw();
			}
		}
	}
	planeGraphicObject.draw();
	Texture::disableAll();
	if (!playerKill)
	{
		player->draw();
	}
	for (int i = 0; i < countMonters; i++)
	{
		if (monsters[i] != nullptr)
		{
			monsters[i]->draw();
		}
	}
	if (statusBomb)
	{
		bomb->draw();
	}

	// смена переднего и заднего буферов
	glutSwapBuffers();

	// выводим количество FPS 
	auto count = getFPS();
	char strTitle[128];
	sprintf_s(strTitle, 128, "Laba_10 FPS [%d]", count);
	glutSetWindowTitle(strTitle);
};