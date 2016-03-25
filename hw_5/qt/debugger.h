#include "values_window.h"
#include <stdexcept>
#include <exception>
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
		void logic_error();
		void program_done(bool, bool);
	private:
		bool is_done;
		int row, prev_row;
		QApplication *app;
		QPushButton *breakpoint, *continue_button, *step_button;
		QPushButton *next_button, *inspect_button, *quit_button;
		QListWidget *combo;
		QWidget *window;
		QHBoxLayout *h1;
		QVBoxLayout *v1;
		Facile * calc;
		values_window * val_win;
};