#include "pch.h"
#include <3DEngine/Scene3D/RenderableSceneObject.h>

namespace RenderEngine {

	RenderableSceneObject::RenderableSceneObject(glm::vec3&& inPosition, glm::vec3&& inScale, glm::vec3&& inRotationAxis,
		float inRadianRotation, Model* inModel, RenderableSceneObject* inParent, bool inIsStatic, bool inIsTransparent)
		: mPosition(inPosition)
		, mScale(inScale)
		, mOrientation(glm::angleAxis(inRadianRotation, inRotationAxis))
		, mModel(inModel)
		, mIsStatic(inIsStatic)
		, mIsTransparent(inIsTransparent)
	{
	}

	RenderableSceneObject::~RenderableSceneObject() 
	{			   
		if (mModel) {
			delete mModel;
			mModel = nullptr;
		}	
	}

	void RenderableSceneObject::draw(Shader *shader, RenderPassType pass) const 
	{
		if(mModel)
			mModel->Draw(shader, pass);
	}
}
