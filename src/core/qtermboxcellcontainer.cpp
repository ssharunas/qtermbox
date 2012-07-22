#include "private/qtermboxcellcontainerprivate.h"

QTermboxCellContainer::QTermboxCellContainer(QObject *parent, long width, long height)
	: QObject(parent), _width(width), _height(height)
{
}

void QTermboxCellContainer::setHeight(long height)
{
	_height = height;
}

/*!
	\brief Method to create new instance of an object.

	Cells are divided into separate lines using parameter \a width, therefore \a cells list length should be
	divisible by \a width. If it is not divisible, empty cells are used to fill up remaining space and warning
	(only in debug version) is printed using qDebug().
	If \a width is -1 no spliting is done: \a width is assumed to be a length of \a cells list itself.

	\param cells - cells that will be used in this container.
	\param width - width of cells block.
	\param parent - parent object.
*/
QTermboxCellContainer *QTermboxCellContainer::create(QList<QTermboxCell> cells, long width, QObject *parent)
{
	if(width == -1)
		width = cells.count();

	return new QTermboxCellContainerPrivate(cells, width, parent);
}


/*!
	\brief Creates a copy of current instance.
	\param newParent - a parent for a copied collection.
*/
QTermboxCellContainer *QTermboxCellContainer::copy(QObject *newParent)
{
	QTermboxCellContainer * result = new QTermboxCellContainerPrivate(width(), newParent);
	result->_height = _height;
	return result;
}

/*!
	\brief Precalculated height of cell container block.
*/
long QTermboxCellContainer::height() const
{
	return _height;
}

QTermboxCellContainer::~QTermboxCellContainer() { }
