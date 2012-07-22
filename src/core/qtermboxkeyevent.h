#ifndef QTERMBOXKEYEVENT_H
#define QTERMBOXKEYEVENT_H

#include "stdint.h"
#include <QEvent>
#include <QString>

/*!
	\brief The QTermboxKeyEvent class describes a key event.
	Note that key events in terminal are not always same as in regular GUI applications. Due to key clashing it is not
	always possiable to determine which key exacly was pressed. To resolve this issue two signals are used:
		- one reports key press only once (one key event is emited on one key press);
		- other is emited for each possible key combination (multiple events for one key press).

	Note also that Shift modifyer is not recognized. For Alt modifyer to work alt input mode must be activated (see
	QTermoboxEventPool::setInputMode for more detail) in which case Esc button is lost.
	\see QTermoboxEventPool::onKeyEvent
	\see QTermoboxEventPool::onKeyEventAlternative
	*/
class QTermboxKeyEvent : public QEvent
{
public:
	explicit QTermboxKeyEvent(int key, Qt::KeyboardModifiers modifyers, const QString text = QString(), QChar originalChar = QChar(), uint16_t originalKey = 0);

	inline int key() { return _key; } //!< Qt::Key eqvivalent of reported key.
	inline Qt::KeyboardModifiers modifiers() { return _modifyers; } //!< Modifyers of pressed key.
	inline QString text() { return _text; } //!< Text representation of pressed key (usually one QChar).

	inline QChar originalChar() { return _originalChar; }   //!< Original char reported Termbox event loop.
	inline uint16_t originalKey() { return _originalKey; }  //!< Original key reported by Termbox event loop.

private:
	QChar _originalChar;
	uint16_t _originalKey;

	int _key;
	Qt::KeyboardModifiers _modifyers;
	QString _text;

};

#endif // QTERMBOXKEYEVENT_H
