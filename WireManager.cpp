#include "WireManager.h"

WireManager::WireManager() {

}

WireManager::~WireManager() {

}

void WireManager::Init() {
	this->wirecount = 0;
}

void WireManager::AddWire(Node n1, Node n2) {
	if (this->wirecount < 9) {
		Wire n;
		n.Init(n1.xpos, n1.ypos, n2.xpos, n2.ypos, n1.ID, n2.ID);
		this->wires[this->wirecount] = n;
		this->wirecount++;
	}
}

void WireManager::UpdateWires(Node n) {
	for (int i = 0; i < this->wirecount; i++) {
		if (this->wires[i].NodeID1 == n.ID) {
			this->wires[i].NewStart(n.xpos, n.ypos);
		}
		else if (this->wires[i].NodeID2 == n.ID) {
			this->wires[i].NewEnd(n.xpos, n.ypos);
		}
	}
}

void WireManager::DrawWires() {
	for (int i = 0; i < this->wirecount; i++) {
		this->wires[i].Draw();
	}
}