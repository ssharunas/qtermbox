#include "qtermboxstyle.h"
#include "../../lib/termbox.h"
#include <QtCore>

QTermboxStyle::QTermboxStyle(QTermbox::QTermboxColor color, QTermbox::QTermboxAttribute attribute)
{
	setStyle(color, attribute);
}

void QTermboxStyle::setStyle(QTermbox::QTermboxColor color, QTermbox::QTermboxAttribute attribute)
{
	_style = convertToTermboxColor(color) | convertToTermboxAttribute(attribute);
}

uint16_t QTermboxStyle::convertToTermboxColor(QTermbox::QTermboxColor color)
{
	switch(color)
	{
	case QTermbox::Black:
		return TB_BLACK;

	case QTermbox::Red:
		return TB_RED;

	case QTermbox::Green:
		return TB_GREEN;

	case QTermbox::Yellow:
		return TB_YELLOW;

	case QTermbox::Blue:
		return TB_BLUE;

	case QTermbox::Magenta:
		return TB_MAGENTA;

	case QTermbox::Cyan:
		return TB_CYAN;

	case QTermbox::White:
		return TB_WHITE;

	default:
		qFatal("Could not convert color %x to termbox color.", (int)color);
		break;
	}

	return 0;
}

uint16_t QTermboxStyle::convertToTermboxAttribute(QTermbox::QTermboxAttribute attribute)
{
	switch(attribute)
	{
	case QTermbox::NoAttribute:
		return 0;

	case QTermbox::Bold:
		return TB_BOLD;

	case QTermbox::Underline:
		return TB_UNDERLINE;

	default:
		qFatal("Could not convert attribute %x to termbox attribute.", (int)attribute);
		break;
	}

	return 0;
}
