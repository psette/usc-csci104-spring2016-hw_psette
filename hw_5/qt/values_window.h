#ifndef _VALUES_WINDOW_H
#define _VALUES_WINDOW_H
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QListWidget>
#include <QApplication>
#include <QFile>
#include <QString>
#include <QMessageBox>
#include <QTextStream>
#include <vector>
#include <QRadioButton>
#include "../lib/Facile.h"
class values_window : public QWidget {
	Q_OBJECT
	public slots:
		void show_win();
		void update_win();
		void hide_win();
	public:
		values_window(Facile*);
		~values_window();
		void show_win_helper();
		void getValues();
		template <class T, class Comparator>
		void mergesort(std::vector<T>&, int, int, Comparator);
		template <class T, class Comparator>
		void sort(std::vector<T>&);
	private:
		QApplication *app;
		QRadioButton *ascending_name, *ascending_value, *descending_name, *descending_value;
		QPushButton  *update, *hide_button;
		QListWidget *combo;
		QWidget *window;
		QHBoxLayout *h1;
		QVBoxLayout *v1,*v2;
		Facile * calc;
		std::vector<std::pair<std::string,int> > values_vector;
		char sort_type;
};
#endif