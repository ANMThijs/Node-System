#include "ShapePresets.h"

void DrawRect(float top, float right, float bottom, float left) {
	glLineWidth(1.0f);

	glBegin(GL_LINES);

	glColor3f(0.04f, 0.04f, 0.04f);

	glVertex2f(left, top);
	glVertex2f(right, top);

	glVertex2f(right, top);
	glVertex2f(right, bottom);

	glVertex2f(right, bottom);
	glVertex2f(left, bottom);

	glVertex2f(left, bottom);
	glVertex2f(left, top);

	glEnd();
}