#include "qtermboxcoreprivate.h"
#include <QtCore/qmath.h>

namespace QTermboxCorePrivate
{
	bool _wasInitialized = false;
	struct tb_cell EMPTY_CELL = {' ', 0, 0};

	long getTotalCount(long cellCount, long w){
		if(w != -1 && cellCount % w != 0){
			qDebug("Inconsisten count of cells detected. Tryed to divide %ld cells into %ld rows. Filling missing cells with empty data",
				cellCount, w);

			cellCount = height(cellCount, w) * w;
		}

		return cellCount;
	}

	tb_cell toTermboxCell(QTermboxCell cell){
		struct tb_cell tCell;
		tCell.ch = cell.ch().unicode();
		tCell.bg = cell.bg().style();
		tCell.fg = cell.fg().style();

		return tCell;
	}

	template <class T> tb_cell* toTermobCellsTmpl(T cells, long length, long width)
	{
		int totalCount = getTotalCount(length, width);

		tb_cell* result = new tb_cell[totalCount];
		int i = 0;
		for(; i < length; ++i)
		{
			result[i] = toTermboxCell(cells[i]);
		}

		for(; i < totalCount; ++i){
			result[i] = EMPTY_CELL;
		}

		return result;
	}

	tb_cell* toTermobCells(QList<QTermboxCell> cells, long w){
		return toTermobCellsTmpl<QList<QTermboxCell> >(cells, cells.count(), w);
	}

	tb_cell* toTermobCells(QTermboxCell cells[], long length, long w){
		return toTermobCellsTmpl<QTermboxCell[]>(cells, length, w);
	}

	long height(long cellCount, long w){
		return qCeil((double)cellCount / w);
	}

	bool wasInitialized(){
		return _wasInitialized;
	}

	void setWasInitialized(bool value){
		_wasInitialized = value;
	}

	void setInputMode(QTermbox::QTermboxInputMode mode){
		Q_ASSERT_X(wasInitialized(), "setInputMode", "Termbox was not initialized.");

		switch(mode)
		{
			case QTermbox::AltInputMode:
				tb_select_input_mode(TB_INPUT_ALT);
				break;

			case QTermbox::EscInputMode:
				tb_select_input_mode(TB_INPUT_ESC);
				break;

			default:
				qFatal("Could not convert input mode %d to termbox input mode.", (int)mode);
		}
	}

	QTermbox::QTermboxInputMode inputMode(){
		Q_ASSERT_X(wasInitialized(), "inputMode", "Termbox was not initialized.");

		int mode = tb_select_input_mode(0);
		switch(mode)
		{
			case TB_INPUT_ALT:
				return QTermbox::AltInputMode;

			case TB_INPUT_ESC:
				return QTermbox::EscInputMode;

			default:
				qFatal("Could not convert termbox input mode %d to QTermbox::QTermboxInputMode.", mode);
		}

		return QTermbox::EscInputMode;
	}

}
