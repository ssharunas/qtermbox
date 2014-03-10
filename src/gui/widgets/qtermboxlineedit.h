#ifndef QTERMBOXLINEEDIT_H
#define QTERMBOXLINEEDIT_H

#include "qtermboxwidget.h"

class QTermboxLineEdit : public QTermboxWidget
{
	Q_OBJECT
public:
	explicit QTermboxLineEdit(QObject *parent = 0);

	virtual inline QTermboxWidgetStyle* theme() const { return _theme; }
	virtual void setTheme(QTermboxWidgetStyle* theme);

	inline QString text() const { return _text; }
	void setText(QString text);

public slots:
	virtual void paint();
	virtual void onKeyEvent(QTermboxKeyEvent event);

private:
	QTermboxWidgetStyle* _theme;
	QString _text;
};

#endif // QTERMBOXLINEEDIT_H
