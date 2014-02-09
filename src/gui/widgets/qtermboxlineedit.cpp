#include "qtermboxlineedit.h"
#include "../qtermboxfocusmanager.h"
#include "../../core/qtermboxcore.h"
#include <QDebug>

static QTermboxTheme* defaultTermboxLineEditTheme = 0;

QTermboxLineEdit::QTermboxLineEdit(QObject *parent) :
	QTermboxWidget(parent), _theme(0)
{
	QTermboxFocusManager::instance()->registerWidget(this);
	QTermboxFocusManager::instance()->focusNext();

	qDebug() << QTermboxFocusManager::instance()->isFocused(this);
}

QTermboxTheme *QTermboxLineEdit::defaultTheme()
{
	if(!defaultTermboxLineEditTheme){
		defaultTermboxLineEditTheme = new QTermboxTheme(0);
		setDefaultThemeValues(defaultTermboxLineEditTheme);
	}

	return defaultTermboxLineEditTheme;
}

void QTermboxLineEdit::setDefaultTheme(QTermboxTheme *theme)
{
	defaultTermboxLineEditTheme = theme;
	update(false);
}

void QTermboxLineEdit::setTheme(QTermboxTheme *theme)
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
	const QTermboxTheme& theme = getActiveTheme();

	QTermboxCore::putCell(geometry().x(), geometry().y(), geometry().width(), geometry().height(), text(),
						  theme.foreground(), theme.background());

	qDebug() << QPoint(geometry().x() + 1, geometry().y());

	QTermboxCore::moveCursor(QPoint(geometry().x() + 1, geometry().y()));
}

void QTermboxLineEdit::onKeyEvent(QTermboxKeyEvent event)
{


	setText(event.text());
	update();
}


