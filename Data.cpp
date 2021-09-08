#include "Data.h"

// ������������ ������������ ����
using namespace glm;

// ��� ������� �������
std::shared_ptr<GameObject> mapObjects[21][21];
std::shared_ptr<GameObject> player;
std::shared_ptr<GameObject> monsters[countMonters];
std::shared_ptr<GameObject> bomb;

// ������ ��� ������
Camera camera;

// ������ ��� ������������
Light light;

// ����� ������������
int passabilityMap[21][21] = {
3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
3,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,2,0,0,0,3,
3,0,2,1,2,0,2,0,2,2,2,1,2,0,2,0,2,0,2,2,3,
3,0,2,0,2,0,0,0,2,0,2,0,0,0,2,0,1,0,0,0,3,
3,0,1,0,2,2,1,2,2,0,2,0,2,2,2,1,2,0,2,0,3,
3,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,0,2,0,3,
3,0,2,2,1,1,2,0,2,0,2,2,2,2,2,0,2,2,2,0,3,
3,0,2,0,0,0,2,0,2,0,0,0,0,0,2,0,0,0,0,0,3,
3,0,2,0,2,2,2,0,2,0,2,2,1,2,2,2,1,2,2,0,3,
3,0,0,0,2,0,0,0,2,0,2,0,0,0,0,0,0,0,1,0,3,
3,2,2,2,2,0,2,2,2,0,2,0,2,2,2,2,2,2,2,0,3,
3,0,0,0,2,0,0,0,1,0,2,0,0,0,2,0,0,0,0,0,3,
3,0,2,0,2,2,2,0,2,1,2,0,2,2,2,0,2,2,2,2,3,
3,0,2,0,0,0,2,0,0,0,2,0,0,0,2,0,2,0,0,0,3,
3,2,2,2,2,0,2,2,2,0,2,2,2,0,1,0,2,2,2,0,3,
3,0,0,0,0,0,2,0,2,0,0,0,2,0,1,0,0,0,2,0,3,
3,0,2,0,2,1,2,0,2,0,2,2,2,0,2,2,2,0,2,0,3,
3,0,1,0,1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,3,
3,0,2,1,2,0,2,2,2,2,2,0,2,0,2,0,2,2,2,2,3,
3,0,0,0,0,0,0,0,0,0,0,0,2,0,2,0,0,0,0,0,3,
3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
};

// ����������� ������ ��� ��������� (������� ������)
GraphicObject planeGraphicObject;

// ������� ��� �������� ������� ��������
GameObjectFactory gameObjectFactory;

// ������� ��� ������������� ���� ����� ������ (������, ������� � �.�.)
void 
Data()
{

	// ��������� ���������� �� OPENGL
	printf("GL_VENDOR = %s\n", glGetString(GL_VENDOR));
	printf("GL_RENDERER = %s\n", glGetString(GL_RENDERER));
	printf("GL_VERSION = %s\n\n", glGetString(GL_VERSION));

	// ������������� ������� (� ���������� �� ������ json-�����)
	gameObjectFactory.init("data\\GameObjectsDescription.json");

	// ������������� ������
	camera.setPosition(vec3(20, 25, 17.5));

	// ������������� ������������ 
	{
		light.setPosition(vec3(20.0, 20.0, 15.0));
		light.setAmbient(vec4(0.4, 0.4, 0.4, 1.0));
		light.setDiffuse(vec4(1.0, 1.0, 1.0, 1.0));
		light.setSpecular(vec4(1.0, 1.0, 1.0, 1.0));
	}

	// ����������� ������ ��� ��������� (������� ������)
	// ��������� ���� ��� ���������
	planeGraphicObject.setPosition(vec3(0.0, 0.0, 0.0));
	std::shared_ptr<Mesh> planeMesh = std::make_shared<Mesh>();
	planeMesh->load("data\\meshes\\HighPolyPlane.obj");
	planeGraphicObject.setMesh(planeMesh);

	// �������� �������� ��� ���������
	std::shared_ptr<Texture> planeTexture = std::make_shared<Texture>();
	planeTexture->load("data\\textures\\plane.jpg");

	// ��������� ��������� ��� ���������
	std::shared_ptr<PhongMaterialWithTexture> planeMaterial = std::make_shared<PhongMaterialWithTexture>();
	planeMaterial->load("data\\materials\\PlaneMaterial.txt");
	planeMaterial->setTexture(planeTexture);
	planeGraphicObject.setMaterial(planeMaterial);

	// ������������� �������� �����
	player = gameObjectFactory.create(GameObjectType::PLAYER, 19, 1);

	// ������������� ��������
	monsters[0] = gameObjectFactory.create(GameObjectType::MONSTER, 1, 19);
	passabilityMap[1][19] = 4;
	monsters[1] = gameObjectFactory.create(GameObjectType::MONSTER, 19, 19);
	passabilityMap[19][19] = 4;
	monsters[2] = gameObjectFactory.create(GameObjectType::MONSTER, 1, 1);
	passabilityMap[1][1] = 4;

	// ������������� �����
	bomb = gameObjectFactory.create(GameObjectType::BOMB, 0, 0);

	// ������������� �������� �����
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			switch (passabilityMap[i][j]) {
			case 1:
				mapObjects[i][j] = gameObjectFactory.create(GameObjectType::LIGHT_OBJECT, i, j);
				break;
			case 2:
				mapObjects[i][j] = gameObjectFactory.create(GameObjectType::HEAVY_OBJECT, i, j);
				break;
			case 3:
				mapObjects[i][j] = gameObjectFactory.create(GameObjectType::BORDER_OBJECT, i, j);
				break;
			default:
				mapObjects[i][j] = nullptr;
				break;
			}

		}
	}
}