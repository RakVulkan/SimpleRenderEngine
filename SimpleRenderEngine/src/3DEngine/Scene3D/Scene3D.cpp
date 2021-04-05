#include "pch.h"
#include "Scene3D.h"
#include <string>
#include <3DEngine/mesh/Mesh.h>
#include <3DEngine/mesh/common/Cube.h>
#include <3DEngine/mesh/common/Quad.h>

namespace RenderEngine {

	Scene3D::Scene3D(Window* inWindow)
		: mSceneCamera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f) 
		, mSceneObjectRenderer(getCamera())
		, mLightManager(new LightManager())
	{   
		// Get the OpenGL global state
		mGLState = GLState::getInstance();
		init();
	}

	Scene3D::~Scene3D() 
	{
		if (mSkybox) {
			delete mSkybox;
			mSkybox = nullptr;
		}

		if (mLightManager) {
			delete mLightManager;
			mLightManager = nullptr;
		}
		
		for (auto *lRenderableObject : mRenderableSceneObjects) {
			delete lRenderableObject;	
			lRenderableObject = nullptr;
		}		
	}

	// Intializes all the scene objects along with material properties. 
	void Scene3D::init() 
	{   
		TextureSettings srgbTextureSettings;
		srgbTextureSettings.IsSRGB = true;
    
		// PBR Gun model
		Model *lPbrGunModel = new RenderEngine::Model("resources/3DModels/Cerberus/cerberus.FBX");
		mRenderableSceneObjects.push_back(new RenderableSceneObject(glm::vec3(950.0f, 165.5f, 1000.0f), 
			glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::radians(-90.0f), lPbrGunModel, nullptr, true, false));
        
		// Materials setup for PBR Gun model
		Texture* lPbrGunModelAlbedo = TextureLoader::load2DTexture(std::string("resources/3DModels/Cerberus/cerberus_A.png"));
		Texture* lPbrGunModelNormal = TextureLoader::load2DTexture(std::string("resources/3DModels/Cerberus/cerberus_N.png"));
		Texture* lPbrGunModelMetallic = TextureLoader::load2DTexture(std::string("resources/3DModels/Cerberus/cerberus_M.png"));
		Texture* lPbrGunModelRoughness = TextureLoader::load2DTexture(std::string("resources/3DModels/Cerberus/cerberus_R.png"));
		lPbrGunModel->getMeshes()[0].getMaterial().setAlbedoMap(lPbrGunModelAlbedo);
		lPbrGunModel->getMeshes()[0].getMaterial().setNormalMap(lPbrGunModelNormal);
		lPbrGunModel->getMeshes()[0].getMaterial().setMetallicMap(lPbrGunModelMetallic);
		lPbrGunModel->getMeshes()[0].getMaterial().setRoughnessMap(lPbrGunModelRoughness);

		// Floor model
		Model* lFloorModel = new RenderEngine::Model("resources/3DModels/Floor.obj");	
		mRenderableSceneObjects.push_back(new RenderableSceneObject(glm::vec3(950.0f, -50.0f, 1000.0f), 
			glm::vec3(200.0f, 200.0f, 200.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::radians(0.0f), lFloorModel, nullptr, true, false));

		// Materials setup for Floor model
		Texture* lPlaneAlbedo = TextureLoader::load2DTexture(std::string("resources/textures/PBR/HardwoodBrown/hardwood-brown-planks-albedo.png"));
		Texture* lPlaneNormal = TextureLoader::load2DTexture(std::string("resources/textures/PBR/HardwoodBrown/hardwood-brown-planks-normal-dx.png"));
		Texture* lPlaneMettalic = TextureLoader::load2DTexture(std::string("resources/textures/PBR/HardwoodBrown/hardwood-brown-planks-metallic.png"));
		Texture* lPlaneRoughness = TextureLoader::load2DTexture(std::string("resources/textures/PBR/HardwoodBrown/hardwood-brown-planks-roughness.png"));
		Texture* lPlaneAo = TextureLoader::load2DTexture(std::string("resources/textures/PBR/HardwoodBrown/hardwood-brown-planks-ao.png"));

		lFloorModel->getMeshes()[0].getMaterial().setAlbedoMap(lPlaneAlbedo);
		lFloorModel->getMeshes()[0].getMaterial().setNormalMap(lPlaneNormal);
		lFloorModel->getMeshes()[0].getMaterial().setMetallicMap(lPlaneMettalic);
		lFloorModel->getMeshes()[0].getMaterial().setRoughnessMap(lPlaneRoughness);
		lFloorModel->getMeshes()[0].getMaterial().setAmbientOcclusionMap(lPlaneAo);
		
		// PBR Shiny Metal Sphere
		Model* lPbrShinyMetalSphere = new RenderEngine::Model("resources/3DModels/Sphere/globe-sphere.obj");
		mRenderableSceneObjects.push_back(new RenderableSceneObject(glm::vec3(1000.0f, 200.0f, 500.0f), 
			glm::vec3(150.0f, 150.0f, 150.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::radians(-90.0f), lPbrShinyMetalSphere, nullptr, true, false));

		Texture* lPbrShinyAmbient = TextureLoader::load2DTexture(std::string("resources/textures/PBR/ShinyMetal/worn-shiny-metal-albedo.png"));
		Texture* lPbrShinyNormal = TextureLoader::load2DTexture(std::string("resources/textures/PBR/ShinyMetal/worn-shiny-metal-Normal-dx.png"));
		Texture* lPbrShinyMetallic = TextureLoader::load2DTexture(std::string("resources/textures/PBR/ShinyMetal/worn-shiny-metal-Metallic.png"));
		Texture* lPbrShinyRoughness = TextureLoader::load2DTexture(std::string("resources/textures/PBR/ShinyMetal/worn-shiny-metal-Roughness.png"));
		Texture* lPbrShinyAo = TextureLoader::load2DTexture(std::string("resources/textures/PBR/ShinyMetal/worn-shiny-metal-ao.png"));
		lPbrShinyMetalSphere->getMeshes()[0].getMaterial().setAlbedoMap(lPbrShinyAmbient);
		lPbrShinyMetalSphere->getMeshes()[0].getMaterial().setNormalMap(lPbrShinyNormal);
		lPbrShinyMetalSphere->getMeshes()[0].getMaterial().setMetallicMap(lPbrShinyMetallic);
		lPbrShinyMetalSphere->getMeshes()[0].getMaterial().setRoughnessMap(lPbrShinyRoughness);
		lPbrShinyMetalSphere->getMeshes()[0].getMaterial().setAmbientOcclusionMap(lPbrShinyAo);

		// PBR Plastic Sphere
		Model* lPbrPlasticSphere = new RenderEngine::Model("resources/3DModels/Sphere/globe-sphere.obj");
		mRenderableSceneObjects.push_back(new RenderableSceneObject(glm::vec3(1200.0f, 200.0f, 650.0f), glm::vec3(150.0f, 150.0f, 150.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::radians(-90.0f), lPbrPlasticSphere, nullptr, true, false));

		Texture* lPbrPlasticSphereAlbedo = TextureLoader::load2DTexture(std::string("resources/textures/PBR/Plastic/albedo.png"));
		Texture* lPbrPlasticSphereNormal = TextureLoader::load2DTexture(std::string("resources/textures/PBR/Plastic/normal.png"));
		Texture* lPbrPlasticSphereMetallic = TextureLoader::load2DTexture(std::string("resources/textures/PBR/Plastic/metallic.png"));
		Texture* lPbrPlasticSphereRoughness = TextureLoader::load2DTexture(std::string("resources/textures/PBR/Plastic/roughness.png"));
		Texture* lPbrPlasticSphereAo = TextureLoader::load2DTexture(std::string("resources/textures/PBR/Plastic/ao.png"));
		lPbrPlasticSphere->getMeshes()[0].getMaterial().setAlbedoMap(lPbrPlasticSphereAlbedo);
		lPbrPlasticSphere->getMeshes()[0].getMaterial().setNormalMap(lPbrPlasticSphereNormal);
		lPbrPlasticSphere->getMeshes()[0].getMaterial().setMetallicMap(lPbrPlasticSphereMetallic);
		lPbrPlasticSphere->getMeshes()[0].getMaterial().setRoughnessMap(lPbrPlasticSphereRoughness);
		lPbrPlasticSphere->getMeshes()[0].getMaterial().setAmbientOcclusionMap(lPbrPlasticSphereAo);

		// PBR Rusted Iron Sphere
		Model* lPbrSphereRustedIron = new RenderEngine::Model("resources/3DModels/Sphere/globe-sphere.obj");
		mRenderableSceneObjects.push_back(new RenderableSceneObject(glm::vec3(946.9f, 165.5f, 859.0f), 
			glm::vec3(150.0f, 150.0f, 150.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::radians(-90.0f), lPbrSphereRustedIron, nullptr, true, false));

		Texture* lPbrSphereRustedIronAlbedo = TextureLoader::load2DTexture(std::string("resources/textures/PBR/Gold/albedo.png"));
		Texture* lPbrSphereRustedIronNormal = TextureLoader::load2DTexture(std::string("resources/textures/PBR/Gold/normal.png"));
		Texture* lPbrSphereRustedIronMetallic = TextureLoader::load2DTexture(std::string("resources/textures/PBR/Gold/metallic.png"));
		Texture* lPbrSphereRustedIronRoughness = TextureLoader::load2DTexture(std::string("resources/textures/PBR/Gold/roughness.png"));
		Texture* lPbrSphereRustedIronAo = TextureLoader::load2DTexture(std::string("resources/textures/PBR/Gold/ao.png"));

		lPbrSphereRustedIron->getMeshes()[0].getMaterial().setAlbedoMap(lPbrSphereRustedIronAlbedo);
		lPbrSphereRustedIron->getMeshes()[0].getMaterial().setNormalMap(lPbrSphereRustedIronNormal);
		lPbrSphereRustedIron->getMeshes()[0].getMaterial().setMetallicMap(lPbrSphereRustedIronMetallic);
		lPbrSphereRustedIron->getMeshes()[0].getMaterial().setRoughnessMap(lPbrSphereRustedIronRoughness);
		lPbrSphereRustedIron->getMeshes()[0].getMaterial().setAmbientOcclusionMap(lPbrSphereRustedIronAo); 		

		// Skybox
		std::vector<std::string> skyboxFilePaths;
		skyboxFilePaths.push_back("resources/skybox/right.png");
		skyboxFilePaths.push_back("resources/skybox/left.png");
		skyboxFilePaths.push_back("resources/skybox/top.png");
		skyboxFilePaths.push_back("resources/skybox/bottom.png");
		skyboxFilePaths.push_back("resources/skybox/back.png");
		skyboxFilePaths.push_back("resources/skybox/front.png");
		mSkybox = new Skybox(skyboxFilePaths);

		// Set Camera position
		mSceneCamera.setPosition(glm::vec3(1100.0f, 400.0f, 1600.0f));
	}

	// When the scene got updated, camera and light position will be updated
	void Scene3D::onUpdate(float deltaTime) 
	{
		// Camera Update
		mSceneCamera.processInput(deltaTime);
		mLightManager->setSpotLightDirection(0, mSceneCamera.getFront());
		mLightManager->setSpotLightPosition(0, mSceneCamera.getPosition());
	}

	// Iterate over the list of renderable scene objects and seprate the objects into opaque , transparent objects.
	// The separation of opaque and transparent objects adds benefit to achieve better FPS
	void Scene3D::addSceneObjectsToRenderer()
	{
		auto iter = mRenderableSceneObjects.begin();
		while (iter != mRenderableSceneObjects.end()) {
			RenderableSceneObject *curr = *iter;
			if (curr->getTransparent()) {
				mSceneObjectRenderer.addTransparentObject(curr); 
			}
			else {
				mSceneObjectRenderer.addOpaqueObject(curr);
			}
			iter++;
		}
	}
}
