#pragma once
#include "Wire.h"
#include "Node.h"

class WireManager
{
private:
	Wire* wires;
	int wirecount;

public:
	WireManager();
	~WireManager();

	void Destroy();

	void Init();
	void AddWire(Node n1, Node n2);
	void GetConnectedWires(Node n);
	void DeleteWire(Node n);
	void UpdateWires(Node n);
	void DrawWires();
};

