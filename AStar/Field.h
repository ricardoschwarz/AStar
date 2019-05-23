#pragma once
#include <Node.h>
#include <vector>
#include <qpixmap.h>
#include <qwidget.h>
#include <QMouseEvent>

#define FIELD_SIZE 30

namespace astar
{
	typedef std::vector<std::vector<Node>> Grid;

	class Field : public QWidget
	{
		Q_OBJECT
	public:
		Field();
		~Field();

		std::vector<Node*> getNeighborhood(Node* node);

		Node* getStartNode();
		void setStartNode(Node* node);
		Node* getEndNode();
		void setEndNode(Node* node);
		void clear(bool path = false, bool visited = false, bool blocked = false, bool start = false, bool end = false);

	protected:
		void paintEvent(QPaintEvent* event) override;
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);

	private:
		Grid grid_;
		Node* start_node_ = nullptr;
		Node* end_node_ = nullptr;
	};
}
