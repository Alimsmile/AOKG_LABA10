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

// состо¤ние игрока
extern bool playerKill;
// —осто¤ние бомбы
extern bool statusBomb;


// функци¤ дл¤ подсчета времени выполнении функции 
float getSimulationTime();

// функци¤ симул¤ции - вызываетс¤ максимально часто
// через заранее неизвестные промежутки времени
// дл¤ чего регистрируетс¤ с помощью glutIdleFunc
void simulation();