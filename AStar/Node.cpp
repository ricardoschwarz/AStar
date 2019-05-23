#include "Node.h"
#include <math.h>

namespace astar
{
	Node::Node(int x_pos, int y_pos, NodeType type, int g_cost, int h_cost, int f_cost) : x_pos_(x_pos), y_pos_(y_pos), type_(type), g_cost_(g_cost), h_cost_(h_cost), f_cost_(f_cost)
	{
	}

	Node::~Node()
	{
	}

	void Node::draw(QPainter & painter)
	{
		switch (type_) {
		case NodeType::free:
			painter.setBrush(Qt::white);
			painter.setPen(Qt::black);
			break;
		case NodeType::blocked:
			painter.setBrush(Qt::black);
			painter.setPen(Qt::black);
			break;
		case NodeType::start:
			painter.setBrush(Qt::red);
			painter.setPen(Qt::black);
			break;
		case NodeType::end:
			painter.setBrush(Qt::green);
			painter.setPen(Qt::black);
			break;
		case NodeType::path:
			painter.setBrush(Qt::cyan);
			painter.setPen(Qt::darkCyan);
			break;
		case NodeType::visited:
			painter.setBrush(Qt::lightGray);
			painter.setPen(Qt::black);
			break;
		}
		painter.drawRect(x_pos_ * NODE_SIZE, y_pos_ * NODE_SIZE, NODE_SIZE, NODE_SIZE);
	}

	int Node::distanceTo(Node * node)
	{ 
		/*
		 * Returns distance to neighbor.
		 *  - vertical/horizontal neighbor: 10
		 *  - diagonal neighbor: 14
		 */
		int x_diff = (this->getXPos() - node->getXPos()) * 10;
		int y_diff = (this->getYPos() - node->getYPos()) * 10;
		return std::sqrt(std::pow(x_diff, 2) + std::pow(y_diff, 2));
	}
	
	void Node::setType(NodeType type)
	{
		type_ = type;
	}

	void Node::setGCost(int gcost)
	{
		g_cost_ = gcost;
	}

	void Node::setHCost(int hcost)
	{
		h_cost_ = hcost;
	}

	void Node::setFCost(int fcost)
	{
		f_cost_ = fcost;
	}

	NodeType Node::getType()
	{
		return type_;
	}

	int Node::getGCost()
	{
		return g_cost_;
	}

	int Node::getHCost()
	{
		return h_cost_;
	}

	int Node::getFCost()
	{
		return f_cost_;
	}

	int Node::getXPos()
	{
		return x_pos_;
	}
	
	int Node::getYPos()
	{
		return y_pos_;
	}
}
