#include "Node.h"

Node::Node() {
	this->xpos = 0.0f;
	this->ypos = 0.0f;
	this->colourr = NODE_COLOURR_DEF;
	this->colourg = NODE_COLOURG_DEF;
	this->colourb = NODE_COLOURB_DEF;
	this->selected = false;
}

Node::~Node() {

}

Node::Node(float x, float y) {
	this->xpos = x;
	this->ypos = y;
	this->colourr = NODE_COLOURR_DEF;
	this->colourg = NODE_COLOURG_DEF;
	this->colourb = NODE_COLOURB_DEF;
	this->selected = false;
}

void Node::Render() {
	float nsize = NODE_SIZE / 2;

	glBegin(GL_TRIANGLES);

	if (this->selected == true) {
		glColor3f(NODE_COLOURR_SEL, NODE_COLOURG_SEL, NODE_COLOURB_SEL);
	}
	else if (this->selected == false) {
		glColor3f(NODE_COLOURR_DEF, NODE_COLOURG_DEF, NODE_COLOURB_DEF);
	}
	glVertex2f(this->xpos - nsize, this->ypos - nsize);
	glVertex2f(this->xpos + nsize, this->ypos - nsize);
	glVertex2f(this->xpos + nsize, this->ypos + nsize);
	
	glVertex2f(this->xpos - nsize, this->ypos - nsize);
	glVertex2f(this->xpos + nsize, this->ypos + nsize);
	glVertex2f(this->xpos - nsize, this->ypos + nsize);
	glEnd();
}

void Node::Move(float x, float y) {
	this->xpos -= x;
	this->ypos -= y;
}