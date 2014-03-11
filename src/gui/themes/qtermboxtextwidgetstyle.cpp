#include "qtermboxtextwidgetstyle.h"

QTermboxTextWidgetStyle::QTermboxTextWidgetStyle(QObject *parent) :
	QTermboxWidgetStyle(parent), _text(QTermbox::White), _textFocus(QTermbox::White, QTermbox::Bold)
{
}

void QTermboxTextWidgetStyle::copy(QTermboxWidgetStyle *other)
{
	QTermboxTextWidgetStyle* myType = qobject_cast<QTermboxTextWidgetStyle *>(other);

	if(myType != 0){
		setText(myType->text());
		setTextFocus(myType->textFocus());
	}

	QTermboxWidgetStyle::copy(other);
}

QTermboxWidgetStyle *QTermboxTextWidgetStyle::getDefault()
{
	return new QTermboxTextWidgetStyle();
}

