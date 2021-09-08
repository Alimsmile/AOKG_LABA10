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

#include "Camera.h"
#include "GraphicObject.h"
#include "Light.h"
#include "PhongMaterial.h"
#include "Mesh.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "Texture.h"
#include "PhongMaterialWithTexture.h"

// количество монстров на карте
const unsigned char countMonters = 3;

// объект для камеры
extern Camera camera;

// объект для освещенности
extern Light light;

// список игровых объектов расположенных на карте
extern std::shared_ptr<GameObject> mapObjects[21][21];
extern std::shared_ptr<GameObject> player;
extern std::shared_ptr<GameObject> monsters[countMonters];
extern std::shared_ptr<GameObject> bomb;

// графический объект для плоскости (частный случай)
extern GraphicObject planeGraphicObject; 

// скорость изменения камеры
const float speedRotate = 90;
const float speedZoom = 10;

// функция для инициализации всех общих данных (камера, объекты и т.д.)
void initData();

// карта проходимости
extern int passabilityMap[21][21];

// текстура для плоскости
extern Texture planeTexture;