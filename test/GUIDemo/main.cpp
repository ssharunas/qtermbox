#include <QCoreApplication>
#include "qtermbox.h"
#include "core/QTermboxCore"
#include "gui/qtermboxscreen.h"
#include "gui/widgets/qtermboxlabel.h"
#include "gui/widgets/qtermboxlineedit.h"
#include "gui/themes/qtermboxstylefactory.h"
#include "gui/themes/qtermboxtextwidgetstyle.h"

#include <QDebug>
#include <QTimer>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	QTermboxScreen *screen = QTermboxScreen::instance();
	QTermboxLineEdit *label = new QTermboxLineEdit(screen);

	QTermboxTextWidgetStyle* style = new QTermboxTextWidgetStyle();
	style->setText(QTermboxStyle(QTermbox::Green));
	style->setBackground(QTermboxStyle(QTermbox::Blue));

	QTermboxStyleFactory::instance().installStyle(&QTermboxLabel::staticMetaObject, style);

//	QTermboxWidgetStyle* theme = label->defaultTheme();
//	theme->setBackground(QTermboxStyle(QTermbox::Green));

	label->setGeometry(QRect(1, 1, 30, 1));
//	label->setText("Hello world!1324678901346789123Hello world!132467890134678912");
	label->setText("Hello world!");

	screen->exec();

	return a.exec();
}
