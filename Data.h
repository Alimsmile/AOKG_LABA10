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

// ���������� �������� �� �����
const unsigned char countMonters = 3;

// ������ ��� ������
extern Camera camera;

// ������ ��� ������������
extern Light light;

// ������ ������� �������� ������������� �� �����
extern std::shared_ptr<GameObject> mapObjects[21][21];
extern std::shared_ptr<GameObject> player;
extern std::shared_ptr<GameObject> monsters[countMonters];
extern std::shared_ptr<GameObject> bomb;

// ����������� ������ ��� ��������� (������� ������)
extern GraphicObject planeGraphicObject; 

// �������� ��������� ������
const float speedRotate = 90;
const float speedZoom = 10;

// ������� ��� ������������� ���� ����� ������ (������, ������� � �.�.)
void initData();

// ����� ������������
extern int passabilityMap[21][21];

// �������� ��� ���������
extern Texture planeTexture;