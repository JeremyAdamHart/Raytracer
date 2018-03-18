#pragma once

#include <glm/glm.hpp>
#include "SceneObject.h"

class Light : public SceneObject {
protected:
	Light() {}
public:
	virtual glm::vec3 lightIntensity(glm::vec3 point) const { return glm::vec3(); }
	//Direction from point to light
	virtual glm::vec3 lightDir(glm::vec3 point) const { return glm::vec3(); }
};

class DirectionalLight : public Light {
public:
	glm::vec3 dir;
	glm::vec3 intensity;
	int samples;

	DirectionalLight(glm::vec3 dir = glm::vec3(0), glm::vec3 intensity = glm::vec3(0), int samples=1);

	glm::vec3 lightIntensity(glm::vec3 point) const override;
	glm::vec3 lightDir(glm::vec3 point) const override;
};

class PointLight : public Light {
public:
	glm::vec3 pos;
	glm::vec3 intensity;
	int samples;

	PointLight(glm::vec3 pos = glm::vec3(0), glm::vec3 intensity = glm::vec3(0), int samples=1);

	glm::vec3 lightIntensity(glm::vec3 point) const override;
	glm::vec3 lightDir(glm::vec3 point) const override;
};

class SphereLight : public Light {
	glm::vec3 sampleSphere() const;

public:
	glm::vec3 pos;
	float radius;
	glm::vec3 intensity;
	int samples;

	SphereLight(glm::vec3 pos = glm::vec3(0), float radius = 0.f, 
		glm::vec3 intensity = glm::vec3(0), int samples = 1);

	glm::vec3 lightIntensity(glm::vec3 point) const override;
	glm::vec3 lightDir(glm::vec3 point) const override;
};
