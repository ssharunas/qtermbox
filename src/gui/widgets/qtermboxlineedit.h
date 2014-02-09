#ifndef QTERMBOXLINEEDIT_H
#define QTERMBOXLINEEDIT_H

#include "qtermboxwidget.h"

class QTermboxLineEdit : public QTermboxWidget
{
	Q_OBJECT
public:
	explicit QTermboxLineEdit(QObject *parent = 0);

	virtual QTermboxTheme* defaultTheme();
	virtual void setDefaultTheme(QTermboxTheme* theme);

	virtual inline QTermboxTheme* theme() const { return _theme; }
	virtual void setTheme(QTermboxTheme* theme);

	inline QString text() const { return _text; }
	void setText(QString text);

public slots:
	virtual void paint();
	virtual void onKeyEvent(QTermboxKeyEvent event);

private:
	QTermboxTheme* _theme;
	QString _text;
};

#endif // QTERMBOXLINEEDIT_H
