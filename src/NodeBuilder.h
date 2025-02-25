#pragma once

#include <vector>
#include <cstdint>
#include "levelcomponents.h"

class NodeBuilder
{
private:
	std::vector<Segment> segList;
	Node root;

	void splitSpace(Node* node, std::vector<Segment>* input, std::vector<Segment>* front, std::vector<Segment>* back);
	void buildBSPTree(Node* node, std::vector<Segment>* input);

public:
	NodeBuilder();
	NodeBuilder(Segment* segArray, unsigned int length);
	~NodeBuilder();

};

