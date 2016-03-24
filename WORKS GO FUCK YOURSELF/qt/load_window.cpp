#include "load_window.h"
LoadWindow::LoadWindow(QApplication* App){
	this->App = App;
	setWindowTitle("Facile Debug");
	overallLayout = new QVBoxLayout();
	filename_layout = new QHBoxLayout();
	filename_label = new QLabel("Filename");
	filename = new QLineEdit();
	filename_layout->addWidget(filename_label);
	filename_layout->addWidget(filename);
	other_layout = new QHBoxLayout();
	quit_button = new QPushButton("QUIT");
	run_button = new QPushButton("RUN");
	other_layout->addWidget(quit_button);
	other_layout->addWidget(run_button);
	overallLayout->addLayout(filename_layout);
	overallLayout->addLayout(other_layout);
	run_button->setAutoDefault(true);
	run_button->setDefault(true);
	run_button->setFocus();
	connect(filename, SIGNAL(returnPressed()), run_button, SIGNAL(clicked()));
	connect(quit_button, SIGNAL( clicked() ), this, SLOT(quit()));
	connect(run_button, SIGNAL( clicked() ), this, SLOT(run()));
	setLayout(overallLayout);
}
LoadWindow::~LoadWindow(){
	delete run_button;
	delete quit_button;
	delete other_layout;
	delete filename_label;
	delete filename;
	delete filename_layout;
	delete overallLayout;
}
void LoadWindow::quit(){
	App->quit();
}
void LoadWindow::run(){
	QString tempName = filename->text();
 	QFile* file = new QFile(tempName);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))	QMessageBox::information(0, "File Does Not Exsist", file->errorString());
    else	{
    	debug =  new Debugger(file,tempName.toStdString());
    	this->close();
    }
}