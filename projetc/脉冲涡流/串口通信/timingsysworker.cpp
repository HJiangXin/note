// .cpp
#include "TimingSysWorker.h"
#include <QDebug>

TimingSysWorker::TimingSysWorker(QObject *parent) : QObject(parent)
{
	m_pQSerialPort = nullptr;
	m_nBaudrate = 115200;
	m_strPortName = "COM3";
}

TimingSysWorker::~TimingSysWorker()
{
	if (m_pQSerialPort)
	{
		if (m_pQSerialPort->isOpen()){
			m_pQSerialPort->close();
			delete m_pQSerialPort;
			m_pQSerialPort = nullptr;
		}
	}
}

void TimingSysWorker::setBaudrate(int nBaudrate)
{
	m_nBaudrate = nBaudrate;
}

void TimingSysWorker::setPortName(const QString &strName)
{
	m_strPortName = strName;
}

void TimingSysWorker::slot_initSerial(int deviceId)
{
	if (nullptr == m_pQSerialPort)
	{
		m_pQSerialPort = new QSerialPort;
	}
	bool bExist = false;
	foreach(const QSerialPortInfo&info, QSerialPortInfo::availablePorts())
	{
		if (info.portName() == m_strPortName)
		{
			m_pQSerialPort->setPortName(info.systemLocation());
			bExist = true;
		}
	}
	
	if (!bExist)
	{
		qDebug() << QStringLiteral("����%1������").arg(m_strPortName);
	}
	if (m_pQSerialPort)
	{
		//m_pQSerialPort->setDataTerminalReady(true);
		//m_pQSerialPort->setRequestToSend(true);//����422����ȫ˫��ͨ�ţ��������Ĭ�ϲ���ȫ˫��������ֻ���գ����ܷ�
		
		connect(m_pQSerialPort, &QSerialPort::readyRead, this, &TimingSysWorker::slot_readReady);
		//connect(m_pQSerialPort, &QSerialPort::readyRead, [](){qDebug() << "nihao" << endl;});
		
		//���ò�����
		m_pQSerialPort->setBaudRate(m_nBaudrate, QSerialPort::AllDirections);
		//��������λ
		m_pQSerialPort->setDataBits(QSerialPort::Data8);
		//����У��λ
		m_pQSerialPort->setParity(QSerialPort::NoParity);
		//����ֹͣλ
		m_pQSerialPort->setStopBits(QSerialPort::OneStop);
		//��������
		m_pQSerialPort->setFlowControl(QSerialPort::NoFlowControl);
		
		bool bRet = m_pQSerialPort->open(QIODevice::ReadWrite);//�򿪴��ڲ�ѡ���дģʽ
		if (bRet)
		{
			m_isOpen = true;
			m_pQSerialPort->setRequestToSend(true);//���ô���ȫ˫��ͨ�ţ��������Ĭ�ϲ���ȫ˫��������ֻ���գ����ܷ���
			qDebug()<<"Open serial "<<m_strPortName << "successfully";
		}
		else {
			//qDebug()<<"Open serial "<<m_strPortName << "failed";
			//serialOpenRes(deviceId,false);//��ʧ�ܣ������°�
		}
	}
}

void TimingSysWorker::slot_readReady()
{

	//�Ȼ���
	// �洢ת�����ͺ������
	QByteArray ba = m_pQSerialPort->readAll();
	qDebug() << ba << endl;
	int num = 0;
	for (int i = 1; i < 5; i++)
	{
		num += (int)ba.at(i);
	}
	qDebug() <<  num << endl;
	//�жϻ����е�һ���ַ��ǲ���$,���һ���ַ��ǲ��ǻ��з���������߽Գ�����ʾ�յ���һ������֡
	ba.clear();
}

void TimingSysWorker::slot_sendcmd(QByteArray ba)
{
	m_pQSerialPort->write(ba);
	m_pQSerialPort->flush();
}
