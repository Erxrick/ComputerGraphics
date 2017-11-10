#pragma once
#include "stdafx.h"
#include "glm\vec2.hpp"
#include "glm\vec3.hpp"


#define LOADER
namespace MeshLoader {

	bool LoadMesh(const std::string& filename, std::vector<glm::vec3>& positions, std::vector<glm::vec3>& normals, std::vector<glm::vec2>& uvs);
}

