#include "qtermboxwidget.h"
#include "../qtermboxscreen.h"
#include "../qtermboxfocusmanager.h"
#include <QDebug>

QTermboxWidget::QTermboxWidget(QObject *parent) :
	QObject(parent), _style(0)
{
	//QTermboxFocusManager::instance()->registerWidget(this);
}

void QTermboxWidget::setGeometry(QRect geometry)
{
	_geometry = geometry;
	update();
}

bool QTermboxWidget::hasFocus()
{
	return QTermboxFocusManager::instance()->isFocused(this);
}

QTermboxWidgetStyle &QTermboxWidget::theme()
{
	return getTheme<QTermboxWidgetStyle>();
}

void QTermboxWidget::setTheme(QTermboxWidgetStyle *theme)
{
	_style = theme;
	_style->setParent(this);
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
