#pragma once

#include <windows.h>
#include <fstream>
#include <string>

#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Material.h"
#include "Texture.h"

using namespace glm;

//  Ћј—— ƒЋя –јЅќ“џ — ћј“≈–»јЋќћ
class PhongMaterialWithTexture : public Material
{
public:
  // конструктор по умолчанию
  PhongMaterialWithTexture();
  // задание параметров материала
  void setAmbient(vec4 color);
  void setDiffuse(vec4 color);
  void setSpecular(vec4 color);
  void setEmission(vec4 color);
  void setShininess(float p);
  // установка используемой текстуры
  void setTexture(std::shared_ptr<Texture> texture);
  // загрузка параметров материала из внешнего текстового файла
  void load(std::string filename);
  // установка всех параметров материала
  void apply() override;
private:
  // фонова¤ составл¤юща¤
  vec4 ambient;
  // диффузна¤ составл¤юща¤
  vec4 diffuse;
  // зеркальна¤ составл¤юща¤
  vec4 specular;
  // самосвечение
  vec4 emission;
  // степень отполированности
  float shininess;
  // используема¤ текстура
  std::shared_ptr<Texture> texture;
};