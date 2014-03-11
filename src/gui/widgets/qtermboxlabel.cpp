#include "qtermboxlabel.h"
#include "../themes/qtermboxstylefactory.h"
#include "../../core/qtermboxcore.h"
#include <QDebug>

QTB_REGISTER_STYLE(QTermboxLabel, QTermboxTextWidgetStyle)

QTermboxLabel::QTermboxLabel(QObject *parent) :
	QTermboxWidget(parent)
{
}

QTermboxTextWidgetStyle &QTermboxLabel::theme()
{
	return getTheme<QTermboxTextWidgetStyle>();
}

void QTermboxLabel::setTheme(QTermboxTextWidgetStyle *theme)
{
	QTermboxWidget::setTheme(theme);
}

void QTermboxLabel::setText(QString text)
{
	_text = text;
	update();
}

void QTermboxLabel::paint()
{
	if(geometry().height() > 0 && geometry().width() > 0)
	{
		QTermboxTextWidgetStyle* currTheme = &theme();
		qDebug() << currTheme;

		QTermboxCore::putCell(geometry().x(), geometry().y(), geometry().width(), geometry().height(), text(),
							  currTheme->text(), currTheme->background());
	}
}
