#pragma once

#include <Vector>
#include <cstdint>
#include "levelcomponents.h"

class NodeTraverser
{
private:
	Node* root;
	
	std::vector<Segment>* segments;

	std::vector<uint32_t> segIdsToDraw;

public:
	NodeTraverser();
	NodeTraverser(Node* node, std::vector<Segment>* segs);
	~NodeTraverser();

	Node* getRoot();

	void traverse(Node* node, Vector2* cameraPosition);
	void update();

};

