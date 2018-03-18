#include "Scene.h"

#include <algorithm>
#include <limits>

using namespace glm;
using namespace std;

const float INTERSECTION_OFFSET = 0.001f;

void Scene::add(shared_ptr<Light> light) {
	light->parentScene = this;
	lights.push_back(light);
}

void Scene::add(SceneTriangle triangle) {
	triangle.parentScene = this;
	triangles.push_back(triangle);
}

void Scene::add(SceneSphere sphere) {
	sphere.parentScene = this;
	spheres.push_back(sphere);
}

void Scene::add(ScenePlane plane) {
	plane.parentScene = this;
	planes.push_back(plane);
}

RayIntersection intersect(Ray ray, const Scene *scene) {
	RayIntersection closestIntersection;
	closestIntersection.t = numeric_limits<float>::max();

	//Test triangle intersections
	for (int i = 0; i < scene->triangles.size(); i++) {
		RayIntersection intersection = intersect(ray, &scene->triangles[i].geometry);
		if (intersection.intersected && intersection.t < closestIntersection.t) {
			closestIntersection = intersection;
			closestIntersection.materialHit = scene->triangles[i].shader;
		}
	}

	//Test sphere intersections
	for (int i = 0; i < scene->spheres.size(); i++) {
		RayIntersection intersection = intersect(ray, &scene->spheres[i].geometry);
		if (intersection.intersected && intersection.t < closestIntersection.t) {
			closestIntersection = intersection;
			closestIntersection.materialHit = scene->spheres[i].shader;
		}
	}

	//Test plane intersections
	for (int i = 0; i < scene->planes.size(); i++) {
		RayIntersection intersection = intersect(ray, &scene->planes[i].geometry);
		if (intersection.intersected && intersection.t < closestIntersection.t) {
			closestIntersection = intersection;
			closestIntersection.materialHit = scene->planes[i].shader;
		}
	}

	return closestIntersection;
}

bool shadowIntersect(Ray ray, const Scene *scene, float lightDist) {

	//Test triangle intersections
	for (int i = 0; i < scene->triangles.size(); i++) {
		RayIntersection intersection = intersect(ray, &scene->triangles[i].geometry);
		if (intersection.intersected && intersection.t < lightDist)
			return true;
	}

	//Test sphere intersections
	for (int i = 0; i < scene->spheres.size(); i++) {
		RayIntersection intersection = intersect(ray, &scene->spheres[i].geometry);
		if (intersection.intersected && intersection.t < lightDist)
			return true;
	}

	//Test plane intersections
	for (int i = 0; i < scene->planes.size(); i++) {
		RayIntersection intersection = intersect(ray, &scene->planes[i].geometry);
		if (intersection.intersected && intersection.t < lightDist)
			return true;
	}

	return false;
}

/*vector<RayIntersection> intersect(Ray ray, const Scene *scene, int maxIntersections) {
	vector<RayIntersection> intersectionList;
	
	Ray currentRay = ray;

	while (intersectionList.size() < maxIntersections) {
		vector<RayIntersection> currentIntersections;

		//Test triangle intersections
		for (int i = 0; i < scene->triangles.size(); i++) {
			RayIntersection intersection = intersect(currentRay, &scene->triangles[i]);
			if (intersection.intersected)
				currentIntersections.push_back(intersection);
		}

		//Test sphere intersections
		for (int i = 0; i < scene->spheres.size(); i++) {
			RayIntersection intersection = intersect(currentRay, &scene->spheres[i]);
			if (intersection.intersected)
				currentIntersections.push_back(intersection);
		}

		//Test plane intersections
		for (int i = 0; i < scene->planes.size(); i++) {
			RayIntersection intersection = intersect(currentRay, &scene->planes[i]);
			if (intersection.intersected)
				currentIntersections.push_back(intersection);
		}

		if (currentIntersections.size() == 0)
			break;
		else {
			//Push back closest intersection
			intersectionList.push_back(*(min_element(currentIntersections.begin(), currentIntersections.end())));
			vec3 normal = intersectionList.back().object->getNormal(intersectionList.back().position);
			currentRay = reflectRay(	currentRay,
										intersectionList.back().position + normal*INTERSECTION_OFFSET,
										normal);
		}
	}

	return intersectionList;
}*/