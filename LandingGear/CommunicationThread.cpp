#include "CommunicationThread.h"
#include "GearStatus.h"

#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
CommThread::CommThread(const std::string _ip, int _port)
{
	WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 2), &wsadata);
	c_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_addr.S_un.S_addr = inet_addr(_ip.c_str());
	saddr.sin_port = htons(_port);

	int n = connect(c_socket, (sockaddr*)&saddr, sizeof saddr);
	if (n != -1)
	{
		printf("connect succeed!  socket_c : %d \n connect return :%d\n", c_socket, n);
		m_isconnect = true;
	}
	else printf("connect failed\n");
}

int CommThread::getStatus(PlaneStatus& _ps)
{
	if (m_isconnect)
	{
		char buf[64] = { NULL };
		int  n = recv(c_socket, buf, 64, NULL);
		if (n > 0)
		{
			buf[16] = '\0';
			_ps.doorSta = atoi(&buf[6]);
			_ps.gearSta = atoi(&buf[15]);
			//std::cout << "door: " << _ps.doorSta << " gear: " << _ps.gearSta << std::endl;
			//std::cout << buf << std::endl;
			return true;
		}
		
	}
	else return false;
}

