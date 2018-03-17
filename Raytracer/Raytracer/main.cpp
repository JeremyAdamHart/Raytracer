/********************
* 2 Hour raytracer
********************/

#include "RayGenerator.h"
#include "Geometry.h"

using namespace glm;

int main() {

	Scene scene;
	Raytracer raytracer(800, 800);

	ShadingInfo red(0.4, 0.5, 0.4, 10, vec3(1, 0, 0), 0.5f);
	ShadingInfo blue(0.4, 0.5, 0.4, 10, vec3(0, 0, 1), 0.5f);
	ShadingInfo green(0.4, 0.5, 0.4, 10, vec3(0, 1, 0), 0.5f);

	vec3 offset(1.f, 0.f, 1.5f);

	scene.triangles.push_back(Triangle(
		vec3(-0.5f, -0.5f, 2.f) + offset, 
		vec3(0.5f, -0.5f, 2.f) + offset,
		vec3(0.f, 0.5f, 2.f) + offset, red));
	scene.spheres.push_back(Sphere(vec3(0.0f, 0.f, 5.f), 0.5f, blue));
	scene.lights.push_back(Light(vec3(5.f, 5.f, -10.f)));

	scene.planes.push_back(Plane(vec3(0.0, -0.5f, 0.0), vec3(0, 1, 0), green));

	raytracer.renderScene(glm::radians(90.f), 0.5f, &scene);

	return 0;
}