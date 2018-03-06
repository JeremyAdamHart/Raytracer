#pragma once

#include "Geometry.h"
#include <vector>

class Light {
public:
	glm::vec3 pos;

	Light(glm::vec3 pos) :pos(pos) {}
};

class Scene {
public:
	std::vector<Light> lights;
	std::vector<Triangle> triangles;
	std::vector<Sphere> spheres;
	std::vector<Plane> planes;
};

std::vector<RayIntersection> intersect(Ray ray, Scene *scene, int maxIntersections);