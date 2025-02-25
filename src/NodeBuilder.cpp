#include "NodeBuilder.h"

#include <math.h>
#include "Utils.h"

void NodeBuilder::splitSpace(Node* node, std::vector<Segment>* input, std::vector<Segment>* front, std::vector<Segment>* back)
{
	Segment* splitterSeg = &input->at(0);

	node->splitterVec = splitterSeg->getVector();
	node->splitterStart = splitterSeg->getStart();
	node->splitterEnd = splitterSeg->getEnd();

	for (unsigned int i = 0; i < input->size(); ++i) 
	{
		Vector2 segStart = input->at(i).getStart();
		Vector2 segEnd = input->at(i).getEnd();
		Vector2 segVec = input->at(i).getVector();

		float numerator = Utils::cross2d(Utils::subVec(segStart, splitterSeg->getStart()), node->splitterVec);
		float denominator = Utils::cross2d(node->splitterVec, segVec);

		bool denomIsZero = fabsf(denominator) < EPS;
		bool numerIsZero = fabsf(numerator) < EPS;

		if (denomIsZero && numerIsZero) 
		{
			//append to front segment list
			front->push_back(input->at(i));
			continue;
		}

		if (!denomIsZero) 
		{
			float intersection = numerator / denominator;

			if (0.f < intersection && intersection < 1.f) 
			{
				//I think this is how I do this, if I can reengineer this to use operators that would be nice
				Vector2 intersectPoint = Utils::addVec(segStart, Utils::multVec(segVec, intersection));

			}
		}
	}
}

//Recursively builds the BSP tree which contains level data
//Expensive, will eventually be moved into it's own program
void NodeBuilder::buildBSPTree(Node* node, std::vector<Segment>* input)
{
	if (input->size() == 0) 
	{
		return;
	}

	std::vector<Segment> front;
	std::vector<Segment> back;

	//This is where we split space
	//Get front segemnts
	//Get back segments
	splitSpace(node, input, &front, &back);

	if (back.size() > 0) 
	{
		Node* backNode = new Node();
		node->setBack(backNode);
		buildBSPTree(node->getBack(), &back);
	}

	if (front.size() > 0) 
	{
		Node* frontNode = new Node();
		node->setFront(frontNode);
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
	//Free memory
	Node* node = &root;
}
