#ifndef QTERMBOXSCREEN_H
#define QTERMBOXSCREEN_H

#include <QObject>
#include "../core/qtermboxkeyevent.h"
#include "../core/qtermboxresizeevent.h"
#include "layout/qtermboxlayout.h"

class QTermboxScreen : public QObject
{
	Q_OBJECT

public:
	static QTermboxScreen* instance();

	inline QTermboxLayout* layout() const { return _layout; }
	void setLayout(QTermboxLayout* layout);

protected slots:
	void onKeyEvent(QTermboxKeyEvent event);
	void onKeyEventAlternative(QTermboxKeyEvent event);
	void onResizeEvent(QTermboxResizeEvent event);

public slots:
	void exec();
	void close();
	inline void reflow() { _needsReflow = true; }

	void update();

protected:
	explicit QTermboxScreen(QObject *parent = 0);

private:
	static QTermboxScreen *_instance;
	QTermboxLayout* _layout;
	bool _needsReflow;
};

#endif // QTERMBOXSCREEN_H
