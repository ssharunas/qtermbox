#ifndef QTERMBOXLINEEDIT_H
#define QTERMBOXLINEEDIT_H

#include "qtermboxwidget.h"
#include "../themes/qtermboxselectabletextwidgetstyle.h"

class QTermboxLineEdit : public QTermboxWidget
{
	Q_OBJECT
public:
	explicit QTermboxLineEdit(QObject *parent = 0);

	virtual QTermboxSelectableTextWidgetStyle &theme();
	virtual void setTheme(QTermboxSelectableTextWidgetStyle* theme);

	inline QString text() const { return _text; }
	void setText(QString text);

public slots:
	virtual void paint();
	virtual void onKeyEvent(QTermboxKeyEvent event);

private:
	QString _text;
};

#endif // QTERMBOXLINEEDIT_H
