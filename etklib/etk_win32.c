#include "etk_win32.h"
size_t etk_get_relative_time(void){
	FILETIME        ft;
	LARGE_INTEGER   li;
	__int64         t;

	GetSystemTimeAsFileTime(&ft);
	li.LowPart  = ft.dwLowDateTime;
	li.HighPart = ft.dwHighDateTime;
	t  = li.QuadPart;       /* In 100-nanosecond intervals */
	t /= 10;                /* In microseconds */
	return t/1000;
}

int win32_socketpair(SOCKET socks[2])
{
    int e;
    DWORD flags = 0;
    SOCKET listener;
    struct sockaddr_in addr;
    int addrlen = sizeof(addr);

    if (socks == 0) {
      WSASetLastError(WSAEINVAL);
      return SOCKET_ERROR;
    }

    socks[0] = socks[1] = INVALID_SOCKET;
    if ((listener = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) 
        return SOCKET_ERROR;

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(0x7f000001);
    addr.sin_port = 0;

    e = bind(listener, (const struct sockaddr*) &addr, sizeof(addr));
    if (e == SOCKET_ERROR) {
        e = WSAGetLastError();
    	closesocket(listener);
        WSASetLastError(e);
        return SOCKET_ERROR;
    }

    e = getsockname(listener, (struct sockaddr*) &addr, &addrlen);
    if (e == SOCKET_ERROR) {
        e = WSAGetLastError();
    	closesocket(listener);
        WSASetLastError(e);
        return SOCKET_ERROR;
    }

    do {
        if (listen(listener, 1) == SOCKET_ERROR)                      break;
        if ((socks[0] = socket(AF_INET, SOCK_STREAM, 0))
                == INVALID_SOCKET)                                    break;
        if (connect(socks[0], (const struct sockaddr*) &addr,
                    sizeof(addr)) == SOCKET_ERROR)                    break;
        if ((socks[1] = accept(listener, NULL, NULL))
                == INVALID_SOCKET)                                    break;
        closesocket(listener);
        return 0;
    } while (0);
    e = WSAGetLastError();
    closesocket(listener);
    closesocket(socks[0]);
    closesocket(socks[1]);
    WSASetLastError(e);

    return SOCKET_ERROR;
}

int etk_platform_init(int argc, char** argv){
	int Ret = 0;
	char* p = NULL;
	WSADATA wsaData = {0};
	if ((Ret = WSAStartup(MAKEWORD(2,2), &wsaData)) != 0){
		//assert(!"WSAStartup failed with error %d\n");
		dbg_printf("WSAStartup failed with error %d\n");
		return 0;
	}

	return 0;
}

void etk_platform_deinit(void){
	if (WSACleanup() == SOCKET_ERROR)
	{
		//etk_logd("WSACleanup failed with error %d\n", WSAGetLastError());
	}

	return;
}
