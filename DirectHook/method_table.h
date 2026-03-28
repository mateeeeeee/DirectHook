#pragma once
#include <windows.h>
#include <cassert>

typedef struct _DH_METHOD_TABLE
{
	LPVOID* lpMethods;
	UINT    cMethods;
	UINT    cCapacity;
} DH_METHOD_TABLE, *PDH_METHOD_TABLE;

inline VOID DH_MethodTableGrow(PDH_METHOD_TABLE pTable, UINT cMinimum)
{
	if (pTable->cCapacity >= cMinimum)
	{
		return;
	}

	UINT cNew = pTable->cCapacity ? pTable->cCapacity * 2 : 16;
	while (cNew < cMinimum)
	{
		cNew *= 2;
	}

	HANDLE hHeap = GetProcessHeap();
	LPVOID* lpNew = pTable->lpMethods
		? (LPVOID*)HeapReAlloc(hHeap, 0, pTable->lpMethods, cNew * sizeof(LPVOID))
		: (LPVOID*)HeapAlloc(hHeap, 0, cNew * sizeof(LPVOID));

	assert(lpNew != nullptr);
	pTable->lpMethods = lpNew;
	pTable->cCapacity = cNew;
}

inline VOID WINAPI DH_MethodTableInit(PDH_METHOD_TABLE pTable)
{
	pTable->lpMethods = nullptr;
	pTable->cMethods = 0;
	pTable->cCapacity = 0;
}

inline VOID WINAPI DH_MethodTableFree(PDH_METHOD_TABLE pTable)
{
	if (pTable->lpMethods)
	{
		HeapFree(GetProcessHeap(), 0, pTable->lpMethods);
	}
	pTable->lpMethods = nullptr;
	pTable->cMethods = 0;
	pTable->cCapacity = 0;
}

inline VOID WINAPI DH_MethodTableClear(PDH_METHOD_TABLE pTable)
{
	pTable->cMethods = 0;
}

inline VOID WINAPI DH_MethodTableAddEntry(PDH_METHOD_TABLE pTable, LPVOID lpEntry)
{
	DH_MethodTableGrow(pTable, pTable->cMethods + 1);
	pTable->lpMethods[pTable->cMethods++] = lpEntry;
}

inline VOID WINAPI DH_MethodTableAddEntriesRaw(PDH_METHOD_TABLE pTable, LPVOID lpComObject, UINT cEntries, UINT cMaxEntries)
{
	if (cMaxEntries < cEntries)
	{
		cMaxEntries = cEntries;
	}

	DH_MethodTableGrow(pTable, pTable->cMethods + cMaxEntries);

	LPVOID* lpVTable = *(LPVOID**)lpComObject;
	for (UINT i = 0; i < cEntries; ++i)
	{
		pTable->lpMethods[pTable->cMethods++] = lpVTable[i];
	}
	for (UINT i = cEntries; i < cMaxEntries; ++i)
	{
		pTable->lpMethods[pTable->cMethods++] = nullptr;
	}
}

inline BOOL WINAPI DH_MethodTableIsValidIndex(const DH_METHOD_TABLE* pTable, UINT uIndex)
{
	return uIndex < pTable->cMethods && pTable->lpMethods[uIndex] != nullptr;
}

inline LPVOID WINAPI DH_MethodTableGet(const DH_METHOD_TABLE* pTable, UINT uIndex)
{
	return pTable->lpMethods[uIndex];
}

template<typename T>
inline VOID DH_MethodTableAddEntries(PDH_METHOD_TABLE pTable, T* lpComObject, UINT cEntries, UINT cMaxEntries = 0)
{
	DH_MethodTableAddEntriesRaw(pTable, (LPVOID)lpComObject, cEntries, cMaxEntries);
}
