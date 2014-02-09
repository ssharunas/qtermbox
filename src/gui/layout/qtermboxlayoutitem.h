#ifndef QTERMBOXLAYOUTITEM_H
#define QTERMBOXLAYOUTITEM_H

#include <QSize>

class QTermboxLayoutItem
{
public:
	QTermboxLayoutItem();
	virtual ~QTermboxLayoutItem() { }

	virtual Qt::Orientations expandingDirections() = 0;
	virtual QSize minimumSize() = 0;
	virtual QSize maximumSize() = 0;
	virtual QSize sizeHint() = 0;

};

#endif // QTERMBOXLAYOUTITEM_H
