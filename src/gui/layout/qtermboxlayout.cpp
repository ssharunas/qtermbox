#include "qtermboxlayout.h"

QTermboxLayout::QTermboxLayout(QObject *parent) :
	QObject(parent), _spacing(0), _isEnabled(0)
{
}

void QTermboxLayout::addItem(QTermboxLayoutItem *item)
{
	if(item){
		if(!_items.contains(item)){
			_items.append(item);
		}
	}
}

void QTermboxLayout::removeItem(QTermboxLayoutItem *item)
{
	if(item){
		if(!_items.contains(item)){
			_items.removeAll(item);
		}
	}
}

int QTermboxLayout::indexOf(QTermboxLayoutItem *item)
{
	if(item){
		_items.indexOf(item);
	}

	return -1;
}

QTermboxLayoutItem *QTermboxLayout::takeAt(int index)
{
	if(index >= 0 && index < _items.count()){
		return _items.takeAt(index);
	}

	return 0;
}
