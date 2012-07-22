#include <QString>
#include <QtTest>
#include "../../src/core/QTermboxCore"
#include "AutoTest.h"

class QTermboxCellFactoryTest : public QObject
{
	Q_OBJECT

public:
	QTermboxCellFactoryTest();

private Q_SLOTS:
	void constructorTest();
	void setStyleTest();
	void appendTest();
};

QTermboxCellFactoryTest::QTermboxCellFactoryTest()
{
}

void QTermboxCellFactoryTest::constructorTest()
{
	QTermboxCore::initialize();
	QTermboxCore::setClearAttributes(QTermboxStyle(QTermbox::Red, QTermbox::Underline),
									 QTermboxStyle(QTermbox::Green, QTermbox::Bold));
	QTermboxCore::shutdown();

	QTermboxCellFactory *factory = new QTermboxCellFactory();
	QTermboxCell cell = factory->create(QChar('X'));

	QCOMPARE(cell.fg(), QTermboxStyle(QTermbox::Red, QTermbox::Underline));
	QCOMPARE(cell.bg(), QTermboxStyle(QTermbox::Green, QTermbox::Bold));

	delete factory;

	factory = new QTermboxCellFactory(QTermbox::White, QTermbox::Blue);
	cell = factory->create(QChar('X'));

	QCOMPARE(cell.fg(), QTermboxStyle(QTermbox::White));
	QCOMPARE(cell.bg(), QTermboxStyle(QTermbox::Blue));

	delete factory;

	factory = new QTermboxCellFactory(
				QTermboxStyle(QTermbox::Yellow, QTermbox::Bold),
				QTermboxStyle(QTermbox::Magenta, QTermbox::Underline));

	cell = factory->create(QChar('X'));

	QCOMPARE(cell.fg(), QTermboxStyle(QTermbox::Yellow, QTermbox::Bold));
	QCOMPARE(cell.bg(), QTermboxStyle(QTermbox::Magenta, QTermbox::Underline));

	delete factory;
}

void QTermboxCellFactoryTest::setStyleTest()
{
	QTermboxCellFactory factory;
	factory.setStyle(QTermboxStyle(QTermbox::Red, QTermbox::Underline),
					 QTermboxStyle(QTermbox::Green, QTermbox::Bold));

	QTermboxCell cell = factory.create(QChar('X'));

	QCOMPARE(cell.fg(), QTermboxStyle(QTermbox::Red, QTermbox::Underline));
	QCOMPARE(cell.bg(), QTermboxStyle(QTermbox::Green, QTermbox::Bold));

	factory.setStyle(QTermbox::White, QTermbox::Blue);
	cell = factory.create(QChar('X'));

	QCOMPARE(cell.fg(), QTermboxStyle(QTermbox::White));
	QCOMPARE(cell.bg(), QTermboxStyle(QTermbox::Blue));
}

void QTermboxCellFactoryTest::appendTest()
{
	QTermboxCellFactory factory(QTermbox::Black, QTermbox::White);
	QList<QTermboxCell> cells = factory
		.append(QChar('1'))
		->append(QChar('2'), QTermbox::Red, QTermbox::Cyan)
		->append(QChar('3'), QTermboxStyle(QTermbox::Green), QTermboxStyle(QTermbox::Magenta))
		->append(QString('4'))
		->append(QString('5'), QTermbox::Yellow, QTermbox::Blue)
		->append(QString('6'), QTermboxStyle(QTermbox::Blue), QTermboxStyle(QTermbox::Yellow))
		->append(QChar('7'), 2)
		->append(QChar('8'), 2, QTermbox::Magenta, QTermbox::Green)
		->append(QChar('9'), 2, QTermboxStyle(QTermbox::Cyan), QTermboxStyle(QTermbox::Red))
		->create();

	QCOMPARE(cells.length(),12);

	QCOMPARE(cells[0].fg(), QTermboxStyle(QTermbox::Black));
	QCOMPARE(cells[0].bg(), QTermboxStyle(QTermbox::White));

	QCOMPARE(cells[1].fg(), QTermboxStyle(QTermbox::Red));
	QCOMPARE(cells[1].bg(), QTermboxStyle(QTermbox::Cyan));

	QCOMPARE(cells[2].fg(), QTermboxStyle(QTermbox::Green));
	QCOMPARE(cells[2].bg(), QTermboxStyle(QTermbox::Magenta));

	QCOMPARE(cells[3].fg(), QTermboxStyle(QTermbox::Black));
	QCOMPARE(cells[3].bg(), QTermboxStyle(QTermbox::White));

	QCOMPARE(cells[4].fg(), QTermboxStyle(QTermbox::Yellow));
	QCOMPARE(cells[4].bg(), QTermboxStyle(QTermbox::Blue));

	QCOMPARE(cells[5].fg(), QTermboxStyle(QTermbox::Blue));
	QCOMPARE(cells[5].bg(), QTermboxStyle(QTermbox::Yellow));

	QCOMPARE(cells[6].fg(), QTermboxStyle(QTermbox::Black));
	QCOMPARE(cells[6].bg(), QTermboxStyle(QTermbox::White));

	QCOMPARE(cells[7].fg(), QTermboxStyle(QTermbox::Black));
	QCOMPARE(cells[7].bg(), QTermboxStyle(QTermbox::White));

	QCOMPARE(cells[8].fg(), QTermboxStyle(QTermbox::Magenta));
	QCOMPARE(cells[8].bg(), QTermboxStyle(QTermbox::Green));

	QCOMPARE(cells[9].fg(), QTermboxStyle(QTermbox::Magenta));
	QCOMPARE(cells[9].bg(), QTermboxStyle(QTermbox::Green));

	QCOMPARE(cells[10].fg(), QTermboxStyle(QTermbox::Cyan));
	QCOMPARE(cells[10].bg(), QTermboxStyle(QTermbox::Red));

	QCOMPARE(cells[11].fg(), QTermboxStyle(QTermbox::Cyan));
	QCOMPARE(cells[11].bg(), QTermboxStyle(QTermbox::Red));
}

DECLARE_TEST(QTermboxCellFactoryTest)

#include "tst_cellFactorytests.moc"
