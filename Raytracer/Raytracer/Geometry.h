#pragma once

#include <glm/glm.hpp>
#include <memory>
#include "Shader.h"
#include "SceneObject.h"

class Scene;
/*
class ShadingInfo{
public:
	float ka, kd, ks, n;
	glm::vec3 color;
	float reflectivity, transparency;

	ShadingInfo(float ka, float kd, float ks, float n, glm::vec3 color,
		float reflectivity = 0.f, float transparency = 0.f) :
		ka(ka), kd(kd), ks(ks), n(n), color(color), reflectivity(reflectivity), transparency(transparency) {}
};
*/

class Triangle {
public:
	glm::vec3 a, b, c;

	Triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c) 
		:a(a), b(b), c(c){}

	glm::vec3 getNormal() const;
};

class Sphere {
public:
	glm::vec3 origin;
	float radius;

	Sphere(glm::vec3 origin, float radius) 
		:origin(origin), radius(radius){}

	glm::vec3 getNormal(glm::vec3 position) const;
};

class Plane {
public:
	glm::vec3 origin, normal;

	Plane(glm::vec3 origin, glm::vec3 normal)
		:origin(origin), normal(normal){}

	glm::vec3 getNormal() const;
};

class Ray {
public:
	glm::vec3 origin, dir;
	int remainingBounces;

	Ray() :origin(0.f), dir(0.f) {}
	Ray(glm::vec3 origin, glm::vec3 dir, int remainingBounces=0) :
		origin(origin), dir(normalize(dir)), remainingBounces(remainingBounces) {}
};

Ray reflectRay(Ray ray, glm::vec3 pos, glm::vec3 normal);

class RayIntersection {
public:
	Shader *materialHit;
	Ray ray;
	bool intersected;
	float t;
	glm::vec3 normal, position;

	RayIntersection() :materialHit(nullptr), intersected(false), t(-1) {}

	bool operator<(RayIntersection ray);
};

glm::vec3 reflect(glm::vec3 dir, glm::vec3 pos, glm::vec3 normal);


RayIntersection intersect(Ray ray, const Sphere *sphere);
RayIntersection intersect(Ray ray, const Triangle *triangle);
RayIntersection intersect(Ray ray, const Plane *plane);


typedef SceneGeometry<Triangle> SceneTriangle;
typedef SceneGeometry<Sphere> SceneSphere;
typedef SceneGeometry<Plane> ScenePlane;

