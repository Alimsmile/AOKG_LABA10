#pragma once

#include <windows.h>
#include <string>
#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IL/il.h"
#include "IL/ilu.h"
#include "IL/ilut.h"

// ѕ≈–≈„»—Ћ≈Ќ»≈ ƒЋя ќѕ–≈ƒ≈Ћ≈Ќ»я –≈∆»ћј ‘»Ћ№“–ј÷»»
enum class TextureFilter {
  POINT, // “ќ„≈„Ќјя
  BILINEAR, // Ѕ»Ћ»Ќ≈…Ќјя
  TRILINEAR, // “–»Ћ»Ќ≈…Ќјя
  ANISOTROPIC // јЌ»«“ќ–ќѕЌјя
};

//  Ћј—— ƒЋя –јЅќ“џ — “≈ —“”–ќ…
class Texture
{
public:
  // загрузка текстуры из внешнего файла
  void load(std::string filename);
  // применение текстуры (прив¤зка к текстурному блоку и установка параметров)
  void apply(TextureFilter texFilter = TextureFilter::ANISOTROPIC);
  // отключение текстурировани¤ дл¤ всех текстурных блоков
  static void disableAll();
private:
  // идентификатор (индекс) текстурного объекта
  GLuint texIndex;
};


