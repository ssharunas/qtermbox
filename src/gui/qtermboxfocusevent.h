#ifndef QTERMBOXFOCUSEVENT_H
#define QTERMBOXFOCUSEVENT_H

#include <QEvent>

class QTermboxFocusEvent : public QEvent
{
public:
	QTermboxFocusEvent(Type type);

	inline bool gotFocus() { return type() == QEvent::FocusIn; }
	inline bool lostFocus() { return type() == QEvent::FocusOut; }
};

#endif // QTERMBOXFOCUSEVENT_H
