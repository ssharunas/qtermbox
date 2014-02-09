#ifndef QTERMBOXFOCUSMANAGER_H
#define QTERMBOXFOCUSMANAGER_H

#include <QObject>
#include <QStack>
#include "widgets/qtermboxwidget.h"

class QTermboxFocusManager : QObject
{
	Q_OBJECT

public:
	static QTermboxFocusManager* instance();
	bool focusNext();
	bool focusPrev();
	QTermboxWidget* focused();
	inline bool isFocused(QTermboxWidget* widget) { return focused() == widget; }
	void registerWidget(QTermboxWidget* widget);
protected:
	explicit QTermboxFocusManager();

signals:
	void focusChanged(QTermboxWidget* oldWidget, QTermboxWidget* newWidget);

public slots:
	void unregisterWidget(QTermboxWidget* widget);

protected slots:
	void unregisterSender();

private:
	static QTermboxFocusManager *_instance;
	QStack<QTermboxWidget*> _widgets;
};

#endif // QTERMBOXFOCUSMANAGER_H
