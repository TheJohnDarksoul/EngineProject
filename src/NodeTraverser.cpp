#include "NodeTraverser.h"

#include "Utils.h"

NodeTraverser::NodeTraverser()
{
	root = nullptr;
	segments = nullptr;
}

NodeTraverser::NodeTraverser(Node* node, std::vector<Segment>* segs)
{
	root = node;
	segments = segs;
}

NodeTraverser::~NodeTraverser()
{

}

Node* NodeTraverser::getRoot()
{
	return root;
}

void NodeTraverser::traverse(Node* node, Vector2* cameraPosition)
{
	if (node == nullptr) 
	{
		return;
	}

	bool onFront = Utils::isOnFront(Utils::subVec(*cameraPosition, node->splitterStart), node->splitterVec);

	if (onFront) 
	{
		traverse(node->front, cameraPosition);

		segIdsToDraw.push_back(node->segmentId);

		traverse(node->back, cameraPosition);
	}
	else 
	{
		traverse(node->back, cameraPosition);

		segIdsToDraw.push_back(node->segmentId);

		traverse(node->front, cameraPosition);
	}
}

void NodeTraverser::update()
{
	segIdsToDraw.clear();
}
