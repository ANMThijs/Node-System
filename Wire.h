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
	void InitRT(float x1, float y1, float x2, float y2); //Should only be use for realtime drawing
	void NewStart(float x, float y);
	void NewEnd(float x, float y);

	void Draw();
	void Draw(float x1, float y1, float x2, float y2);
};

Wire* CopyWires(int wirecount, Wire* wires);

//bool DrawWire(Node n1, Node n2);