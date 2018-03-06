#include "RayGenerator.h"
#include "ImageWriter.h"

using namespace glm;
using namespace std;

Raytracer::Raytracer(int width, int height) :width(width), height(height), pixels(width*height){

}

vec3 phongLighting(RayIntersection rayIntersect, Scene *scene) {
	Ray& ray = rayIntersect.ray;
	ShadingInfo& shading = rayIntersect.object->shading;
	vec3 normal = rayIntersect.object->getNormal(rayIntersect.position);
	vec3 viewer = -normalize(rayIntersect.position);
	
	vec3 color = shading.ka *shading.color;

	for (int l = 0; l < scene->lights.size(); l++) {
		vec3 light = normalize(scene->lights[l].pos - rayIntersect.position);
		Ray refLight = reflectRay(Ray(scene->lights[l].pos, -light), rayIntersect.position, normal);

		vec3 diffuse = shading.kd*dot(normal, light)*shading.color;
		vec3 specular = shading.ks*pow(dot(viewer, refLight.dir), shading.n)*shading.color;

		color += diffuse + specular;

	}

	return color;
}

void Raytracer::renderScene(float fov, float nearPlane, Scene *scene) {

	//Establish view plane
	float planeWidth = 2.f*tan(fov*0.5f)*nearPlane;
	float planeHeight = float(height)/ float(width)*planeWidth;

	float pixelWidth = planeWidth / float(width);
	float pixelHeight = planeHeight / float(height);

	vec3 topLeftLocation = vec3((-planeWidth - pixelWidth)*0.5f, (planeHeight - pixelHeight)*.5f, nearPlane);

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			glm::vec3 rayOrigin = topLeftLocation + vec3(float(i)*pixelWidth, -float(j)*pixelWidth, 0.f);
			Ray ray = Ray(rayOrigin, normalize(rayOrigin));

			vector<RayIntersection> intersectionList = intersect(ray, scene, 1);
			vec3 color = vec3(0.f);
			float rayContribution = 1.f;
			for (int k = 0; k < intersectionList.size(); k++) {
				float reflectivity = intersectionList[k].object->shading.reflectivity;
				color += rayContribution*(1-reflectivity)*phongLighting(intersectionList[k], scene);
				rayContribution *= reflectivity;
			}

			pixels[j*height + i] = color;

		}
	}

	writePng(pixels.data(), width, height, "Output.png");

}