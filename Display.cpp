#include "Display.h"
#include "Simulation.h"

// ������� ��� �������� FPS
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

// �������, ���������� ��� ��������� �������� ����
void reshape(int w, int h)
{
	// ���������� ����� ������� ���������, ������ ���� ������� ����
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	// ���������� ������� �������� � ���������� ��������
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};

// ������� ���������� ��� ����������� ����
// � ��� ����� � �������������, �� �������� glutPostRedisplay
void display(void)
{
	// �������� ����� ����� � ����� �������
	glClearColor(0.00, 0.00, 0.00, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// �������� ���� �������
	glEnable(GL_DEPTH_TEST);

	// �������� ����� ������� ���������
	glEnable(GL_LIGHTING);

	// ��������� ������
	camera.apply();

	// ��������� ��������� ����� � �������� �������
	light.apply(GL_LIGHT0);

	// ������� ��� ������� �������
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

	// ����� ��������� � ������� �������
	glutSwapBuffers();

	// ������� ���������� FPS 
	auto count = getFPS();
	char strTitle[128];
	sprintf_s(strTitle, 128, "Laba_10 FPS [%d]", count);
	glutSetWindowTitle(strTitle);
};