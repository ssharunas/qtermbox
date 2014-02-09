#ifndef QTERMBOXCORE_H
#define QTERMBOXCORE_H

#include <QChar>
#include <QList>
#include <QSize>
#include <QPoint>

#include "qtermboxstyle.h"
#include "qtermboxcell.h"
#include "qtermboxcellcontainer.h"

/*!
	\brief namespace for core Termbox functions.
	*/
namespace QTermboxCore
{
	QSize screenSize();

	void initialize();
	void shutdown();
	bool wasInitialized();

	void clearScreen();
	void present();

	void moveCursor(QPoint point);
	void hideCursor();

	void setClearAttributes(QTermboxStyle fg, QTermboxStyle bg);
	QTermboxStyle clearForeground();
	QTermboxStyle clearBackground();

	void putCell(unsigned int x, unsigned int y, QTermboxCell cell);
	void putCell(unsigned int x, unsigned int y, QChar ch);
	void putCell(unsigned int x, unsigned int y, QChar ch, QTermboxStyle fg, QTermboxStyle bg);
	void putCell(unsigned int x, unsigned int y, int w, QList<QTermboxCell> cells);
	void putCell(unsigned int x, unsigned int y, const QTermboxCellContainer & cells);
	void putCell(unsigned int x, unsigned int y, QString str);
	void putCell(unsigned int x, unsigned int y, QString str, QTermboxStyle fg, QTermboxStyle bg);
	void putCell(unsigned int x, unsigned int y, int w, QString str);
	void putCell(unsigned int x, unsigned int y, int w, QString str, QTermboxStyle fg, QTermboxStyle bg);
	void putCell(unsigned int x, unsigned int y, int w, int h, QString str, QTermboxStyle fg, QTermboxStyle bg);
}

#endif // QTERMBOXCORE_H
