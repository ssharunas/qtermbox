#include <QString>
#include <QtTest>
#include "../../src/core/private/qtermboxcoreprivate.h"
#include "../../src/core/QTermboxCore"
#include "AutoTest.h"
#include "unistd.h"
#include <QDebug>

class QTermboxCoreTest : public QObject
{
	Q_OBJECT

public:
	QTermboxCoreTest();

private Q_SLOTS:
	void initTestCase();
	void initializationTest();
	void sizeTest();
	void clearScreenTest();
	void moveCursorTest();
	void setClearAttributesTest();
	void putCellTest();
};

QTermboxCoreTest::QTermboxCoreTest()
{
}

void QTermboxCoreTest::initTestCase()
{
	QCOMPARE(QTermboxCorePrivate::wasInitialized(), false);
}

void QTermboxCoreTest::initializationTest()
{
	QCOMPARE(QTermboxCorePrivate::wasInitialized(), false);

	QTermboxCore::initialize();
	QCOMPARE(QTermboxCorePrivate::wasInitialized(), true);

	QTermboxCore::shutdown();
	QCOMPARE(QTermboxCorePrivate::wasInitialized(), false);
}

void QTermboxCoreTest::sizeTest()
{
	QTermboxCore::initialize();
	QSize size = QTermboxCore::screenSize();
	QTermboxCore::shutdown();

	qDebug() << "Measured size of screen:" << size;
	QVERIFY(size != QSize());
}

void QTermboxCoreTest::clearScreenTest()
{
	QTermboxCore::initialize();
	QTermboxCore::clearScreen();
	QTermboxCore::shutdown();
}

void QTermboxCoreTest::moveCursorTest()
{
	QTermboxCore::initialize();

	QTermboxCore::putCell(1, 1, QString("Cursor yes: "), QTermboxStyle(QTermbox::Red), QTermboxStyle(QTermbox::Green));
	QTermboxCore::moveCursor(QPoint(12, 1));
	QTermboxCore::present();

	sleep(1);

	QTermboxCore::putCell(1, 1, QString("Cursor  no: "), QTermboxStyle(QTermbox::Red), QTermboxStyle(QTermbox::Green));
	QTermboxCore::hideCursor();
	QTermboxCore::present();
	sleep(1);

	QTermboxCore::shutdown();
}

void QTermboxCoreTest::setClearAttributesTest()
{
	QTermboxCore::initialize();
	QTermboxCore::setClearAttributes(QTermboxStyle(QTermbox::Blue), QTermboxStyle(QTermbox::Red));
	QTermboxCore::clearScreen();
	QTermboxCore::present();
	sleep(1);
	QTermboxCore::shutdown();
}

void QTermboxCoreTest::putCellTest()
{
	QTermboxCore::initialize();

	QList<QTermboxCell> cells;
	cells
			<< QTermboxCell('+', QTermboxStyle(QTermbox::Blue), QTermboxStyle(QTermbox::Green))
			<< QTermboxCell('-', QTermboxStyle(QTermbox::Blue), QTermboxStyle(QTermbox::Green))
			<< QTermboxCell('+', QTermboxStyle(QTermbox::Blue), QTermboxStyle(QTermbox::Green))
			<< QTermboxCell('|')
			<< QTermboxCell(' ')
			<< QTermboxCell('|')
			<< QTermboxCell('+', QTermbox::Blue, QTermbox::Green)
			<< QTermboxCell('-', QTermbox::Blue, QTermbox::Green)
			<< QTermboxCell('+', QTermbox::Blue, QTermbox::Green);

	QTermboxCore::moveCursor(QPoint(10, 10));
	QTermboxCore::putCell(1, 1, QTermboxCell('X', QTermboxStyle(QTermbox::Red, QTermbox::Bold), QTermboxStyle(QTermbox::Green)));
	QTermboxCore::putCell(1, 2, 'Y', QTermboxStyle(QTermbox::Blue), QTermboxStyle(QTermbox::Green));

	QTermboxCore::putCell(1, 3, 3, cells);
	QTermboxCore::putCell(1, 6, -1, cells);

	QTermboxCore::putCell(1, 7, *QTermboxCellContainer::create(cells, 3, this));

	QTermboxCore::putCell(1, 10, QString("abcdefg"), QTermboxStyle(QTermbox::Red), QTermboxStyle(QTermbox::Green));
	QTermboxCore::putCell(1, 11, 3, QString("abcdefg"), QTermboxStyle(QTermbox::Red), QTermboxStyle(QTermbox::Green));

	QTermboxCore::present();
	sleep(5);

	QTermboxCore::shutdown();
}

DECLARE_TEST(QTermboxCoreTest)

#include "tst_coretests.moc"
