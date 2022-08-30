// .h
#ifndef TIMINGSYSWORKER_H
#define TIMINGSYSWORKER_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

#include<qthread.h>
class TimingSysWorker : public QObject
{
	Q_OBJECT
public:
	explicit TimingSysWorker(QObject *parent = nullptr);
	~TimingSysWorker();
	void setPortName(const QString& strName);
	void setBaudrate(int nBaudrate);
signals:
	void sig_recv(QByteArray ba);
	void serialOpenRes(int deviceId, bool);//���ڴ򿪽��
	public slots:
	//��ʼ�����򿪴���
	void slot_initSerial(int deviceId);
	void slot_readReady();
	void slot_sendcmd(QByteArray);

private:
	QSerialPort* m_pQSerialPort;
	//������
	QString m_strPortName;
	//������
	int m_nBaudrate;
	bool m_isOpen = false;
	QByteArray m_baBuff;
};

#endif // TIMINGSYSWORKER_H


