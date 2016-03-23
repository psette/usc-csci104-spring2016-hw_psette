#include "values_window.h"
#include <iostream>
#include <string>
values_window::~values_window() {
	delete h1;
	delete v1;
	delete combo;
	delete ascending_name;
	delete descending_name;
	delete ascending_value;
	delete descending_value;
	delete hide_button;
	delete window;
}
values_window::values_window(Facile* pass_in_calc) {
	std::cout<<"VALS"<<std::endl;
	calc = pass_in_calc;
	this->app = app;
	h1 = new QHBoxLayout;
	combo = new QListWidget;
	v1 = new QVBoxLayout;
	window = new QWidget;
	ascending_name = new QPushButton("Names ↑");
	descending_name = new QPushButton("Names ↓");
	ascending_value = new QPushButton("Values ↑");
	descending_value = new QPushButton("Values ↓");
	hide_button = new QPushButton("Hide");
	update = new QPushButton("update");
	h1->addWidget(ascending_name);
	h1->addWidget(descending_name);
	h1->addWidget(ascending_value);
	h1->addWidget(descending_value);
	h1->addWidget(hide_button);
	h1->addWidget(update);
	v1->addWidget(combo);
	v1->addLayout(h1);
	window->setLayout(v1);
	window->setWindowTitle("values_window");
	QObject::connect(ascending_name, SIGNAL(clicked()), this, SLOT( ascendName() ));
	QObject::connect(descending_name, SIGNAL(clicked()), this, SLOT( descendName() ) );
	QObject::connect(ascending_value, SIGNAL(clicked()), this, SLOT( ascendVal() ));
	QObject::connect(descending_value, SIGNAL(clicked()), this, SLOT( descendVal() ));
	QObject::connect(update, SIGNAL(clicked()), this, SLOT( update_win() ) );
	QObject::connect(hide_button, SIGNAL(clicked()), this, SLOT( hide_win() ));
}
void values_window::update_win(){}
void values_window::ascendName(){
	sort_type = 'A';
}
void values_window::descendName(){
	sort_type = 'B';
}
void values_window::ascendVal(){
	sort_type = 'C';
}
void values_window::descendVal(){
	sort_type = 'D';
}
void values_window::getValues(){
	values_vector = calc->getVals();
}
void values_window::show_win(){
	for(std::vector<std::pair<std::string,int> >::iterator it = values_vector.begin(); it != values_vector.end(); ++it){
		std::string var = it -> first;
		std::stringstream ss;
		ss << it->second;
		std::string temp;
		ss >> temp;
		var += "\t" + temp;
		combo->addItem( QString::fromStdString(var) );
	}
}
void values_window::hide_win(){
	window->hide();
}
template <class T, class Comparator>
void values_window::mergesort(std::vector<T>& input, int low, int high, Comparator comp) {
	if (low >= high - 1)	return;
	int mid = (low + high) / 2;
	mergesort(input, low, mid, comp);
	mergesort(input, mid + 1, high);
	int l1 = low, h1 = mid, l2 = mid, h2 = high;
	std::vector<T> temp;
	while (l1 < h1 && l2 < h2){
		if (input[l1] < input[l2]) temp.push_back(input[l1++]);
		else	temp.push_back(input[l2++]);
	}
	while (l1 < h1)	temp.push_back(input[l1++]);
	while (l2 < h2)	temp.push_back(input[l2++]);
	for (int i=0; i<temp.size(); i++) input[i + low] = temp[i];
}
