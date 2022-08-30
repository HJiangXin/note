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
		qDebug() << QStringLiteral("串口%1不存在").arg(m_strPortName);
	}
	if (m_pQSerialPort)
	{
		//m_pQSerialPort->setDataTerminalReady(true);
		//m_pQSerialPort->setRequestToSend(true);//设置422串口全双工通信，这个串口默认不是全双工，导致只能收，不能发
		
		connect(m_pQSerialPort, &QSerialPort::readyRead, this, &TimingSysWorker::slot_readReady);
		//connect(m_pQSerialPort, &QSerialPort::readyRead, [](){qDebug() << "nihao" << endl;});
		
		//设置波特率
		m_pQSerialPort->setBaudRate(m_nBaudrate, QSerialPort::AllDirections);
		//设置数据位
		m_pQSerialPort->setDataBits(QSerialPort::Data8);
		//设置校验位
		m_pQSerialPort->setParity(QSerialPort::NoParity);
		//设置停止位
		m_pQSerialPort->setStopBits(QSerialPort::OneStop);
		//流量控制
		m_pQSerialPort->setFlowControl(QSerialPort::NoFlowControl);
		
		bool bRet = m_pQSerialPort->open(QIODevice::ReadWrite);//打开串口并选择读写模式
		if (bRet)
		{
			m_isOpen = true;
			m_pQSerialPort->setRequestToSend(true);//设置串口全双工通信，这个串口默认不是全双工，导致只能收，不能发。
			qDebug()<<"Open serial "<<m_strPortName << "successfully";
		}
		else {
			//qDebug()<<"Open serial "<<m_strPortName << "failed";
			//serialOpenRes(deviceId,false);//打开失败，则重新绑定
		}
	}
}

void TimingSysWorker::slot_readReady()
{

	//先缓存
	// 存储转换类型后的数据
	QByteArray ba = m_pQSerialPort->readAll();
	qDebug() << ba << endl;
	int num = 0;
	for (int i = 1; i < 5; i++)
	{
		num += (int)ba.at(i);
	}
	qDebug() <<  num << endl;
	//判断缓存中第一个字符是不是$,最后一个字符是不是换行符，如果二者皆成立表示收到了一个完整帧
	ba.clear();
}

void TimingSysWorker::slot_sendcmd(QByteArray ba)
{
	m_pQSerialPort->write(ba);
	m_pQSerialPort->flush();
}
