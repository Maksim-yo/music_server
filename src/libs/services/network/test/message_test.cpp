#include <QByteArray>
#include <QTest>

#include "services/network/message.h"


using namespace Network;


class TestMessage: public QObject{

    Q_OBJECT

private slots:

    void testMessageSerialization(){

        message msgSerialize1{MessageType::Ping};
        message msgDeserialize1;
        message* msgSerialize2 = new message{MessageType::Ping};
        message* msgDeserialize2 = new message();
        QByteArray serialized_data1;
        QByteArray serialized_data2;
        QByteArray test;

        {
            QDataStream data_stream(&serialized_data1, QIODevice::ReadWrite);
            data_stream << msgSerialize1;
        }

        {
            QDataStream data_stream(&serialized_data1, QIODevice::ReadWrite);
            data_stream >> msgDeserialize1;
        }

        {
            QDataStream data_stream2(&serialized_data2, QIODevice::ReadWrite);
            data_stream2 << msgSerialize2;
        }

        {
            QDataStream data_stream2(&serialized_data2, QIODevice::ReadWrite);
            data_stream2 >> msgDeserialize2;
        }


        QVERIFY(serialized_data1 == serialized_data2);
        QVERIFY(msgSerialize1.get_type() == msgDeserialize1.get_type());
        QVERIFY(msgSerialize2->get_type() == msgDeserialize2->get_type());


    }


    void testMessageSize(){


        int messageTypeSize = sizeof(std::underlying_type<MessageType>::type);
        message msg{MessageType::Ping};
        QVERIFY(msg.get_size() == 16 + messageTypeSize);

        ping_message msg2;
        QVERIFY(msg2.get_size() == 16 + messageTypeSize);

        header head{MessageType::Ping};
        QVERIFY(head.get_size() == 8 + messageTypeSize);

    }


};



QTEST_MAIN(TestMessage)
#include "message_test.moc"

