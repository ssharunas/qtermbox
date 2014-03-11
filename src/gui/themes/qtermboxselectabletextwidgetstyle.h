#ifndef QTERMBOXSELECTABLETEXTWIDGETSTYLE_H
#define QTERMBOXSELECTABLETEXTWIDGETSTYLE_H

#include "qtermboxtextwidgetstyle.h"

class QTermboxSelectableTextWidgetStyle : public QTermboxTextWidgetStyle
{
		Q_OBJECT
	public:
		explicit QTermboxSelectableTextWidgetStyle(QObject *parent = 0);

		inline QTermboxStyle highlightForeground() const { return _highlightForeground; }
		inline void setHighlightForeground(const QTermboxStyle& highlightForeground) { _highlightForeground = highlightForeground; }

		inline QTermboxStyle highlightBackground() const { return _highlightBackground; }
		inline void setHighlightBackground(const QTermboxStyle& highlightBackground) { _highlightBackground = highlightBackground; }

		virtual void copy(QTermboxWidgetStyle* other);
		static QTermboxWidgetStyle* getDefault();

	private:
		QTermboxStyle _highlightForeground;
		QTermboxStyle _highlightBackground;
};

#endif // QTERMBOXSELECTABLETEXTWIDGETSTYLE_H
