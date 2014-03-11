#include "qtermboxlineedit.h"
#include "../qtermboxfocusmanager.h"
#include "../../core/qtermboxcore.h"
#include <QDebug>

QTB_REGISTER_STYLE(QTermboxLineEdit, QTermboxSelectableTextWidgetStyle)

QTermboxLineEdit::QTermboxLineEdit(QObject *parent) :
	QTermboxWidget(parent)
{
	QTermboxFocusManager::instance()->registerWidget(this);
	QTermboxFocusManager::instance()->focusNext();
}

QTermboxSelectableTextWidgetStyle &QTermboxLineEdit::theme()
{
	return getTheme<QTermboxSelectableTextWidgetStyle>();
}

void QTermboxLineEdit::setTheme(QTermboxSelectableTextWidgetStyle *theme)
{
	QTermboxWidget::setTheme(theme);
}

void QTermboxLineEdit::setText(QString text)
{
	_text = text;
	update();
}

void QTermboxLineEdit::paint()
{
	const QTermboxSelectableTextWidgetStyle& curTheme = theme();

	QTermboxCore::putCell(geometry().x(), geometry().y(), geometry().width(), geometry().height(), text(),
						  curTheme.text(), curTheme.background());

	qDebug() << "line: " << QPoint(geometry().x() + 1, geometry().y());

	QTermboxCore::moveCursor(QPoint(geometry().x() + 1, geometry().y()));
}

void QTermboxLineEdit::onKeyEvent(QTermboxKeyEvent event)
{
	qDebug() << text() + event.text();

	setText(text() + event.text());
	update();
}


