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



class Raytracer{
	int width, height;
	std::vector<glm::vec3> pixels;

public:
	Raytracer(int width=0, int height=0);

	void renderScene(float fov, float nearPlane, Scene *scene);
	PixelRay generateRay(int x, int y);
};