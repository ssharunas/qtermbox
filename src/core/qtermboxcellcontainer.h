#ifndef QTERMBOXCELLCONTAINER_H
#define QTERMBOXCELLCONTAINER_H

#include <QObject>
#include "qtermboxcell.h"

/*!
	\brief Class to contain a collection of QTermboxCell`s.

	Class constructor is private, therefore method create() should be used to create new instance of an object.
	This class should be used instead of simple QList of QTermboxCell, because it caches internal Termbox data, therefore
	no convertion for Qt types to internal Termbox data is needed during each call to drawing functions.
*/
class QTermboxCellContainer : public QObject
{
	Q_OBJECT
public:
	~QTermboxCellContainer();

	static QTermboxCellContainer* create(QList<QTermboxCell> cells, long width = -1, QObject *parent = 0);
	virtual QTermboxCellContainer* copy(QObject *newParent = 0);

	/*!
	 \brief Width of cell container block.
	 If width is -1, length of cell container is used.
	*/
	inline long width() const { return _width; }
	virtual long height() const;

protected:
	explicit QTermboxCellContainer(QObject *parent, long width, long height);
	virtual void setHeight(long height);

private:
	long _width;
	long _height;
};

#endif // QTERMBOXCELLCONTAINER_H
