#include"stdafx.h"
int client()
{
	WORD wVersionRequested;
	WSADATA wsadata;
	int err;
	wVersionRequested = MAKEWORD( 2, 2 );
	err = WSAStartup( wVersionRequested, &wsadata );
	if ( err != 0 )
	{
		return 0;
	}
	if(LOBYTE(wsadata.wVersion) != 2 || HIBYTE( wsadata.wVersion) != 2 )
	{
		WSACleanup();
		std::cout<<"we couldn't find a WSA"<<std::endl;
		return 0;
	}
	SOCKET sockClient = socket(AF_INET,SOCK_DGRAM,0);
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);
	char sendBuf[100];
	char recvBuf[100];
	char tempBuf[200];
	int len=sizeof(SOCKADDR);
	while(1)
	{
		printf("Please input data:\n");
		gets(sendBuf);
		int p = sendto(sockClient,sendBuf,strlen(sendBuf)+1,0,(SOCKADDR*)&addrSrv, len);
		//std::cout<<p<<std::endl;
		/*if(p != -1)
		{
			recvfrom(sockClient, recvBuf,100,0,(SOCKADDR*)&addrSrv, &len);
		}*/
		if(('q' == sendBuf[0])&&(strlen(sendBuf) == 1))
		{
			sendto(sockClient,"char end!",strlen("char end!")+1,0,(SOCKADDR*)&addrSrv,len);
			std::cout<<"chat end/n";
			break;
		}
		//sprintf(tempBuf,"%s say: %s", inet_ntoa(addrSrv.sin_addr), recvBuf);
		//printf("%s\n",tempBuf);
	}
	closesocket(sockClient);
	WSACleanup();
	return 0;
}