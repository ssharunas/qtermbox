#include "qtermboxlabel.h"
#include "../themes/qtermboxstylefactory.h"
#include "../../core/qtermboxcore.h"

QTB_REGISTER_STYLE(QTermboxLabel, QTermboxWidgetStyle)

QTermboxLabel::QTermboxLabel(QObject *parent) :
	QTermboxWidget(parent), _theme(0)
{
}

void QTermboxLabel::setTheme(QTermboxWidgetStyle *theme)
{
	if(_theme != theme){
		_theme = theme;

		update(false);
	}
}

void QTermboxLabel::setText(QString text)
{
	_text = text;
	update();
}

void QTermboxLabel::paint()
{


	if(geometry().height() > 0 && geometry().width() > 0){
//		QTermboxCore::putCell(geometry().x(), geometry().y(), geometry().width(), geometry().height(), text(),
//							  theme.foreground(), theme.background());
	}
}
