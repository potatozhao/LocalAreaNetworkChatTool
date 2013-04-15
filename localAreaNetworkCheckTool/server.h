#include"stdafx.h"

int server()
{
	WORD wVersionRequested;
	WSADATA wsadata;
	int err;
	
	wVersionRequested = MAKEWORD(2,2);
	err = WSAStartup(wVersionRequested,&wsadata);
	if(err != 0)
	{
		std::cout<<"err is not exite"<<std::endl;
		return 0;
	}
	if(LOBYTE(wsadata.wVersion) != 2 || HIBYTE( wsadata.wVersion) != 2 )
	{
		WSACleanup();
		std::cout<<"we couldn't find a WSA"<<std::endl;
		return 0;
	}
	SOCKET sockSrv = socket(AF_INET, SOCK_DGRAM, 0);
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);
	bind(sockSrv,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));
	char sendBuf[100];
	char recvBuf[100];
	char tempBuf[200];
	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);
	while(1)
	{
		recvfrom(sockSrv,recvBuf,100,0,(SOCKADDR*)&addrClient,&len);
		if('q' == recvBuf[0])
		{
			sendto(sockSrv,"char end!",strlen("char end!")+1,0,(SOCKADDR*)&addrClient,len);
			std::cout<<"chat end/n";
			break;
		}
		sprintf(tempBuf,"%s say: %s", inet_ntoa(addrClient.sin_addr), recvBuf);
		printf("%s\n",tempBuf);
		//std::cout<<"Please input data:\n";
		//gets(sendBuf);
		//sendto(sockSrv,sendBuf,strlen(sendBuf)+1,0,(SOCKADDR*)&addrClient,len);
	}
	closesocket(sockSrv);
	WSACleanup();
	return 0;
}