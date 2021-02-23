#include "ATM_SendSocket.h"

ATM_SendSocket::ATM_SendSocket()
{
	_autoMapUdpSocket = new QUdpSocket();
}

ATM_SendSocket::~ATM_SendSocket()
{
	delete _autoMapUdpSocket;
}

void ATM_SendSocket::setPort(quint16 port)
{
	_clientPort = port;
}

void ATM_SendSocket::AutoMapUdpSocketSend(int x, int y, double orientationAngle)
{
	if (_x == x && _y == y && _orientationAngle == orientationAngle)
	{
		return;
	}
	_x = x;
	_y = y;
	_orientationAngle = orientationAngle;

	_AvatarData.clear();
	_AvatarData.append(QString::number(x));
	_AvatarData.append(" ");
	_AvatarData.append(QString::number(y));
	_AvatarData.append(" ");
	_AvatarData.append(QString::number(orientationAngle));
	//_AvatarData.append("\n");

	_statusCode = _autoMapUdpSocket->writeDatagram(_AvatarData.toUtf8(), QHostAddress::LocalHost/*_clientIp*/, _clientPort);
	//if()
	
}

