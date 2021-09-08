#include "glew.h"
#include "Texture.h"


// загрузка текстуры из внешнего файла
void Texture::load(std::string filename)
{
  // создаем новое "изображение"
  ILuint imageId = ilGenImage();
  // задаем текущее "изображение"
  ilBindImage(imageId);
  // загружаем изображение
  wchar_t unicodeString[256];
  wsprintf(unicodeString, L"%S", filename.c_str());
  bool result = ilLoadImage(unicodeString);
  if (!result)
  {
    std::cout << "Не удалось загрузить: " << filename << std::endl;
  }
  // получение параметров загруженной текстуры
  int width = ilGetInteger(IL_IMAGE_WIDTH);
  int height = ilGetInteger(IL_IMAGE_HEIGHT);
  int format = ilGetInteger(IL_IMAGE_FORMAT);
  int type = ilGetInteger(IL_IMAGE_TYPE);
  char* data = new char[width * height * 4];
  ilCopyPixels(0, 0, 0, width, height, 1, format, type, data);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // определяем модель памяти (параметры распаковки)
  glActiveTexture(GL_TEXTURE0);
  glGenTextures(1, &texIndex);
  glBindTexture(GL_TEXTURE_2D, texIndex);
  glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, type, data);
  glGenerateMipmap(GL_TEXTURE_2D);
  delete[] data;

  // удаляем "изображение"
  ilDeleteImage(imageId);
}

// применение текстуры (привязка к текстурному блоку и установка параметров)
void Texture::apply(TextureFilter texFilter)
{	
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texIndex);
  glEnable(GL_TEXTURE_2D);

  switch (texFilter)
  {
  case TextureFilter::POINT:
  {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  };
    break;
  case TextureFilter::BILINEAR:
  {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  };
    break;
  case TextureFilter::TRILINEAR:
  {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  };
    break;
  case TextureFilter::ANISOTROPIC:
  {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 8.0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  };
    break;
  default:
    break;
  }
}

// отключение текстурирования для всех текстурных блоков
void Texture::disableAll()
{
  glActiveTexture(GL_TEXTURE0);
  glDisable(GL_TEXTURE_2D);
}