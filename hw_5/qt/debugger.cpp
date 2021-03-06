#include "debugger.h"
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
	delete val_win;
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
	val_win = new values_window(calc);
	h1->addWidget(breakpoint);
	h1->addWidget(continue_button);
	h1->addWidget(step_button);
	h1->addWidget(next_button);
	h1->addWidget(inspect_button);
	h1->addWidget(quit_button);
	QTextStream inFile(file);
    for(int i = 1; !inFile.atEnd(); i++){
    	std::stringstream ss;
		ss << i;
		combo->addItem(QString::fromStdString(ss.str())+"\t"+ inFile.readLine());
    }
    combo->setCurrentRow(0);
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
	row = 1;
	prev_row = 1;
	is_done = false;
}
void Debugger::setBreak(){
	row = combo->currentRow();
	if(calc->Facile::breakpoint(row, false))	return;
	combo->item(row)->setForeground(Qt::blue);
}
void Debugger::logic_error(){
	std::stringstream ss;
	ss << row;
	std::string ErrorMsg = "Logic Error on or after line " + ss.str() + "\nProgram restarting";
	reset();
	QMessageBox::information(0, "Logic Error", QString::fromStdString(ErrorMsg) );
}
void Debugger::program_done(bool is_done, bool continue_statement){
	if(is_done) {
		for(int i = 0; i < combo->count(); ++i){
			combo->item(i)->setBackground(Qt::white);
			combo->item(i)->setForeground(Qt::black);
		}
		std::cout<<"***************PROGRAM RESTARTING***************"<<std::endl;
	}
	else {
		if(continue_statement)	row += 2;
		for(int i = 0; i < combo->count(); ++i){
			if(	calc->breakpoint(i, true) && i != prev_row) continue;
			combo->item(i)->setBackground(Qt::white);
			combo->item(i)->setForeground(Qt::black);
		}
		combo->item(row)->setBackground(Qt::black);
		combo->item(row)->setForeground(Qt::white);
		prev_row = row;
	}
}
void Debugger::continue_func(){
	if(is_done) Debugger::reset();
	try{
		row = calc->Facile::execute('c') - 2;
		combo->setCurrentRow(row);
	}catch(std::logic_error){
		logic_error();
	}
	is_done = -42 == row;
	program_done( is_done , true );
}
void Debugger::step() {
	if(is_done) Debugger::reset();
	try{
		row = calc->Facile::execute('s') - 2;
		combo->setCurrentRow(row);
	}catch(std::logic_error){
		logic_error();
	}
	is_done = -42 == row;
	program_done( is_done, false );
}
void Debugger::next(){
	if(is_done) Debugger::reset();
	try{
		row = calc->Facile::execute('n') - 2;
		combo->setCurrentRow(row);
	}catch(std::logic_error){
		logic_error();
	}
	is_done = -42 == row;
	program_done( is_done , false );
}
void Debugger::inspect(){
	val_win->show_win();
}
void Debugger::reset(){
	for(int i = combo->count() - 1; i >= 0; i--)	combo->item(i)->setForeground(Qt::black);
	combo->setCurrentRow(0);
	calc->Facile::reset();
	is_done = false;
	row = 1;
	prev_row =1;
}
void Debugger::quit(){
	app->quit();
}