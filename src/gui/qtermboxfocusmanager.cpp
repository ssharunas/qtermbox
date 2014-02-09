#include "qtermboxfocusmanager.h"

QTermboxFocusManager* QTermboxFocusManager::_instance = 0;

QTermboxFocusManager::QTermboxFocusManager()
{
}

QTermboxFocusManager *QTermboxFocusManager::instance()
{
	if(!_instance)
		_instance = new QTermboxFocusManager();

	return _instance;
}

void QTermboxFocusManager::unregisterWidget(QTermboxWidget *widget)
{
	if(widget){
		int index = _widgets.indexOf(widget);
		if(index >= 0){
			_widgets.remove(index);

			if(index > _widgets.count()){
				if(_widgets.count() > 0)
					emit focusChanged(0, _widgets.first());
				else
					emit focusChanged(0, 0);
			}
		}
	}
}

void QTermboxFocusManager::unregisterSender()
{
	QTermboxWidget* widget = qobject_cast<QTermboxWidget*>(sender());

	if(widget){
		unregisterWidget(widget);
	}
}

bool QTermboxFocusManager::focusNext()
{
	//TODO: write it. Stack does not fit there.

	return  false;
}

bool QTermboxFocusManager::focusPrev()
{
	//TODO: write it. Stack does not fit there.

	return  false;
}

QTermboxWidget *QTermboxFocusManager::focused()
{
	if(_widgets.count() > 0)
		return _widgets.first();

	return 0;
}

void QTermboxFocusManager::registerWidget(QTermboxWidget *widget)
{
	if(widget){
		connect(widget, SIGNAL(destroyed()), this, SLOT(unregisterSender()));
		_widgets.push(widget);
	}
}
