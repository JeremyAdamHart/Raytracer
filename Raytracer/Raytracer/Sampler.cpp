#include "Sampler.h"

#include <glm/gtc/quaternion.hpp>

using namespace glm;

//http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-17-quaternions/#how-do-i-find-the-rotation-between-2-vectors-
quat RotationBetweenVectors(vec3 start, vec3 dest) {
	start = normalize(start);
	dest = normalize(dest);

	float cosTheta = dot(start, dest);
	vec3 rotationAxis;

	if (cosTheta < -1 + 0.001f) {
		// special case when vectors in opposite directions:
		// there is no "ideal" rotation axis
		// So guess one; any will do as long as it's perpendicular to start
		rotationAxis = cross(vec3(0.0f, 0.0f, 1.0f), start);
		if (length(rotationAxis) < 0.01) // bad luck, they were parallel, try again!
			rotationAxis = cross(vec3(1.0f, 0.0f, 0.0f), start);

		rotationAxis = normalize(rotationAxis);
		return angleAxis(glm::radians(180.0f), rotationAxis);
	}

	rotationAxis = cross(start, dest);

	float s = sqrt((1 + cosTheta) * 2);
	float invs = 1 / s;

	return quat(
		s * 0.5f,
		rotationAxis.x * invs,
		rotationAxis.y * invs,
		rotationAxis.z * invs
	);

}

float rand01() {
	return float(rand()) / float(RAND_MAX);
}

glm::vec3 sampleDirection(glm::vec3 up, float angle, float exponent) {

	const float PI_F = 3.14159265359;

	float cos_angle = cos(angle);
	float z = pow(rand01(), exponent)*(1.f - cos_angle) + cos_angle;
	float theta = 2.f*PI_F*rand01();

	vec3 dir (sqrt(1 - z*z)*cos(theta), sqrt(1 - z*z)*sin(theta), z);

	return glm::mat3_cast(RotationBetweenVectors(vec3(0, 0, 1), up)) * dir;
}