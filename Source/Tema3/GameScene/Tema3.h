#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <time.h>

#include <Core/Engine.h>
#include <Component/SimpleScene.h>

#include "../Models2D.h"
#include "../Models3D.h"

#include "../Components/ComponentsList.h"

#include "../Input/Input.h"

#include <stb/stb_image.h>


class Tema3 : public SimpleScene
{
public:
	Tema3();
	~Tema3();

	void Init() override;

	void StartGame();
protected:
	std::unordered_map<std::string, Texture2D*> mapTextures;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;
};
