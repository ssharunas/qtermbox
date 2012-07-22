#ifndef QTERMBOXCOREPRIVATE_H
#define QTERMBOXCOREPRIVATE_H

#include <QList>
#include "../qtermboxcell.h"
#include "../../../lib/termbox.h"

//utilities shared between shared parts of library.
namespace QTermboxCorePrivate
{
	bool wasInitialized();
	void setWasInitialized(bool value);

	tb_cell toTermboxCell(QTermboxCell cell);
	tb_cell* toTermobCells(QList<QTermboxCell> cells, long w = -1);
	tb_cell* toTermobCells(QTermboxCell cells[], long length, long w = -1);
	long height(long cellCount, long w);

	void setInputMode(QTermbox::QTermboxInputMode mode);
	QTermbox::QTermboxInputMode inputMode();
}

#endif // QTERMBOXCOREPRIVATE_H
