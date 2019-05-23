#pragma once

#include "ui_AStar.h"
#include "Field.h"

#include <QtWidgets/QMainWindow>
#include <qgraphicsscene.h>
#include <qlabel.h>

namespace astar
{
	class AStar : public QMainWindow
	{
		Q_OBJECT

	public:
		AStar(QWidget *parent = Q_NULLPTR);

	protected:
		void keyPressEvent(QKeyEvent* event);

	private:
		Ui::AStarClass ui;
		Field field_;
		QLabel controls_label_;

		void run();
		void reconstructPath(std::map<Node*, Node*> came_from, Node* current);
	};
}
