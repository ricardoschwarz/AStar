#pragma once
#include <qpainter.h>

#define NODE_SIZE 20

namespace astar
{
	enum class NodeType { free = 0, blocked = 1, start = 2, end = 3, visited = 4, path = 5 };

	class Node
	{
	public:
		Node(int x_pos = 0, int y_pos = 0, NodeType type = NodeType::free, int g_cost = 0, int h_cost = 0, int f_cost = INT_MAX);
		~Node();
		void draw(QPainter& painter);
		int distanceTo(Node* node);

		void setType(NodeType type);
		void setGCost(int gcost);
		void setHCost(int hcost);
		void setFCost(int fcost);

		NodeType getType();
		int getGCost();
		int getHCost();
		int getFCost();
		int getXPos();
		int getYPos();

		friend inline bool operator< (const Node& lhs, const Node& rhs)
		{
			return lhs.f_cost_ < rhs.f_cost_;
		}

		static bool cmp(const Node* lhs, const Node* rhs)
		{
			return lhs->f_cost_ < rhs->f_cost_;
		}

	private:
		NodeType type_;
		int x_pos_;
		int y_pos_;
		int g_cost_;
		int h_cost_;
		int f_cost_;
	};	
}
