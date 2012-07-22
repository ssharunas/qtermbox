#ifndef QTERMBOXCELL_H
#define QTERMBOXCELL_H

#include <QChar>
#include <QList>
#include "qtermboxstyle.h"
#include "qtermbox.h"

/*!
\brief Class to represent one cell (char with background and decorations).
	Class contains three properties:
		- ch - character to be displayed
		- fg - foreground style.
		- bg - background style.

	Equals operators are overriden, therefore they work as expected.
*/
class QTermboxCell
{
public:

	QTermboxCell(QChar ch);
	QTermboxCell(QChar ch, const QTermboxStyle &fg, const QTermboxStyle &bg);
	QTermboxCell(QChar ch, const QTermbox::QTermboxColor &fg, const QTermbox::QTermboxColor &bg);

	inline QChar const ch() { return _ch; }	//!< Character to be displayed
	inline QTermboxStyle const fg() { return _fg; } //!< Foreground style.
	inline QTermboxStyle const bg() { return _bg; } //!< Background style.

	QList<QTermboxCell> multiply(unsigned int count);

private:
	QChar _ch;
	QTermboxStyle _fg;
	QTermboxStyle _bg;
};

inline bool operator==(QTermboxCell c1, QTermboxCell c2) { return c1.ch() == c2.ch() && c1.fg() == c2.fg() && c1.bg() == c2.bg(); }
inline bool operator!=(QTermboxCell c1, QTermboxCell c2) { return !(c1 == c2); }

#endif // QTERMBOXCELL_H
