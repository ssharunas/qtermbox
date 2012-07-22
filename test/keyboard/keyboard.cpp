#include "keyboard.h"
#include <QCoreApplication>

Keyboard::Keyboard(QObject *parent) :
	QObject(parent), ctrlxpressed(false), lastAlternativeKeyX(0), lastAlternativeTextX(0)
{
	initVariables();

	QTermboxCore::initialize();
	QTermboxEventPool::instance()->setInputMode(QTermbox::EscInputMode);

	paintKeyboard();
	QTermboxCore::present();
}

Keyboard::~Keyboard()
{
	QTermboxCore::shutdown();
}

void Keyboard::initVariables()
{
	keys = new KeyContainer(this);
	hBorder = QTermboxCellContainer::create(QTermboxCell(QChar(0x2500)).multiply(78), -1, this);
	vBorder = QTermboxCellContainer::create(QTermboxCell(QChar(0x2502)).multiply(22), 1, this);
	vBar = QTermboxCellContainer::create(QTermboxCell(QChar(0x2588), QTermbox::Yellow, QTermbox::Yellow).multiply(12), 1, this);
}

void Keyboard::paintKeyboard()
{
	QTermboxCore::clearScreen();
	QTermboxCore::putCell( 0, 0, QChar(0x250C));
	QTermboxCore::putCell(79, 0, QChar(0x2510));
	QTermboxCore::putCell( 0, 23, QChar(0x2514));
	QTermboxCore::putCell(79, 23, QChar(0x2518));

	QTermboxCore::putCell(1, 0, *hBorder);
	QTermboxCore::putCell(1, 23, *hBorder);
	QTermboxCore::putCell(1, 17, *hBorder);
	QTermboxCore::putCell(1, 4, *hBorder);

	QTermboxCore::putCell(0, 1, *vBorder);
	QTermboxCore::putCell(79, 1, *vBorder);

	QTermboxCore::putCell(0, 17, QChar(0x251C));
	QTermboxCore::putCell(79, 17, QChar(0x2524));
	QTermboxCore::putCell(0, 4, QChar(0x251C));
	QTermboxCore::putCell(79, 4, QChar(0x2524));

	QTermboxCore::putCell( 1, 5, *vBar);
	QTermboxCore::putCell(78, 5, *vBar);

	QList<Key*> allKeys = keys->allKeys();
	foreach (Key* key, allKeys) {
		if(key->isShift())
			continue;
		key->draw(false);
	}

	QTermboxCore::putCell(33, 1, "Keyboard demo!", QTermboxStyle(QTermbox::Magenta, QTermbox::Bold), QTermboxStyle(QTermbox::Black));
	QTermboxCore::putCell(21, 2, "(press CTRL+X and then CTRL+Q to exit)", QTermbox::Magenta, QTermbox::Black);
	QTermboxCore::putCell(15, 3, "(press CTRL+X and then CTRL+C to change input mode)", QTermbox::Magenta, QTermbox::Black);

	QString inputMode = "Input mode: ";
	if(QTermboxEventPool::instance()->inputMode() == QTermbox::EscInputMode)
		inputMode += "TB_INPUT_ESC";
	else
		inputMode += "TB_INPUT_ALT";

	QTermboxCore::putCell(3, 18, inputMode);
}

void Keyboard::drawPressed(QTermboxKeyEvent &ev)
{
	QList<Key*> pressed = keys->getKeys(ev);

	foreach (Key* key, pressed) {
		key->draw(true);
	}
}

void Keyboard::prettyPrintPress(QTermboxKeyEvent &ev)
{
	QString keyStr = keys->qtKeyAsString(ev.key());

	QString text = ev.text();
	if(text.length() > 0 && !text[0].isPrint())
		text = ' ';

	QTermboxCore::putCell(3, 19, "Qt Key: ");
	QTermboxCore::putCell(11, 19, keyStr, QTermbox::Red, QTermbox::Black);

	QTermboxCore::putCell(43, 19, "Text: ");
	QTermboxCore::putCell(49, 19, QString("string: '%1'").arg(text), QTermbox::Red, QTermbox::Black);

	QString modifyers;
	if(ev.modifiers() & Qt::ControlModifier)
		modifyers += "Ctrl ";

	if(ev.modifiers() & Qt::AltModifier)
		modifyers += "Alt ";

	if(ev.modifiers() & Qt::ShiftModifier)
		modifyers += "Shift ";

	QTermboxCore::putCell(49, 18, QString("Modifier: ") + modifyers);
}

void Keyboard::prettyPrintPressAlternative(QTermboxKeyEvent &ev)
{
	QTermboxCore::putCell(3, 21, "Alternative Keys: ");
	QTermboxCore::putCell(3, 22, "Alternative Text: ");

	QString text = "'" + ev.text() + "'";
	QString keyStr = keys->qtKeyAsString(ev.key());

	if(lastAlternativeKeyX)
		keyStr = ", " + keyStr;

	if(lastAlternativeTextX)
		text = ", " + text;

	QTermboxCore::putCell(21 + lastAlternativeKeyX, 21, keyStr);
	QTermboxCore::putCell(21 + lastAlternativeTextX, 22, text);

	lastAlternativeKeyX += keyStr.length();
	lastAlternativeTextX += text.length();
}

void Keyboard::prettyPrintResize(QTermboxResizeEvent &ev)
{
	QTermboxCore::putCell(3, 19, QString("Resize event: %1 x %2").arg(ev.size().width()).arg(ev.size().height()));
}

void Keyboard::onKeyEvent(QTermboxKeyEvent event)
{
	lastAlternativeKeyX = 0;
	lastAlternativeTextX = 0;

	if((event.key() == Qt::Key_Q) && (event.modifiers() & Qt::ControlModifier) && ctrlxpressed){
		QTermboxCore::shutdown();
		QCoreApplication::quit();
	}

	if((event.key() == Qt::Key_C) && (event.modifiers() & Qt::ControlModifier) && ctrlxpressed){
		if(QTermboxEventPool::instance()->inputMode() == QTermbox::EscInputMode)
			QTermboxEventPool::instance()->setInputMode(QTermbox::AltInputMode);
		else
			QTermboxEventPool::instance()->setInputMode(QTermbox::EscInputMode);
	}

	if(event.key() == Qt::Key_X && (event.modifiers() & Qt::ControlModifier)){
		ctrlxpressed = true;
	}else{
		ctrlxpressed = false;
	}

	paintKeyboard();
	prettyPrintPress(event);
	drawPressed(event);
	QTermboxCore::present();
}

void Keyboard::onKeyEventAlternative(QTermboxKeyEvent event)
{
	prettyPrintPressAlternative(event);
	drawPressed(event);
	QTermboxCore::present();
}

void Keyboard::onResizeEvent(QTermboxResizeEvent event)
{
	paintKeyboard();
	prettyPrintResize(event);
}
