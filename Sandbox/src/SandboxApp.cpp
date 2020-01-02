#include "SandboxApp.h"
SandboxApp::SandboxApp() {
	this->LoadLevel(1);
}
void SandboxApp::LoadLevel(int level) {
	sol::state lua;
	lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);

	lua.set_function("AddTexture", [this](std::string textureId, std::string filePath) {
		AssetManager::AddTexture(textureId, filePath.c_str());
	});

	lua.set_function("AddFont", [this](std::string fontId, std::string filePath, int fontSize) {
		AssetManager::AddFont(fontId, filePath.c_str(), fontSize);
	});
	 
	lua.set_function("CreateLayer", [this](std::string layerName) -> Layer* {
		Layer* newLayer = new Layer(layerName);
		newLayer->manager = layerManager;
		layerManager->AddLayer(newLayer);
		return newLayer;
	});
	

	lua.set_function("CreateTileMap", [this](sol::table params){
		Layer* parentLayer = params["parentLayer"];
		std::string textureId = params["textureId"];
		std::string mapFile = params["file"];
		int mapScale = params["scale"];
		int tileSize = params["tileSize"];
		int mapSizeX = params["mapSizeX"];
		int mapSizeY = params["mapSizeY"];
		map = new Map(parentLayer, AssetManager::GetTexture(textureId), mapScale, tileSize);
		map->LoadMap(mapFile, mapSizeX, mapSizeY);
	});

	lua.set_function("CreateGameEntity", [this](sol::table params) -> Entity* {
		sol::optional<std::string> scriptFile = params["scriptFile"];
		std::string name = params["name"];
		Layer* layer = params["layer"];
		Entity* newEntity = new Entity(name);
		if (scriptFile != sol::nullopt) {
			newEntity->AttachScriptFile(scriptFile.value());
		}

		layer->AddEntity(newEntity);
		newEntity->ownerLayer = layer;
		return newEntity;
	});


	lua.set_function("AttachCameraToEntity", [this](Entity* e) {
		CameraAttachedEntity = e;
	});
	
	
	std::string levelName = "Level" + std::to_string(level);
	lua.script_file(".\\src\\assets\\scripts\\" + levelName + ".lua");
	sol::function loadAssets = lua["loadAssets"];
	sol::function start = lua["start"];
	loadAssets();
	start();
	
	layerManager->GetCollidableEntities();
}

void SandboxApp::Render() {
	SDL_RenderClear(Renderer::renderer);
	layerManager->Render(Renderer::renderer);
	SDL_RenderPresent(Renderer::renderer);
}

void SandboxApp::Update() {
	// Setting up a basic game loop, + clamping the deltaTime
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME));

	float deltaTime = this->GetDeltaTime();
	layerManager->Update(deltaTime);
	HandleCameraMovement();
	CheckCollisions();
}


void SandboxApp::HandleCameraMovement() {
	if (CameraAttachedEntity) {
		Transform* CameraAttachedEntityTrasnform = CameraAttachedEntity->GetComponent<Transform>();
		Camera::source.x = CameraAttachedEntityTrasnform->position.x - (WINDOW_WIDTH / 2);
		Camera::source.y = CameraAttachedEntityTrasnform->position.y - (WINDOW_HEIGHT / 2);
		Camera::source.x = Camera::source.x < 0 ? 0 : Camera::source.x;
		Camera::source.y = Camera::source.y < 0 ? 0 : Camera::source.y;

		Camera::source.x = Camera::source.x > Camera::source.w ? Camera::source.w : Camera::source.x;
		Camera::source.y = Camera::source.y > Camera::source.h ? Camera::source.h : Camera::source.y;	
	}
}

void SandboxApp::CheckCollisions() {
	//	Entity* mainPlayer = layerManager->GetLayer("PlayerLayer")->GetEntity("PlayerEntity");

	if (layerManager->CheckEntityCollisions() == PLAYER_ENEMY_COLLISION) {
		std::cout << layerManager->CheckEntityCollisions() << std::endl;
	}
}


void SandboxApp::ProcessInput() {
	if (SDL_PollEvent(&Application::event)) {
		if (Application::event.type == SDL_QUIT) {
			this->Destroy();
		}
	}
}

void SandboxApp::Run() {
	while (this->isActive) {
		this->ProcessInput();
		this->Render();
		this->Update();
	}
}