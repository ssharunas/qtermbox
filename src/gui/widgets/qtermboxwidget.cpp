#include "qtermboxwidget.h"
#include "../qtermboxscreen.h"
#include "../qtermboxfocusmanager.h"

QTermboxWidget::QTermboxWidget(QObject *parent) :
	QObject(parent)
{
	//QTermboxFocusManager::instance()->registerWidget(this);
}

void QTermboxWidget::setGeometry(QRect geometry)
{
	_geometry = geometry;
	update();
}

void QTermboxWidget::setDefaultThemeValues(QTermboxTheme *theme)
{
	Q_UNUSED(theme);
}

const QTermboxTheme &QTermboxWidget::getActiveTheme()
{
	QTermboxTheme* result = theme();

	if(!result)
		result = defaultTheme();

	if(!result)
		qFatal("Failed to get theme and default theme. Default theme must never be null.");

	return *result;
}

bool QTermboxWidget::hasFocus()
{
	return QTermboxFocusManager::instance()->isFocused(this);
}

void QTermboxWidget::onKeyEvent(QTermboxKeyEvent event)
{
	if(event.key() == Qt::Key_Tab){
		QTermboxFocusManager::instance()->focusNext();
		event.accept();
	}
}

void QTermboxWidget::onKeyEventAlternative(QTermboxKeyEvent event)
{
	Q_UNUSED(event)
	//Do nothing
}

void QTermboxWidget::onResizeEvent(QTermboxResizeEvent event)
{
	Q_UNUSED(event)
	//Do nothing. QTermboxScreen handles repaint on resize.
}

void QTermboxWidget::update(bool reflow)
{
	//TODO: Maybe update only child itself? needs additional parameter then..

	if(reflow)
		QTermboxScreen::instance()->reflow();

	QTermboxScreen::instance()->update();
}
