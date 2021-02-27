#pragma once
#include <QWidget>
#include <QUdpSocket>


class ATM_SendSocket
{
	QString _AvatarData;
	QString _statusCode; //״̬��Ϣ
	QUdpSocket *_autoMapUdpSocket; //�׽���
	QHostAddress _clientIp=QHostAddress::LocalHost; //�ͻ���ip
	quint16 _clientPort = 23333; //�ͻ���port
	int _x = 0;
	int _y = 0;
	double _orientationAngle = 0;
	int _uid = 0;

public:
	ATM_SendSocket();
	~ATM_SendSocket();
	void setPort(quint16 port);
	void AutoMapUdpSocketSend(int x,int y,double orientationAngle,int uid);
	//void SocketSend(QString sendStr, QHostAddress targetIp, quint16 targetPort); //��������,������ָ��Ŀ�귢�ͣ����߹㲥

};

