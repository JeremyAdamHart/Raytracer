#pragma once

#include "Geometry.h"

using namespace glm;

vec3 Geometry::getNormal(vec3 position) {
	return vec3(0.f);
}

vec3 Triangle::getNormal(vec3 position){
	return normalize(cross(c - b, a - b));
}

vec3 Sphere::getNormal(vec3 position) {
	return normalize(position - origin);
}

vec3 Plane::getNormal(vec3 position) {
	return normal;
}

float quadraticFormula(float a, float b, float c, float sign) {
	return (-b + sign*sqrt(b*b - 4.f * a*c)) / (2.f * a);
}

RayIntersection intersect(Ray ray, Sphere *sphere) {
	RayIntersection intersection;

	float a = dot(ray.dir, ray.dir);
	float b = 2.f*dot(ray.dir, (ray.origin - sphere->origin));
	float c = dot(ray.origin - sphere->origin, ray.origin - sphere->origin) 
		- sphere->radius*sphere->radius;
	
	float discriminant = b*b - 4 * a*c;

	if (discriminant < 0.f) {
		return intersection;
	}

	float t1 = (-b - sqrt(discriminant)) / (2.f * a);
	float t2 = (-b + sqrt(discriminant)) / (2.f * a);

	if (t2 < 0)
		return intersection;

	intersection.intersected = true;
	intersection.t = (t1 > 0) ? t1 : t2;
	intersection.position = ray.origin + ray.dir*intersection.t;
	intersection.object = sphere;
	intersection.ray = ray;
	return intersection;
}

RayIntersection intersect(Ray ray, Triangle *triangle) {
	RayIntersection intersection;

	mat3 matrix = mat3(triangle->a - triangle->b, triangle->a - triangle->c, ray.dir);
	vec3 result = inverse(matrix)*(triangle->a - ray.origin);

	if (result.x < 0 || result.y < 0 || result.x + result.y > 1)
		return intersection;

	intersection.intersected = true;
	intersection.t = result.z;
	intersection.position = ray.origin + ray.dir*intersection.t;
	intersection.object = triangle;
	intersection.ray = ray;
	return intersection;
}

RayIntersection intersect(Ray ray, Plane *plane) {
	RayIntersection intersection;



	return intersection;
}


bool RayIntersection::operator<(RayIntersection ray) {
	return t < ray.t;
}


Ray reflectRay(Ray ray, vec3 pos, vec3 normal) {
	vec3 newDir = -dot(ray.dir, normal)*normal*2.f + ray.dir;

	return Ray(pos, newDir);
}