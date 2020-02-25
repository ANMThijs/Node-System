#include <Windows.h>

#include "Letters.h"
#include "WireManager.h"

#define HK_VPMODE_DEFAULT 100
#define HK_VPMODE_DRAW 101

#define HK_DRAW_WIRE 105

#define HK_SELECT_BOX 110

#define SCREEN_WIDTH 1920.0f
#define SCREEN_HEIGHT 1080.0f

#define BG_COLOURR 0.4f
#define BG_COLOURG 0.4f
#define BG_COLOURB 0.4f
#define BG_COLOURA 0.0f

enum VPModes {
	Default = 0,
	Draw = 1,
};

class Engine
{
private:
	Node* nodes;
	WireManager wm;

	int nodecount; //starts at 1
	int nodesel;   //starts at 0. Set to -1 if no nodes are selected
	int currentmode;
	float OMousePosGLX, OMousePosGLY; //Get's set when rbutton is pushed, used for node movement
	float PrevMousePosGLX, PrevMousePosGLY;

public:
	Engine();
	~Engine();

	void Init();
	void Destroy();

	void AddNode(Node n); //Adds a node which is already defined
	void AddNode(float xpos, float ypos); //Adds a node based off coordinates
	void DeleteNode(); //Delete the current selected node
	void Render();

	int* GetSelNodes();

	void OnRMouse();
	void OnHotKey(WPARAM wparam);
	void OnMouseMove();
	void OnKey();
};

