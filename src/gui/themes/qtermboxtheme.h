#ifndef QTERMBOXTHEME_H
#define QTERMBOXTHEME_H

#include <QObject>
#include "../../core/qtermboxstyle.h"

class QTermboxTheme : public QObject
{
	Q_OBJECT
public:
	explicit QTermboxTheme(QObject *parent = 0);

	inline QTermboxStyle foreground() const { return _foreground; }
	inline void setForeground(const QTermboxStyle& foreground) { _foreground = foreground; }

	inline QTermboxStyle background() const { return _background; }
	inline void setBackground(const QTermboxStyle& background) { _background = background; }
private:
	QTermboxStyle _foreground;
	QTermboxStyle _background;
};

#endif // QTERMBOXTHEME_H
