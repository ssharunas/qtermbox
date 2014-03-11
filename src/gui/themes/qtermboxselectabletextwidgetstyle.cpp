#include "qtermboxselectabletextwidgetstyle.h"

QTermboxSelectableTextWidgetStyle::QTermboxSelectableTextWidgetStyle(QObject *parent) :
	QTermboxTextWidgetStyle(parent), _highlightForeground(QTermbox::Black, QTermbox::Bold), _highlightBackground(QTermbox::Cyan)
{
}

void QTermboxSelectableTextWidgetStyle::copy(QTermboxWidgetStyle *other)
{
	QTermboxSelectableTextWidgetStyle* myType = qobject_cast<QTermboxSelectableTextWidgetStyle *>(other);

	if(myType != 0){
		setHighlightBackground(myType->highlightBackground());
		setHighlightForeground(myType->highlightForeground());
	}

	QTermboxTextWidgetStyle::copy(other);
}

QTermboxWidgetStyle *QTermboxSelectableTextWidgetStyle::getDefault()
{
	return new QTermboxSelectableTextWidgetStyle(0);
}
