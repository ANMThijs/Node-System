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

	this->nodeclicked = false;
	this->selbox = false;

	this->currentmode = Default;

	this->wm.Init();

	this->tb.Init();
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
	this->wm.DeleteWire(this->nodes[this->nodesel]);
	for (int i = 0; i < (this->nodecount - 1); i++) {
		if (i >= this->nodesel) {
			this->nodes[i] = this->nodes[i + 1];
		}
	}
	this->nodecount--;
}

void Engine::DeleteNode(int NodeID) {
	this->wm.DeleteWire(this->nodes[NodeID]);
	for (int i = 0; i < (this->nodecount - 1); i++) {
		if (i >= NodeID) {
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

	if (this->RealTimeWire.init == true) {
		this->RealTimeWire.Draw();
	}

	if (this->selbox == true) {
		DrawRect(this->OMousePosGLY, this->PrevMousePosGLX, this->PrevMousePosGLY, this->OMousePosGLX);
	}

	for (int i = 0; i < nodecount; i++) {
		nodes[i].Render();
	}

	this->tb.Render();
}

int* Engine::GetSelNodes() {
	int j = 0;
	/*Get amount of selected nodes*/
	for (int i = 0; i < this->nodecount; i++) {
		if (this->nodes[i].selected == true) {
			j++;
		}
	}
	
	int* nums = new int[j];
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

int* Engine::GetSelNodesW() {
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

	int* nums = new int[2];
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

void Engine::SetVPMode(VPModes mode) {
	this->currentmode = mode;
	switch (mode) {
	case Default:  printf("Default\n"); break;
	case DrawNode: printf("DrawNode\n"); break;
	case DrawWire: printf("DrawWire\n"); break;
	}
}

void Engine::LMouseDown() {
	POINT mouseposwin;				//win is the mouse position on the window,
	GetCursorPos(&mouseposwin);

	this->OMousePosGLX = mouseposwin.x - SCREEN_WIDTH / 2.0f;
	this->OMousePosGLY = mouseposwin.y - SCREEN_HEIGHT / 2.0f + 6.0f; //-6.0f so mousepos is at the top of cursor icon

	bool Tbclicked = false;
	if (this->tb.DetectMouse(this->OMousePosGLX, this->OMousePosGLY)) {
		int tbb = this->tb.Toolbarproc(this->OMousePosGLX, this->OMousePosGLY);
		switch (tbb) {
		case -1: break;
		case 0: SetVPMode(Default); break;
		case 1: SetVPMode(DrawNode); break;
		case 2: SetVPMode(DrawWire); break;
		}
		Tbclicked = true;
	}

	if ((this->currentmode == Default) && (!Tbclicked)) {
		/*Check if mousepos is on a node, by loping through all the nodes*/
		for (int i = 0; i < this->nodecount; i++) {
			if (((this->nodes[i].xpos - 50.0f) <= this->OMousePosGLX) && ((this->nodes[i].xpos + 50.0f) >= this->OMousePosGLX)) {
				if (((this->nodes[i].ypos - 50.0f) <= this->OMousePosGLY) && ((this->nodes[i].ypos + 50.0f) >= this->OMousePosGLY)) {
					this->nodeclicked = true;
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
		}
		if (this->nodeclicked == false) {
			for (int i = 0; i < this->nodecount; i++) {
				this->nodes[i].selected = false;
				this->nodesel = -1;
			}
		}
	}
	else if ((this->currentmode == DrawNode) && (!Tbclicked)) {
		this->AddNode(this->OMousePosGLX, this->OMousePosGLY);
	}
	else if ((this->currentmode == DrawWire) && (!Tbclicked)) {
		this->RealTimeWire.InitRT(this->OMousePosGLX, this->OMousePosGLY, this->OMousePosGLX, this->OMousePosGLY);
	}

	this->Render();

	this->PrevMousePosGLX = this->OMousePosGLX;
	this->PrevMousePosGLY = this->OMousePosGLY;
}

void Engine::LMouseUp() {
	if (this->currentmode == Default) {
		for (int i = 0; i < this->nodecount; i++) {
			if (this->nodes[i].xpos > this->OMousePosGLX && this->nodes[i].xpos < this->PrevMousePosGLX) {
				if (this->nodes[i].ypos > this->OMousePosGLY&& this->nodes[i].ypos < this->PrevMousePosGLY) {
					this->nodes[i].selected = true;
				}
			}
			else if (this->nodes[i].xpos < this->OMousePosGLX&& this->nodes[i].xpos > this->PrevMousePosGLX) {
				if (this->nodes[i].ypos < this->OMousePosGLY&& this->nodes[i].ypos > this->PrevMousePosGLY) {
					this->nodes[i].selected = true;
				}
			}
		}
		this->Render();
	}
	if (this->currentmode == DrawWire) {
		POINT mouseposwin;
		float mouseposglx, mouseposgly;
		GetCursorPos(&mouseposwin);

		mouseposglx = mouseposwin.x - SCREEN_WIDTH / 2.0f;
		mouseposgly = mouseposwin.y - SCREEN_HEIGHT / 2.0f + 6.0f;

		int n1 = -1, n2 = -1;

		this->RealTimeWire.init = false;
		for (int i = 0; i < this->nodecount; i++) {
			if (((this->nodes[i].xpos - 50.0f) <= this->OMousePosGLX) && ((this->nodes[i].xpos + 50.0f) >= this->OMousePosGLX)) {
				if (((this->nodes[i].ypos - 50.0f) <= this->OMousePosGLY) && ((this->nodes[i].ypos + 50.0f) >= this->OMousePosGLY)) {
					n1 = i;
				}
			}
			else if (((this->nodes[i].xpos - 50.0f) <= mouseposglx) && ((this->nodes[i].xpos + 50.0f) >= mouseposglx)) {
				if (((this->nodes[i].ypos - 50.0f) <= mouseposgly) && ((this->nodes[i].ypos + 50.0f) >= mouseposgly)) {
					n2 = i;
				}
			}
		}
		if ((n1 != -1) && (n2 != -1)) {
			this->wm.AddWire(this->nodes[n1], this->nodes[n2]);
			printf("%i, %i\n", n1, n2);
		}
	}

	this->nodeclicked = false;
	this->selbox = false;

	this->Render();
}

void Engine::OnHotKey(WPARAM wparam) {
	if (wparam == HK_VPMODE_DEFAULT)   this->SetVPMode(Default);
	if (wparam == HK_VPMODE_DRAW_NODE) this->SetVPMode(DrawNode);
	if (wparam == HK_VPMODE_DRAW_WIRE) this->SetVPMode(DrawWire);
	if (wparam == HK_DRAW_WIRE) {
		int* selnodes;
		selnodes = this->GetSelNodesW();
		if (selnodes != NULL) {
			this->wm.AddWire(this->nodes[selnodes[0]], this->nodes[selnodes[1]]);
		}
		this->Render();
	}
}

void Engine::OnMouseMove() {
	POINT mouseposwin;
	float mouseposglx, mouseposgly;
	GetCursorPos(&mouseposwin);

	mouseposglx = mouseposwin.x - SCREEN_WIDTH / 2.0f;
	mouseposgly = mouseposwin.y - SCREEN_HEIGHT / 2.0f + 6.0f;

	int sel = 0;

	if (this->currentmode == Default) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			for (int i = 0; i < this->nodecount; i++) {
				if (this->nodes[i].selected == true) {
					float dx = this->PrevMousePosGLX - mouseposglx;
					float dy = this->PrevMousePosGLY - mouseposgly;

					this->nodes[i].Move(dx, dy);
					this->wm.UpdateWires(this->nodes[i]);
					this->Render(); //Placed here so it is only called when necessary

					sel = 1;
				}
			}
			if (this->nodeclicked == false) {
				this->selbox = true;
				this->Render();
			}
		}
	}
	else if (this->currentmode == DrawWire) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			this->RealTimeWire.NewEnd(mouseposglx, mouseposgly);
			this->Render();
		}
	}

	this->PrevMousePosGLX = mouseposglx;
	this->PrevMousePosGLY = mouseposgly;

	sel = 0;
}

void Engine::OnKey() {
	if (GetKeyState(VK_ESCAPE) & 0x8000) PostQuitMessage(0);
	if (GetKeyState(VK_DELETE) & 0x8000) {
		int selnodec = 0;
		for (int i = 0; i < this->nodecount; i++) {
			if (this->nodes[i].selected == true) {
				selnodec++;
			}
		}
		if (selnodec == 1) {
			this->DeleteNode();
		}
		else if (selnodec > 1) {
			int* selnodes;
			selnodes = this->GetSelNodes();
			for (int i = 0; i < selnodec; i++) {
				this->DeleteNode(selnodes[i]);
			}
		}
		this->Render();
	}
}


/*	wm.AddWire(this->nodes[0], this->nodes[1]);
	wm.AddWire(this->nodes[2], this->nodes[3]);
	wm.AddWire(this->nodes[2], this->nodes[4]);
	wm.AddWire(this->nodes[2], this->nodes[5]);*/

	/*	this->AddNode(440.0f, 234.0f);
		this->AddNode(240.0f, 342.0f);

		this->AddNode(0.0f, 350.0f);
		this->AddNode(733.0f, -260.0f);
		this->AddNode(-780.0f, 80.0f);
		this->AddNode(-504.0f, 452.0f);*/
