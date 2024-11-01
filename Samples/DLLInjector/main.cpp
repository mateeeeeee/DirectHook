#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>


const wchar_t* ConvertCharToWChar(const char* charStr) 
{
	int bufferSize = MultiByteToWideChar(CP_ACP, 0, charStr, -1, nullptr, 0);
	if (bufferSize == 0) 
	{
		std::cerr << "Error in MultiByteToWideChar: " << GetLastError() << std::endl;
		return nullptr;
	}

	wchar_t* wideStr = new wchar_t[bufferSize];
	int result = MultiByteToWideChar(CP_ACP, 0, charStr, -1, wideStr, bufferSize);
	if (result == 0) 
	{
		std::cerr << "Error in MultiByteToWideChar: " << GetLastError() << std::endl;
		delete[] wideStr;
		return nullptr;
	}
	return wideStr;
}

DWORD GetProcessIDByName(const wchar_t* processName)
{
	DWORD processID = 0;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot != INVALID_HANDLE_VALUE) 
	{
		PROCESSENTRY32 processEntry = { sizeof(PROCESSENTRY32) };
		if (Process32First(hSnapshot, &processEntry)) 
		{
			do {
				if (wcscmp(processEntry.szExeFile, processName) == 0)
				{
					processID = processEntry.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnapshot, &processEntry));
		}
		CloseHandle(hSnapshot);
	}
	return processID;
}

bool InjectDLL(DWORD processID, const char* dllPath) 
{
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
	if (!hProcess) 
	{
		std::cerr << "Could not open process: " << GetLastError() << std::endl;
		return false;
	}

	SIZE_T pathLen = strlen(dllPath) + 1;
	LPVOID remoteMemory = VirtualAllocEx(hProcess, nullptr, pathLen, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	if (!remoteMemory) 
	{
		std::cerr << "Could not allocate memory in target process: " << GetLastError() << std::endl;
		CloseHandle(hProcess);
		return false;
	}

	if (!WriteProcessMemory(hProcess, remoteMemory, dllPath, pathLen, nullptr)) 
	{
		std::cerr << "Could not write to process memory: " << GetLastError() << std::endl;
		VirtualFreeEx(hProcess, remoteMemory, 0, MEM_RELEASE);
		CloseHandle(hProcess);
		return false;
	}

	HMODULE hKernel32 = GetModuleHandle(L"kernel32.dll");
	LPVOID loadLibraryAddr = GetProcAddress(hKernel32, "LoadLibraryA");
	if (!loadLibraryAddr) 
	{
		std::cerr << "Could not find LoadLibraryA address: " << GetLastError() << std::endl;
		VirtualFreeEx(hProcess, remoteMemory, 0, MEM_RELEASE);
		CloseHandle(hProcess);
		return false;
	}

	HANDLE hThread = CreateRemoteThread(hProcess, nullptr, 0, (LPTHREAD_START_ROUTINE)loadLibraryAddr, remoteMemory, 0, nullptr);
	if (!hThread) 
	{
		std::cerr << "Could not create remote thread: " << GetLastError() << std::endl;
		VirtualFreeEx(hProcess, remoteMemory, 0, MEM_RELEASE);
		CloseHandle(hProcess);
		return false;
	}

	WaitForSingleObject(hThread, INFINITE);

	VirtualFreeEx(hProcess, remoteMemory, 0, MEM_RELEASE);
	CloseHandle(hThread);
	CloseHandle(hProcess);

	std::cout << "DLL injected successfully." << std::endl;
	return true;
}

int main(int argc, char* argv[]) 
{
	if (argc != 3) 
	{
		std::cerr << "Usage: " << argv[0] << " <target_process_name> <dll_path>" << std::endl;
		return 1;
	}

	const char* targetProcessName = argv[1];
	const char* dllPath = argv[2];

	DWORD processID = GetProcessIDByName(ConvertCharToWChar(targetProcessName));
	if (!processID) 
	{
		std::cerr << "Process not found: " << targetProcessName << std::endl;
		return 1;
	}

	if (InjectDLL(processID, dllPath)) 
	{
		std::cout << "Injection succeeded!" << std::endl;
	}
	else 
	{
		std::cerr << "Injection failed." << std::endl;
	}

	return 0;
}