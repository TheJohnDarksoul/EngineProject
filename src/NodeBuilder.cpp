#include "NodeBuilder.h"

#include <math.h>
#include <iostream>
#include "Utils.h"

void NodeBuilder::splitSpace(Node* node, std::vector<Segment>* input, std::vector<Segment>* front, std::vector<Segment>* back)
{
	/*
	Segment splitterSeg = input->at(0);

	node->splitterVec = splitterSeg.getVector();
	node->splitterStart = splitterSeg.getStart();
	node->splitterEnd = splitterSeg.getEnd();

	for (unsigned int i = 0; i < input->size(); ++i) 
	{
		Vector2 segStart = input->at(i).getStart();
		Vector2 segEnd = input->at(i).getEnd();
		Vector2 segVec = input->at(i).getVector();

		float numerator = Utils::cross2d(Utils::subVec(segStart, splitterSeg.getStart()), node->splitterVec);
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

				Segment rightSeg = input->at(i);
				rightSeg.setPosition(segStart, intersectPoint);
				rightSeg.setVector(Utils::subVec(rightSeg.getEnd(), rightSeg.getStart()));

				Segment leftSeg = input->at(i);
				leftSeg.setPosition(intersectPoint, segEnd);
				leftSeg.setVector(Utils::subVec(leftSeg.getEnd(), leftSeg.getStart()));

				if (numerator > 0) 
				{
					Segment tmpSeg = rightSeg;
					rightSeg = leftSeg;
					leftSeg = tmpSeg;
				}

				front->push_back(rightSeg);
				back->push_back(leftSeg);
				continue;
			}

			if (numerator < 0 || (numerIsZero && denominator > 0)) 
			{
				front->push_back(input->at(i));
			}
			else if (numerator > 0 || (numerIsZero && denominator < 0)) 
			{
				back->push_back(input->at(i));
			}
		}
	}

	addSegment(splitterSeg, node);
	*/

	Segment* splitterSeg = &input->at(0);

	node->splitterVec = splitterSeg->getVector();
	node->splitterStart = splitterSeg->getStart();
	node->splitterEnd = splitterSeg->getEnd();

	for (uint32_t i = 1; i < input->size(); ++i) 
	{
		Vector2 segStart = input->at(i).getStart();
		Vector2 segEnd = input->at(i).getEnd();
		Vector2 segVec = input->at(i).getVector();

		float numerator = Utils::cross2d((Utils::subVec(segStart, splitterSeg->getStart())), splitterSeg->getVector());
		float denominator = Utils::cross2d(splitterSeg->getVector(), segVec);

		bool denomIsZero = fabsf(denominator) < EPS;
		bool numerIsZero = fabsf(numerator) < EPS;

		if (denomIsZero && numerIsZero) 
		{
			front->push_back(input->at(i));
			continue;
		}

		if (!denomIsZero) 
		{
			float intersection = numerator / denominator;

			if (0.0f < intersection && intersection < 1.0f) 
			{
				Vector2 intersectionPoint = Utils::addVec(segStart, Utils::multVec(segVec, intersection));

				Segment rSegment = input->at(i);
				rSegment.setPosition(segStart, intersectionPoint);
				rSegment.setVector(Utils::subVec(rSegment.getEnd(), rSegment.getStart()));

				Segment lSegment = input->at(i);
				lSegment.setPosition(intersectionPoint, segEnd);
				lSegment.setVector(Utils::subVec(lSegment.getEnd(), lSegment.getStart()));

				if (numerator > 0.f)
				{
					Segment tmp = rSegment;
					rSegment = lSegment;
					lSegment = rSegment;
				}

				front->push_back(rSegment);
				back->push_back(lSegment);
				continue;
			}

			if (numerator < 0.f || (numerIsZero && denominator > 0.f)) 
			{
				front->push_back(input->at(i));
			}
			else if (numerator > 0.f or (numerIsZero && denominator < 0.f)) 
			{
				back->push_back(input->at(i));
			}
		}
	}

	addSegment(splitterSeg, node);
	//done
}

//Recursively builds the BSP tree which contains level data
//Expensive, will eventually be moved into it's own program
void NodeBuilder::buildBSPTree(Node* node, std::vector<Segment>* input)
{
	if (input->size() == 0) 
	{
		return;
	}

	std::vector<Segment> frontSegs;
	std::vector<Segment> backSegs;

	splitSpace(node, input, &frontSegs, &backSegs);

	if (backSegs.size() > 0) 
	{
		node->back = new Node();
		buildBSPTree(node, &backSegs);
	}

	if (frontSegs.size() > 0) 
	{
		node->front = new Node();
		buildBSPTree(node, &frontSegs);
	}
}

void NodeBuilder::addSegment(Segment* spllitterSeg, Node* node)
{
	segments.push_back(*spllitterSeg);
	node->segmentId = segId;
	++segId;
}

NodeBuilder::NodeBuilder()
{
	segId = 0;
}

NodeBuilder::NodeBuilder(Segment* segArray, unsigned int length)
{
	segId = 0;

	for (unsigned int i = 0; i < length; ++i) 
	{
		rawSegments.push_back(segArray[i]);
	}

	buildBSPTree(&this->root, &rawSegments);

	//std::cout << "Done building tree!\n";
}

NodeBuilder::~NodeBuilder()
{
	//Free memory

	freeTree(root.back);
	freeTree(root.front);
}

void NodeBuilder::freeTree(Node* node)
{
	if (node != nullptr) 
	{
		freeTree(node->front);
		freeTree(node->back);
		delete node;
	}
}

void NodeBuilder::drawSegs(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);

	for (unsigned int i = 0; i < segments.size(); ++i) 
	{
		segments.at(i).render2d(renderer);
	}
}
