#pragma once

#include <vector>
#include <cstdint>
#include <SDL.h>
#include "levelcomponents.h"

class NodeBuilder
{
private:
	std::vector<Segment> rawSegments;
	std::vector<Segment> segments;
	Node root;

	uint32_t segId;

	void splitSpace(Node* node, std::vector<Segment>* input, std::vector<Segment>* front, std::vector<Segment>* back);
	void buildBSPTree(Node* node, std::vector<Segment>* input);
	void addSegment(Segment* spllitterSeg, Node* node);

public:
	NodeBuilder();
	NodeBuilder(Segment* segArray, unsigned int length);
	~NodeBuilder();

	void freeTree(Node* node);
	void drawSegs(SDL_Renderer* renderer);

};

