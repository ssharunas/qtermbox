#include "qtermboxcell.h"
#include "qtermboxcore.h"

/*!
	Constructs cell with given char. Current clear Background and foreground.
	\see clearForeground clearBackground
*/
QTermboxCell::QTermboxCell(QChar ch)
	: _ch(ch), _fg(QTermbox::White), _bg(QTermbox::Black)
{
	_fg = QTermboxCore::clearForeground();
	_bg = QTermboxCore::clearBackground();
}

/*!
	Constructs cell with given char, background and foreground by given QTermboxStyle.
*/
QTermboxCell::QTermboxCell(QChar ch, const QTermboxStyle &fg, const QTermboxStyle &bg)
	: _ch(ch), _fg(fg), _bg(bg)
{
}

/*!
	Constructs cell with given char, background and foreground by given QTermboxColor.
	Use constructor variant with QTermboxStyle to supply additional style attributes for cell.
*/
QTermboxCell::QTermboxCell(QChar ch, const QTermbox::QTermboxColor &fg, const QTermbox::QTermboxColor &bg)
	: _ch(ch), _fg(fg), _bg(bg)
{
}

/*!
	\brief Creates a list of cells using current cell as template.
	\param count - amount of new items to create.
*/
QList<QTermboxCell> QTermboxCell::multiply(unsigned int count)
{
	QList<QTermboxCell> result;
	result.reserve(count);

	for(unsigned int i = 0; i < count; i++)
	{
		result.append(*this);
	}

	return result;
}
