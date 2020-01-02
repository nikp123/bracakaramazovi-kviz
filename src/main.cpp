#include "include/mainwindow.h"
#include "include/assetmanager.h"

#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.startAsset();
	w.show();

	return a.exec();
}
