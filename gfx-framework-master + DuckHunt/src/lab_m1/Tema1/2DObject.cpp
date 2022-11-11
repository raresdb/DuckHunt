#include "2DObject.h"

using namespace obj;
using namespace std;

Mesh* Object2D::CreateMesh(const std::string& name,
	vector<VertexFormat> vertices,
	unsigned int indices_number) {

	Mesh* figure = new Mesh(name);
	vector<unsigned> indices;

	for (int i = 0; i < indices_number; i++)
		indices.push_back(i);

	figure->InitFromData(vertices, indices);
    return figure;
}

pair<vector<VertexFormat>, unsigned int> Object2D::Triangle(
	glm::vec3 dot1,
	glm::vec3 dot2,
	glm::vec3 dot3,
	glm::vec3 color) {

	return pair<vector<VertexFormat>, unsigned int>
		({ VertexFormat(dot1, color), VertexFormat(dot2, color), VertexFormat(dot3, color) }, 3);
}

pair<vector<VertexFormat>, unsigned int> Object2D::Circle(
	glm::vec3 center,
	double radius,
	glm::vec3 color) { 
	vector<VertexFormat> vertices;

	vertices.reserve(CIRCLE_PRECISION);

	double angle1, angle2;
	glm::vec3 dot1 = center;
	glm::vec3 dot2;
	glm::vec3 dot3;

	pair<vector<VertexFormat>, unsigned int> triangle;

	for (int i = 0; i < CIRCLE_PRECISION; i++) {
		angle1 = 2 * M_PI * i / CIRCLE_PRECISION;
		angle2 = 2 * M_PI * (i + 1) / CIRCLE_PRECISION;

		dot2 = glm::vec3(center.x + radius * cos(angle1), center.y + radius * sin(angle1), 0);
		dot3 = glm::vec3(center.x + radius * cos(angle2), center.y + radius * sin(angle2), 0);

		triangle = Triangle(dot1, dot2, dot3, color);
		vertices.insert(vertices.end(), triangle.first.begin(), triangle.first.end());
	}

	return pair<vector<VertexFormat>, unsigned int>(vertices, CIRCLE_PRECISION * 3);
}

pair<vector<VertexFormat>, unsigned int> Object2D::Rectangle(
	glm::vec3 lowerLeftCorner,
	double horizontalLength,
	double verticalLength,
	glm::vec3 color) {
	
	vector<VertexFormat> vertices;

	pair<vector<VertexFormat>, unsigned int> leftTriangle = Triangle(
		lowerLeftCorner,
		lowerLeftCorner + glm::vec3(0, verticalLength, 0),
		lowerLeftCorner + glm::vec3(horizontalLength, 0, 0),
		color
		);

	pair<vector<VertexFormat>, unsigned int> rightTriangle = Triangle(
		lowerLeftCorner + glm::vec3(0, verticalLength, 0),
		lowerLeftCorner + glm::vec3(horizontalLength, 0, 0),
		lowerLeftCorner + glm::vec3(horizontalLength, verticalLength, 0),
		color
		);

	vertices.reserve(leftTriangle.first.size() + rightTriangle.first.size());
	vertices.insert(vertices.end(), leftTriangle.first.begin(), leftTriangle.first.end());
	vertices.insert(vertices.end(), rightTriangle.first.begin(), rightTriangle.first.end());
	return pair<vector<VertexFormat>, unsigned>(vertices, 6);
}