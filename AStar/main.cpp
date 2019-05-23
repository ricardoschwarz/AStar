#include "AStar.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	astar::AStar w;
	w.setWindowIcon(QIcon(":/AStar/Resources/star.PNG"));
	w.resize(NODE_SIZE * FIELD_SIZE + 23 /* ui offset */, NODE_SIZE * FIELD_SIZE + 23 /* ui offset */);
	w.show();
	return a.exec();
}
