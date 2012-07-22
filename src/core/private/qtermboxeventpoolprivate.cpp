#include "qtermboxeventpoolprivate.h"
#include "qtermboxcoreprivate.h"
#include "../../../lib/termbox.h"

#define STOP_CHECK_INTERVAL 2000

QTermboxEventPoolPrivate* QTermboxEventPoolPrivate::_instance = 0;

QTermboxEventPoolPrivate::QTermboxEventPoolPrivate() :
	QThread(0), _continueLoop(true), _isStopped(true)
{
}

QTermboxEventPoolPrivate *QTermboxEventPoolPrivate::instance()
{
	if(!_instance)
		_instance = new QTermboxEventPoolPrivate();

	return _instance;
}

void QTermboxEventPoolPrivate::run()
{
	if(!QTermboxCorePrivate::wasInitialized()){
		qFatal("QTermbox must be initialized before starting event pool.");
	}

	struct tb_event ev;
	_continueLoop = true;
	_isStopped = false;

	//check _continueLoop before and after event peek.
	while (_continueLoop)
	{
		int event = tb_peek_event(&ev, STOP_CHECK_INTERVAL);
		if(!_continueLoop)
			break;
		if(event){

			if(ev.type != event)
				qFatal("Internal termbox error: returned event type does not match event type.");

			switch (ev.type)
			{
			case TB_EVENT_KEY:
				raiseKeyEvent(ev.mod, ev.key, ev.ch);
				break;

			case TB_EVENT_RESIZE:
				raiseResizeEvent(ev.w, ev.h);
				break;

			default:
				break;
			}
		}
	}

	_isStopped = true;
	emit stopped();
}

bool QTermboxEventPoolPrivate::isStopped()
{
	return _isStopped;
}

bool QTermboxEventPoolPrivate::isActive()
{
	return !_isStopped && _continueLoop;
}

void QTermboxEventPoolPrivate::stop()
{
	if(!_continueLoop){
		if(_isStopped)
			qDebug("Event loop is already stopped.");
		else
			qDebug("Event loop stopping procedure is already in progress.");
	}

	_continueLoop = false;
}

void QTermboxEventPoolPrivate::raiseResizeEvent(int32_t w, int32_t h)
{
	emit onResizeEvent(QTermboxResizeEvent(QSize(w, h)));
}

void QTermboxEventPoolPrivate::raiseKeyEvent(uint8_t mod, uint16_t key, uint32_t ch)
{
	Qt::KeyboardModifiers modifyer = Qt::NoModifier;
	if(mod & TB_MOD_ALT)
		modifyer |= Qt::AltModifier;

	if(ch != 0)
	{
		emit onKeyEvent(QTermboxKeyEvent(Qt::Key_unknown, modifyer, QChar(ch), QChar(ch), key));
	}
	else
	{
		QList<QTermboxEventPoolPrivate::KeyInfo> keys = mapQtKey(key);

		if(keys.length() > 0)
		{
			QString text = "";
			if(keys[0].ch)
				text = QChar(keys[0].ch);

			emit onKeyEvent(QTermboxKeyEvent(keys[0].key, modifyer | keys[0].modifyer, text, QChar(ch), key));

			for(int i = 1; i < keys.length(); i++)
			{
				if(keys[i].ch)
					text = QChar(keys[i].ch);
				else
					text = "";

				emit onKeyEventAlternative(QTermboxKeyEvent(
					keys[i].key, modifyer | keys[i].modifyer, text, QChar(ch), key));
			}
		}
		else
		{
			emit onKeyEvent(QTermboxKeyEvent(Qt::Key_unknown, modifyer, QChar(ch), QChar(ch), key));
		}
	}
}

QList<QTermboxEventPoolPrivate::KeyInfo> QTermboxEventPoolPrivate::mapQtKey(uint16_t key)
{
	QList<KeyInfo> result;

	switch(key){
	case TB_KEY_F1:
		result.append(KeyInfo(Qt::Key_F1));
		break;

	case TB_KEY_F2:
		result.append(KeyInfo(Qt::Key_F2));
		break;

	case TB_KEY_F3:
		result.append(KeyInfo(Qt::Key_F3));
		break;

	case TB_KEY_F4:
		result.append(KeyInfo(Qt::Key_F4));
		break;

	case TB_KEY_F5:
		result.append(KeyInfo(Qt::Key_F6));
		break;

	case TB_KEY_F6:
		result.append(KeyInfo(Qt::Key_F6));
		break;

	case TB_KEY_F7:
		result.append(KeyInfo(Qt::Key_F7));
		break;

	case TB_KEY_F8:
		result.append(KeyInfo(Qt::Key_F8));
		break;

	case TB_KEY_F9:
		result.append(KeyInfo(Qt::Key_F9));
		break;

	case TB_KEY_F10:
		result.append(KeyInfo(Qt::Key_F10));
		break;

	case TB_KEY_F11:
		result.append(KeyInfo(Qt::Key_F11));
		break;

	case TB_KEY_F12:
		result.append(KeyInfo(Qt::Key_F12));
		break;

	case TB_KEY_INSERT:
		result.append(KeyInfo(Qt::Key_Insert));
		break;

	case TB_KEY_DELETE:
		result.append(KeyInfo(Qt::Key_Delete, key, 0));
		break;

	case TB_KEY_HOME:
		result.append(KeyInfo(Qt::Key_Home));
		break;

	case TB_KEY_END:
		result.append(KeyInfo(Qt::Key_End));
		break;

	case TB_KEY_PGUP:
		result.append(KeyInfo(Qt::Key_PageUp));
		break;

	case TB_KEY_PGDN:
		result.append(KeyInfo(Qt::Key_PageDown));
		break;

	case TB_KEY_ARROW_UP:
		result.append(KeyInfo(Qt::Key_Up));
		break;

	case TB_KEY_ARROW_DOWN:
		result.append(KeyInfo(Qt::Key_Down));
		break;

	case TB_KEY_ARROW_LEFT:
		result.append(KeyInfo(Qt::Key_Left));
		break;

	case TB_KEY_ARROW_RIGHT:
		result.append(KeyInfo(Qt::Key_Right));
		break;

	case TB_KEY_CTRL_TILDE:
		// case TB_KEY_CTRL_2: /* clash with 'CTRL_TILDE' */
		result.append(KeyInfo(Qt::Key_AsciiTilde, '`', Qt::ControlModifier));
		result.append(KeyInfo(Qt::Key_2, '2', Qt::ControlModifier));
		break;

	case TB_KEY_CTRL_A:
		result.append(KeyInfo(Qt::Key_A, 'a', Qt::ControlModifier));
		break;

	case TB_KEY_CTRL_B:
		result.append(KeyInfo(Qt::Key_B, 'b', Qt::ControlModifier));
		break;

	case TB_KEY_CTRL_C:
		result.append(KeyInfo(Qt::Key_C, 'c', Qt::ControlModifier));
		break;

	case TB_KEY_CTRL_D:
		result.append(KeyInfo(Qt::Key_D, 'd', Qt::ControlModifier));
		break;

	case TB_KEY_CTRL_E:
		result.append(KeyInfo(Qt::Key_E, 'e', Qt::ControlModifier));
		break;

	case TB_KEY_CTRL_F:
		result.append(KeyInfo(Qt::Key_F, 'f', Qt::ControlModifier));
		break;

	case TB_KEY_CTRL_G:
		result.append(KeyInfo(Qt::Key_G, 'g', Qt::ControlModifier));
		break;

	case TB_KEY_BACKSPACE:
		//case TB_KEY_CTRL_H /* clash with 'CTRL_BACKSPACE' */:
		result.append(KeyInfo(Qt::Key_Backspace, 8, Qt::ControlModifier));
		result.append(KeyInfo(Qt::Key_H, 'h', Qt::ControlModifier));
		break;

	case TB_KEY_TAB:
		//case TB_KEY_CTRL_I /* clash with 'TAB' */:
		result.append(KeyInfo(Qt::Key_Tab, 9, 0));
		result.append(KeyInfo(Qt::Key_I, 'i', Qt::ControlModifier));
		break;

	case TB_KEY_CTRL_J:
		result.append(KeyInfo(Qt::Key_J, 'j', Qt::ControlModifier));
		break;

	case TB_KEY_CTRL_K:
		result.append(KeyInfo(Qt::Key_K, 'k', Qt::ControlModifier));
		break;

	case TB_KEY_CTRL_L:
		result.append(KeyInfo(Qt::Key_L, 'l', Qt::ControlModifier));
		break;

	case TB_KEY_ENTER:
		//case TB_KEY_CTRL_M /* clash with 'ENTER' */:
		result.append(KeyInfo(Qt::Key_Return, 13, 0));
		result.append(KeyInfo(Qt::Key_M, 'm', Qt::ControlModifier));
		break;

	case TB_KEY_CTRL_N:
		result.append(KeyInfo(Qt::Key_N, 'n', Qt::ControlModifier));
		break;

	case TB_KEY_CTRL_O:
		result.append(KeyInfo(Qt::Key_O, 'o', Qt::ControlModifier));
		break;

	case TB_KEY_CTRL_P:
		result.append(KeyInfo(Qt::Key_P, 'p', Qt::ControlModifier));
		break;

	case TB_KEY_CTRL_Q:
		result.append(KeyInfo(Qt::Key_Q, 'q', Qt::ControlModifier));
		break;

	case TB_KEY_CTRL_R:
		result.append(KeyInfo(Qt::Key_R, 'r', Qt::ControlModifier));
		break;

	case TB_KEY_CTRL_S:
		result.append(KeyInfo(Qt::Key_S, 's', Qt::ControlModifier));
		break;

	case TB_KEY_CTRL_T:
		result.append(KeyInfo(Qt::Key_T, 't', Qt::ControlModifier));
		break;

	case TB_KEY_CTRL_U:
		result.append(KeyInfo(Qt::Key_U, 'u', Qt::ControlModifier));
		break;

	case TB_KEY_CTRL_V:
		result.append(KeyInfo(Qt::Key_V, 'v', Qt::ControlModifier));
		break;

	case TB_KEY_CTRL_W:
		result.append(KeyInfo(Qt::Key_W, 'w', Qt::ControlModifier));
		break;

	case TB_KEY_CTRL_X:
		result.append(KeyInfo(Qt::Key_X, 'x', Qt::ControlModifier));
		break;

	case TB_KEY_CTRL_Y:
		result.append(KeyInfo(Qt::Key_Y, 'y', Qt::ControlModifier));
		break;

	case TB_KEY_CTRL_Z:
		result.append(KeyInfo(Qt::Key_Z, 'z', Qt::ControlModifier));
		break;

	case TB_KEY_ESC:
		//case TB_KEY_CTRL_LSQ_BRACKET /* clash with 'ESC' */:
		//case TB_KEY_CTRL_3 /* clash with 'ESC' */:
		result.append(KeyInfo(Qt::Key_Escape, 27, 0));
		result.append(KeyInfo(Qt::Key_BraceLeft, '[', Qt::ControlModifier));
		result.append(KeyInfo(Qt::Key_3, '3', Qt::ControlModifier));
		break;

	case TB_KEY_CTRL_4:
		//case TB_KEY_CTRL_BACKSLASH /* clash with 'CTRL_4' */:
		result.append(KeyInfo(Qt::Key_Backslash, '\\', Qt::ControlModifier));
		result.append(KeyInfo(Qt::Key_4, '4', Qt::ControlModifier));
		break;

	case TB_KEY_CTRL_5:
		//case TB_KEY_CTRL_RSQ_BRACKET /* clash with 'CTRL_5' */:
		result.append(KeyInfo(Qt::Key_BraceRight, ']', Qt::ControlModifier));
		result.append(KeyInfo(Qt::Key_5, '5', Qt::ControlModifier));
		break;

	case TB_KEY_CTRL_6:
		result.append(KeyInfo(Qt::Key_6, '6', Qt::ControlModifier));
		break;

	case TB_KEY_CTRL_7:
		//case TB_KEY_CTRL_SLASH /* clash with 'CTRL_7' */:
		//case TB_KEY_CTRL_UNDERSCORE /* clash with 'CTRL_7' */:
		result.append(KeyInfo(Qt::Key_7, '7', Qt::ControlModifier));
		result.append(KeyInfo(Qt::Key_Slash, '/', Qt::ControlModifier));
		result.append(KeyInfo(Qt::Key_Underscore, '_', Qt::ControlModifier));
		break;

	case TB_KEY_SPACE:
		result.append(KeyInfo(Qt::Key_Space, ' ', 0));
		break;

	case TB_KEY_BACKSPACE2:
		//case TB_KEY_CTRL_8 /* clash with 'BACKSPACE2' */:
		result.append(KeyInfo(Qt::Key_Backspace, 8, 0));
		result.append(KeyInfo(Qt::Key_8, '8', Qt::ControlModifier));
		break;
	}

	return result;
}
