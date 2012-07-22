#ifndef EVENTPOOL_H
#define EVENTPOOL_H

#include <QObject>
#include "qtermbox.h"
#include "qtermboxkeyevent.h"
#include "qtermboxresizeevent.h"

/*!
	\brief Termbox event loop class.
*/
class QTermboxEventPool : public QObject
{
	Q_OBJECT
public:
	static QTermboxEventPool* instance();

	void setInputMode(QTermbox::QTermboxInputMode mode);
	QTermbox::QTermboxInputMode inputMode();

	bool isStopped();
	bool isActive();

signals:

	void stopped(); //!< Emited after event loop was fully stopped.
	void onKeyEvent(QTermboxKeyEvent event); //!< Emited on key press.
	void onKeyEventAlternative(QTermboxKeyEvent event);//!< Emited on key press for clashing keys.
	void onResizeEvent(QTermboxResizeEvent event); //!< Emited on resize event.

public slots:
	void start();
	void stop();

private:
	explicit QTermboxEventPool();

	static QTermboxEventPool* _instance;
};

#endif // EVENTPOOL_H
