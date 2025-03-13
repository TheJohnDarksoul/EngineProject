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

	unsigned int numFront;
	unsigned int numBack;
	unsigned int numSplits;

	void splitSpace(Node* node, std::vector<Segment>* input, std::vector<Segment>* front, std::vector<Segment>* back);
	void buildBSPTree(Node* node, std::vector<Segment>* input);
	void addSegment(Segment* splitterSeg, Node* node);

	void traverseSplitsAndDraw(Node* node, SDL_Renderer* renderer);
	void printSplitters(Node* node);

public:
	NodeBuilder();
	NodeBuilder(Segment* segArray, unsigned int length);
	~NodeBuilder();

	Node* getRoot();
	std::vector<Segment>* getSegments();

	void freeTree(Node* node);
	void drawSegs(SDL_Renderer* renderer);
	void drawSplitters(SDL_Renderer* renderer);

};

