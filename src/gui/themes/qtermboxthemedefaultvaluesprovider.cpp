#include "qtermboxthemedefaultvaluesprovider.h"

QTermboxThemeDefaultValuesProvider::QTermboxThemeDefaultValuesProvider(QObject *parent) :
	QObject(parent),
	_text(QTermbox::White),
	_highlightedText(QTermbox::Red),
	_windowBackground(QTermbox::Black),
	_inputControlBackground(QTermbox::White)
{
}
