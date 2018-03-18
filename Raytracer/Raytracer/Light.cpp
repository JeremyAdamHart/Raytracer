#include "Light.h"
#include "Scene.h"
#include "Sampler.h"

#include <random>

using namespace glm;

const float PI = 3.14159265359;

DirectionalLight::DirectionalLight(vec3 dir, vec3 intensity, int samples) 
	:dir(normalize(dir)), intensity(intensity), samples(samples) {}

vec3 DirectionalLight::lightIntensity(vec3 point) const{
	if (!shadowIntersect(Ray(point, lightDir(point)), parentScene))
		return intensity;
	else
		return vec3(0.f);
}

vec3 DirectionalLight::lightDir(vec3 point) const {
	return -dir;
}

PointLight::PointLight(vec3 pos, vec3 intensity, int samples)
	:pos(pos), intensity(intensity), samples(samples) {}

vec3 PointLight::lightIntensity(vec3 point) const {
	Ray shadowRay(point, lightDir(point));
	if (!shadowIntersect(shadowRay, parentScene, dot(shadowRay.dir, pos - point)))
		return intensity / length(point - pos);
	else
		return vec3(0.f);
}

vec3 PointLight::lightDir(vec3 point) const {
	return normalize(pos - point);
}

SphereLight::SphereLight(vec3 pos, float radius, vec3 intensity, int samples)
	:pos(pos), intensity(intensity), samples(samples), radius(radius) {}



vec3 SphereLight::sampleSphere() const {
	float z = 2.f*rand01() - 1.f;
	float theta = 2.f*PI*rand01();

	return vec3(sqrt(1 - z*z)*cos(theta), sqrt(1 - z*z)*sin(theta), z)*radius + pos;
}

vec3 SphereLight::lightIntensity(vec3 point) const {
	
	float visibility = 0.f;
	for (int i = 0; i < samples; i++) {
		vec3 lightSample = sampleSphere();
		Ray shadowRay(point, lightSample - point);
		if (!shadowIntersect(shadowRay, parentScene, dot(shadowRay.dir, lightSample - point)))
			visibility += 1.f;
	}

	visibility /= float(samples);

	return visibility*intensity / length(point - pos);
}

vec3 SphereLight::lightDir(vec3 point) const {
	return normalize(pos - point);
}
