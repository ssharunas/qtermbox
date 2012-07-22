#include "qtermboxcellcontainerprivate.h"
#include"qtermboxcoreprivate.h"

QTermboxCellContainerPrivate::QTermboxCellContainerPrivate(long width, QObject *parent)
	: QTermboxCellContainer(parent, width, -1)
{
}

QTermboxCellContainerPrivate::QTermboxCellContainerPrivate(QList<QTermboxCell> cell, long width, QObject *parent)
	: QTermboxCellContainer(parent, width, QTermboxCorePrivate::height(cell.length(), width))
{
	tb_cell* data = QTermboxCorePrivate::toTermobCells(cell, width);
	_data = QSharedPointer<tb_cell>(data, QTermboxCellContainerPrivate::delete_data);
}

QTermboxCellContainerPrivate::~QTermboxCellContainerPrivate()
{
	_data.clear();
}

const tb_cell *QTermboxCellContainerPrivate::serializedData() const
{
	return _data.data();
}

void QTermboxCellContainerPrivate::delete_data(tb_cell data[])
{
	delete[] data;
}

QTermboxCellContainer *QTermboxCellContainerPrivate::copy(QObject *newParent)
{
	QTermboxCellContainerPrivate* result = dynamic_cast<QTermboxCellContainerPrivate*>(QTermboxCellContainer::copy(newParent));
	if(!result)
		qFatal("Failed to cast QTermboxCellContainer to private datatype.");

	result->_data = _data;
	return result;
}
