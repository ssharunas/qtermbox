#ifndef QTERMBOXTHEMEDEFAULTVALUESPROVIDER_H
#define QTERMBOXTHEMEDEFAULTVALUESPROVIDER_H

#include <QObject>
#include "../../core/qtermboxstyle.h"

class QTermboxThemeDefaultValuesProvider : public QObject
{
	Q_OBJECT
public:
	explicit QTermboxThemeDefaultValuesProvider(QObject *parent = 0);

	inline QTermboxStyle text() { return _text; }
	inline QTermboxStyle highlightedText() { return _highlightedText; }
	inline QTermboxStyle windowBackground() { return _windowBackground; }
	inline QTermboxStyle inputControlBackground() { return _inputControlBackground; }

	//TODO: implement setters

private:
	QTermboxStyle _text;
	QTermboxStyle _highlightedText;
	QTermboxStyle _windowBackground;
	QTermboxStyle _inputControlBackground;

signals:

};

#endif // QTERMBOXTHEMEDEFAULTVALUESPROVIDER_H
