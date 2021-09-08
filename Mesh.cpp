#include "glew.h"
#include "Mesh.h"
#include <iostream>
using namespace std;
using namespace glm;

// конструктор 
Mesh::Mesh()
{

}

// загрузка меша из файла с указанным именем
void Mesh::load(std::string filename)
{
	// массив вершин полигональной сетки
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	// вектор для хранения геометрических координат
	std::vector<vec3> v;
	// вектор для хранения нормалей
	std::vector<vec3> n;
	// вектор для хранения текстурных координат
	std::vector<vec2> t;
	// вектор для хранения индексов атрибутов, для построения вершин
	std::vector<ivec3> fPoints;
	// отображение вершины (по используемым ею атрибутам) на индекс в массиве вершин
	map<string, int> vertexToIndexTable;

	vec3 temp;
	ivec3 temp1;
	vec2 temp2;

	// чтение из файла
	std::ifstream fileIn;
	fileIn.open(filename, std::ios_base::in);
	if (!fileIn.is_open())
	{
		std::cout << "Ошибка открытия файла!" << std::endl;
	}
	else
	{
		std::cout << filename << std::endl;
		std::string str;

		while (!fileIn.eof())
		{
			fileIn >> str;

			if (str == "v")
			{
				fileIn >> temp.x;
				fileIn >> temp.y;
				fileIn >> temp.z;
				v.push_back(temp);
			//	printf("v %6.4f %6.4f %6.4f \n", temp.x, temp.y, temp.z);
			}

			if (str == "vn")
			{
				fileIn >> temp.x;
				fileIn >> temp.y;
				fileIn >> temp.z;
				n.push_back(temp);
				//printf("vn %3.4f %3.4f %3.4f \n", temp.x, temp.y, temp.z);
			}

			if (str == "vt")
			{
				fileIn >> temp2.x;
				fileIn >> temp2.y;
				t.push_back(temp2);
				//printf("vt %3.4f %3.4f \n", temp2.x, temp2.y);
			}

			if (str == "f")
			{
				fileIn >> temp1.x;
				fileIn.get();
				fileIn >> temp1.y;
				fileIn.get();
				fileIn >> temp1.z;
				fPoints.push_back(temp1);
				//printf("f %d/%d/%d ", temp1.x, temp1.y, temp1.z);
				fileIn >> temp1.x;
				fileIn.get();
				fileIn >> temp1.y;
				fileIn.get();
				fileIn >> temp1.z;
				fPoints.push_back(temp1);
				//printf("%d/%d/%d ", temp1.x, temp1.y, temp1.z);
				fileIn >> temp1.x;
				fileIn.get();
				fileIn >> temp1.y;
				fileIn.get();
				fileIn >> temp1.z;
				fPoints.push_back(temp1);
				//printf("%d/%d/%d \n", temp1.x, temp1.y, temp1.z);
			}
		}
	}
	fileIn.close();

	int key = 0; // ключ

	for (int i = 0; i < fPoints.size(); i++)
	{
		string st = to_string(fPoints[i].x) + "/" + to_string(fPoints[i].y) +"/"+ to_string(fPoints[i].z);
		auto fi = vertexToIndexTable.find(st);// ищем элемент в контейнере
		if (fi != vertexToIndexTable.end())
		{
			indices.push_back(fi->second);
		}
		else 
		{
			vertexToIndexTable.insert(pair<string, int>(st, key));// добавление вершины в map
			Vertex temp;
			// геометрические координаты
			temp.coord[0] = v[fPoints[i].x - 1].x;
			temp.coord[1] = v[fPoints[i].x - 1].y;
			temp.coord[2] = v[fPoints[i].x - 1].z;
			// вектор нормали
			temp.normal[0] = n[fPoints[i].z - 1].x;
			temp.normal[1] = n[fPoints[i].z - 1].y;
			temp.normal[2] = n[fPoints[i].z - 1].z;
			// текстурные координаты нулевого текстурного блока
			temp.texCoord[0] = t[fPoints[i].y - 1].x;
			temp.texCoord[1] = t[fPoints[i].y - 1].y;
			vertices.push_back(temp);
			indices.push_back(key);
			key++;
		}
	}

	// Справочная информация
	{
		std::cout << "# " << v.size() << " vertices" << std::endl;
		std::cout << "# " << n.size() << " vertex normals" << std::endl;
		std::cout << "# " << t.size() << " texture cords" << std::endl;
		std::cout << "# " << fPoints.size() / 3 << " faces" << std::endl;
	}
	// Загрузка буферов
	glGenBuffers(2,bufferIds);
	//
	glBindBuffer(GL_ARRAY_BUFFER, bufferIds[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* vertices.size(), vertices.data(), GL_STATIC_DRAW);
	//
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferIds[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)* indices.size(), indices.data(), GL_STATIC_DRAW);
	//
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//
	indexCount = indices.size();

}

// вывод меша (передача всех вершин в OpenGL)
void Mesh::draw()
{
	// Включение необходимых вершинных массивов
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	//
	glBindBuffer(GL_ARRAY_BUFFER, bufferIds[0]);
	// Указание адреса начала данных и их структур
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, coord));
	glNormalPointer(GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
	//
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferIds[1]);
	// Вывод полигонов на экран
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	//
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	// Отключение раннее включенных вершинных массивов
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
