#ifndef QTERMBOXCELLCONTAINERPRIVATE_H
#define QTERMBOXCELLCONTAINERPRIVATE_H

#include <QSharedPointer>
#include "../qtermboxcellcontainer.h"
#include "../../../lib/termbox.h"

class QTermboxCellContainerPrivate : public QTermboxCellContainer
{
	Q_OBJECT
public:
	explicit QTermboxCellContainerPrivate(long width = -1, QObject *parent = 0);
	explicit QTermboxCellContainerPrivate(QList<QTermboxCell> cell, long width = -1, QObject *parent = 0);
	~QTermboxCellContainerPrivate();

	virtual QTermboxCellContainer* copy(QObject *newParent = 0);

	const tb_cell * serializedData() const;

private:
	static void delete_data(tb_cell data[]);

private:
	QSharedPointer<tb_cell> _data;
};

#endif // QTERMBOXCELLCONTAINERPRIVATE_H
