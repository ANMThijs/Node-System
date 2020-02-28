#pragma once
#include <gl/glew.h>

#define NODE_SIZE 100.0f

#define NODE_COLOURR_DEF 0.2f
#define NODE_COLOURG_DEF 0.2f
#define NODE_COLOURB_DEF 0.2f

#define NODE_COLOURR_SEL 1.0f
#define NODE_COLOURG_SEL 0.94f
#define NODE_COLOURB_SEL 0.7f

class Node
{
public:
	float xpos, ypos;
	float colourr, colourg, colourb;
	bool selected;
	int ID;

	Node();
	~Node();
	Node(float x, float y);

	void Render();
	void Move(float x, float y);
};

