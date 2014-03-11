#include "qtermboxwidgetstyle.h"
#include <QDebug>

QTermboxWidgetStyle::QTermboxWidgetStyle(QObject *parent) :
	QObject(parent), _background(QTermbox::Black), _backgroundFocus(QTermbox::Black)
{
}

void QTermboxWidgetStyle::searialize(QString file)
{
	Q_UNUSED(file);
}

void QTermboxWidgetStyle::deserialize(QString file)
{
	Q_UNUSED(file);
}

void QTermboxWidgetStyle::copy(QTermboxWidgetStyle *other)
{
	if(other != 0){
		setBackground(other->background());
		setBackgroundFocus(other->backgroundFocus());
	}
}

QTermboxWidgetStyle *QTermboxWidgetStyle::getDefault()
{
	//TODO: implement reading from settings/file/etc
	return new QTermboxWidgetStyle();
}
