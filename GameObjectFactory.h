#pragma once

#include <iostream>
#include <vector>
#include <windows.h>
#include <string>

#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "GameObject.h"
#include "PhongMaterial.h"
#include "PhongMaterialWithTexture.h"
#include "GraphicObject.h"

// ОПРЕДЕЛЕНИЕ ТИПОВ ИГРОВЫХ ОБЪЕКТОВ
enum class GameObjectType {
  LIGHT_OBJECT, // легкий игровой объект
  HEAVY_OBJECT, // тяжелый игровой объект
  BORDER_OBJECT, // граничный игровой объект
  PLAYER, // игровой объект для представления игрока
  BOMB, // игровой объект для представления бомбы
  MONSTER // игровой объект для представления монстров
};

// КЛАСС ДЛЯ СОЗДАНИЯ ИГРОВЫХ ОБЪЕКТОВ
class GameObjectFactory
{
public:
  // инициализация фабрики (загрузка мешей и установка параметров материала)
  bool init(std::string filename);
  // создание нового объекта заданного типа
  std::shared_ptr<GameObject> create(GameObjectType type, int x, int y);
private:
  // меши для каждого типа объекта
  std::vector<std::shared_ptr<Mesh>> meshes;
  // материалы для каждого типа объекта
  std::vector<std::shared_ptr<Material>> materials;
};
