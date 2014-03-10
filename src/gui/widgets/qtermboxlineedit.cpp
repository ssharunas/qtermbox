#include "qtermboxlineedit.h"
#include "../qtermboxfocusmanager.h"
#include "../../core/qtermboxcore.h"
#include <QDebug>

QTermboxLineEdit::QTermboxLineEdit(QObject *parent) :
	QTermboxWidget(parent), _theme(0)
{
	QTermboxFocusManager::instance()->registerWidget(this);
	QTermboxFocusManager::instance()->focusNext();
}

void QTermboxLineEdit::setTheme(QTermboxWidgetStyle *theme)
{
	if(_theme != theme){
		_theme = theme;

		update(false);
	}
}

void QTermboxLineEdit::setText(QString text)
{
	_text = text;
	update();
}

void QTermboxLineEdit::paint()
{
//	const QTermboxWidgetStyle& theme = getActiveTheme();

//	QTermboxCore::putCell(geometry().x(), geometry().y(), geometry().width(), geometry().height(), text(),
//						  theme.foreground(), theme.background());

	qDebug() << "line: " << QPoint(geometry().x() + 1, geometry().y());

	QTermboxCore::moveCursor(QPoint(geometry().x() + 1, geometry().y()));
}

void QTermboxLineEdit::onKeyEvent(QTermboxKeyEvent event)
{
	qDebug() << text() + event.text();

	setText(text() + event.text());
	update();
}


