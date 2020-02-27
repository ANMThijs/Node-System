#include "WireManager.h"

WireManager::WireManager() {

}

WireManager::~WireManager() {

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

void WireManager::DeleteWire(Node n) {
	int count = 0;
	for (int i = 0; i < this->wirecount; i++) { //scan all wires
		if ((this->wires[i].NodeID1 == n.ID) || (this->wires[i].NodeID2 == n.ID)) { //if wire is connected with both nodes
			printf("YAY\n\n");
			printf("i: %i, wirecount: %i", i, this->wirecount);
			for (int j = 0; j < this->wirecount; j++) {
				if (i + j < this->wirecount) {
					this->wires[i] = this->wires[i + 1];
				}
			}
			count++;
		}
	}
	this->wirecount -= count;
}

void WireManager::DeleteWire(Node n1, Node n2) {
	for (int i = 0; i < this->wirecount; i++) { //scan all wires
		if ((this->wires[i].NodeID1 == n1.ID) && (this->wires[i].NodeID2 == n2.ID)) { //if wire is connected with both nodes
			int a = this->wirecount - i - 1;
			for (int j = 0; j < a; j++) {
				if (i + j < this->wirecount) {
					this->wires[i + j] = this->wires[i + j + 1];
				}
			}
			this->wirecount--;
		}
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