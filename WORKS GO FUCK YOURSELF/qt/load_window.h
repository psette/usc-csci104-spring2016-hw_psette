#include "debugger.h"

class LoadWindow : public QWidget{
	Q_OBJECT
public:
	LoadWindow(QApplication* App);
	~LoadWindow();

private slots:
	void run();
	void quit();

private:
	QApplication* App;
	QVBoxLayout* overallLayout;
	QHBoxLayout* filename_layout;
	QHBoxLayout* other_layout;
	QLabel* filename_label;
	QLineEdit* filename;
	QPushButton* run_button;
	QPushButton* quit_button;
	Debugger* debug;
};