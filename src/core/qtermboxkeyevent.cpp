#include "qtermboxkeyevent.h"
#include <QDebug>

QTermboxKeyEvent::QTermboxKeyEvent(int key, Qt::KeyboardModifiers modifyers, const QString text, QChar originalChar, uint16_t originalKey) :
	QEvent(QEvent::KeyPress)
{
	_key = key;
	_modifyers = modifyers;
	_text = text;

	_originalChar = originalChar;
	_originalKey = originalKey;
	setAccepted(false);
}

