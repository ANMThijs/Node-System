#include <Windows.h>

#include "Letters.h"
#include "WireManager.h"

#define HK_VPMODE_DEFAULT 100
#define HK_VPMODE_DRAW_NODE 101
#define HK_VPMODE_DRAW_WIRE 102		//For realtime drawing
#define HK_DRAW_WIRE 105			//For shortcut drawing

#define HK_SELECT_BOX 110

#define SCREEN_WIDTH 1920.0f
#define SCREEN_HEIGHT 1080.0f

#define BG_COLOURR 0.4f
#define BG_COLOURG 0.4f
#define BG_COLOURB 0.4f
#define BG_COLOURA 0.0f

enum VPModes {
	Default = 0,
	DrawNode = 1,
	DrawWire = 2,
};

class Engine
{
private:
	Node* nodes;
	WireManager wm;
	Wire RealTimeWire;

	int nodecount; //starts at 1
	int nodesel;   //starts at 0. Set to -1 if no nodes are selected
	int currentmode;
	float OMousePosGLX, OMousePosGLY; //Gets set when mouse button is clicked
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
	void SetVPMode(VPModes mode);

	void LMouseUp();
	void LMouseDown();
	void OnHotKey(WPARAM wparam);
	void OnMouseMove();
	void OnKey();
};

