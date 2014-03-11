#ifndef QTERMBOXTHEMEDEFAULTVALUESPROVIDER_H
#define QTERMBOXTHEMEDEFAULTVALUESPROVIDER_H

#include <QObject>
#include <QList>
#include <QHash>
#include <QDebug>
#include "qtermboxwidgetstyle.h"

class QTermboxStyleFactory : public QObject
{
	Q_OBJECT
private:
	explicit QTermboxStyleFactory(QObject *parent = 0);

public:
	QTermboxWidgetStyle& getStyle(const QMetaObject* widgetType);
	void installStyle(const QMetaObject* widgetType, QTermboxWidgetStyle* style);
	void tryInstallStyle(const QMetaObject* widgetType, QTermboxWidgetStyle* style);

	template<class T> T& getStyleOfType(const QMetaObject* widgetType){
		QTermboxWidgetStyle* style = &getStyle(widgetType);
		T* result = qobject_cast<T*>(style);

		//if containing style is of invalid type, it must be replaced with  correct one
		if(!result){
			result = new T(this);
			result->copy(style);

			installStyle(widgetType, result);
		}

		return *result;
	}

	static QTermboxStyleFactory& instance();

protected:
	void installStyle(const QMetaObject* widgetType, QTermboxWidgetStyle* style, bool replace);

private:
	struct StyleInfo{
		StyleInfo(const QMetaObject* widgetType, QTermboxWidgetStyle* style);

		const QMetaObject* widgetType;
		QTermboxWidgetStyle* style;
	};
	QTermboxWidgetStyle* _nullStyle;

	static QTermboxStyleFactory* _instance;
	QList<StyleInfo> _styles;
	QHash<const QMetaObject*, QTermboxWidgetStyle*> _styleCache;
};

class QTermboxStyleFactoryRegistrator{
	public:
		QTermboxStyleFactoryRegistrator(const QMetaObject *widgetType, QTermboxWidgetStyle* style){
			QTermboxStyleFactory::instance().tryInstallStyle(widgetType, style);
	}
};

#define QTB_REGISTER_STYLE(cls, style) static QTermboxStyleFactoryRegistrator _QTermboxStyleFactoryRegisteredClass_##cls(&cls::staticMetaObject, style::getDefault());

#endif // QTERMBOXTHEMEDEFAULTVALUESPROVIDER_H
