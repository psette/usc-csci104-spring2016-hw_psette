#include "debugger.h"
#include <iostream>
#include <string>
Debugger::~Debugger() {
	delete h1;
	delete v1;
	delete combo;
	delete breakpoint;
	delete continue_button;
	delete step_button;
	delete next_button;
	delete inspect_button;
	delete quit_button;
	delete window;
	delete calc;
}
Debugger::Debugger(QFile* file, std::string filename) {
	this->app = app;
	h1 = new QHBoxLayout;
	combo = new QListWidget;
	v1 = new QVBoxLayout;
	window = new QWidget;
	breakpoint = new QPushButton("Set Breakpoint");
	continue_button = new QPushButton("Continue");
	step_button = new QPushButton("Step");
	next_button = new QPushButton("Next");
	inspect_button = new QPushButton("Inspect");
	quit_button = new QPushButton("Quit");
	calc = new Facile(filename);
	h1->addWidget(breakpoint);
	h1->addWidget(continue_button);
	h1->addWidget(step_button);
	h1->addWidget(next_button);
	h1->addWidget(inspect_button);
	h1->addWidget(quit_button);
	QTextStream inFile(file);
	combo->addItem(inFile.readLine());
    while (!inFile.atEnd()) combo->addItem(inFile.readLine());
	v1->addWidget(combo);
	v1->addLayout(h1);
	window->setLayout(v1);
	window->setWindowTitle("Debugger");
	QObject::connect(breakpoint, SIGNAL(clicked()), this, SLOT( setBreak() ));
	QObject::connect(continue_button, SIGNAL(clicked()), this, SLOT( continue_func() ) );
	QObject::connect(step_button, SIGNAL(clicked()), this, SLOT( step() ));
	QObject::connect(next_button, SIGNAL(clicked()), this, SLOT( next() ));
	QObject::connect(inspect_button, SIGNAL(clicked()), this, SLOT( inspect() ) );
	QObject::connect(quit_button, SIGNAL(clicked()), this, SLOT( quit() ));
	window->show();
}
void Debugger::setBreak(){
	int row = combo->currentRow();
	if(calc->Facile::breakpoint(row))	return;
	combo->item(row)->setForeground(Qt::blue);
}
void Debugger::continue_func(){
	int row = calc->Facile::execute('c');
	if(-42 == row) Debugger::reset();
	else combo->setCurrentRow(row);
}
void Debugger::step() {
	int row = calc->Facile::execute('s');
	if(-42 == row) Debugger::reset();
	else combo->setCurrentRow(row);
}
void Debugger::next(){
	int row = calc->Facile::execute('n');
	if(-42 == row) Debugger::reset();
	else combo->setCurrentRow(row);
}
void Debugger::inspect(){
	calc->Facile::inspect();
}
void Debugger::reset(){
	for(int i = combo->count() - 1; i >= 0; i--)	combo->item(i)->setForeground(Qt::black);
	combo->setCurrentRow(0);
	calc->Facile::reset();
}
void Debugger::quit(){
	app->quit();
}