#ifndef QTERMBOXTEXTWIDGETSTYLE_H
#define QTERMBOXTEXTWIDGETSTYLE_H

#include "qtermboxwidgetstyle.h"

class QTermboxTextWidgetStyle : public QTermboxWidgetStyle
{
		Q_OBJECT
	public:
		explicit QTermboxTextWidgetStyle(QObject *parent = 0);

		inline QTermboxStyle text() const { return _text; }
		inline void setText(const QTermboxStyle& text) { _text = text; }

		inline QTermboxStyle textFocus() const { return _textFocus; }
		inline void setTextFocus(const QTermboxStyle& textFocus) { _textFocus = textFocus; }

		virtual void copy(QTermboxWidgetStyle* other);
		static QTermboxWidgetStyle* getDefault();

	private:
		QTermboxStyle _text;
		QTermboxStyle _textFocus;
};

#endif // QTERMBOXTEXTWIDGETSTYLE_H
