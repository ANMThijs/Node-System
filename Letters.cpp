#include "Letters.h"

void DrawA() {
	glColor3f(0.0f, 0.0f, 0.0f);

	glBegin(GL_TRIANGLES);

	glVertex2f(-33.0f - 910.0f, 50.0f - 470.0f);
	glVertex2f(-27.0f - 910.0f, 50.0f - 470.0f);
	glVertex2f(0.0f - 910.0f, -47.0f - 470.0f);

	glVertex2f(-33.0f - 910.0f, 50.0f - 470.0f);
	glVertex2f(0.0f - 910.0f, -47.0f - 470.0f);
	glVertex2f(0.0f - 910.0f, -62.0f - 470.0f);

	glVertex2f(33.0f - 910.0f, 50.0f - 470.0f);
	glVertex2f(27.0f - 910.0f, 50.0f - 470.0f);
	glVertex2f(0.0f - 910.0f, -47.0f - 470.0f);

	glVertex2f(33.0f - 910.0f, 50.0f - 470.0f);
	glVertex2f(0.0f - 910.0f, -47.0f - 470.0f);
	glVertex2f(0.0f - 910.0f, -62.0f - 470.0f);

	glVertex2f(-15.0f - 910.0f, -3.0f - 470.0f);
	glVertex2f(15.0f - 910.0f, -3.0f - 470.0f);
	glVertex2f(15.0f - 910.0f, 3.0f - 470.0f);

	glVertex2f(-15.0f - 910.0f, -3.0f - 470.0f);
	glVertex2f(15.0f - 910.0f, 3.0f - 470.0f);
	glVertex2f(-15.0f - 910.0f, 3.0f - 470.0f);

	glEnd();
}