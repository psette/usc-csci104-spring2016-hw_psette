#include "values_window.h"
#include <iostream>
#include <string>
struct AscendNameComp {
    bool operator()(const std::pair<std::string,int>& lhs, const std::pair<std::string,int>& rhs) { 
      return lhs.first < rhs.first; 
	}
};
struct AscendValComp {
    bool operator()(const std::pair<std::string,int>& lhs, const std::pair<std::string,int>& rhs) { 
      return lhs.second < rhs.second; 
	}
};
struct DescendNameComp {
    bool operator()(const std::pair<std::string,int>& lhs, const std::pair<std::string,int>& rhs) { 
      return lhs.first > rhs.first; 
	}
};
struct DescendValComp {
    bool operator()(const std::pair<std::string,int>& lhs, const std::pair<std::string,int>& rhs) { 
      return lhs.second > rhs.second; 
	}
};
values_window::~values_window() {
	delete v2;
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
	calc = pass_in_calc;
	this->app = app;
	h1 = new QHBoxLayout;
	combo = new QListWidget;
	v1 = new QVBoxLayout;
	v2 = new QVBoxLayout;
	window = new QWidget;
	ascending_name = new QRadioButton("Names ^");
	descending_name = new QRadioButton("Names V");
	ascending_value = new QRadioButton("Values ^");
	descending_value = new QRadioButton("Values V");
	hide_button = new QPushButton("Hide");
	update = new QPushButton("update");
	v2->addWidget(ascending_name);
	v2->addWidget(descending_name);
	v2->addWidget(ascending_value);
	v2->addWidget(descending_value);
	h1->addWidget(hide_button);
	h1->addWidget(update);
	v1->addWidget(combo);
	v1->addLayout(h1);
	v1->addLayout(v2);
	window->setLayout(v1);
	window->setWindowTitle("values_window");
	QObject::connect(update, SIGNAL(clicked()), this, SLOT( update_win() ) );
	QObject::connect(hide_button, SIGNAL(clicked()), this, SLOT( hide_win() ));
}

void values_window::update_win(){
	getValues();
	if(ascending_name->isChecked()){
		AscendNameComp comp;
		mergesort(values_vector,0,values_vector.size(),comp);
	} else if(descending_name->isChecked()){
		DescendNameComp comp;
		mergesort(values_vector,0,values_vector.size(),comp);
	} else if(ascending_value->isChecked()){
		AscendValComp comp;
		mergesort(values_vector,0,values_vector.size(),comp);
	} else{
		DescendValComp comp;
		mergesort(values_vector,0,values_vector.size(),comp);
	}
	show_win_helper(); 
}
void values_window::getValues(){
	combo->clear();
	values_vector.clear();
	values_vector = calc->getVals();
}
void values_window::show_win_helper(){
	for(std::vector<std::pair<std::string,int> >::const_iterator it = values_vector.begin(); it != values_vector.end(); ++it){
		std::string var = it -> first;
		std::stringstream ss;
		ss << it->second;
		std::string temp;
		ss >> temp;
		var += "\t" + temp;
		combo->addItem( QString::fromStdString(var) );
	}
	window->show();
}
void values_window::show_win(){
	getValues();
	show_win_helper();
}
void values_window::hide_win(){
	window->hide();
}
template <class T, class Comparator>
void values_window::mergesort(std::vector<T>& input, int low, int high, Comparator comp) {
	if (low >= high - 1)	return;
	int mid = (low + high) / 2;
	mergesort(input, low, mid, comp);
	mergesort(input, mid, high,comp);
	int l1 = low, h1 = mid, l2 = mid, h2 = high;
	std::vector<T> temp;
	while (l1 < h1 && l2 < h2){
		if ( comp(input[l1],input[l2]) ) temp.push_back(input[l1++]);
		else	temp.push_back(input[l2++]);
	}
	while (l1 < h1)	temp.push_back(input[l1++]);
	while (l2 < h2)	temp.push_back(input[l2++]);
	for (int i=0; i<temp.size(); i++) input[i + low] = temp[i];
}
