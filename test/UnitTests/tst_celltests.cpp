#include <QString>
#include <QtTest>
#include "../../src/core/QTermboxCore"
#include "AutoTest.h"

class QTermboxCellTest : public QObject
{
	Q_OBJECT

public:
	QTermboxCellTest();

private Q_SLOTS:
	void multiplyTest();
	void containerTest();
	void containerCopyTest();
	void containerTestFail();
	void equalTest();
};

QTermboxCellTest::QTermboxCellTest()
{
}

void QTermboxCellTest::multiplyTest()
{
	QTermboxCell *cell = new QTermboxCell(QChar('x'), QTermbox::White, QTermbox::Black);
	QList<QTermboxCell> other = cell->multiply(10);

	QCOMPARE(other.length(), 10);

	foreach (QTermboxCell item, other) {
		QVERIFY(*cell == item);
	}

	delete cell;
}

void QTermboxCellTest::containerTest()
{
	QTermboxCell *cell = new QTermboxCell(QChar('x'), QTermbox::White, QTermbox::Black);
	QTermboxCellContainer *container = QTermboxCellContainer::create(cell->multiply(10), 5, this);

	QCOMPARE(container->width(), 5l);
	QCOMPARE(container->height(), 2l);

	delete container;

	container = QTermboxCellContainer::create(cell->multiply(10), 2, this);

	QCOMPARE(container->width(), 2l);
	QCOMPARE(container->height(), 5l);

	delete container;
	delete cell;
}


void QTermboxCellTest::containerCopyTest()
{
	QTermboxCell *cell = new QTermboxCell(QChar('x'), QTermbox::White, QTermbox::Black);
	QTermboxCellContainer *container = QTermboxCellContainer::create(cell->multiply(10), 5, this);

	QCOMPARE(container->width(), 5l);
	QCOMPARE(container->height(), 2l);

	container = container->copy();

	QCOMPARE(container->width(), 5l);
	QCOMPARE(container->height(), 2l);

	delete container;
	delete cell;
}

void QTermboxCellTest::containerTestFail()
{
	QTermboxCell *cell = new QTermboxCell(QChar('x'), QTermbox::White, QTermbox::Black);
	QTermboxCellContainer *container = QTermboxCellContainer::create(cell->multiply(10), 7, this);

	QCOMPARE(container->width(), 7l);
	QCOMPARE(container->height(), 2l);

	delete container;
	delete cell;
}


void QTermboxCellTest::equalTest()
{
	QTermboxCell *cellA = new QTermboxCell(QChar('x'), QTermbox::White, QTermbox::Black);
	QTermboxCell *cellB = new QTermboxCell(QChar('x'), QTermbox::Green, QTermbox::Black);
	QTermboxCell *cellC = new QTermboxCell(QChar('x'), QTermbox::White, QTermbox::Black);

	QVERIFY(*cellA == *cellC);
	QVERIFY(*cellB != *cellA);
	QVERIFY(*cellB != *cellC);

	delete cellA;
	delete cellB;
	delete cellC;
}

DECLARE_TEST(QTermboxCellTest)

#include "tst_celltests.moc"
