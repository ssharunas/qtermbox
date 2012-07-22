#include "qtermboxeventpool.h"
#include "private/qtermboxeventpoolprivate.h"
#include "private/qtermboxcoreprivate.h"

/*!
	\class QTermboxEventPool
	To acess class members use method instance().
	Typical use of this class is connecting required signalls to your code and calling signal start once your application
	is ready to accept user events. It is not necessary to call stop(), since it is automatically is called during
	QTermboxCore::shutdown().

	For more information about key clashing and input modes please see NOTES in original termbox library
	(https://github.com/nsf/termbox/blob/master/NOTES)
	*/

QTermboxEventPool* QTermboxEventPool::_instance = 0;

QTermboxEventPool::QTermboxEventPool()
	: QObject(0)
{
	connect(QTermboxEventPoolPrivate::instance(), SIGNAL(stopped()), this, SIGNAL(stopped()), Qt::BlockingQueuedConnection);
	connect(QTermboxEventPoolPrivate::instance(), SIGNAL(onKeyEvent(QTermboxKeyEvent)), this, SIGNAL(onKeyEvent(QTermboxKeyEvent)), Qt::BlockingQueuedConnection);
	connect(QTermboxEventPoolPrivate::instance(), SIGNAL(onKeyEventAlternative(QTermboxKeyEvent)), this, SIGNAL(onKeyEventAlternative(QTermboxKeyEvent)), Qt::BlockingQueuedConnection);
	connect(QTermboxEventPoolPrivate::instance(), SIGNAL(onResizeEvent(QTermboxResizeEvent)), this, SIGNAL(onResizeEvent(QTermboxResizeEvent)), Qt::BlockingQueuedConnection);
}

/*!
	\brief Returns instance of event loop.
	*/
QTermboxEventPool *QTermboxEventPool::instance()
{
	if(!_instance)
		_instance = new QTermboxEventPool();

	return _instance;
}

/*!
	\brief Sets input mode for Termbox.

	Termbox has two input modes:

	1. Esc input mode. When ESC sequence is in the buffer and it doesn't match any known sequence.

	2. Alt input mode. When ESC sequence is in the buffer and it doesn't match any known sequence. ESC enables
	ModAlt modifier for the next keyboard event.
	*/
void QTermboxEventPool::setInputMode(QTermbox::QTermboxInputMode mode)
{
	QTermboxCorePrivate::setInputMode(mode);
}

/*!
	\brief Returns input mode.
	\see setInputMode
	*/
QTermbox::QTermboxInputMode QTermboxEventPool::inputMode()
{
	return QTermboxCorePrivate::inputMode();
}

/*!
	\brief Returns true if event loop was never started or is already fully stopped.
	*/
bool QTermboxEventPool::isStopped()
{
	return QTermboxEventPoolPrivate::instance()->isStopped();
}

/*!
	\brief Returns true if event loop is running or stopping is in progress.
	If event loop was never started or if it is already fully stopped, false is returned.
	*/
bool QTermboxEventPool::isActive()
{
	return QTermboxEventPoolPrivate::instance()->isActive();
}

/*!
	\brief Stops event pool.
	Stop is not forsed, therefore it may take up to 2000 miliseconds (defined as STOP_CHECK_INTERVAL in
	qtermboxeventpoolprivate.cpp) to actualy stop the loop. However user input after stop request won't be
	sent (no signals will be emited.) and therefore input will be lost. To check is loop is still active use
	isActive() function.
	\see isActive isStopped
	*/
void QTermboxEventPool::stop()
{
	QTermboxEventPoolPrivate::instance()->stop();
}

/*!
	\brief Starts event pool.
	*/
void QTermboxEventPool::start()
{
	QTermboxEventPoolPrivate::instance()->start();
}
