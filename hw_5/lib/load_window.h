#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QListWidget>
#include <QApplication>

#include <string>

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
	QHBoxLayout* filename_layout,other_layout;
	QLabel filename_label;
	QLineEdit* filename;
	QPushButton* run_button, quit_button;
};