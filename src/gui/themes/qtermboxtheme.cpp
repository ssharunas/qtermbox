#include "qtermboxtheme.h"

QTermboxTheme::QTermboxTheme(QObject *parent) :
	QObject(parent), _foreground(QTermbox::White), _background(QTermbox::Black)
{
}
