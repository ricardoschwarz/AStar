#include "AStar.h"
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <qlayout.h>

namespace astar
{
	AStar::AStar(QWidget *parent)
		: QMainWindow(parent)
	{
		ui.setupUi(this);
		ui.verticalLayout->addWidget(&field_);
	}

	void AStar::keyPressEvent(QKeyEvent * event)
	{
		if (event->key() == Qt::Key_Return)
			this->run();
		else if (event->key() == Qt::Key_Backspace)
			field_.clear(true, true, true, true, true);
	}

	void AStar::run()
	{
		field_.clear(true, true);

		if (field_.getStartNode() != nullptr)
			field_.getStartNode()->setType(NodeType::start);

		if (field_.getEndNode() != nullptr)
			field_.getEndNode()->setType(NodeType::end);

		// *** evaluated nodes ***
		std::set<Node*> closed_set = {};

		// *** nodes that are discovered and need to be evaluated ***
		if (field_.getStartNode() == nullptr || field_.getEndNode() == nullptr)
			return;
		std::set<Node*> open_set = { field_.getStartNode() };

		// *** every node has a parent node from which it can be reached ***
		std::map<Node*, Node*> came_from;

		// *** starting f cost
		field_.getStartNode()->setFCost(field_.getStartNode()->distanceTo(field_.getEndNode()));

		while (!open_set.empty()) {
			Node* current = *std::min_element(open_set.begin(), open_set.end(), Node::cmp);
			if (current == field_.getEndNode()) {
				reconstructPath(came_from, current);
				return;
			}
			open_set.erase(current);
			closed_set.insert(current);
			
			std::vector<Node*> neighborhood = field_.getNeighborhood(current);
			for (auto* neighbor : neighborhood) {
				if (closed_set.count(neighbor) > 0)
					continue;

				int tent_g_score = current->getGCost() + current->distanceTo(neighbor);

				if (open_set.count(neighbor) == 0) {
					open_set.insert(neighbor);
				}
				else if (tent_g_score >= neighbor->getGCost()) {
					continue;
				}

				came_from[neighbor] = current;
				neighbor->setGCost(tent_g_score);
				neighbor->setFCost(neighbor->getGCost() + neighbor->distanceTo(field_.getEndNode()));
			}
			update();
			QApplication::processEvents();
		}
	}

	void AStar::reconstructPath(std::map<Node*, Node*> came_from, Node* current)
	{
		current->setType(NodeType::end);
		while (came_from.find(current) != came_from.end()) {
			current = came_from[current];
			current->setType(NodeType::path);
		}
		current->setType(NodeType::start);
		update();
	}
}
