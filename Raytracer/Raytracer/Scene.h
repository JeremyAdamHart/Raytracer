#pragma once

#include <vector>
#include <memory>
#include <limits>

#include "Light.h"
#include "Geometry.h"
#include "Shader.h"


class Scene {
public:
	std::vector<std::shared_ptr<Light>> lights;
	std::vector<SceneGeometry<Triangle>> triangles;
	std::vector<SceneGeometry<Sphere>> spheres;
	std::vector<SceneGeometry<Plane>> planes;
	float ambient;
	glm::vec3 backgroundColor;

	Scene(float ambient = 0.3f, glm::vec3 backgroundColor = glm::vec3(0.f)) 
		:ambient(ambient), backgroundColor(backgroundColor) {}

	void add(std::shared_ptr<Light> light);
	void add(SceneTriangle triangle);
	void add(SceneSphere sphere);
	void add(ScenePlane plane);

};

RayIntersection intersect(Ray ray, const Scene *scene);
bool shadowIntersect(Ray ray, const Scene *scene, float lightDist = std::numeric_limits<float>::max());