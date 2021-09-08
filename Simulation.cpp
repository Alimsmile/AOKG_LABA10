#include "Simulation.h"
#include <cstdlib> // для функции rand()

// состояние игрока
bool playerKill = false;

// состояние бомбы
bool statusBomb = false;
// Время отсчета
static float timeStart = 0.0;
// Время до взрыва
static float timeEnd = 3.0;
// Позиция бомбы
static ivec2 positionBomb;
// функция для подсчета времени выполнении функции 
float getSimulationTime()
{
	static LARGE_INTEGER timeOld;
	LARGE_INTEGER timeNew, perfomanceFrenquency;
	float value;
	QueryPerformanceCounter(&timeNew);
	QueryPerformanceFrequency(&perfomanceFrenquency);
	value = float((timeNew.QuadPart - timeOld.QuadPart) * 1000 / perfomanceFrenquency.QuadPart);
	timeOld.QuadPart = timeNew.QuadPart;
	return value;
}

// симуляция камеры
void CameraSimulation(float simulationTime)
{
	// передвижение камеры
	if (GetAsyncKeyState(VK_LEFT))
		camera.rotateLeftRight(simulationTime * speedRotate / 1000); // влево

	if (GetAsyncKeyState(VK_RIGHT))
		camera.rotateLeftRight(simulationTime * -speedRotate / 1000); // вправо

	if (GetAsyncKeyState(VK_UP))
		camera.rotateUpDown(simulationTime * -speedRotate / 1000); // вверх

	if (GetAsyncKeyState(VK_DOWN))
		camera.rotateUpDown(simulationTime * speedRotate / 1000); // вниз

	if (GetAsyncKeyState(VK_ADD))
		camera.zoomInOut(simulationTime * -speedZoom / 1000); // +

	if (GetAsyncKeyState(VK_SUBTRACT))
		camera.zoomInOut(simulationTime * speedZoom / 1000); // -
}

// симуляция всех игровых объектов (их плавное перемещение)
void gameObjectsSimulation(float simulationTime)
{
	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			if (mapObjects[i][j] != nullptr)
			{
				mapObjects[i][j]->simulate(simulationTime / 1000);
			}
		}
	}
	player->simulate(simulationTime / 1000);

}

// Генерируем рандомное число между значениями min и max.
int getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	// Равномерно распределяем рандомное число в нашем диапазоне
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

// симуляция монстров
void monsterSimulatiion(float simulationTime)
{
	static  MoveDirection directionMonsters[countMonters];
	for (int i = 0; i < countMonters; i++)
	{
		if (monsters[i] != nullptr)
		{
			ivec2 logicPos = monsters[i]->getPosition();
			if (!monsters[i]->isMoving())
			{
				switch (directionMonsters[i])
				{
				case MoveDirection::STOP:
				{
					int random_number = getRandomNumber(1, 100);
					if (random_number < 25) // вверх 
					{
						directionMonsters[i] = MoveDirection::UP;
					}
					if (random_number >= 25 && random_number < 50) // влево
					{
						directionMonsters[i] = MoveDirection::LEFT;
					}
					if (random_number >= 50 && random_number < 75) // вниз 
					{
						directionMonsters[i] = MoveDirection::DOWN;
					}
					if (random_number >= 75 && random_number < 100) // вправо 
					{
						directionMonsters[i] = MoveDirection::RIGHT;
					}
				}
				break;
				case MoveDirection::LEFT:
				{
					if (passabilityMap[logicPos.x - 1][logicPos.y] == 0)
					{
						monsters[i]->move(directionMonsters[i]);
						passabilityMap[logicPos.x - 1][logicPos.y] = 4;
						passabilityMap[logicPos.x][logicPos.y] = 0;
						if (player->getPosition().x == (logicPos.x - 1) && player->getPosition().y == logicPos.y)
						{
							playerKill = true;
						}
					}
					else
					{
						directionMonsters[i] = MoveDirection::STOP;
					}
					if (passabilityMap[logicPos.x - 1][logicPos.y + 1] == 0)
					{
						directionMonsters[i] = MoveDirection::STOP;
					}
					if (passabilityMap[logicPos.x - 1][logicPos.y - 1] == 0)
					{
						directionMonsters[i] = MoveDirection::STOP;
					}
					if (passabilityMap[logicPos.x - 2][logicPos.y] != 0)
					{
						directionMonsters[i] = MoveDirection::STOP;
					}
				}
				break;
				case MoveDirection::RIGHT:
				{
					if (passabilityMap[logicPos.x + 1][logicPos.y] == 0)
					{
						monsters[i]->move(directionMonsters[i]);
						passabilityMap[logicPos.x + 1][logicPos.y] = 4;
						passabilityMap[logicPos.x][logicPos.y] = 0;
						if (player->getPosition().x == (logicPos.x + 1) && player->getPosition().y == logicPos.y)
						{
							playerKill = true;
						}
					}
					else
					{
						directionMonsters[i] = MoveDirection::STOP;
					}
					if (passabilityMap[logicPos.x + 1][logicPos.y + 1] == 0)
					{
						directionMonsters[i] = MoveDirection::STOP;
					}
					if (passabilityMap[logicPos.x + 1][logicPos.y - 1] == 0)
					{
						directionMonsters[i] = MoveDirection::STOP;
					}
					if (passabilityMap[logicPos.x + 2][logicPos.y] != 0)
					{
						directionMonsters[i] = MoveDirection::STOP;
					}
				}
				break;
				case MoveDirection::UP:
				{
					if (passabilityMap[logicPos.x][logicPos.y - 1] == 0)
					{
						monsters[i]->move(directionMonsters[i]);
						passabilityMap[logicPos.x][logicPos.y - 1] = 4;
						passabilityMap[logicPos.x][logicPos.y] = 0;
						if (player->getPosition().x == logicPos.x && player->getPosition().y == (logicPos.y - 1))
						{
							playerKill = true;
						}
					}
					else
					{
						directionMonsters[i] = MoveDirection::STOP;
					}
					if (passabilityMap[logicPos.x - 1][logicPos.y - 1] == 0)
					{
						directionMonsters[i] = MoveDirection::STOP;
					}
					if (passabilityMap[logicPos.x + 1][logicPos.y - 1] == 0)
					{
						directionMonsters[i] = MoveDirection::STOP;
					}
					if (passabilityMap[logicPos.x][logicPos.y - 2] != 0)
					{
						directionMonsters[i] = MoveDirection::STOP;
					}
				}
				break;
				case MoveDirection::DOWN:
				{
					if (passabilityMap[logicPos.x][logicPos.y + 1] == 0)
					{
						monsters[i]->move(directionMonsters[i]);
						passabilityMap[logicPos.x][logicPos.y + 1] = 4;
						passabilityMap[logicPos.x][logicPos.y] = 0;
						if (player->getPosition().x == logicPos.x && player->getPosition().y == (logicPos.y + 1))
						{
							playerKill = true;
						}
					}
					else
					{
						directionMonsters[i] = MoveDirection::STOP;
					}
					if (passabilityMap[logicPos.x - 1][logicPos.y + 1] == 0)
					{
						directionMonsters[i] = MoveDirection::STOP;
					}
					if (passabilityMap[logicPos.x + 1][logicPos.y + 1] == 0)
					{
						directionMonsters[i] = MoveDirection::STOP;
					}
					if (passabilityMap[logicPos.x][logicPos.y + 2] != 0)
					{
						directionMonsters[i] = MoveDirection::STOP;
					}
				}
				break;
				default: std::cout << "Error monsterSimulatiion!" << std::endl;
					break;
				}
			}
			monsters[i]->simulate(simulationTime / 1000);
		}
	}
}

// Установка бомбы
void SetBomb(ivec2 pos)
{
	if (statusBomb)
	{
		return;
	}

	statusBomb = true;
	positionBomb = pos;
	bomb->setPosition(pos);
	passabilityMap[pos.x][pos.y] = 5;
}

// Работа бомбы
void executionBomb(float time)
{
	if (!statusBomb)
	{
		return;
	}

	if (timeStart > timeEnd * 1000)
	{
		// -->
		if (
				    passabilityMap[positionBomb.x + 1][positionBomb.y] != 2
			   && passabilityMap[positionBomb.x + 1][positionBomb.y] != 3
			 )
		{
			bool killFirstObject = false;
			// Легкий объект
			if (passabilityMap[positionBomb.x + 1][positionBomb.y] == 1)
			{
				mapObjects[positionBomb.x + 1][positionBomb.y] = nullptr;
				passabilityMap[positionBomb.x + 1][positionBomb.y] = 0;
				killFirstObject = true;
			}
			// Игрок
			if (
					    player->getPosition().x == positionBomb.x + 1
				   && player->getPosition().y == positionBomb.y
				 )
			{
				playerKill = true;
				killFirstObject = true;
			}
			// Монстры
			for (int i = 0; i < countMonters; i++)
			{
				if (monsters[i] != nullptr)
				{
					if (
						monsters[i]->getPosition().x == positionBomb.x + 1
						&& monsters[i]->getPosition().y == positionBomb.y
						)
					{
						monsters[i] = nullptr;
						passabilityMap[positionBomb.x + 1][positionBomb.y] = 0;
						killFirstObject = true;
					}
				}
			}
			// Если ничем не загородили
			// Легкий объект
			if (
				       passabilityMap[positionBomb.x + 2][positionBomb.y] == 1 
				   &&  !killFirstObject
				 )
			{
				mapObjects[positionBomb.x + 2][positionBomb.y] = nullptr;
				passabilityMap[positionBomb.x + 2][positionBomb.y] = 0;
			}
			// Монстры
			if (!killFirstObject)
			{
				for (int i = 0; i < countMonters; i++)
				{
					if (monsters[i] != nullptr)
					{
						if (
							monsters[i]->getPosition().x == positionBomb.x + 2
							&& monsters[i]->getPosition().y == positionBomb.y
							)
						{
							monsters[i] = nullptr;
							passabilityMap[positionBomb.x + 2][positionBomb.y] = 0;
						}
					}
				}
			}
			// Игрок
			if (
				player->getPosition().x == positionBomb.x + 2
				&& player->getPosition().y == positionBomb.y
				&& !killFirstObject
				)
			{
				playerKill = true;
			}
		}

		// <--
		if (
			passabilityMap[positionBomb.x - 1][positionBomb.y] != 2
			&& passabilityMap[positionBomb.x - 1][positionBomb.y] != 3
			)
		{
			bool killFirstObject = false;
			// Легкий объект
			if (passabilityMap[positionBomb.x - 1][positionBomb.y] == 1)
			{
				mapObjects[positionBomb.x - 1][positionBomb.y] = nullptr;
				passabilityMap[positionBomb.x - 1][positionBomb.y] = 0;
				killFirstObject = true;
			}
			// Игрок
			if (
				player->getPosition().x == positionBomb.x - 1
				&& player->getPosition().y == positionBomb.y
				)
			{
				playerKill = true;
				killFirstObject = true;
			}
			// Монстры
			for (int i = 0; i < countMonters; i++)
			{
				if (monsters[i] != nullptr)
				{
					if (
						monsters[i]->getPosition().x == positionBomb.x - 1
						&& monsters[i]->getPosition().y == positionBomb.y
						)
					{
						monsters[i] = nullptr;
						passabilityMap[positionBomb.x - 1][positionBomb.y] = 0;
						killFirstObject = true;
					}
				}
			}
			// Если ничем не загородили
			// Легкий объект
			if (
				passabilityMap[positionBomb.x - 2][positionBomb.y] == 1
				&& !killFirstObject
				)
			{
				mapObjects[positionBomb.x - 2][positionBomb.y] = nullptr;
				passabilityMap[positionBomb.x - 2][positionBomb.y] = 0;
			}
			// Монстры
			if (!killFirstObject)
			{
				for (int i = 0; i < countMonters; i++)
				{
					if (monsters[i] != nullptr)
					{
						if (
							monsters[i]->getPosition().x == positionBomb.x - 2
							&& monsters[i]->getPosition().y == positionBomb.y
							)
						{
							monsters[i] = nullptr;
							passabilityMap[positionBomb.x - 2][positionBomb.y] = 0;
						}
					}
				}
			}
			// Игрок
			if (
				player->getPosition().x == positionBomb.x - 2
				&& player->getPosition().y == positionBomb.y
				&& !killFirstObject
				)
			{
				playerKill = true;
			}
		}

		// Вниз
		if (
			passabilityMap[positionBomb.x][positionBomb.y + 1] != 2
			&& passabilityMap[positionBomb.x][positionBomb.y + 1] != 3
			)
		{
			bool killFirstObject = false;
			// Легкий объект
			if (passabilityMap[positionBomb.x][positionBomb.y + 1] == 1)
			{
				mapObjects[positionBomb.x][positionBomb.y + 1] = nullptr;
				passabilityMap[positionBomb.x][positionBomb.y + 1] = 0;
				killFirstObject = true;
			}
			// Игрок
			if (
				player->getPosition().x == positionBomb.x
				&& player->getPosition().y == positionBomb.y + 1
				)
			{
				playerKill = true;
				killFirstObject = true;
			}
			// Монстры
			for (int i = 0; i < countMonters; i++)
			{
				if (monsters[i] != nullptr)
				{
					if (
						monsters[i]->getPosition().x == positionBomb.x
						&& monsters[i]->getPosition().y == positionBomb.y + 1
						)
					{
						monsters[i] = nullptr;
						passabilityMap[positionBomb.x][positionBomb.y + 1] = 0;
						killFirstObject = true;
					}
				}
			}
			// Если ничем не загородили
			// Легкий объект
			if (
				passabilityMap[positionBomb.x][positionBomb.y + 2] == 1
				&& !killFirstObject
				)
			{
				mapObjects[positionBomb.x][positionBomb.y + 2] = nullptr;
				passabilityMap[positionBomb.x][positionBomb.y + 2] = 0;
			}
			// Монстры
			if (!killFirstObject)
			{
				for (int i = 0; i < countMonters; i++)
				{
					if (monsters[i] != nullptr)
					{
						if (
							monsters[i]->getPosition().x == positionBomb.x
							&& monsters[i]->getPosition().y == positionBomb.y + 2
							)
						{
							monsters[i] = nullptr;
							passabilityMap[positionBomb.x][positionBomb.y + 2] = 0;
						}
					}
				}
			}
			// Игрок
			if (
				player->getPosition().x == positionBomb.x
				&& player->getPosition().y == positionBomb.y + 2
				&& !killFirstObject
				)
			{
				playerKill = true;
			}
		}

		// Вверх
		if (
			passabilityMap[positionBomb.x][positionBomb.y - 1] != 2
			&& passabilityMap[positionBomb.x][positionBomb.y - 1] != 3
			)
		{
			bool killFirstObject = false;
			// Легкий объект
			if (passabilityMap[positionBomb.x][positionBomb.y - 1] == 1)
			{
				mapObjects[positionBomb.x][positionBomb.y - 1] = nullptr;
				passabilityMap[positionBomb.x][positionBomb.y - 1] = 0;
				killFirstObject = true;
			}
			// Игрок
			if (
				player->getPosition().x == positionBomb.x
				&& player->getPosition().y == positionBomb.y - 1
				)
			{
				playerKill = true;
				killFirstObject = true;
			}
			// Монстры
			for (int i = 0; i < countMonters; i++)
			{
				if (monsters[i] != nullptr)
				{
					if (
						monsters[i]->getPosition().x == positionBomb.x
						&& monsters[i]->getPosition().y == positionBomb.y - 1
						)
					{
						monsters[i] = nullptr;
						passabilityMap[positionBomb.x][positionBomb.y - 1] = 0;
						killFirstObject = true;
					}
				}
			}
			// Если ничем не загородили
			// Легкий объект
			if (
				passabilityMap[positionBomb.x][positionBomb.y - 2] == 1
				&& !killFirstObject
				)
			{
				mapObjects[positionBomb.x][positionBomb.y - 2] = nullptr;
				passabilityMap[positionBomb.x][positionBomb.y - 2] = 0;
			}
			// Монстры
			if (!killFirstObject)
			{
				for (int i = 0; i < countMonters; i++)
				{
					if (monsters[i] != nullptr)
					{
						if (
							monsters[i]->getPosition().x == positionBomb.x
							&& monsters[i]->getPosition().y == positionBomb.y - 2
							)
						{
							monsters[i] = nullptr;
							passabilityMap[positionBomb.x][positionBomb.y - 2] = 0;
						}
					}
				}
			}
			// Игрок
			if (
				player->getPosition().x == positionBomb.x
				&& player->getPosition().y == positionBomb.y - 2
				&& !killFirstObject
				)
			{
				playerKill = true;
			}
		}
		statusBomb = false;
		timeStart = 0.0;
		passabilityMap[positionBomb.x][positionBomb.y] = 0;
	}
	else
	{
		timeStart += time;
	}
}

// перемещение главного героя (распределение сообщений)
void movePlayer()
{
	ivec2 logicPos = player->getPosition();
	// передвижение игрока
	if ( GetAsyncKeyState('W') && (!player->isMoving()) ) // вверх
	{
		if (passabilityMap[logicPos.x][logicPos.y - 1] == 0)
		{
			player->move(MoveDirection::UP);
		}
		else
		{
			if (passabilityMap[logicPos.x][logicPos.y - 1] == 1)
			{
				if (passabilityMap[logicPos.x][logicPos.y - 2] == 0)
				{
					mapObjects[logicPos.x][logicPos.y - 1]->move(MoveDirection::UP);
					passabilityMap[logicPos.x][logicPos.y - 1] = 0;
					passabilityMap[logicPos.x][logicPos.y - 2] = 1;
					mapObjects[logicPos.x][logicPos.y - 2] = mapObjects[logicPos.x][logicPos.y - 1];
					mapObjects[logicPos.x][logicPos.y - 1] = nullptr;
					player->move(MoveDirection::UP);
				}
			}
		}
	}

	if (GetAsyncKeyState('S') && (!player->isMoving()) ) // вниз
	{
		if (passabilityMap[logicPos.x][logicPos.y + 1] == 0)
		{
			player->move(MoveDirection::DOWN);
		}
		else
		{
			if (passabilityMap[logicPos.x][logicPos.y + 1] == 1)
			{
				if (passabilityMap[logicPos.x][logicPos.y + 2] == 0)
				{
					mapObjects[logicPos.x][logicPos.y + 1]->move(MoveDirection::DOWN);
					passabilityMap[logicPos.x][logicPos.y + 1] = 0;
					passabilityMap[logicPos.x][logicPos.y + 2] = 1;
					mapObjects[logicPos.x][logicPos.y + 2] = mapObjects[logicPos.x][logicPos.y + 1];
					mapObjects[logicPos.x][logicPos.y + 1] = nullptr;
					player->move(MoveDirection::DOWN);
				}
			}
		}
	}

	if (GetAsyncKeyState('A') && (!player->isMoving()) ) // влево
	{
		if (passabilityMap[logicPos.x - 1][logicPos.y] == 0)
		{
			player->move(MoveDirection::LEFT);
		}
		else
		{
			if (passabilityMap[logicPos.x - 1][logicPos.y] == 1)
			{
				if (passabilityMap[logicPos.x - 2][logicPos.y] == 0)
				{
					mapObjects[logicPos.x - 1][logicPos.y]->move(MoveDirection::LEFT);
					passabilityMap[logicPos.x - 1][logicPos.y] = 0;
					passabilityMap[logicPos.x - 2][logicPos.y] = 1;
					mapObjects[logicPos.x - 2][logicPos.y] = mapObjects[logicPos.x - 1][logicPos.y];
					mapObjects[logicPos.x - 1][logicPos.y] = nullptr;
					player->move(MoveDirection::LEFT);
				}
			}
		}
	}

	if (GetAsyncKeyState('D') && (!player->isMoving()) ) // вправо
	{
		if (passabilityMap[logicPos.x + 1][logicPos.y] == 0)
		{
			player->move(MoveDirection::RIGHT);
		}
		else
		{
			if (passabilityMap[logicPos.x + 1][logicPos.y] == 1)
			{
				if (passabilityMap[logicPos.x + 2][logicPos.y] == 0)
				{
					mapObjects[logicPos.x + 1][logicPos.y]->move(MoveDirection::RIGHT);
					passabilityMap[logicPos.x + 1][logicPos.y] = 0;
					passabilityMap[logicPos.x + 2][logicPos.y] = 1;
					mapObjects[logicPos.x + 2][logicPos.y] = mapObjects[logicPos.x + 1][logicPos.y];
					mapObjects[logicPos.x + 1][logicPos.y] = nullptr;
					player->move(MoveDirection::RIGHT);
				}
			}
		}
	}

	// установка бомбы
	if (GetAsyncKeyState(VK_SPACE) && (!player->isMoving()) && !statusBomb) // вправо
	{
		SetBomb(player->getPosition());		
	}
}


// функция симуляции - вызывается максимально часто
// через заранее неизвестные промежутки времени
// для чего регистрируется с помощью glutIdleFunc
void simulation()
{
	// определение времени симуляции (МС)
	float simulationTime = getSimulationTime();

	// симуляция камеры
	CameraSimulation(simulationTime);

	// симуляция всех игровых объектов (их плавное перемещение)
	gameObjectsSimulation(simulationTime);

	// симуляция монстров
	monsterSimulatiion(simulationTime);

	// перемещение главного героя (распределение сообщений)
	if (!playerKill)
	{
		movePlayer();
	}
	
	// работа бомбы
	executionBomb(simulationTime);

	// устанавливаем признак того, что окно нуждается в перерисовке
	glutPostRedisplay();
};