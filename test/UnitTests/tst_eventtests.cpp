#include <QString>
#include <QtTest>
#include "../../src/core/QTermboxCore"
#include "AutoTest.h"
#include <QSize>

class QTermboxEventTestCases : public QObject
{
	Q_OBJECT

public:
	QTermboxEventTestCases(QObject *parent);
	void reset();
	bool wasStopped;
	bool xPressed;
	bool altXPressed;
	bool ctrlHPressed;
	bool wasResized;

private:
	void tryStop();
	bool partialPressed;

public slots:
	void resize(QTermboxResizeEvent event);
	void keyEvent(QTermboxKeyEvent event);
	void keyEventAlternative(QTermboxKeyEvent event);
	void stop();
};


class QTermboxEventTest : public QObject
{
	Q_OBJECT

public:
	QTermboxEventTest();
private:
	QTermboxEventTestCases* cases;
	void doInputTest(QTermbox::QTermboxInputMode mode, QString title);
private Q_SLOTS:
	void initTestCase();
	void altInputModeTest();
	void escInputModeTest();
};

QTermboxEventTest::QTermboxEventTest()
{
	cases = new QTermboxEventTestCases(this);
}

void QTermboxEventTest::initTestCase()
{
	connect(QTermboxEventPool::instance(), SIGNAL(onKeyEvent(QTermboxKeyEvent)), cases, SLOT(keyEvent(QTermboxKeyEvent)));
	connect(QTermboxEventPool::instance(), SIGNAL(onKeyEventAlternative(QTermboxKeyEvent)), cases, SLOT(keyEventAlternative(QTermboxKeyEvent)));
	connect(QTermboxEventPool::instance(), SIGNAL(onResizeEvent(QTermboxResizeEvent)), cases, SLOT(resize(QTermboxResizeEvent)));
	connect(QTermboxEventPool::instance(), SIGNAL(stopped()), cases, SLOT(stop()));
}

void QTermboxEventTest::altInputModeTest(){
	doInputTest(QTermbox::AltInputMode, "Input test in Alt mode");
}

void QTermboxEventTest::escInputModeTest(){
	doInputTest(QTermbox::EscInputMode, "Input test in ESC mode");
}

void QTermboxEventTest::doInputTest(QTermbox::QTermboxInputMode mode, QString title)
{
	int argc = 0;
	QCoreApplication a(argc, (char **) 0);

	cases->reset();
	QTermboxCore::putCell(0, 0, title, QTermboxStyle(QTermbox::White), QTermboxStyle(QTermbox::Black));

	QTermboxEventPool::instance()->setInputMode(mode);
	QTermboxEventPool::instance()->start();

	int i = 31;
	do {
		if(--i <= 0){
			QTermboxCore::putCell(20, 0, "Forced stop.",
				QTermboxStyle(QTermbox::White), QTermboxStyle(QTermbox::Black));

			QTermboxEventPool::instance()->stop();
		}

		QTermboxCore::putCell(0, 10, QString("%1 s. to complete test.").arg(i),
			QTermboxStyle(QTermbox::White), QTermboxStyle(QTermbox::Black));
		QTermboxCore::present();

		QTest::qWait(1000);

	} while(!QTermboxEventPool::instance()->isStopped());

	QCOMPARE(cases->wasStopped, true);
	QCOMPARE(cases->xPressed, true);
	QCOMPARE(cases->altXPressed, true);
	QCOMPARE(cases->ctrlHPressed, true);
	QCOMPARE(cases->wasResized, true);
}

QTermboxEventTestCases::QTermboxEventTestCases(QObject *parent) : QObject(parent) { }

void QTermboxEventTestCases::reset()
{
	partialPressed = false;
	wasStopped = false;
	xPressed = false;
	altXPressed = false;
	ctrlHPressed = false;
	wasResized = false;

	QTermboxCore::initialize();
	QTermboxCore::setClearAttributes(QTermboxStyle(QTermbox::White), QTermboxStyle(QTermbox::Black));

	QTermboxCore::clearScreen();
	QTermboxCore::putCell(0, 2, "Press key 'x'", QTermboxStyle(QTermbox::White), QTermboxStyle(QTermbox::Black));
	QTermboxCore::putCell(0, 3, "Press key 'Alt+x'", QTermboxStyle(QTermbox::White), QTermboxStyle(QTermbox::Black));
	QTermboxCore::putCell(0, 4, "Press key 'Ctrl+h'", QTermboxStyle(QTermbox::White), QTermboxStyle(QTermbox::Black));
	QTermboxCore::putCell(0, 5, "Resize window", QTermboxStyle(QTermbox::White), QTermboxStyle(QTermbox::Black));

	QTermboxCore::putCell(25, 2, "  NO  ", QTermboxStyle(QTermbox::White), QTermboxStyle(QTermbox::Red));
	QTermboxCore::putCell(25, 3, "  NO  ", QTermboxStyle(QTermbox::White), QTermboxStyle(QTermbox::Red));
	QTermboxCore::putCell(25, 4, "  NO  ", QTermboxStyle(QTermbox::White), QTermboxStyle(QTermbox::Red));
	QTermboxCore::putCell(25, 5, "  NO  ", QTermboxStyle(QTermbox::White), QTermboxStyle(QTermbox::Red));

	QTermboxCore::present();
}

void QTermboxEventTestCases::stop()
{
	QTermboxCore::shutdown();
	wasStopped = true;
}

void QTermboxEventTestCases::tryStop(){
	if(wasResized && xPressed && altXPressed && ctrlHPressed){
		QTermboxEventPool::instance()->stop();
	}
}

void QTermboxEventTestCases::resize(QTermboxResizeEvent event)
{
	wasResized = true;

	QTermboxCore::putCell(25, 5, " YES  ", QTermboxStyle(QTermbox::White), QTermboxStyle(QTermbox::Green));
	QTermboxCore::putCell(33, 5, QString("%1x%2").arg(event.size().width()).arg(event.size().height()),
						  QTermboxStyle(QTermbox::Red), QTermboxStyle(QTermbox::Black));
	QTermboxCore::present();

	tryStop();
}

void QTermboxEventTestCases::keyEvent(QTermboxKeyEvent event)
{
	if(event.key() == Qt::Key_unknown && event.modifiers() == Qt::NoModifier && event.text() == "x"){
		QTermboxCore::putCell(25, 2, " YES  ", QTermboxStyle(QTermbox::White), QTermboxStyle(QTermbox::Green));
		xPressed = true;
	}

	if(QTermboxEventPool::instance()->inputMode() == QTermbox::AltInputMode){
		if(event.key() == Qt::Key_unknown && event.modifiers() == Qt::AltModifier && event.text() == "x"){
			QTermboxCore::putCell(25, 3, " YES  ", QTermboxStyle(QTermbox::White), QTermboxStyle(QTermbox::Green));
			altXPressed = true;
		}
	}else{
		QTermboxCore::putCell(25, 3, " INVL ", QTermboxStyle(QTermbox::White), QTermboxStyle(QTermbox::Green));
		altXPressed = true;
	}

	if(event.key() == Qt::Key_Backspace && event.modifiers() == Qt::ControlModifier){
		partialPressed = true;
		QTermboxCore::putCell(25, 4, " PART ", QTermboxStyle(QTermbox::White), QTermboxStyle(QTermbox::Yellow));
	}

	QTermboxCore::putCell(0, 8, QString("Pressed: %1 %2 %3").arg(event.key()).arg(event.modifiers()).arg(event.text()),
		QTermboxStyle(QTermbox::White), QTermboxStyle(QTermbox::Black));

	QTermboxCore::present();
	tryStop();
}

void QTermboxEventTestCases::keyEventAlternative(QTermboxKeyEvent event)
{
	if(partialPressed){
		if(event.key() == Qt::Key_H && event.modifiers() == Qt::ControlModifier && event.text() == "h"){
			QTermboxCore::putCell(25, 4, " YES  ", QTermboxStyle(QTermbox::White), QTermboxStyle(QTermbox::Green));
			ctrlHPressed = true;
		}
	}

	QTermboxCore::putCell(0, 9, QString("Alternative pressed: %1 %2 %3").arg(event.key())
		.arg(event.modifiers()).arg(event.text()),
		QTermboxStyle(QTermbox::White), QTermboxStyle(QTermbox::Black));

	QTermboxCore::present();
	tryStop();
}

DECLARE_TEST(QTermboxEventTest)

#include "tst_eventtests.moc"
