#include "NodeBuilder.h"

void NodeBuilder::splitSpace(Node* node, std::vector<Segment>* input)
{

}

//Recursively builds the BSP tree which contains level data
void NodeBuilder::buildBSPTree(Node* node, std::vector<Segment>* input)
{
	if (input->size() == 0) 
	{
		return;
	}

	std::vector<Segment> front;
	std::vector<Segment> back;

	//Get front segemnts
	//Get back segments

	if (back.size() > 0) 
	{
		buildBSPTree(node->getBack(), &back);
	}

	if (front.size() > 0) 
	{
		buildBSPTree(node->getFront(), &front);
	}
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

	buildBSPTree(&this->root, &segList);
}

NodeBuilder::~NodeBuilder()
{

}
