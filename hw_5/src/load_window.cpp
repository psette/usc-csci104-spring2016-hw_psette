#include "load_window.h"
LoadWindow::LoadWindow(QApplication* App){
	this->App = App;
	overallLayout = new QVBoxLayout();
	filename_layout = new QHBoxLayout();
	filename_label = new QLabel("Filename");
	filename = new QLineEdit();
	filename_layout->addWidget(filename_label);
	filename_layout->addWidget(filename);
	other_layout = new QHBoxLayout();
	quit_button = new QLabel("QUIT");
	run_button = new QLabel("RUN");
	other_layout->addWidget(quit);
	other_layout->addWidget(run);
	overallLayout->addLayout(filename_layout);
	overallLayout->addLayout(other_layout);
	connect(quit, SIGNAL( clicked() ), this, SLOT(quit()));
	connect(run, SIGNAL( clicked() ), this, SLOT(run()));
}
LoadWindow::~LoadWindow(){}

void LoadWindow::quit(){
	App->quit();
}
void LoadWindow::run(){
}
