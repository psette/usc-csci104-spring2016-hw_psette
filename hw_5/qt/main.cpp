#include "load_window.h"
#include <QRect>
#include <QDesktopWidget>
int main(int argc, char* argv[]){
	QApplication app(argc,argv);
	LoadWindow loadWindow(&app);
	QRect screenGeometry = QApplication::desktop()->screenGeometry();
	loadWindow.move(screenGeometry.width()/2, screenGeometry.height()/2);
	loadWindow.show();
	return app.exec();
}