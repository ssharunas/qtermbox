#include "key.h"

Key::Key(QObject* parent, int x, int y, QList<QChar> &drawData, bool isShift, int drawWidth) :
	QObject(parent), _x(x), _y(y), _isShift(isShift), key(0), keyPressed(0)
{
	QList<QTermboxCell> data;
	QList<QTermboxCell> pressedData;

	foreach(QChar ch, drawData){
		data.append(QTermboxCell(ch, QTermbox::White, QTermbox::Blue));
		pressedData.append(QTermboxCell(ch, QTermbox::White, QTermbox::Red));
	}

	key = QTermboxCellContainer::create(data, drawWidth, this);
	keyPressed = QTermboxCellContainer::create(pressedData, drawWidth, this);
}

void Key::draw(bool pressed)
{
	if(pressed){
		QTermboxCore::putCell(_x, _y, *keyPressed);
	}else{
		QTermboxCore::putCell(_x, _y, *key);
	}
}

bool Key::isShift()
{
	return _isShift;
}
