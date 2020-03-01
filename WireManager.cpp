#include "WireManager.h"

WireManager::WireManager() {

}

WireManager::~WireManager() {

}

void WireManager::Destroy() {
	delete[] this->wires;
}

void WireManager::Init() {
	this->wirecount = 0;
	this->wires = new Wire[64];
}

void WireManager::AddWire(Node n1, Node n2) {
	Wire n;
	n.Init(n1.xpos, n1.ypos, n2.xpos, n2.ypos, n1.ID, n2.ID);
	this->wires[this->wirecount] = n;
	this->wirecount++;
}

void WireManager::GetConnectedWires(Node n) {
	for (int i = 0; i < this->wirecount; i++) {
		if ((this->wires[i].NodeID1 == n.ID) || this->wires[i].NodeID2 == n.ID) {
			printf("SelWire: %i\n", i);
		}
	}
	printf("\n");
}

void WireManager::DeleteWire(Node n) {
	for (int i = 0; i < this->wirecount; i++) { //scan all wires
		if ((this->wires[i].NodeID1 == n.ID) || (this->wires[i].NodeID2 == n.ID)) { //if wire is connected with both nodes
			printf("DelWire: %i\n", i);
			this->wires[i] = this->wires[this->wirecount - 1];
			this->wirecount--;
		}
	}
	printf("\n");
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