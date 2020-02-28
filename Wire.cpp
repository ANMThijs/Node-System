#include "Wire.h"

Wire::Wire() {
	
}

void Wire::Init(float x1, float y1, float x2, float y2, int NodeID1, int NodeID2) {
	this->startx = x1;
	this->starty = y1;
	this->endx = x2;
	this->endy = y2;

	this->NodeID1 = NodeID1;
	this->NodeID2 = NodeID2;
}

void Wire::InitRT(float x1, float y1, float x2, float y2) {
	this->startx = x1;
	this->starty = y1;
	this->endx = x2;
	this->endy = y2;

	this->init = true;
}

void Wire::NewStart(float x, float y) {
	this->startx = x;
	this->starty = y;
}

void Wire::NewEnd(float x, float y) {
	this->endx = x;
	this->endy = y;
}

void Wire::Draw() {
	float dx = this->endx - this->startx;
	float dy = this->endy - this->starty;

	glColor3f(0.3f, 0.3f, 0.7f);

	glLineWidth(5.0f);

	glBegin(GL_LINES);

	if (dx > 100.0f || dx < -100.0f) {
		if (this->startx < this->endx) {
			glVertex2f(this->startx + 50.0f, this->starty);
			glVertex2f(this->startx + dx / 2 + 2.5f, this->starty);

			glVertex2f(this->startx + dx / 2, this->starty);
			glVertex2f(this->startx + dx / 2, this->endy);

			glVertex2f(this->startx + dx / 2 - 2.5f, this->endy);
			glVertex2f(this->endx - 50.0f, this->endy);
		}
		else if (this->endx < this->startx) {
			glVertex2f(this->endx + 50.0f, this->endy);
			glVertex2f(this->endx - dx / 2 + 2.5f, this->endy);

			glVertex2f(this->endx - dx / 2, this->endy);
			glVertex2f(this->endx - dx / 2, this->starty);

			glVertex2f(this->endx - dx / 2 - 2.5f, this->starty);
			glVertex2f(this->startx - 50.0f, this->starty);
		}
	}
	else {
		if (this->starty > this->endy) {
			if (this->startx < this->endx) {
				glVertex2f(this->startx, this->starty - 50.0f);
				glVertex2f(this->startx, this->starty + dy / 2 - 2.5f);

				glVertex2f(this->startx, this->starty + dy / 2);
				glVertex2f(this->endx, this->starty + dy / 2);

				glVertex2f(this->endx, this->starty + dy / 2 + 2.5f);
				glVertex2f(this->endx, this->endy + 50.0f);
			}
			else if (this->endx < this->startx) {
				glVertex2f(this->startx, this->starty - 50.0f);
				glVertex2f(this->startx, this->starty + dy / 2 - 2.5f);

				glVertex2f(this->startx, this->starty + dy / 2);
				glVertex2f(this->endx, this->starty + dy / 2);

				glVertex2f(this->endx, this->starty + dy / 2 + 2.5f);
				glVertex2f(this->endx, this->endy + 50.0f);
			}
			else if (this->startx == this->endx) {
				glVertex2f(this->startx, this->starty - 50.0f);
				glVertex2f(this->endx, this->endy + 50.0f);
			}
		}
		else {
			if (this->startx < this->endx) {
				glVertex2f(this->startx, this->starty + 50.0f);
				glVertex2f(this->startx, this->starty + dy / 2 + 2.5f);

				glVertex2f(this->startx, this->starty + dy / 2);
				glVertex2f(this->endx, this->starty + dy / 2);

				glVertex2f(this->endx, this->starty + dy / 2 - 2.5f);
				glVertex2f(this->endx, this->endy - 50.0f);
			}
			else if (this->endx < this->startx) {
				glVertex2f(this->startx, this->starty + 50.0f);
				glVertex2f(this->startx, this->starty + dy / 2 + 2.5f);

				glVertex2f(this->startx, this->starty + dy / 2);
				glVertex2f(this->endx, this->starty + dy / 2);

				glVertex2f(this->endx, this->starty + dy / 2 - 2.5f);
				glVertex2f(this->endx, this->endy - 50.0f);
			}
			else if (this->startx == this->endx) {
				glVertex2f(this->startx, this->starty + 50.0f);
				glVertex2f(this->endx, this->endy - 50.0f);
			}
		}
	}

	glEnd();
}

void Wire::Draw(float x1, float y1, float x2, float y2) {
	float dx = x2 - x1;
	float dy = y2 - y1;

	glColor3f(0.3f, 0.3f, 0.7f);

	glLineWidth(5.0f);

	glBegin(GL_LINES);

	if (dx > 100.0f || dx < -100.0f) {
		if (x1 < x2) {
			glVertex2f(x1 + 50.0f, y1);
			glVertex2f(x1 + dx / 2 + 2.5f, y1);

			glVertex2f(x1 + dx / 2, y1);
			glVertex2f(x1 + dx / 2, y2);

			glVertex2f(x1 + dx / 2 - 2.5f, y2);
			glVertex2f(x2 - 50.0f, y2);
		}
		else if (x2 < x1) {
			glVertex2f(x2 + 50.0f, y2);
			glVertex2f(x2 - dx / 2 + 2.5f, y2);

			glVertex2f(x2 - dx / 2, y2);
			glVertex2f(x2 - dx / 2, y1);

			glVertex2f(x2 - dx / 2 - 2.5f, y1);
			glVertex2f(x1 - 50.0f, y1);
		}
	}
	else {
		if (y1 > y2) {
			if (x1 < x2) {
				glVertex2f(x1, y1 - 50.0f);
				glVertex2f(x1, y1 + dy / 2 - 2.5f);

				glVertex2f(x1, y1 + dy / 2);
				glVertex2f(x2, y1 + dy / 2);

				glVertex2f(x2, y1 + dy / 2 + 2.5f);
				glVertex2f(x2, y2 + 50.0f);
			}
			else if (x2 < x1) {
				glVertex2f(x1, y1 - 50.0f);
				glVertex2f(x1, y1 + dy / 2 - 2.5f);

				glVertex2f(x1, y1 + dy / 2);
				glVertex2f(x2, y1 + dy / 2);

				glVertex2f(x2, y1 + dy / 2 + 2.5f);
				glVertex2f(x2, y2 + 50.0f);
			}
			else if (x1 == x2) {
				glVertex2f(x1, y1 - 50.0f);
				glVertex2f(x2, y2 + 50.0f);
			}
		}
		else {
			if (x1 < x2) {
				glVertex2f(x1, y1 + 50.0f);
				glVertex2f(x1, y1 + dy / 2 + 2.5f);

				glVertex2f(x1, y1 + dy / 2);
				glVertex2f(x2, y1 + dy / 2);

				glVertex2f(x2, y1 + dy / 2 - 2.5f);
				glVertex2f(x2, y2 - 50.0f);
			}
			else if (x2 < x1) {
				glVertex2f(x1, y1 + 50.0f);
				glVertex2f(x1, y1 + dy / 2 + 2.5f);

				glVertex2f(x1, y1 + dy / 2);
				glVertex2f(x2, y1 + dy / 2);

				glVertex2f(x2, y1 + dy / 2 - 2.5f);
				glVertex2f(x2, y2 - 50.0f);
			}
			else if (x1 == x2) {
				glVertex2f(x1, y1 + 50.0f);
				glVertex2f(x2, y2 - 50.0f);
			}
		}
	}

	glEnd();
}

Wire* CopyWires(int wirecount, Wire* wires) {
	Wire* wire = new Wire[wirecount];
	for (int i = 0; i < wirecount; i++) {
		wire[i] = wires[i];
	}

	return wire;
}