#pragma once

#include "Shader.h"

class Scene;

class SceneObject {
protected:
	SceneObject() {}
public:
	const Scene *parentScene;

};

template <class G> 
class SceneGeometry : public SceneObject{
public:
	G geometry;
	Shader *shader;

	SceneGeometry(G geometry, Shader *shader):geometry(geometry), shader(shader) {}

};