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
#include "../lib/Facile.h"
class values_window : public QWidget {
	Q_OBJECT
	public slots:
		void ascendName();
		void descendName();
		void ascendVal();
		void descendVal();
		void hide_win();
		void show_win();
		void update_win();
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
		QPushButton *ascending_name, *ascending_value, *hide_button;
		QPushButton *descending_name, *descending_value, *update;
		QListWidget *combo;
		QWidget *window;
		QHBoxLayout *h1;
		QVBoxLayout *v1;
		Facile * calc;
		std::vector<std::pair<std::string,int> > values_vector;
		char sort_type;
};
#endif