#ifndef QTERMBOXLABEL_H
#define QTERMBOXLABEL_H

#include <QObject>
#include "qtermboxwidget.h"
#include "../themes/qtermboxtextwidgetstyle.h"

class QTermboxLabel : public QTermboxWidget
{
		Q_OBJECT
	public:
		explicit QTermboxLabel(QObject *parent = 0);

		virtual QTermboxTextWidgetStyle &theme();
		virtual void setTheme(QTermboxTextWidgetStyle* theme);

		inline QString text() const { return _text; }
		void setText(QString text);

	public slots:
		virtual void paint();

	private:
		QString _text;
};

#endif // QTERMBOXLABEL_H
