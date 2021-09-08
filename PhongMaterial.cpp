#include "PhongMaterial.h"
using namespace std;

// конструктор по умолчанию
PhongMaterial::PhongMaterial()
{
	ambient = vec4(0.0, 0.0, 0.0, 0.0);
	diffuse = vec4(0.0, 0.0, 0.0, 0.0);
	specular = vec4(0.0, 0.0, 0.0, 0.0);
	emission = vec4(0.0, 0.0, 0.0, 0.0);
	shininess = 0.0;
};

// задание параметров материала
void PhongMaterial::setAmbient(vec4 color)
{
	ambient = color;
};

void PhongMaterial::setDiffuse(vec4 color)
{
	diffuse = color;
};

void PhongMaterial::setSpecular(vec4 color)
{
	specular = color;
};

void PhongMaterial::setEmission(vec4 color)
{
	emission = color;
};

void PhongMaterial::setShininess(float p)
{
	shininess = p;
};

// вывод на кансоль всех параметров на консоль
void PhongMaterial::printMaterials()
{
	printf("diffuse: %3.1f %3.1f %3.1f %3.1f \n", diffuse.r, diffuse.g, diffuse.b, diffuse.a);
	printf("ambient: %3.1f %3.1f %3.1f %3.1f \n", ambient.r, ambient.g, ambient.b, ambient.a);
	printf("specular: %3.1f %3.1f %3.1f %3.1f \n", specular.r, specular.g, specular.b, specular.a);
	printf("emission: %3.1f %3.1f %3.1f %3.1f \n", emission.r, emission.g, emission.b, ambient.a);
	printf("shininess: %4.1f \n\n", shininess);
};

// загрузка параметров материала из внешнего текстового файла
void PhongMaterial::load(std::string filename)
{
	ifstream fileIn;
	fileIn.open(filename, ios_base::in);
	if (!fileIn.is_open())
	{
		cout << "ќшибка открыти¤ файла!" << endl;
	}
	else
	{
		//cout << filename << endl;
		string str;

		while (!fileIn.eof())
		{
			fileIn >> str;
			if (str == "diffuse:")
			{
				fileIn >> diffuse.r;
				fileIn >> diffuse.g;
				fileIn >> diffuse.b;
				fileIn >> diffuse.a;
				//printf("diffuse: %3.1f %3.1f %3.1f %3.1f \n", diffuse.r, diffuse.g, diffuse.b, diffuse.a);
			}
			if(str == "ambient:")
			{
				fileIn >> ambient.r;
				fileIn >> ambient.g;
				fileIn >> ambient.b;
				fileIn >> ambient.a;
				//printf("ambient: %3.1f %3.1f %3.1f %3.1f \n", ambient.r, ambient.g, ambient.b, ambient.a);
			}
			if (str == "specular:")
			{
				fileIn >> specular.r;
				fileIn >> specular.g;
				fileIn >> specular.b;
				fileIn >> specular.a;
				//printf("specular: %3.1f %3.1f %3.1f %3.1f \n", specular.r, specular.g, specular.b, specular.a);
			}
			if (str == "emission:")
			{
				fileIn >> emission.r;
				fileIn >> emission.g;
				fileIn >> emission.b;
				fileIn >> emission.a;
				//printf("emission: %3.1f %3.1f %3.1f %3.1f \n", emission.r, emission.g, emission.b, ambient.a);
			}
			if (str == "shininess:")
			{
				fileIn >> shininess;
				//printf("shininess: %4.1f \n\n", shininess);
			}

		}
	}
	fileIn.close();
};

// установка всех параметров материала
void PhongMaterial::apply()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, value_ptr(ambient));
	glMaterialfv(GL_FRONT, GL_DIFFUSE, value_ptr(diffuse));
	glMaterialfv(GL_FRONT, GL_SPECULAR, value_ptr(specular));
	glMaterialfv(GL_FRONT, GL_EMISSION, value_ptr(emission));
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
};