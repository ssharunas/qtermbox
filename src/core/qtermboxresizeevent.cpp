#include "qtermboxresizeevent.h"

QTermboxResizeEvent::QTermboxResizeEvent(const QSize & size) :
	QEvent(QEvent::Resize)
{
	_size = size;
}

/*!
	\brief Returns the new size.
*/
const QSize &QTermboxResizeEvent::size()
{
	return _size;
}
