#pragma once
#include <windows.h>
#include <vector>

#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GraphicObject.h"

// класс-перечисление для указания направления перемещения
enum class MoveDirection { STOP, LEFT, RIGHT, UP, DOWN };

// КЛАСС ДЛЯ ПРЕДСТАВЛЕНИЯ ИГРОВОГО ОБЪЕКТА
class GameObject
{
public:
	// конструктор
	GameObject();

	// установка используемого графического объекта
	// происходит копирование переданного объекта для последующего использования
	void setGraphicObject(const GraphicObject & graphicObject);

	// установка логических координат (два перегруженных метода для удобства)
	void setPosition(int x, int y);
	void setPosition(ivec2 position);

	// получение текущих логических координат
	ivec2 getPosition();

	// начать движение в выбранном направлении с указанной скоростью
	// скорость передвижения определяется количеством клеток в секунду
	void move(MoveDirection direction, float speed = 3.0f);

	// проверка на то, что объект в настоящий момент движется
	bool isMoving();

	// симуляция игрового объекта (плавное перемещение объекта)
	// метод вызывается непрерывно в функции simulation
	void simulate(float sec);

	// вывод игрового объекта на экран
	void draw(void);
private:
	// логические координаты игрового объекта
	glm::ivec2 position;
	// графический объект (для вывода на экран)
	GraphicObject graphicObject;
	// состояние объекта (заданное направление перемещения)
	MoveDirection sost;
	// прогресс в перемещении (от 0.0 до 1.0)
	float progress;
	// скорость перемещения
	float speed;
};

#include "GameObjectFactory.h"
#include "rapidjson/document.h"

// óêàçûâàåì èñïîëüçóåìûå ïðîñòðàíñòâà èìåí
using namespace rapidjson;
using namespace std;

// èíèöèàëèçàöèÿ ôàáðèêè (çàãðóçêà ìåøåé è óñòàíîâêà ïàðàìåòðîâ ìàòåðèàëà)
bool GameObjectFactory::init(string filename)
{
	// îòêðûâàåì ôàéë ñ çàäàííûì èìåíåì è ïðîâåðÿåì, óäàëîñü ëè åãî îòêðûòü
	ifstream f(filename);
	if (!f.is_open()) {
		cout << "Íå óäàåòñÿ íàéòè ôàéë " << filename << endl;
		return false;
	}
	// çàãðóæàåì âåñü èñõîäíûé òåêñò (äî ðàçäåëèòåëÿ - íóëåâîãî ñèìâîëà)
	string jsonString;
	getline(f, jsonString, static_cast<char>(0));
	f.close();
	// ïàðñèì - åñëè îøèáêà, òî âûõîäèì
	Document document;
	document.Parse(jsonString.c_str());
	for (auto& obj : document.GetObject()) 
	{
		for (auto& objParam : document[obj.name.GetString()].GetObject())
		{
			if (document[obj.name.GetString()][objParam.name.GetString()].IsString()) 
			{
				meshes.push_back(make_shared<Mesh>());
				meshes.back()->load(document[obj.name.GetString()][objParam.name.GetString()].GetString());
			}
			else
			{
				shared_ptr<PhongMaterialWithTexture> typeMaterial = make_shared<PhongMaterialWithTexture>();
				shared_ptr<PhongMaterial> typeMaterial1 = make_shared<PhongMaterial>();
				shared_ptr<Texture> texture = make_shared<Texture>();
				bool flag = false;
				for (auto& objMaterial : document[obj.name.GetString()][objParam.name.GetString()].GetObject())
				{
					string tempStr =  objMaterial.name.GetString();
					if (tempStr == "type")
					{
						string type = objMaterial.value.GetString();
						if (type == "PhongMaterialWithTexture")
						{
							flag = true;
						}
						if (type == "PhongMaterial")
						{
							flag = false;
						}
					}
					if ( flag)
					{
						if (tempStr == "texture")
						{
							string loadTexture = objMaterial.value.GetString();
							texture->load(loadTexture);
							typeMaterial->setTexture(texture);
						}
						if (tempStr == "diffuse")
						{
							auto arr = objMaterial.value.GetArray();
							typeMaterial->setDiffuse(vec4(arr[0].GetFloat(),
							arr[1].GetFloat(),
							arr[2].GetFloat(),
							arr[3].GetFloat()));
						}
						if (tempStr == "ambient")
							{
								auto arr = objMaterial.value.GetArray();
								typeMaterial->setAmbient(vec4(arr[0].GetFloat(),
									arr[1].GetFloat(),
									arr[2].GetFloat(),
									arr[3].GetFloat()));
							}
						if (tempStr == "specular")
							{
								auto arr = objMaterial.value.GetArray();
								typeMaterial->setSpecular(vec4(arr[0].GetFloat(),
									arr[1].GetFloat(),
									arr[2].GetFloat(),
									arr[3].GetFloat()));
							}
						if (tempStr == "emission")
						{
							auto arr = objMaterial.value.GetArray();
							typeMaterial->setEmission(vec4(arr[0].GetFloat(),
							arr[1].GetFloat(),
							arr[2].GetFloat(),
							arr[3].GetFloat()));
						}
						if (tempStr == "shininess")
						{
							typeMaterial->setShininess(objMaterial.value.GetFloat());
						}
					}
					else
					{
						if (tempStr == "diffuse")
						{
							auto arr = objMaterial.value.GetArray();
							typeMaterial1->setDiffuse(vec4(arr[0].GetFloat(),
								arr[1].GetFloat(),
								arr[2].GetFloat(),
								arr[3].GetFloat()));
						}
						if (tempStr == "ambient")
						{
							auto arr = objMaterial.value.GetArray();
							typeMaterial1->setAmbient(vec4(arr[0].GetFloat(),
								arr[1].GetFloat(),
								arr[2].GetFloat(),
								arr[3].GetFloat()));
						}
						if (tempStr == "specular")
						{
							auto arr = objMaterial.value.GetArray();
							typeMaterial1->setSpecular(vec4(arr[0].GetFloat(),
								arr[1].GetFloat(),
								arr[2].GetFloat(),
								arr[3].GetFloat()));
						}
						if (tempStr == "emission")
						{
							auto arr = objMaterial.value.GetArray();
							typeMaterial1->setEmission(vec4(arr[0].GetFloat(),
								arr[1].GetFloat(),
								arr[2].GetFloat(),
								arr[3].GetFloat()));
						}
						if (tempStr == "shininess")
						{
							typeMaterial1->setShininess(objMaterial.value.GetFloat());
						}
					}
				}
				if (flag)
				{
					materials.push_back(typeMaterial);
				}
				else
				{
					materials.push_back(typeMaterial1);
				}
			}

		}
	}
	if (document.GetParseError() != 0) {
		cout << "íåâåðíûé ôîðìàò ôàéëà\n";
		return false;
	}
}

// ñîçäàíèå íîâîãî îáúåêòà çàäàííîãî òèïà
std::shared_ptr<GameObject> GameObjectFactory::create(GameObjectType type, int x, int y)
{
	shared_ptr<GameObject> GameObj = make_shared<GameObject>();
	GraphicObject GraphicObj;
	switch (type)
	{
	case GameObjectType::LIGHT_OBJECT: 
	{
		GraphicObj.setMesh(meshes[0]);
		GraphicObj.setMaterial(materials[0]);
		GameObj->setGraphicObject(GraphicObj);
		GameObj->setPosition(x, y);
	}; break;
	case GameObjectType::HEAVY_OBJECT:
	{
		GraphicObj.setMesh(meshes[1]);
		GraphicObj.setMaterial(materials[1]);
		GameObj->setGraphicObject(GraphicObj);
		GameObj->setPosition(x, y);
	}; break; 
	case GameObjectType::BORDER_OBJECT:
	{
		GraphicObj.setMesh(meshes[2]);
		GraphicObj.setMaterial(materials[2]);
		GameObj->setGraphicObject(GraphicObj);
		GameObj->setPosition(x, y);
	}; break;
	case GameObjectType::PLAYER:
	{
		GraphicObj.setMesh(meshes[3]);
		GraphicObj.setMaterial(materials[3]);
		GameObj->setGraphicObject(GraphicObj);
		GameObj->setPosition(x, y);
	}; break;
	case GameObjectType::BOMB:
	{
		GraphicObj.setMesh(meshes[4]);
		GraphicObj.setMaterial(materials[4]);
		GameObj->setGraphicObject(GraphicObj);
		GameObj->setPosition(x, y);
	}; break;
	case GameObjectType::MONSTER:
	{
		GraphicObj.setMesh(meshes[5]);
		GraphicObj.setMaterial(materials[5]);
		GameObj->setGraphicObject(GraphicObj);
		GameObj->setPosition(x, y);
	}; break;
	default: 
		std::cout << "Error" << std::endl;
		break;
	}
	return GameObj;
}
