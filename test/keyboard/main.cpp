#include <QCoreApplication>
#include <unistd.h>
#include "keyboard.h"
#include <QTermboxCore>
#include <QTimer>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	Keyboard keyboard;
	keyboard.connect(QTermboxEventPool::instance(), SIGNAL(onKeyEvent(QTermboxKeyEvent)), &keyboard, SLOT(onKeyEvent(QTermboxKeyEvent)));
	keyboard.connect(QTermboxEventPool::instance(), SIGNAL(onKeyEventAlternative(QTermboxKeyEvent)), &keyboard, SLOT(onKeyEventAlternative(QTermboxKeyEvent)));
	keyboard.connect(QTermboxEventPool::instance(), SIGNAL(onResizeEvent(QTermboxResizeEvent)), &keyboard, SLOT(onResizeEvent(QTermboxResizeEvent)));

	QTermboxCore::putCell(1, 1, QString("1"), QTermboxStyle(QTermbox::White), QTermboxStyle(QTermbox::Black));
	QTermboxCore::present();

	QTermboxEventPool::instance()->start();

	return a.exec();
}
