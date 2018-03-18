/********************
* 2 Hour raytracer
********************/
#include <memory>
#include <random>
#include <ctime>

#include "RayGenerator.h"
#include "Geometry.h"
#include "Shader.h"
#include "SceneObject.h"
#include "Scene.h"

using namespace glm;
using namespace std;

int main() {

	srand(time(0));

	Scene scene(0.3f, vec3(0.3f));
	Raytracer raytracer(800, 800);

	/*
	ShadingInfo red(0.4, 0.5, 0.4, 10, vec3(1, 0, 0), 0.5f);
	ShadingInfo blue(0.4, 0.5, 0.4, 10, vec3(0, 0, 1), 0.5f);
	ShadingInfo green(0.4, 0.5, 0.4, 10, vec3(0, 1, 0), 0.5f);
	*/

	PhongShader red (vec3(1, 0, 0), 0.5f, 10.f);
	PhongShader green(vec3(0, 1, 0), 0.8f, 30.f);
	PhongShader blue(vec3(0, 0, 1), 0.5f, 4.f);

	vec3 offset(1.f, 0.f, -1.5f);

	std::shared_ptr<SphereLight> sphereLight = 
		shared_ptr<SphereLight>(new SphereLight(vec3(10, 10, 10)*0.5f, 2.f, vec3(1, 1, 1)*20.f, 100));

	scene.add(SceneTriangle(Triangle(
		vec3(-0.5f, -0.5f, -2.f) + offset, 
		vec3(0.5f, -0.5f, -2.f) + offset,
		vec3(0.f, 0.5f, -2.f) + offset), &red));
	scene.add(SceneSphere(Sphere(vec3(0.0f, 0.f, -5.f), 0.5f), &blue));
	scene.add(ScenePlane(Plane(vec3(0.0, -0.5f, 0.0), vec3(0, 1, 0)), &green));
//	scene.add(std::shared_ptr<Light>(new DirectionalLight(vec3(-0.5, -0.5, -0.5), vec3(1, 1, 1)*2.f)));
	scene.add(sphereLight);

	raytracer.renderScene(glm::radians(90.f), 0.5f, &scene, 2);

	return 0;
}