#pragma once
#include <string>
#include <WinSock2.h>
#include <iostream>
struct PlaneStatus {
	int gearSta;
	int doorSta;
};

class CommThread {
public:
	CommThread(const std::string _ip,int _port);
	~CommThread()
	{

	}
	int getStatus(PlaneStatus& _ps);
private:
	std::string m_IP;
	int m_port;
	SOCKET c_socket;
	bool m_isconnect = false;
};