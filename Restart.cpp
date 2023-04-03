// Restart.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <Windows.h>

int main()
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;

	SetConsoleTitle(L"Restarting");

	std::cout << "Loading";
	for (int i = 0; i < 10; i++)
	{
		std::cout << ".";
		Sleep(500);
	}

	Beep(500, 100);
	Beep(500, 100);
	Beep(500, 600);
	Beep(500, 100);
	Beep(500, 100);


	   if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
	   {
	   	std::cout << "OpenProcessToken() failed: " << GetLastError() << std::endl;
	   	return 1;
	   }

	   LookupPrivilegeValue (NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);

	   tkp.PrivilegeCount = 1;  // one privilege to set
	   tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	   AdjustTokenPrivileges (hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES) NULL, 0);

	   if (GetLastError() != ERROR_SUCCESS)
	   {
	   	std::cout << "AdjustTokenPrivileges() failed: " << GetLastError() << std::endl;
	   	return 1;
	   }

	   if (!ExitWindowsEx(EWX_REBOOT | EWX_FORCE, SHTDN_REASON_MAJOR_OPERATINGSYSTEM | SHTDN_REASON_MINOR_UPGRADE | SHTDN_REASON_FLAG_PLANNED));
}
