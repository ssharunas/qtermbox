#include "qtermboxcore.h"
#include "../../lib/termbox.h"
#include <QString>
#include "private/qtermboxcoreprivate.h"
#include "private/qtermboxcellcontainerprivate.h"
#include "qtermboxeventpool.h"
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QDebug>

namespace QTermboxCore
{
/// \cond PRIVATE
QTermboxStyle clearFg(QTermbox::White);
QTermboxStyle clearBg(QTermbox::Black);


QFile log(QDir::homePath() + "/termbox-log");

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
QtMsgHandler defaultHandler(0);
void termboxMessageOutput(QtMsgType type, const char *msg)
#else
QtMessageHandler defaultHandler(0);
void termboxMessageOutput(QtMsgType type, const QMessageLogContext &, const QString &msg)
#endif
{
	if(type == QtFatalMsg)
	{
		QTermboxCorePrivate::setWasInitialized(false);
		shutdown();
	}

	if(!log.isOpen()){
		log.open(QIODevice::WriteOnly | QIODevice::Text);
	}

	if(log.isOpen()){
		QTextStream out(&log);
		switch(type){
			case QtDebugMsg:
				out << "DEBUG: ";
				break;
			case QtWarningMsg:
				out << "WARNING: ";
				break;

			case QtFatalMsg:
				out << "FATAL: ";
				break;
			case QtSystemMsg:
				out << "SYSTEM: ";
				break;
		}

		out << msg;
		out << "\n";
	}
}

/// \endcond

/*!
	\brief Returns the size of the internal back buffer (which is the same as terminal's window size in characters).
	*/
QSize screenSize(){
	Q_ASSERT_X(QTermboxCorePrivate::wasInitialized(), "screenSize", "Termbox was not initialized.");

	return QSize(tb_width(), tb_height());
}

/*!
	\brief Initializes termbox library.
	This function should be called before any other function. After successful initialization, library must	be
	finalized using 'Close' function.
	*/
void initialize(){
	int errorCode = tb_init();
	if(errorCode){
		switch(errorCode){
		case TB_EUNSUPPORTED_TERMINAL:
			qFatal("Unsupported terminal.");
			break;

		case TB_EFAILED_TO_OPEN_TTY:
			qFatal("TB_EFAILED_TO_OPEN_TTY");
			break;

		case TB_EPIPE_TRAP_ERROR:
			qFatal("TB_EPIPE_TRAP_ERROR");
			break;

		default:
			qFatal("Unknown initialization error.");
			break;
		}
	}
	else{
		#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
		defaultHandler = qInstallMsgHandler(termboxMessageOutput);
		#else
		defaultHandler = qInstallMessageHandler(termboxMessageOutput);
		#endif
		QTermboxCorePrivate::setWasInitialized(true);
	}
}

/*!
	\brief Checks if termbox library was initialized.
	Returns true if library is initialized an not shut down yet.
	*/
bool wasInitialized(){
	return QTermboxCorePrivate::wasInitialized();
}

/*!
	\brief Finalizes termbox library.
	Should be called after successful initialization when termbox's functionality isn't required anymore.
	*/
void shutdown(){
	if(QTermboxCorePrivate::wasInitialized())
	{
		QTermboxCorePrivate::setWasInitialized(false);

		if(!QTermboxEventPool::instance()->isStopped())
			QTermboxEventPool::instance()->stop();

		#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
		qInstallMsgHandler(defaultHandler);
		#else
		qInstallMessageHandler(termboxMessageOutput);
		#endif

		defaultHandler = 0;

		tb_shutdown();
	}
	else
	{
		qFatal("Tried to shut down uninitialized Termbox.");
	}
}

/*!
	\brief Clears the internal back buffer.
	Use present() to flush cleared buffer.
	*/
void clearScreen(){
	Q_ASSERT_X(QTermboxCorePrivate::wasInitialized(), "clearScreen", "Termbox was not initialized.");
	tb_clear();
}

/*!
	\brief Synchronizes the internal back buffer with the terminal.
	*/
void present(){
	Q_ASSERT_X(QTermboxCorePrivate::wasInitialized(), "present", "Termbox was not initialized.");
	tb_present();
}

/*!
	\brief Sets the position of the cursor.
	\see hideCursor()
	*/
void moveCursor(QPoint point){
	Q_ASSERT_X(QTermboxCorePrivate::wasInitialized(), "moveCursor", "Termbox was not initialized.");
	tb_set_cursor(point.x(), point.y());
}

/*!
	\brief Hides cursor.
	Same as moveCursor(QPoint(-1, -1))
	*/
void hideCursor(){
	Q_ASSERT_X(QTermboxCorePrivate::wasInitialized(), "hideCursor", "Termbox was not initialized.");
	tb_set_cursor(TB_HIDE_CURSOR, TB_HIDE_CURSOR);
}

/*!
	\brief Sets default style that is used to fill cells.
	Function clearScreen() should be called for effect to apply.
	\param fg - foreground style.
	\param bg - background style.
	*/
void setClearAttributes(QTermboxStyle fg, QTermboxStyle bg){
	Q_ASSERT_X(QTermboxCorePrivate::wasInitialized(), "setClearAttributes", "Termbox was not initialized.");

	clearFg = fg;
	clearBg = bg;
	tb_set_clear_attributes(fg.style(), bg.style());
}


/*!
	\brief Retirns default style for foreground, that is used to fill cells.
	\see setClearAttributes
	*/
QTermboxStyle clearForeground(){
	return clearFg;
}

/*!
	\brief Retirns default style for background, that is used to fill cells.
	\see setClearAttributes
	*/
QTermboxStyle clearBackground(){
	return clearBg;
}

/*!
	\brief Puts cell at specified position.

	\param x - position from left side of the screen.
	\param y - position from top of the screen.
	\param w - width of the cell list.
	\param cell - cell to print.
	*/
void putCell(unsigned int x, unsigned int y, QTermboxCell cell){
	Q_ASSERT_X(QTermboxCorePrivate::wasInitialized(), "putCell", "Termbox was not initialized.");

	struct tb_cell tcell = QTermboxCorePrivate::toTermboxCell(cell);
	tb_put_cell(x, y, &tcell);
}

/*!
	\brief Puts cell at specified position.

	\param x - position from left side of the screen.
	\param y - position from top of the screen.
	\param ch - char of cell.
	\param fg - foreground style of cell.
	\param bg - background style of cell.
	*/
void putCell(unsigned int x, unsigned int y, QChar ch, QTermboxStyle fg, QTermboxStyle bg){
	Q_ASSERT_X(QTermboxCorePrivate::wasInitialized(), "putCell", "Termbox was not initialized.");
	tb_change_cell(x, y, ch.unicode(), fg.style(), bg.style());
}

/*!
	\brief Puts cell at specified position.
	Uses clear foreground and background.

	\param x - position from left side of the screen.
	\param y - position from top of the screen.
	\param ch - char of cell.
	*/
void putCell(unsigned int x, unsigned int y, QChar ch){
	putCell(x, y, ch, clearFg, clearBg);
}

/*!
	\brief Prints list of cells at position.

	Width parameter is used to form block of cells. Example with parameters is shown below:
	<pre>
		x: 1, y: 1, width: 3, cells : [x, x, x, x, x, x]

		00000
		0xxx0
		0xxx0
		00000
	</pre>

	Cell list length should by dividable by width, othervise empty cells (width black background) will be used to
	will remaining space and  warning will be printed (only in debug version). If width is -1, cell list length is used
	instead.

	Overload with QTermboxCellContainer should be used for static elements for performance reasons.

	\param x - position from left side of the screen.
	\param y - position from top of the screen.
	\param w - width of the cell list.
	\param cells - list of cells to print.
	*/
void putCell(unsigned int x, unsigned int y, int w, QList<QTermboxCell> cells){
	Q_ASSERT_X(QTermboxCorePrivate::wasInitialized(), "putCell", "Termbox was not initialized.");

	if(w == -1)
		w = cells.length();

	tb_cell* tCells = QTermboxCorePrivate::toTermobCells(cells, w);
	long height = QTermboxCorePrivate::height(cells.count(), w);

	tb_blit(x, y, w, height, tCells);

	delete tCells;
	tCells = 0;
}


/*!
	\brief Prints list of cells at position.
	Works same as overload with QList<QTermboxCell>, but uses cached list of cells converted to internal type.

	\param x - position from left side of the screen.
	\param y - position from top of the screen.
	\param cells - container of cells to print.
	*/
void putCell(unsigned int x, unsigned int y, const QTermboxCellContainer & cells){
	Q_ASSERT_X(QTermboxCorePrivate::wasInitialized(), "putCell", "Termbox was not initialized.");

	const QTermboxCellContainerPrivate* cellsPrivate = dynamic_cast<const QTermboxCellContainerPrivate*>(&cells);
	if(!cellsPrivate)
		qFatal("Failed to cast QTermboxCellContainer to private datatype.");

	const tb_cell* tCells = cellsPrivate->serializedData();
	tb_blit(x, y, cellsPrivate->width(), cellsPrivate->height(), tCells);
}

/*!
	\brief Prints string with foreground and background styles.
	This function is overload of putCell(unsigned int x, unsigned int y, int w, QString str, QTermboxStyle fg, QTermboxStyle bg)
	with width = -1;
	*/
void putCell(unsigned int x, unsigned int y, QString str, QTermboxStyle fg, QTermboxStyle bg){
	Q_ASSERT_X(QTermboxCorePrivate::wasInitialized(), "putCell", "Termbox was not initialized.");

	putCell(x, y, -1, str, fg, bg);
}

/*!
	\brief Prints string with foreground and background styles.
	This function is overload of putCell(unsigned int x, unsigned int y, QString str, QTermboxStyle fg, QTermboxStyle bg)
	uses clear foreground and background.
	\see setClearAttributes
	*/
void putCell(unsigned int x, unsigned int y, QString str){
	putCell(x, y, str, clearFg, clearBg);
}

/*!
	This function is overload of putCell(unsigned int x, unsigned int y, int w, int h, QString str, QTermboxStyle fg, QTermboxStyle bg)
	with height = -1;
	*/
void putCell(unsigned int x, unsigned int y, int w, QString str, QTermboxStyle fg, QTermboxStyle bg){
	return putCell(x, y, w, -1, str, fg, bg);
}

/*!
	\brief Prints string with foreground and background styles.
	String is wrapped up to \a width. If width is -1, no wrapping is done.
	If string is shorter than width remaining space is filled with spaces.
	No more than \a height lines are printed. Height is ignored if it is less than 0.

	\param x - position from left side of the screen.
	\param y - position from top of the screen.
	\param w - width of string.
	\param h - height of string.
	\param str - string to print.
	\param fg - foreground style.
	\param bg - background style.
	*/
void putCell(unsigned int x, unsigned int y, int w, int h, QString str, QTermboxStyle fg, QTermboxStyle bg){
	Q_ASSERT_X(QTermboxCorePrivate::wasInitialized(), "putCell", "Termbox was not initialized.");

	int remainingWidth = str.length();

	if(w <= 0)
		w = str.length();

	int line = 0;

	//fill text
	while(remainingWidth > 0){

		for(int i = 0; i < qMin(remainingWidth, w); i++){
			tb_change_cell(x + i, y + line, str[line * w + i].unicode(), fg.style(), bg.style());
		}

		remainingWidth -= w;

		if(remainingWidth > 0)
			line++;

		if(h > 0 && line >= h)
			return;
	}

	//fill remaining unfinished empty line
	for(int i = x + w - 1; remainingWidth < 0; remainingWidth++, i--){
		tb_change_cell(i, y + line, ' ', fg.style(), bg.style());
	}

	//fill empty height
	if(h > 0){
		line++;
		while(line < h){

			for(unsigned int i = x + w - 1; i >= x; i--){
				tb_change_cell(i, y + line, ' ', fg.style(), bg.style());
			}

			line++;
		}
	}
}

/*!
	\brief Prints string with foreground and background styles.
	This function is overload of putCell(unsigned int x, unsigned int y, int w, QString str, QTermboxStyle fg, QTermboxStyle bg)
	uses clear foreground and background.
	\see setClearAttributes
	*/
void putCell(unsigned int x, unsigned int y, int w, QString str){
	putCell(x, y, w, str, clearFg, clearBg);
}

}
