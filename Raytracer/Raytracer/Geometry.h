#pragma once

#include <glm/glm.hpp>
#include <memory>

class Scene;

class SceneObject {
	const Scene *parentScene;


};

class ShadingInfo{
public:
	float ka, kd, ks, n;
	glm::vec3 color;
	float reflectivity, transparency;

	ShadingInfo(float ka, float kd, float ks, float n, glm::vec3 color,
		float reflectivity = 0.f, float transparency = 0.f) :
		ka(ka), kd(kd), ks(ks), n(n), color(color), reflectivity(reflectivity), transparency(transparency) {}
};

class Geometry {
public:
	ShadingInfo shading;
	virtual glm::vec3 getNormal(glm::vec3 position);

	Geometry(ShadingInfo shading) :shading(shading) {}
};

class Triangle : public Geometry{
public:
	glm::vec3 a, b, c;

	Triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, ShadingInfo shading) 
		:a(a), b(b), c(c), Geometry(shading) {}

	glm::vec3 getNormal(glm::vec3 position) override;
};

class Sphere : public Geometry{
public:
	glm::vec3 origin;
	float radius;

	Sphere(glm::vec3 origin, float radius, ShadingInfo shading) 
		:origin(origin), radius(radius), Geometry(shading){}

	glm::vec3 getNormal(glm::vec3 position) override;
};

class Plane : public Geometry{
public:
	glm::vec3 origin, normal;

	Plane(glm::vec3 origin, glm::vec3 normal, ShadingInfo shading)
		:origin(origin), normal(normal), Geometry(shading)  {}

	glm::vec3 getNormal(glm::vec3 position) override;
};

class Ray{
public:
	glm::vec3 origin, dir;

	Ray() :origin(0.f), dir(0.f) {}
	Ray(glm::vec3 origin, glm::vec3 dir) :origin(origin), dir(dir) {}
};

Ray reflectRay(Ray ray, glm::vec3 pos, glm::vec3 normal);

class RayIntersection {
public:
	bool intersected;
	float t;
	glm::vec3 position;
	Ray ray;
	Geometry* object;

	RayIntersection():intersected(false), object(nullptr){}

	bool operator<(RayIntersection ray);
};

RayIntersection intersect(Ray ray, Sphere *sphere);
RayIntersection intersect(Ray ray, Triangle *triangle);
RayIntersection intersect(Ray ray, Plane *plane);


