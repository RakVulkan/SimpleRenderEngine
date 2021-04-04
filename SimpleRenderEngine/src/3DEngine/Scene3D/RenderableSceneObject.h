#pragma once

#include <3DEngine/mesh/Model.h>
#include <3DEngine/Renderer/renderpass/RenderPassType.h>

namespace RenderEngine {

	class RenderableSceneObject {
	public:
		RenderableSceneObject(glm::vec3&& inPosition, glm::vec3&& inScale, glm::vec3&& inRotationAxis, 
			float inRadianRotation, Model* inModel, RenderableSceneObject* inParent, bool inIsStatic = false, bool inIsTransparent = false);
		~RenderableSceneObject();

		// Assumes shader is already bound by the renderer
		void draw(Shader* inShader, RenderPassType inRenderPassType) const;

		inline const glm::vec3& getPosition() const { return mPosition; }
		inline const glm::vec3& getScale() const { return mScale; }
		inline const glm::quat& getOrientation() const { return mOrientation; }
		inline bool getTransparent() const { return mIsTransparent; }
		inline bool getStatic() const { return mIsStatic; }

		inline void setPosition(glm::vec3& inOther) { mPosition = inOther; }
		inline void setScale(glm::vec3& inOther) { mScale = inOther; }
		inline void setOrientation(float inRadianRotation, glm::vec3 inRotationAxis) { mOrientation = glm::angleAxis(inRadianRotation, inRotationAxis); }
		inline void setTransparent(bool inChoice) { mIsTransparent = inChoice; }		

	private:
		// Transformation data
		glm::vec3 mPosition, mScale;
		glm::quat mOrientation;
	
		Model *mModel;

		// Should be true if the model contains any translucent material
		bool mIsTransparent; 
		// Should be true if the model will never have its transform modified
		bool mIsStatic;	  
	};

}
