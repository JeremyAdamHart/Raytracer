#include "RayGenerator.h"
#include "ImageWriter.h"

using namespace glm;
using namespace std;

Camera::Camera() :origin(vec3(0.f)), cx(vec3(1, 0, 0)), cy(vec3(0, 1, 0)), cz(vec3(0, 0, 1)) {}

Camera::Camera(vec3 origin, vec3 dir, vec3 up) : origin(origin), cz(normalize(vec3(-dir))) {
	cx = normalize(cross(dir, up));
	cy = normalize(cross(cx, dir));
}

Raytracer::Raytracer(int width, int height) :width(width), height(height), pixels(width*height){

}


void Raytracer::renderScene(Camera cam, float fov, float nearPlane, Scene *scene, int maxBounces) {

	//Establish view plane
	float planeWidth = 2.f*tan(fov*0.5f)*nearPlane;
	float planeHeight = float(height)/ float(width)*planeWidth;

	float pixelWidth = planeWidth / float(width);
	float pixelHeight = planeHeight / float(height);

	vec3 topLeftLocation = vec3((-planeWidth - pixelWidth)*0.5f, (planeHeight - pixelHeight)*.5f, -nearPlane);

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			glm::vec3 rayOrigin = topLeftLocation + vec3(float(i)*pixelWidth, -float(j)*pixelWidth, 0.f);
			Ray ray = Ray(rayOrigin, normalize(rayOrigin), maxBounces-1);

			RayIntersection rayIntersect = intersect(ray, scene);
			vec3 color = scene->backgroundColor;
			if(rayIntersect.intersected)
				color = rayIntersect.materialHit->calculateShading(rayIntersect, scene);

			pixels[j*height + i] = color;

		}
	}

	writePng(pixels.data(), width, height, "Output.png");

}