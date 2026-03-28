#pragma once

template<typename T>
inline void SafeRelease(T*& p)
{
	if (p) p->Release();
	p = nullptr;
}
