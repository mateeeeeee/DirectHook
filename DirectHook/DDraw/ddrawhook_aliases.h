#pragma once
#define DIRECTDRAW_VERSION 0x0700
#include <ddraw.h>

namespace directhook::ddraw
{
	using PFN_DDrawDevice_QueryInterface = HRESULT(WINAPI*)(IDirectDraw7*, REFIID, LPVOID*);
	using PFN_DDrawDevice_AddRef = ULONG(WINAPI*)(IDirectDraw7*);
	using PFN_DDrawDevice_Release = ULONG(WINAPI*)(IDirectDraw7*);
	using PFN_DDrawDevice_CreateSurface = HRESULT(WINAPI*)(IDirectDraw7*, LPDDSURFACEDESC2, LPDIRECTDRAWSURFACE7*, IUnknown*);
	using PFN_DDrawDevice_DuplicateSurface = HRESULT(WINAPI*)(IDirectDraw7*, LPDIRECTDRAWSURFACE7, LPDIRECTDRAWSURFACE7*);
	using PFN_DDrawDevice_EnumDisplayModes = HRESULT(WINAPI*)(IDirectDraw7*, DWORD, LPDDSURFACEDESC2, LPVOID, LPDDENUMMODESCALLBACK2);
	using PFN_DDrawDevice_EnumSurfaces = HRESULT(WINAPI*)(IDirectDraw7*, DWORD, LPDIRECTDRAWSURFACE7, LPVOID, LPDDENUMSURFACESCALLBACK7);
	using PFN_DDrawDevice_ExitFullscreen = HRESULT(WINAPI*)(IDirectDraw7*);
	using PFN_DDrawDevice_GetAvailableVidMem = HRESULT(WINAPI*)(IDirectDraw7*, LPDDSCAPS2, LPDWORD, LPDWORD);
	using PFN_DDrawDevice_GetDeviceIdentifier = HRESULT(WINAPI*)(IDirectDraw7*, LPDDDEVICEIDENTIFIER2, DWORD);
	using PFN_DDrawDevice_GetDisplayMode = HRESULT(WINAPI*)(IDirectDraw7*, LPDDSURFACEDESC2);
	using PFN_DDrawDevice_GetFourCCCodes = HRESULT(WINAPI*)(IDirectDraw7*, LPDWORD, LPDWORD);
	using PFN_DDrawDevice_GetGDISurface = HRESULT(WINAPI*)(IDirectDraw7*, LPDIRECTDRAWSURFACE7*);
	using PFN_DDrawDevice_GetMonitorFrequency = HRESULT(WINAPI*)(IDirectDraw7*, LPDWORD);
	using PFN_DDrawDevice_GetScanLine = HRESULT(WINAPI*)(IDirectDraw7*, LPDWORD);
	using PFN_DDrawDevice_GetVerticalBlankStatus = HRESULT(WINAPI*)(IDirectDraw7*, LPBOOL);
	using PFN_DDrawDevice_Initialize = HRESULT(WINAPI*)(IDirectDraw7*, GUID*);
	using PFN_DDrawDevice_RestoreDisplayMode = HRESULT(WINAPI*)(IDirectDraw7*);
	using PFN_DDrawDevice_SetCooperativeLevel = HRESULT(WINAPI*)(IDirectDraw7*, HWND, DWORD);
	using PFN_DDrawDevice_SetDisplayMode = HRESULT(WINAPI*)(IDirectDraw7*, DWORD, DWORD, DWORD, DWORD, DWORD);
	using PFN_DDrawDevice_WaitForVerticalBlank = HRESULT(WINAPI*)(IDirectDraw7*, DWORD, HANDLE);

	using PFN_DDrawSurface_QueryInterface = HRESULT(WINAPI*)(IDirectDrawSurface7*, REFIID, LPVOID*);
	using PFN_DDrawSurface_AddRef = ULONG(WINAPI*)(IDirectDrawSurface7*);
	using PFN_DDrawSurface_Release = ULONG(WINAPI*)(IDirectDrawSurface7*);
	using PFN_DDrawSurface_AddAttachedSurface = HRESULT(WINAPI*)(IDirectDrawSurface7*, LPDIRECTDRAWSURFACE7);
	using PFN_DDrawSurface_AddOverlayDirtyRect = HRESULT(WINAPI*)(IDirectDrawSurface7*, LPCRECT);
	using PFN_DDrawSurface_Blt = HRESULT(WINAPI*)(IDirectDrawSurface7*, LPCRECT, IDirectDrawSurface7*, LPCRECT, DWORD, LPDDBLTFX);
	using PFN_DDrawSurface_BltBatch = HRESULT(WINAPI*)(IDirectDrawSurface7*, LPDDBLTBATCH, DWORD);
	using PFN_DDrawSurface_BltFast = HRESULT(WINAPI*)(IDirectDrawSurface7*, DWORD, DWORD, IDirectDrawSurface7*, LPCRECT, DWORD);
	using PFN_DDrawSurface_DeleteAttachedSurface = HRESULT(WINAPI*)(IDirectDrawSurface7*, DWORD, LPDIRECTDRAWSURFACE7);
	using PFN_DDrawSurface_EnumAttachedSurfaces = HRESULT(WINAPI*)(IDirectDrawSurface7*, LPVOID, LPDDENUMSURFACESCALLBACK7);
	using PFN_DDrawSurface_EnumOverlayZOrders = HRESULT(WINAPI*)(IDirectDrawSurface7*, DWORD, LPVOID, LPDDENUMSURFACESCALLBACK7);
	using PFN_DDrawSurface_Flip = HRESULT(WINAPI*)(IDirectDrawSurface7*, IDirectDrawSurface7*, DWORD);
	using PFN_DDrawSurface_GetAttachedSurface = HRESULT(WINAPI*)(IDirectDrawSurface7*, LPDDSCAPS2, LPDIRECTDRAWSURFACE7*);
	using PFN_DDrawSurface_GetBltStatus = HRESULT(WINAPI*)(IDirectDrawSurface7*, DWORD);
	using PFN_DDrawSurface_GetCaps = HRESULT(WINAPI*)(IDirectDrawSurface7*, LPDDSCAPS2);
	using PFN_DDrawSurface_GetClipper = HRESULT(WINAPI*)(IDirectDrawSurface7*, LPDIRECTDRAWCLIPPER*);
	using PFN_DDrawSurface_GetColorKey = HRESULT(WINAPI*)(IDirectDrawSurface7*, DWORD, LPDDCOLORKEY);
	using PFN_DDrawSurface_GetDC = HRESULT(WINAPI*)(IDirectDrawSurface7*, HDC*);
	using PFN_DDrawSurface_GetDesc = HRESULT(WINAPI*)(IDirectDrawSurface7*, LPDDSURFACEDESC2);
	using PFN_DDrawSurface_GetSurfaceDesc = HRESULT(WINAPI*)(IDirectDrawSurface7*, LPDDSURFACEDESC2);
	using PFN_DDrawSurface_Lock = HRESULT(WINAPI*)(IDirectDrawSurface7*, LPCRECT, LPDDSURFACEDESC2, DWORD, HANDLE);
	using PFN_DDrawSurface_ReleaseDC = HRESULT(WINAPI*)(IDirectDrawSurface7*, HDC);
	using PFN_DDrawSurface_SetClipper = HRESULT(WINAPI*)(IDirectDrawSurface7*, IDirectDrawClipper*);
	using PFN_DDrawSurface_SetColorKey = HRESULT(WINAPI*)(IDirectDrawSurface7*, DWORD, LPDDCOLORKEY);
	using PFN_DDrawSurface_SetSurfaceDesc = HRESULT(WINAPI*)(IDirectDrawSurface7*, LPDDSURFACEDESC2, DWORD);
	using PFN_DDrawSurface_Unlock = HRESULT(WINAPI*)(IDirectDrawSurface7*, LPVOID);
	using PFN_DDrawSurface_UnlockRect = HRESULT(WINAPI*)(IDirectDrawSurface7*);

	using PFN_DDrawClipper_QueryInterface = HRESULT(WINAPI*)(IDirectDrawClipper*, REFIID, LPVOID*);
	using PFN_DDrawClipper_AddRef = ULONG(WINAPI*)(IDirectDrawClipper*);
	using PFN_DDrawClipper_Release = ULONG(WINAPI*)(IDirectDrawClipper*);
	using PFN_DDrawClipper_SetHWnd = HRESULT(WINAPI*)(IDirectDrawClipper*, DWORD, HWND);
	using PFN_DDrawClipper_GetHWnd = HRESULT(WINAPI*)(IDirectDrawClipper*, HWND*);
	using PFN_DDrawClipper_AddClipList = HRESULT(WINAPI*)(IDirectDrawClipper*, LPRGNDATA, DWORD);
	using PFN_DDrawClipper_GetClipList = HRESULT(WINAPI*)(IDirectDrawClipper*, LPRECT, LPRGNDATA, LPDWORD);
	using PFN_DDrawClipper_GetOverlap = HRESULT(WINAPI*)(IDirectDrawClipper*, LPDWORD);
}