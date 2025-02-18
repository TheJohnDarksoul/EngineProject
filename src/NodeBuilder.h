#pragma once

#include <vector>
#include "levelcomponents.h"

class NodeBuilder
{
private:
	std::vector<Segment> segList;
	Node root;

	void splitSpace(Node* node, std::vector<Segment>* input);
	void buildBSPTree(Node* node, std::vector<Segment>* input);

public:
	NodeBuilder();
	NodeBuilder(Segment* segArray, unsigned int length);
	~NodeBuilder();

};

