#include "Scene.h"

#include <algorithm>

using namespace glm;
using namespace std;

vector<RayIntersection> intersect(Ray ray, Scene *scene, int maxIntersections) {
	vector<RayIntersection> intersectionList;
	
	Ray currentRay = ray;

	while (intersectionList.size() < maxIntersections) {
		vector<RayIntersection> currentIntersections;

		//Test triangle intersections
		for (int i = 0; i < scene->triangles.size(); i++) {
			RayIntersection intersection = intersect(ray, &scene->triangles[i]);
			if (intersection.intersected)
				currentIntersections.push_back(intersection);
		}

		//Test sphere intersections
		for (int i = 0; i < scene->spheres.size(); i++) {
			RayIntersection intersection = intersect(ray, &scene->spheres[i]);
			if (intersection.intersected)
				currentIntersections.push_back(intersection);
		}

		//Test plane intersections
		for (int i = 0; i < scene->planes.size(); i++) {
			RayIntersection intersection = intersect(ray, &scene->planes[i]);
			if (intersection.intersected)
				currentIntersections.push_back(intersection);
		}

		if (currentIntersections.size() == 0)
			break;
		else {
			//Push back closest intersection
			intersectionList.push_back(*(min_element(currentIntersections.begin(), currentIntersections.end())));

			currentRay = reflectRay(	currentRay,
										intersectionList.back().position,
										intersectionList.back().object->getNormal(intersectionList.back().position));

		}
	}

	return intersectionList;
}