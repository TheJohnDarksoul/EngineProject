#include "NodeBuilder.h"

void NodeBuilder::splitSpace(Node* node, std::vector<Segment> input)
{

}

void NodeBuilder::buildBSPTree(Node* node, std::vector<Segment> input)
{

}

NodeBuilder::NodeBuilder()
{

}

NodeBuilder::NodeBuilder(Segment* segArray, unsigned int length)
{
	for (unsigned int i = 0; i < length; ++i) 
	{
		segList.push_back(segArray[i]);
	}

	buildBSPTree(&this->root, segList);
}

NodeBuilder::~NodeBuilder()
{

}
