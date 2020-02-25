#include "Engine.h"

Engine::Engine() {

}

Engine::~Engine() {

}

void Engine::Init() {
	glEnable(GL_TEXTURE_2D);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(BG_COLOURR, BG_COLOURG, BG_COLOURB, BG_COLOURA);

	this->nodes = new Node[64];
	this->nodecount = 0;
	this->nodesel = -1;

	this->AddNode(0.0f, 350.0f);
	this->AddNode(733.0f, -260.0f);
	this->AddNode(-780.0f, 80.0f);

	this->currentmode = Default;

	wm.Init();
	wm.AddWire(this->nodes[0], this->nodes[1]);
	wm.AddWire(this->nodes[2], this->nodes[1]);
}

void Engine::Destroy() {
	delete[] this->nodes;
}

void Engine::AddNode(Node n) {
	n.ID = this->nodecount;
	this->nodes[this->nodecount] = n;
	this->nodecount++;
}

void Engine::AddNode(float xpos, float ypos) {
	Node n(xpos, ypos);
	n.ID = this->nodecount;
	this->nodes[this->nodecount] = n;
	this->nodecount++;
}

void Engine::DeleteNode() {
	this->nodes[this->nodesel].deleted = true;
	for (int i = 0; i < (this->nodecount - 1); i++) {
		if (i >= this->nodesel) {
			printf("%i\n\n", this->nodesel);
			this->nodes[i] = this->nodes[i + 1];
		}
	}
	this->nodecount--;
}

void Engine::Render() {
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f);

	wm.DrawWires();

	for (int i = 0; i < nodecount; i++) {
		nodes[i].Render();
	}
}

int* Engine::GetSelNodes() {
	int j = 0;
	/*Get amount of selected nodes*/
	for (int i = 0; i < this->nodecount; i++) {
		if (this->nodes[i].selected == true) {
			j++;
		}
	}

	if (j != 2) {
		int* nums = NULL;
		return nums;
	}
	
	int nums[2];
	int m = 0;
	/*Get the array numbers of the selected nodes*/

	for (int i = 0; i < this->nodecount; i++) {
		if (this->nodes[i].selected == true) {
			nums[m] = i;
			m++;
		}
	}
	return nums;
}

void Engine::OnRMouse() {
	POINT mouseposwin;				//win is the mouse position on the window,
	GetCursorPos(&mouseposwin);

	this->OMousePosGLX = mouseposwin.x - SCREEN_WIDTH / 2.0f;
	this->OMousePosGLY = mouseposwin.y - SCREEN_HEIGHT / 2.0f + 6.0f; //-6.0f so mousepos is at the top of cursor icon

	if (this->currentmode == Default) {
		/*Check if mousepos is on a node, by loping through all the nodes*/
		for (int i = 0; i < this->nodecount; i++) {
			if (((this->nodes[i].xpos - 50.0f) <= this->OMousePosGLX) && ((this->nodes[i].xpos + 50.0f) >= this->OMousePosGLX)) {
				if (((this->nodes[i].ypos - 50.0f) <= this->OMousePosGLY) && ((this->nodes[i].ypos + 50.0f) >= this->OMousePosGLY)) {
					if (GetKeyState(VK_SHIFT) & 0x8000) {
						if (this->nodes[i].selected == false) {
							this->nodes[i].selected = true;
						}
					}
					else if (GetKeyState(VK_CONTROL) & 0x8000) {
						if (this->nodes[i].selected == true) {
							this->nodes[i].selected = false;
						}
					}
					else {
						for (int j = 0; j < this->nodecount; j++) {
							this->nodes[j].selected = false;
							this->nodes[i].selected = true;
							this->nodesel = i;
						}
					}
				}
			}
/*			else if (((this->nodes[i].xpos - 100.0f) <= this->OMousePosGLX) && ((this->nodes[i].xpos + 100.0f) >= this->OMousePosGLX)) {
				if (((this->nodes[i].ypos - 100.0f) <= this->OMousePosGLY) && ((this->nodes[i].ypos + 100.0f) >= this->OMousePosGLY)) {
				}
			}
			else {
				this->nodes[this->nodesel].selected = false;
				this->nodesel = -1;
			}
*/		}
	}
	else if (this->currentmode == Draw) {
		this->AddNode(this->OMousePosGLX, this->OMousePosGLY);
	}

	this->Render();

	this->PrevMousePosGLX = this->OMousePosGLX;
	this->PrevMousePosGLY = this->OMousePosGLY;
}

void Engine::OnHotKey(WPARAM wparam) {
	if (wparam == HK_VPMODE_DEFAULT) this->currentmode = Default;
	if (wparam == HK_VPMODE_DRAW) this->currentmode = Draw;
	if (wparam == HK_DRAW_WIRE) {
		int* selnodes;
		selnodes = this->GetSelNodes();
		if (selnodes != NULL) {
			this->wm.AddWire(this->nodes[selnodes[0]], this->nodes[selnodes[1]]);
		}
	}
	this->Render();
}

void Engine::OnMouseMove() {
	POINT mouseposwin;
	float mouseposglx, mouseposgly;
	GetCursorPos(&mouseposwin);

	mouseposglx = mouseposwin.x - SCREEN_WIDTH / 2.0f;
	mouseposgly = mouseposwin.y - SCREEN_HEIGHT / 2.0f + 6.0f;

	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
		for (int i = 0; i < this->nodecount; i++) {
			if (this->nodes[i].selected == true) {
				float dx = this->PrevMousePosGLX - mouseposglx;
				float dy = this->PrevMousePosGLY - mouseposgly;

				this->nodes[i].Move(dx, dy);
				this->wm.UpdateWires(this->nodes[i]);
				this->Render(); //Placed here so it is only called when necessary
			}
		}
	}

	this->PrevMousePosGLX = mouseposglx;
	this->PrevMousePosGLY = mouseposgly;
}

void Engine::OnKey() {
	if (GetKeyState(VK_ESCAPE) & 0x8000) PostQuitMessage(0);
	if (GetKeyState(VK_DELETE) & 0x8000) {
		if (this->nodesel != -1) {
			DeleteNode();
		}
		this->Render();
	}
}