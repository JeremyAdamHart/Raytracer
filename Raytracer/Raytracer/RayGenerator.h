#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "Geometry.h"
#include "Scene.h"

class PixelRay {
public:
	int x, y;
	Ray ray;

	PixelRay(Ray ray, int x, int y) : x(x), y(y), ray(ray) {}
};

struct Camera {
	glm::vec3 cx, cy, cz;
	glm::vec3 origin;

	Camera();
	Camera(glm::vec3 origin, glm::vec3 dir, glm::vec3 up=glm::vec3(0, 1, 0));
};


class Raytracer{
	int width, height;
	std::vector<glm::vec3> pixels;

public:
	Raytracer(int width=0, int height=0);

	void renderScene(Camera cam, float fov, float nearPlane, Scene *scene, int maxBounces);
	PixelRay generateRay(int x, int y);
};