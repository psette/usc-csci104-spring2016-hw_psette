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
#include "../lib/Facile.h"
class Debugger : public QWidget {
	Q_OBJECT
	public slots:
		void step();
		void setBreak();
		void continue_func();
		void next();
		void inspect();
		void quit();
	public:
		Debugger(QFile*,std::string);
		~Debugger();
		void reset();
	private:
		QApplication *app;
		QPushButton *breakpoint, *continue_button, *step_button;
		QPushButton *next_button, *inspect_button, *quit_button;
		QListWidget *combo;
		QWidget *window;
		QHBoxLayout *h1;
		QVBoxLayout *v1;
		Facile * calc;
};