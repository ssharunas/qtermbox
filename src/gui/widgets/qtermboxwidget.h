#ifndef QTERMBOXWIDGET_H
#define QTERMBOXWIDGET_H

#include <QObject>
#include <QRect>
#include "../../core/qtermboxkeyevent.h"
#include "../../core/qtermboxresizeevent.h"
#include "../themes/qtermboxwidgetstyle.h"
#include "../qtermboxfocusevent.h"

class QTermboxWidget : public QObject
{
	Q_OBJECT
public:
	explicit QTermboxWidget(QObject *parent = 0);
	bool hasFocus();

	virtual QTermboxWidgetStyle* theme() const = 0;
	virtual void setTheme(QTermboxWidgetStyle* theme) = 0;

	inline QRect geometry() const { return _geometry; }
	void setGeometry(QRect geometry);

protected:

public slots:
	virtual void paint() = 0;

	virtual void onKeyEvent(QTermboxKeyEvent event);
	virtual void onKeyEventAlternative(QTermboxKeyEvent event);
	virtual void onResizeEvent(QTermboxResizeEvent event);

protected slots:
	virtual void update(bool reflow = true);

private:
	QRect _geometry;

};

#endif // QTERMBOXWIDGET_H
