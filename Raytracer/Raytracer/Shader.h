#pragma once

#include <glm/glm.hpp>

class Scene;
class RayIntersection;

class Shader {
protected:
	Shader() {}
public:
	virtual glm::vec3 calculateShading(RayIntersection ray, const Scene *scene);
};

class PhongShader : public Shader {
public:
	glm::vec3 color;
	float reflectivity;
	float n;
	float transparency;
	bool metallic;


	PhongShader(	glm::vec3 color=glm::vec3(0), float reflectivity=0.f, float n=0, 
					float transparency=0.f, bool metallic=false);
	glm::vec3 calculateShading(RayIntersection ray, const Scene *scene) override;
};

