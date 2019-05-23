#include "Field.h"
#include "qpainter.h"
#include <qdebug.h>

namespace astar
{
	Field::Field()
	{
		for (int i = 0; i < FIELD_SIZE; i++) {
			grid_.push_back(std::vector<Node>());
			for (int j = 0; j < FIELD_SIZE; j++) {
				grid_[i].push_back(Node(j, i));
			}
		}
	}

	Field::~Field()
	{
	}

	std::vector<Node*> Field::getNeighborhood(Node * node)
	{
		std::vector<Node*> neighborhood;

		if (grid_.empty())
			return neighborhood;

		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				int x = node->getXPos() + j;
				int y = node->getYPos() + i;

				// *** bounds check ***
				if (y < 0 || y > grid_.size() - 1 || x < 0 || x > grid_[0].size() - 1 || i == 0 && j == 0)
					continue;

				Node* neighboor = &grid_[y][x];

				// *** NodeType check ***
				if (neighboor->getType() == NodeType::blocked || neighboor->getType() == NodeType::visited || neighboor->getType() == NodeType::start)
					continue;

				neighboor->setType(NodeType::visited);
				neighborhood.push_back(neighboor);
			}
		}
		return neighborhood;
	}

	Node* Field::getStartNode()
	{
		return start_node_;
	}

	void Field::setStartNode(Node* node)
	{
		start_node_ = node;
	}

	Node* Field::getEndNode()
	{
		return end_node_;
	}

	void Field::setEndNode(Node* node)
	{
		end_node_ = node;
	}

	void Field::clear(bool path, bool visited, bool blocked, bool start, bool end)
	{
		if (start)
			start_node_ = nullptr;
		if (end)
			end_node_ = nullptr;

		for (auto& row : grid_) {
			for (auto& node : row) {
				NodeType type = node.getType();
				if (type == NodeType::path && path)
					node.setType(NodeType::free);
				else if (type == NodeType::visited && visited)
					node.setType(NodeType::free);
				else if (type == NodeType::blocked && blocked)
					node.setType(NodeType::free);
				else if (type == NodeType::start && start)
					node.setType(NodeType::free);
				else if (type == NodeType::end && end)
					node.setType(NodeType::free);
			}
		}
		update();
	}

	void Field::paintEvent(QPaintEvent * event)
	{
		QPainter painter(this);
		for (int i = 0; i < grid_.size(); i++) {
			for (int j = 0; j < grid_[0].size(); j++) {
				grid_[i][j].draw(painter);
			}
		}
	}

	void Field::mousePressEvent(QMouseEvent* event)
	{
		int x = event->pos().x() / NODE_SIZE;
		int y = event->pos().y() / NODE_SIZE;

		// *** bounds checks ***
		if (grid_.empty() || grid_[0].empty())
			return;

		if (y > grid_.size() - 1 || x > grid_[0].size() - 1)
			return;

		// *** Node state handling ***
		if (event->button() == Qt::RightButton) {
			if (start_node_ != nullptr)
				start_node_->setType(NodeType::free);
			grid_[y][x].setType(NodeType::start);
			start_node_ = &grid_[y][x];
		}
		else if (event->button() == Qt::MiddleButton) {
			if (end_node_ != nullptr)
				end_node_->setType(NodeType::free);
			grid_[y][x].setType(NodeType::end);
			end_node_ = &grid_[y][x];
		}
		else if (event->button() == Qt::LeftButton) {
			grid_[y][x].setType(NodeType::blocked);
		}
		update();
	}

	void Field::mouseMoveEvent(QMouseEvent * event)
	{
		int x = event->pos().x() / NODE_SIZE;
		int y = event->pos().y() / NODE_SIZE;

		// *** bounds check ***
		if (grid_.empty() || grid_[0].empty())
			return;

		if (y > grid_.size() - 1 || x > grid_[0].size() - 1)
			return;

		// *** repaint widget only when necessary ***
		if (grid_[y][x].getType() != NodeType::blocked && event->buttons() == Qt::LeftButton) {
			grid_[y][x].setType(NodeType::blocked);
			update();
		}
	}
}
