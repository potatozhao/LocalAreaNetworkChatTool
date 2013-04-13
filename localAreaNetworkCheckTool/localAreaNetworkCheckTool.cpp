// localAreaNetworkCheckTool.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "server.h"
#include "client.h"
DWORD WINAPI Fun1Proc(LPVOID lpParameter);
DWORD WINAPI Fun2Proc(LPVOID lpParameter);

int _tmain(int argc, _TCHAR* argv[])
{

	//server();
	//client();
	HANDLE hThread1;
	//HANDLE hThread2;
	hThread1=CreateThread(NULL,0,Fun1Proc,NULL,0,NULL);
	//hThread2=CreateThread(NULL,0,Fun2Proc,NULL,0,NULL);
	client();
	CloseHandle(hThread1);
    //CloseHandle(hThread2);
	return 0;
}
DWORD WINAPI Fun1Proc(LPVOID lpParameter)
{
	server();
	return 0;
}
//DWORD WINAPI Fun2Proc(LPVOID lpParameter)
//{
//	client();
//	return 0;
//}