#pragma once
#include "glm\vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include<glm/gtc/quaternion.hpp>
#include "glm\matrix.hpp"
class Transform
{
public:
	Transform();
	~Transform();

	glm::mat4 GetMatrix44();

	glm::vec3 scale;
	glm::vec3 position;
	glm::quat rotation;


};

