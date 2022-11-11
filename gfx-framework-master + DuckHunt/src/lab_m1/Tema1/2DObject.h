#pragma once

#include <string>
#include <vector>
#include<math.h>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"
#include "core/engine.h"
#include "utils/gl_utils.h"
#include "2DTransformations.h"

// Number of triangles used to render a circle
#define CIRCLE_PRECISION 120

using namespace std;

namespace obj {

	// 2D figures static factory
	class Object2D{
	private:
		Object2D();

	public:
		// Creates a mesh from vertices and number of indices
		static Mesh* CreateMesh(const std::string& name,
			vector<VertexFormat> vertices,
			unsigned int indices_number);

		/* Generates the vertices and the number of indices for a triangle
			To be used with CreateMesh to generate the triangle*/
		static pair<vector<VertexFormat>, unsigned int> Triangle(
			glm::vec3 dot1,
			glm::vec3 dot2,
			glm::vec3 dot3,
			glm::vec3 color = glm::vec3(1, 1, 1));

		/* Generates the vertices and the number of indices for a circle
			To be used with CreateMesh to generate the circle*/
		static pair<vector<VertexFormat>, unsigned int> Circle(
			glm::vec3 center,
			double radius,
			glm::vec3 color = glm::vec3(1, 1, 1));

		static pair<vector<VertexFormat>, unsigned int> Rectangle(
			glm::vec3 lowerLeftCorner,
			double horizontalLength,
			double verticalLength,
			glm::vec3 color = glm::vec3(1, 1, 1)
		);
	};
} // namespace obj

