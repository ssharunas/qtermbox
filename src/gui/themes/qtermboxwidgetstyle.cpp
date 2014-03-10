#include "qtermboxwidgetstyle.h"

QTermboxWidgetStyle::QTermboxWidgetStyle(QObject *parent) :
	QObject(parent), _background(QTermbox::Black), _backgroundFocus(QTermbox::Black)
{
}

void QTermboxWidgetStyle::searialize(QString file)
{

}

void QTermboxWidgetStyle::deserialize(QString file)
{

}

QTermboxWidgetStyle *QTermboxWidgetStyle::getDefault()
{
	//TODO: implement reading from settings/file/etc
	return new QTermboxWidgetStyle();
}
