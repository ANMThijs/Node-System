#pragma once
#include "ShapePresets.h"

#define ToolbarRectX 30.0f
#define ToolbarRectY 30.0f

#define ButtonSize 13.0f

#define ToolbarButtonCount 3  //Amount of app modes. Should be update with every new mode

struct Button {
	float colourr, colourb, colourg;
	float xpos, ypos;
};

class Toolbar
{
private:
	float xpos, ypos; //Coordinates of left top
	Button buttons[ToolbarButtonCount];
	int buttoncount;

public:
	Toolbar();
	~Toolbar();

	void Init();
	bool DetectMouse(float mouseposx, float mouseposy);
	int Toolbarproc(float mouseposx, float mouseposy); //Gets the clicked button and returns an int
	void Move(float x, float y);
	void Render();
};

struct Button InitButton(float cr, float cb, float cg, int butcount, float tbx, float tby);

void Draw(struct Button* b);