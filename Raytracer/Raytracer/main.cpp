/********************
* 2 Hour raytracer
********************/

#include "RayGenerator.h"
#include "Geometry.h"

using namespace glm;

int main() {

	Scene scene;
	Raytracer raytracer(800, 800);

	ShadingInfo red(0.4, 0.5, 0.4, 10, vec3(1, 0, 0));

	scene.triangles.push_back(Triangle(vec3(-0.5f, -0.5f, 2.f), vec3(0.5f, -0.5f, 2.f), vec3(0.f, 0.5f, 2.f), red));
	scene.lights.push_back(Light(vec3(5.f, 5.f, -10.f)));

	raytracer.renderScene(glm::radians(90.f), 0.5f, &scene);

	return 0;
}