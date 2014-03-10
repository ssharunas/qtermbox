#ifndef QTERMBOXLABEL_H
#define QTERMBOXLABEL_H

#include <QObject>
#include "qtermboxwidget.h"

class QTermboxLabel : public QTermboxWidget
{
	Q_OBJECT
public:
	explicit QTermboxLabel(QObject *parent = 0);

	virtual inline QTermboxWidgetStyle* theme() const { return _theme; }
	virtual void setTheme(QTermboxWidgetStyle* theme);

	inline QString text() const { return _text; }
	void setText(QString text);

public slots:
	virtual void paint();

private:
	QTermboxWidgetStyle* _theme;
	QString _text;
};

#endif // QTERMBOXLABEL_H
