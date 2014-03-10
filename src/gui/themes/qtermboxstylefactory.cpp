#include "qtermboxstylefactory.h"
#include "../qtermboxscreen.h"
#include "../widgets/qtermboxwidget.h"

QTermboxStyleFactory* QTermboxStyleFactory::_instance = 0;

QTermboxStyleFactory::StyleInfo::StyleInfo(const QMetaObject *widgetType, QTermboxWidgetStyle *style)
{
	this->style = style;
	this->widgetType = widgetType;
}

QTermboxStyleFactory::QTermboxStyleFactory(QObject *parent) :
	QObject(parent)
{
	_nullStyle = new  QTermboxWidgetStyle(this);
}

QTermboxWidgetStyle &QTermboxStyleFactory::getStyle(const QMetaObject *widgetType)
{
	if(_styleCache.contains(widgetType)){
		return *_styleCache[widgetType];
	}

	for(int i = 0; i < _styles.count(); i++){
		if(_styles[i].widgetType == widgetType){
			_styleCache[widgetType] = _styles[i].style;
			return *_styles[i].style;
		}
	}

	const QMetaObject *endObject = &QTermboxWidget::staticMetaObject;
	for(int i = 0; i < _styles.count(); i++){

		//TODO: implement proper type hierarchy check, dependant on inherence length etc.

		const QMetaObject* super = _styles[i].widgetType->superClass();
		while(super !=  0 && super != endObject){

			if(super == widgetType){
				_styleCache[widgetType] = _styles[i].style;
				return *_styles[i].style;
			}

			super = super->superClass();
		}
	}

	return *_nullStyle;
}

void QTermboxStyleFactory::installStyle(const QMetaObject *widgetType, QTermboxWidgetStyle *style)
{
	installStyle(widgetType, style, true);
}

void QTermboxStyleFactory::tryInstallStyle(const QMetaObject *widgetType, QTermboxWidgetStyle *style)
{
	installStyle(widgetType, style, false);
}

void QTermboxStyleFactory::installStyle(const QMetaObject *widgetType, QTermboxWidgetStyle *style, bool replace)
{
	if(widgetType != 0 && style != 0){
		_styleCache.clear();
		bool exists = false;

		for(int i = _styles.count() - 1; i >= 0 ; i--){
			if(_styles[i].widgetType == widgetType){
				if(replace){
					_styles[i].style->deleteLater();
					_styles.takeAt(i);
				}

				exists = true;
			}
		}

		if(!exists || replace){
			style->setParent(this);
			_styles.append(StyleInfo(widgetType, style));

			QTermboxScreen::instance()->update();
		}else{
			style->deleteLater();
		}
	}else{
		qDebug("Style was not installed: either widget type either style was null.");
	}
}


QTermboxStyleFactory &QTermboxStyleFactory::instance()
{
	if(_instance == 0)
		_instance = new QTermboxStyleFactory();

	return *_instance;
}
