#include <windows.h>
#include <stdio.h>

int main(void) {
	LPCTSTR pipename = "\\\\.\\pipe\\labpipe";
	HANDLE hNamedPipe;
	DWORD szAddress;
	DWORD cbRead, cbWritten;
	char* msg;
	BOOL Success;

	printf("Creating pipe...");
	hNamedPipe = CreateNamedPipe(pipename, PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, PIPE_UNLIMITED_INSTANCES,
		sizeof(DWORD), sizeof(DWORD), 100, NULL);
	if (hNamedPipe == INVALID_HANDLE_VALUE) {
		printf("Fail!\n");
		system("pause");
		return -1;
	}

	printf("Connecting to pipe...");
	ConnectNamedPipe(hNamedPipe, NULL);

	printf("Reading from pipe...");
	Success = ReadFile(hNamedPipe, &szAddress, sizeof(szAddress), &cbRead, NULL);
	if (Success == FALSE) {
		printf("Fail!\n");
		system("pause");
		return -1;
	}

	printf("String: ");
	msg = (char*)szAddress;
	printf_s("%s\n", msg);

	printf("Sending answer to Proccess A...");
	Success = WriteFile(hNamedPipe, &szAddress, sizeof(szAddress), &cbWritten, NULL);
	if (Success == FALSE) {
		printf("Fail!\n");
		system("pause");
		return -1;
	}

	printf("Disconnecting from named pipe...");
	Success = DisconnectNamedPipe(hNamedPipe);
	if (Success == FALSE) {
		printf("Fail!\n");
		system("pause");
		return -1;
	}

	printf("Closing named pipe...");
	Success = CloseHandle(hNamedPipe);
	if (Success == FALSE) {
		printf("Fail!\n");
		system("pause");
		return -1;
	}

	printf("Process B was finished...\n");
	system("pause");
	return 0;
}