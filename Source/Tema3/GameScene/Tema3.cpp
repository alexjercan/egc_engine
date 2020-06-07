#include "Tema3.h"

Tema3::Tema3()
{

}

Tema3::~Tema3()
{

}

void Tema3::StartGame()
{
	MeshRenderer::mainCamera = GameObject::Instantiate(GameObject::prefabs["cameraPrefab"]);
	CameraComponent* c = MeshRenderer::mainCamera->GetComponent<CameraComponent>();

	MeshRenderer::light0 = GameObject::Instantiate(GameObject::prefabs["lightPrefab"]);
	SpotLight* sLight0 = MeshRenderer::light0->GetComponent<SpotLight>();

	MeshRenderer::light1 = GameObject::Instantiate(GameObject::prefabs["lightPrefab"]);
	SpotLight* sLight1 = MeshRenderer::light1->GetComponent<SpotLight>();

	GameObject* terrain = GameObject::Instantiate(GameObject::prefabs["terrainPrefab"]);
	Terrain* t = terrain->GetComponent<Terrain>();
	TurnBasedController* tbc = terrain->GetComponent<TurnBasedController>();

	GameObject* w1 = GameObject::Instantiate(GameObject::prefabs["wormPrefab"]);
	w1->GetComponent<Transform>()->position.x = (rand() % 100) / 10.0;
	w1->GetComponent<Transform>()->position.z = (rand() % 100) / 10.0;
	w1->GetComponent<PlayerController>()->SetActive(true);
	w1->GetComponent<PlayerController>()->terrainParent = terrain;
	sLight0->target = w1->GetComponent<Transform> ();
	t->AddTerrainObject(w1);
	c->target = w1->GetComponent<Transform>();
	tbc->AddPlayer(w1);

	GameObject* suiMO1 = GameObject::Instantiate(GameObject::prefabs["sliderPrefab"]);
	suiMO1->parent = w1;
	suiMO1->GetComponent<SliderUI>()->value = &w1->GetComponent<PlayerController>()->movementLeft;
	GameObject* suiLO1 = GameObject::Instantiate(GameObject::prefabs["sliderPrefab"]);
	suiLO1->GetComponent<Transform>()->position.y += 0.25f;
	suiLO1->parent = w1;
	suiLO1->GetComponent<SliderUI>()->value = &w1->GetComponent<PlayerController>()->health;

	GameObject* w2 = GameObject::Instantiate(GameObject::prefabs["wormPrefab"]);
	w2->GetComponent<PlayerController>()->terrainParent = terrain;
	w2->GetComponent<Transform>()->position.x = (rand() % 100) / 10.0;
	w2->GetComponent<Transform>()->position.z = (rand() % 100) / 10.0;
	sLight1->target = w2->GetComponent<Transform>();
	t->AddTerrainObject(w2);
	tbc->AddPlayer(w2);

	GameObject* suiMO2 = GameObject::Instantiate(GameObject::prefabs["sliderPrefab"]);
	suiMO2->parent = w2;
	suiMO2->GetComponent<SliderUI>()->value = &w2->GetComponent<PlayerController>()->movementLeft;
	GameObject* suiLO2 = GameObject::Instantiate(GameObject::prefabs["sliderPrefab"]);
	suiLO2->GetComponent<Transform>()->position.y += 0.25f;
	suiLO2->parent = w2;
	suiLO2->GetComponent<SliderUI>()->value = &w2->GetComponent<PlayerController>()->health;

	for (int i = 0; i < 25; i++)
	{
		GameObject* b1 = GameObject::Instantiate(GameObject::prefabs["bambooPrefab"]);
		Transform* tb = b1->GetComponent<Transform>();
		tb->position.x = rand() % 100 / 10.0f;
		tb->position.z = rand() % 100 / 10.0f;
		t->AddTerrainObject(b1);
	}

	glfwSetInputMode(window->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Tema3::Init()
{
	srand(time(NULL));

	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetPerspective(90, resolution.x / (float)resolution.y, 0.001f, 100);
	camera->SetPosition(glm::vec3(5, 2.5, 10));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	const std::string textureLoc = "Source/Tema3/Textures/";

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "moon.png").c_str(), GL_REPEAT);
		mapTextures["moon"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D("Resources/Models/Vegetation/Bamboo/bamboo.png", GL_REPEAT);
		mapTextures["bamboo"] = texture;
	}

	meshes["cube"] = Models3D::CreateSimpleCube("cube");
	meshes["trunk"] = Models3D::CreateTrunk("trunk");
	meshes["cylinderB"] = Models3D::CreateCylinder("cylinderB", 100, 100, 10, 1, 0.05);
	meshes["sphere"] = Models3D::CreateSphere("sphere", 10, 10, 2);
	meshes["plane"] = Models3D::CreatePlane("plane", 100, 100);
	meshes["rectangle"] = Models2D::CreateRectangle("rectangle", glm::vec3(0), 1, 1, glm::vec3(1));

	{
		Mesh* mesh = new Mesh("bamboo");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Vegetation/Bamboo/", "bamboo.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	Shader* shader = new Shader("shader");
	shader->AddShader("Source/Tema3/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
	shader->AddShader("Source/Tema3/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
	shader->CreateAndLink();
	shaders[shader->GetName()] = shader;

	shader = new Shader("water");
	shader->AddShader("Source/Tema3/Shaders/WaterVertexShader.glsl", GL_VERTEX_SHADER);
	shader->AddShader("Source/Tema3/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
	shader->CreateAndLink();
	shaders[shader->GetName()] = shader;

	shader = new Shader("terrain");
	shader->AddShader("Source/Tema3/Shaders/TerrainVertexShader.glsl", GL_VERTEX_SHADER);
	shader->AddShader("Source/Tema3/Shaders/TerrainFragmentShader.glsl", GL_FRAGMENT_SHADER);
	shader->CreateAndLink();
	shaders[shader->GetName()] = shader;

	shader = new Shader("texture");
	shader->AddShader("Source/Tema3/Shaders/VertexShaderT.glsl", GL_VERTEX_SHADER);
	shader->AddShader("Source/Tema3/Shaders/FragmentShaderT.glsl", GL_FRAGMENT_SHADER);
	shader->CreateAndLink();
	shaders[shader->GetName()] = shader;

	{
		GameObject* particlePrefab = new GameObject("particlePrefab");
		particlePrefab->parent = NULL;
		particlePrefab->AddComponent(new Transform(glm::vec3(0), glm::vec3(0), glm::vec3(.01f)));
		particlePrefab->AddComponent(new MeshRenderer(meshes["sphere"], shaders["shader"], 
			{ "r", "g", "b" },
			{ FLOAT, FLOAT, FLOAT },
			{ 0.5f, 0.1f, 0.1f }));
		particlePrefab->AddComponent(new ParticleController());
		GameObject::prefabs[particlePrefab->name] = particlePrefab;
	}

	{
		GameObject* projectilePrefab = new GameObject("projectilePrefab");
		projectilePrefab->parent = NULL;
		projectilePrefab->AddComponent(new Transform(glm::vec3(0), glm::vec3(0), glm::vec3(.025f)));
		projectilePrefab->AddComponent(new MeshRenderer(meshes["sphere"], shaders["shader"], 
			{ "r", "g", "b" },
			{ FLOAT, FLOAT, FLOAT },
			{ 0.5f, 0.5f, 0.3f }));
		projectilePrefab->AddComponent(new ProjectileController());
		projectilePrefab->AddComponent(new ParticleSystem());
		GameObject::prefabs[projectilePrefab->name] = projectilePrefab;
	}

	{
		GameObject* wormPrefab = new GameObject("wormPrefab");
		wormPrefab->parent = NULL;
		wormPrefab->AddComponent(new Transform(glm::vec3(0), glm::vec3(0), glm::vec3(.1f)));
		wormPrefab->AddComponent(new MeshRenderer(meshes["cube"], shaders["shader"], 
			{ "r", "g", "b" },
			{ FLOAT, FLOAT, FLOAT },
			{ 0.5f, 0.3f, 0.3f }));
		PlayerController* pc = new PlayerController();
		wormPrefab->AddComponent(pc);
		GameObject::prefabs[wormPrefab->name] = wormPrefab;
	}

	{
		GameObject* sliderPrefab = new GameObject("sliderPrefab");
		sliderPrefab->parent = NULL;
		sliderPrefab->AddComponent(new Transform(glm::vec3(1, 1.25, 0), glm::vec3(0), glm::vec3(.25, .25, .25)));
		sliderPrefab->AddComponent(new MeshRenderer(meshes["rectangle"], shaders["shader"],
			{ "r", "g", "b" },
			{ FLOAT, FLOAT, FLOAT },
			{ 0, 0, 0 }));
		sliderPrefab->AddComponent(new SliderUI());
		GameObject::prefabs[sliderPrefab->name] = sliderPrefab;
	}

	{
		GameObject* bambooPrefab = new GameObject("bambooPrefab");
		bambooPrefab->parent = NULL;
		bambooPrefab->AddComponent(new Transform(glm::vec3(0), glm::vec3(0), glm::vec3(.1f)));

		float bambooid = (float)mapTextures["bamboo"]->GetTextureID();
		bambooPrefab->AddComponent(new MeshRenderer(meshes["bamboo"], shaders["texture"],
			{ "texture_1" , "time" }, { TEXTURE , TIME }, { bambooid , 0 }));

		GameObject::prefabs[bambooPrefab->name] = bambooPrefab;
	}

	{
		GameObject* cameraPrefab = new GameObject("cameraPrefab");
		cameraPrefab->parent = NULL;
		cameraPrefab->AddComponent(new Transform(glm::vec3(0), glm::vec3(0), glm::vec3(.1f)));
		CameraComponent* c = new CameraComponent();
		c->camera = GetSceneCamera();
		cameraPrefab->AddComponent(c);
		GameObject::prefabs[cameraPrefab->name] = cameraPrefab;
	}

	{
		unsigned char* data;
		int channels, width, height;
		GLuint textureID = 0;

		data = stbi_load((textureLoc + "heightmap.png").c_str(), &width, &height, &channels, STBI_grey);

		glGenTextures(1, &textureID);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4);

		glPixelStorei(GL_PACK_ALIGNMENT, 1);
		CheckOpenGLError();

		glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, (void*)data);

		glGenerateMipmap(GL_TEXTURE_2D);

		CheckOpenGLError();

		Texture2D* texture = new Texture2D();
		texture->Init(textureID, width, height, channels);
		mapTextures["heightmap"] = texture;

		GameObject* terrainPrefab = new GameObject("terrainPrefab");
		terrainPrefab->parent = NULL;
		terrainPrefab->AddComponent(new Transform(glm::vec3(0), glm::vec3(0), glm::vec3(10.0f)));

		Terrain* terrain = new Terrain();
		terrain->data = data;
		terrain->width = width;
		terrain->height = height;
		terrain->channels = channels;
		terrain->textureID = textureID;
		terrainPrefab->AddComponent(terrain);

		TurnBasedController* tbc = new TurnBasedController();
		terrainPrefab->AddComponent(tbc);

		float hmapid = (float)mapTextures["heightmap"]->GetTextureID();
		float moonid = (float)mapTextures["moon"]->GetTextureID();
		unsigned int w, h;
		mapTextures["moon"]->GetSize(w, h);
		terrainPrefab->AddComponent(new MeshRenderer(meshes["plane"], shaders["terrain"],
			{ "heightmap", "texture", "textureW", "textureH" , "light_direction", "light_position", 
			"light_direction1", "light_position1", "eye_position", "cutoff", "material_kd", "material_ks", 
			"material_shininess"},
			{ HEIGHTMAP, TEXTURE, FLOAT, FLOAT , LIGHT_DIRECTION0, LIGHT_POSITION1, LIGHT_DIRECTION1, LIGHT_POSITION0, 
			EYE_POSITION, CUTOFF_ANGLE, FLOAT, FLOAT, INT},
			{ hmapid, moonid , (float)w, (float)h , 0, 0, 0, 0, 0, 0, 0.8f, 0.5f, 30}));
		GameObject::prefabs[terrainPrefab->name] = terrainPrefab;
	}

	{
		GameObject* lightPrefab = new GameObject("lightPrefab");
		lightPrefab->parent = NULL;
		lightPrefab->AddComponent(new Transform(glm::vec3(0, 1, 0), glm::vec3(0), glm::vec3(1)));
		lightPrefab->AddComponent(new SpotLight());
		GameObject::prefabs[lightPrefab->name] = lightPrefab;
	}

	StartGame();

	//glfwSetInputMode(window->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Tema3::FrameStart()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema3::Update(float deltaTimeSeconds)
{
	for (int i = 0; i < GameObject::gameObjects.size(); i++)
	{
		GameObject::gameObjects[i]->Update(deltaTimeSeconds);
	}
}

void Tema3::FrameEnd()
{
	Input::Reset();
	DrawCoordinatSystem();
}



void Tema3::OnInputUpdate(float deltaTime, int mods)
{
	if (window->KeyHold(GLFW_KEY_W)) Input::w = true;
	if (window->KeyHold(GLFW_KEY_A)) Input::a = true;
	if (window->KeyHold(GLFW_KEY_S)) Input::s = true;
	if (window->KeyHold(GLFW_KEY_D)) Input::d = true;
}

void Tema3::OnKeyPress(int key, int mods)
{
	if (key == GLFW_KEY_SPACE) Input::spaceKeyDown = true;
}

void Tema3::OnKeyRelease(int key, int mods)
{

}

void Tema3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	Input::deltaMouseX = deltaX;
	Input::deltaMouseY = deltaY;
}

void Tema3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	Input::fire0 = true;
}

void Tema3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema3::OnWindowResize(int width, int height)
{

}