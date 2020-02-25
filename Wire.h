#pragma once
#include <gl/glew.h>
#include <stdio.h>

class Wire {
private:
	float startx, starty, endx, endy;

public:
	int NodeID1, NodeID2;
	bool init;

	Wire();
	
	void Init(float x1, float y1, float x2, float y2, int NodeID1, int NodeID2);
	void NewStart(float x, float y);
	void NewEnd(float x, float y);

	void Draw();
};

Wire* CopyWires(int wirecount, Wire* wires);

//bool DrawWire(Node n1, Node n2);