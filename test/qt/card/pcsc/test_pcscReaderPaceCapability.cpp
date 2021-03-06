/*!
 * \brief Unit tests for \ref PcscReaderPaceCapability
 *
 * \copyright Copyright (c) 2014-2020 Governikus GmbH & Co. KG, Germany
 */

#include "PcscReaderPaceCapability.h"

#include "LogHandler.h"
#include "TestFileHelper.h"

#include <QtCore>
#include <QtTest>


using namespace governikus;


class test_pcscReaderPaceCapability
	: public QObject
{
	Q_OBJECT

	private:
		int getCapabilityCount(const PcscReaderPaceCapability& pPcscReaderPaceCapability)
		{
			int count = 0;
			const auto list = Enum<PaceCapabilityId>::getList();
			for (PaceCapabilityId capability : list)
			{
				if (pPcscReaderPaceCapability.contains(capability))
				{
					count++;
				}
			}
			return count;
		}

	private Q_SLOTS:
		void initTestCase()
		{
			Env::getSingleton<LogHandler>()->init();
		}


		void cleanup()
		{
			Env::getSingleton<LogHandler>()->resetBacklog();
		}


		void capabilitiesEmpty()
		{
			PcscReaderPaceCapability paceCapa(nullptr);

			QSignalSpy spyLog(Env::getSingleton<LogHandler>(), &LogHandler::fireLog);
			qDebug() << paceCapa;
			QVERIFY(TestFileHelper::containsLog(spyLog, QLatin1String("()")));

			QCOMPARE(getCapabilityCount(paceCapa), 0);
		}


		void capabilitiesCyberjackStandard()
		{
			QByteArray capabilitiesTLV = QByteArray::fromHex("00000000010060");
			PcscReaderPaceCapability paceCapa(capabilitiesTLV.constData(), static_cast<PCSC_INT>(capabilitiesTLV.length()));

			QSignalSpy spyLog(Env::getSingleton<LogHandler>(), &LogHandler::fireLog);
			qDebug() << paceCapa;
			QVERIFY(TestFileHelper::containsLog(spyLog, QLatin1String("(EID, GENERIC)")));

			QCOMPARE(getCapabilityCount(paceCapa), 2);
			QVERIFY(paceCapa.contains(PaceCapabilityId::EID));
			QVERIFY(paceCapa.contains(PaceCapabilityId::GENERIC));
		}


		void capabilitiesCyberjackKomfort()
		{
			QByteArray capabilitiesTLV = QByteArray::fromHex("00000000010070");
			PcscReaderPaceCapability paceCapa(capabilitiesTLV.constData(), static_cast<PCSC_INT>(capabilitiesTLV.length()));

			QSignalSpy spyLog(Env::getSingleton<LogHandler>(), &LogHandler::fireLog);
			qDebug() << paceCapa;
			QVERIFY(TestFileHelper::containsLog(spyLog, QLatin1String("(ESIGN, EID, GENERIC)")));

			QCOMPARE(getCapabilityCount(paceCapa), 3);
			QVERIFY(paceCapa.contains(PaceCapabilityId::EID));
			QVERIFY(paceCapa.contains(PaceCapabilityId::ESIGN));
			QVERIFY(paceCapa.contains(PaceCapabilityId::GENERIC));
		}


};

QTEST_GUILESS_MAIN(test_pcscReaderPaceCapability)
#include "test_pcscReaderPaceCapability.moc"
