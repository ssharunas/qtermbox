#include <QCoreApplication>

#include "qtermboxscreen.h"
#include "../core/qtermboxcore.h"
#include "../core/qtermboxeventpool.h"
#include "widgets/qtermboxwidget.h"
#include "qtermboxfocusmanager.h"
#include <QDebug>

QTermboxScreen* QTermboxScreen::_instance = 0;

QTermboxScreen::QTermboxScreen(QObject *parent) :
	QObject(parent), _layout(0), _needsReflow(true)
{
}


QTermboxScreen *QTermboxScreen::instance()
{
	if(!_instance)
		_instance = new QTermboxScreen();

	return _instance;
}

void QTermboxScreen::setLayout(QTermboxLayout *layout)
{
	if(!QTermboxCore::wasInitialized())
		return;

	if(_layout)
		_layout->deleteLater();

	_layout = layout;
	reflow();
}

void QTermboxScreen::onKeyEvent(QTermboxKeyEvent event)
{
	if(!QTermboxCore::wasInitialized())
		return;

//	qDebug() << event.key() << event.text();

	QTermboxWidget *widget = QTermboxFocusManager::instance()->focused();

	while(widget){
		qDebug("1");
		if(!event.isAccepted()){
			widget->onKeyEvent(event);
		}

		widget = qobject_cast<QTermboxWidget*>(widget->parent());
	}

	//TODO: Remove before relese
	if(event.text() == "q"){
		close();
	}
}

void QTermboxScreen::onKeyEventAlternative(QTermboxKeyEvent event)
{
	if(!QTermboxCore::wasInitialized())
		return;

	QTermboxWidget *widget = QTermboxFocusManager::instance()->focused();

	while(widget){
		if(!event.isAccepted()){
			widget->onKeyEventAlternative(event);
		}

		widget = qobject_cast<QTermboxWidget*>(widget->parent());
	}
}

void QTermboxScreen::onResizeEvent(QTermboxResizeEvent event)
{
	if(!QTermboxCore::wasInitialized())
		return;

	QTermboxWidget *widget = QTermboxFocusManager::instance()->focused();

	while(widget){
		if(!event.isAccepted()){
			widget->onResizeEvent(event);
		}

		widget = qobject_cast<QTermboxWidget*>(widget->parent());
	}
}

void QTermboxScreen::exec()
{
	QTermboxCore::initialize();

	connect(QTermboxEventPool::instance(), SIGNAL(onKeyEvent(QTermboxKeyEvent)), this, SLOT(onKeyEvent(QTermboxKeyEvent)));
	connect(QTermboxEventPool::instance(), SIGNAL(onKeyEventAlternative(QTermboxKeyEvent)), this, SLOT(onKeyEventAlternative(QTermboxKeyEvent)));
	connect(QTermboxEventPool::instance(), SIGNAL(onResizeEvent(QTermboxResizeEvent)), this, SLOT(onResizeEvent(QTermboxResizeEvent)));

	QTermboxCore::setClearAttributes(QTermboxStyle(QTermbox::Red), QTermboxStyle(QTermbox::Blue));

	update();

	QTermboxEventPool::instance()->start();
}

void QTermboxScreen::close()
{
	QTermboxCore::shutdown();
	QCoreApplication::quit();
}

void QTermboxScreen::update()
{
	if(!QTermboxCore::wasInitialized())
		return;

	if(_needsReflow && layout())
		layout()->update();

	foreach (QObject *item, children()) {
		QTermboxWidget *widget = qobject_cast<QTermboxWidget*>(item);
		if(widget){
			widget->paint();

			widget = 0;
		}
	}

	QTermboxCore::present();
}

