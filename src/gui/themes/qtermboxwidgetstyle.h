#ifndef QTERMBOXTHEME_H
#define QTERMBOXTHEME_H

#include <QObject>
#include "../../core/qtermboxstyle.h"

class QTermboxWidgetStyle : public QObject
{
	Q_OBJECT
public:
	explicit QTermboxWidgetStyle(QObject *parent = 0);

	inline QTermboxStyle backgroundFocus() const { return _backgroundFocus; }
	inline void setBackgroundFocus(const QTermboxStyle& backgroundFocus) { _backgroundFocus = backgroundFocus; }

	inline QTermboxStyle background() const { return _background; }
	inline void setBackground(const QTermboxStyle& background) { _background = background; }

	void searialize(QString file);
	void deserialize(QString file);

	static QTermboxWidgetStyle* getDefault();
private:
	QTermboxStyle _background;
	QTermboxStyle _backgroundFocus;
};

#endif // QTERMBOXTHEME_H
