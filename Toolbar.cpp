#include "Toolbar.h"

Toolbar::Toolbar() {

}

Toolbar::~Toolbar() {

}

void Toolbar::Init() {
	this->xpos = -945.0f;
	this->ypos = -525.0f;
	this->buttoncount = 0;

	struct Button b = InitButton(1.0f, 0.0f, 0.0f, this->buttoncount, this->xpos, this->ypos);
	this->buttons[0] = b;
	this->buttoncount++;

	b = InitButton(0.0f, 1.0f, 0.0f, this->buttoncount, this->xpos, this->ypos);
	this->buttons[1] = b;
	this->buttoncount++;

	b = InitButton(0.0f, 0.0f, 1.0f, this->buttoncount, this->xpos, this->ypos);
	this->buttons[2] = b;
	this->buttoncount++;
}

int Toolbar::Toolbarproc(float mouseposx, float mouseposy) {
	for (int i = 0; i < ToolbarButtonCount; i++) {
		float top = this->buttons[i].ypos - ButtonSize + 26.0f;
		float right = this->buttons[i].xpos + ButtonSize;
		float bottom = this->buttons[i].ypos + ButtonSize + 26.0f;
		float left = this->buttons[i].xpos - ButtonSize;

		if ((left < mouseposx) && (right > mouseposx)) {
			if ((top < mouseposy) && (bottom > mouseposy)) {
				return i;
			}
		}
	}
	return -1;
}

bool Toolbar::DetectMouse(float mouseposx, float mouseposy) {
	float top = this->ypos;
	float left = this->xpos;
	float bottom = this->ypos + 5.0f * ToolbarRectY;
	float right = this->xpos + 2.0f * ToolbarRectX;

	if ((mouseposx > left) && (mouseposx < right)) {
		if ((mouseposy > top) && (mouseposy < bottom)) {
			return true;
		}
	}
	return false; 
}

void Toolbar::Move(float x, float y) {
	this->xpos -= x;
	this->ypos -= y;
}

void Toolbar::Render() {
	float top = this->ypos;
	float left = this->xpos;
	float bottom = this->ypos + 5.0f * ToolbarRectY;
	float right = this->xpos + 2.0f * ToolbarRectX;

	glBegin(GL_TRIANGLES);

	glColor3f(0.5f, 0.5f, 0.5f);

	glVertex2f(left, top);
	glVertex2f(right, top);
	glVertex2f(left, bottom);

	glVertex2f(right, top);
	glVertex2f(left, bottom);
	glVertex2f(right, bottom);

	glEnd();

	for (int i = 0; i < ToolbarButtonCount; i++) {
		Draw(&this->buttons[i]);
	}
}

struct Button InitButton(float cr, float cb, float cg, int butcount, float tbx, float tby) {
	struct Button b;

	b.colourr = cr;
	b.colourb = cb;
	b.colourg = cg;

	if ((butcount % 2) == 0) {
		b.xpos = ToolbarRectX;
		b.xpos = tbx + b.xpos / 2;
	}
	else if ((butcount % 2) == 1) {
		b.xpos = ToolbarRectX;
		b.xpos = tbx + b.xpos + b.xpos / 2;
	}
	b.ypos = ToolbarRectY;
	b.ypos = tby + b.ypos * ((butcount / 2) + 0.5f);

	return b;
}

void Draw(struct Button* b) {
	glBegin(GL_TRIANGLES);
	
	glColor3f(b->colourr, b->colourb, b->colourg);

	glVertex2f(b->xpos - ButtonSize, b->ypos - ButtonSize);
	glVertex2f(b->xpos + ButtonSize, b->ypos - ButtonSize);
	glVertex2f(b->xpos - ButtonSize, b->ypos + ButtonSize);

	glVertex2f(b->xpos + ButtonSize, b->ypos - ButtonSize);
	glVertex2f(b->xpos - ButtonSize, b->ypos + ButtonSize);
	glVertex2f(b->xpos + ButtonSize, b->ypos + ButtonSize);

	glEnd();
}