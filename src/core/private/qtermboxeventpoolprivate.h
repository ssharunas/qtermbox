#ifndef QTERMBOXEVENTPOOLPRIVATE_H
#define QTERMBOXEVENTPOOLPRIVATE_H

#include <QThread>
#include <QList>
#include "../qtermboxkeyevent.h"
#include "../qtermboxresizeevent.h"

class QTermboxEventPoolPrivate : public QThread
{
	Q_OBJECT
public:
	static QTermboxEventPoolPrivate* instance();
	void run();
	bool isStopped();
	bool isActive();

private:

	struct KeyInfo{
		KeyInfo(int key){
			this->key = key;
			this->ch = 0;
			this->modifyer = 0;
		}

		KeyInfo(int key, uint32_t ch, Qt::KeyboardModifiers modifyer){
			this->key = key;
			this->ch = ch;
			this->modifyer = modifyer;
		}

		int key;
		uint32_t ch;
		Qt::KeyboardModifiers modifyer;
	};

private:
	explicit QTermboxEventPoolPrivate();
	void raiseKeyEvent(uint8_t mod, uint16_t key, uint32_t ch);
	void raiseResizeEvent(int32_t w, int32_t h);
	QList<KeyInfo> mapQtKey(uint16_t key);

private:
	static QTermboxEventPoolPrivate* _instance;
	bool _continueLoop;
	bool _isStopped;

public slots:
	void stop();

signals:
	void stopped();
	void onKeyEvent(QTermboxKeyEvent event);
	void onKeyEventAlternative(QTermboxKeyEvent event);//!< Trigered for overlaying keys
	void onResizeEvent(QTermboxResizeEvent event);
};

#endif // QTERMBOXEVENTPOOLPRIVATE_H
