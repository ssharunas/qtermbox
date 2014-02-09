#ifndef QTERMBOXLAYOUT_H
#define QTERMBOXLAYOUT_H

#include <QObject>
#include <QMargins>
#include "qtermboxlayoutitem.h"

class QTermboxLayout : public QObject
{
	Q_OBJECT
protected:
	explicit QTermboxLayout(QObject *parent = 0);

public:
	virtual void update() = 0;

	virtual void addItem(QTermboxLayoutItem* item);
	virtual void removeItem(QTermboxLayoutItem* item);
	int indexOf(QTermboxLayoutItem* item);
	QTermboxLayoutItem* takeAt(int index);

	inline QMargins contentMargins() { return _contentMargins; }
	inline void setContentMargins(QMargins margins) { _contentMargins = margins; }

	inline int spacing() { return _spacing; }
	inline void setSpacing(int spacing) { _spacing = spacing; }

	inline bool isEnabled() { return _isEnabled; }
	inline void setIsEnabled(bool isEnabled) { _isEnabled = isEnabled; }
private:
	QList<QTermboxLayoutItem*> _items;
	QMargins _contentMargins;
	int _spacing;
	bool _isEnabled;
};

#endif // QTERMBOXLAYOUT_H
