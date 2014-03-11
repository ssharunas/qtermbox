#ifndef QTERMBOXWIDGET_H
#define QTERMBOXWIDGET_H

#include <QObject>
#include <QRect>
#include <QDebug>
#include "../../core/qtermboxkeyevent.h"
#include "../../core/qtermboxresizeevent.h"
#include "../themes/qtermboxwidgetstyle.h"
#include "../themes/qtermboxstylefactory.h"
#include "../qtermboxfocusevent.h"

class QTermboxWidget : public QObject
{
	Q_OBJECT
public:
	explicit QTermboxWidget(QObject *parent = 0);
	bool hasFocus();

	virtual QTermboxWidgetStyle& theme();
	virtual void setTheme(QTermboxWidgetStyle* theme);

	inline QRect geometry() const { return _geometry; }
	void setGeometry(QRect geometry);

protected:

	template<class T> T& getTheme(){
		T* result;

		if(_style != 0){
			result = qobject_cast<T*>(_style);

			if(!result){
				result = new T(this);
				result->copy(_style);

				delete _style;
				_style = result;
			}
		}else{
			result = &QTermboxStyleFactory::instance().getStyleOfType<T>(metaObject());
		}

		return *result;
	}

public slots:
	virtual void paint() = 0;

	virtual void onKeyEvent(QTermboxKeyEvent event);
	virtual void onKeyEventAlternative(QTermboxKeyEvent event);
	virtual void onResizeEvent(QTermboxResizeEvent event);

protected slots:
	virtual void update(bool reflow = true);

private:
	QRect _geometry;
	QTermboxWidgetStyle* _style;

};

#endif // QTERMBOXWIDGET_H
