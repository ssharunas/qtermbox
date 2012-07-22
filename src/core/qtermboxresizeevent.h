#ifndef QTERMBOXRESIZEEVENT_H
#define QTERMBOXRESIZEEVENT_H

#include <QEvent>
#include <QSize>

/*!
	\brief The QTermboxResizeEvent class contains event parameters for resize events.
	Resize events are sent when terminal window is resized.

	\see QTermoboxEventPool::onResizeEvent
*/
class QTermboxResizeEvent : public QEvent
{
public:
	explicit QTermboxResizeEvent(const QSize & size);
	const QSize & size();

private:
	QSize _size;
};

#endif // QTERMBOXRESIZEEVENT_H
