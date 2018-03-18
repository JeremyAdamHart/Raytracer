#include "Shader.h"
#include "Scene.h"
#include "Light.h"
#include "Geometry.h"
#include "Sampler.h"

using namespace std;
using namespace glm;

const float SPECULAR_EFFICIENCY = 0.3f;
const float DIFFUSE_EFFICIENCY = 0.3f;

vec3 Shader::calculateShading(RayIntersection ray, const Scene *scene) { return vec3(0); }

PhongShader::PhongShader(vec3 color, float reflectivity, float n, float transparency, bool metallic) :
	color(color), reflectivity(reflectivity), n(n), transparency(transparency), metallic(metallic) {}

vec3 PhongShader::calculateShading(RayIntersection point, const Scene *scene)
{
	vec3 viewerDir = -point.ray.dir;
	vec3 pointColor = scene->ambient*color;

	vec3 diffuse = vec3(0.f);
	vec3 specular = vec3(0.f);

	for (int i = 0; i < scene->lights.size(); i++) {
		shared_ptr<const Light> light = scene->lights[i];
		vec3 lightColor = light->lightIntensity(point.position);
		float lightIntensity = length(lightColor);
		vec3 lightDir = light->lightDir(point.position);
		vec3 refLightDir = reflect(-lightDir, point.position, point.normal);

		diffuse += lightIntensity*clamp(dot(point.normal, lightDir), 0.f, 1.f)*color;
		specular += clamp(dot(point.normal, lightDir), 0.f, 1.f)*pow(clamp(dot(viewerDir, refLightDir), 0.f, 1.f), n)*lightColor;
	}
	
	if (point.ray.remainingBounces > 0 && reflectivity > 0.001f) {
		const float REFLECTION_SAMPLES = 100;

		for (int i = 0; i < REFLECTION_SAMPLES; i++) {
			vec3 reflectedRayDir = reflect(point.ray.dir, point.position, point.normal);
			reflectedRayDir = sampleDirection(reflectedRayDir, 3.14159f / 12.f, 0.5f);
			Ray reflectedRay = Ray(	point.position,
									reflectedRayDir,
									point.ray.remainingBounces - 1);
			RayIntersection reflectedPoint = intersect(reflectedRay, scene);
			vec3 reflectedColor = scene->backgroundColor;
			if(reflectedPoint.intersected)
				reflectedColor = reflectedPoint.materialHit->calculateShading(reflectedPoint, scene);	//THIS IS AWFUL
			//Put specular on right side of summation?
			specular += reflectedColor/float(REFLECTION_SAMPLES);
		}
	}

	return (1 - reflectivity)*(scene->ambient*color + diffuse*DIFFUSE_EFFICIENCY) 
			+ reflectivity*specular*SPECULAR_EFFICIENCY;
}