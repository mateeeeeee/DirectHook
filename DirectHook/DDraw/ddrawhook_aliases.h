#pragma once
#define DIRECTDRAW_VERSION 0x0700
#include <ddraw.h>

// IDirectDraw7
using PFN_DDRAW_Device_QueryInterface = HRESULT(WINAPI*)(IDirectDraw7*, REFIID, LPVOID*);
using PFN_DDRAW_Device_AddRef = ULONG(WINAPI*)(IDirectDraw7*);
using PFN_DDRAW_Device_Release = ULONG(WINAPI*)(IDirectDraw7*);
using PFN_DDRAW_Device_Compact = HRESULT(WINAPI*)(IDirectDraw7*);
using PFN_DDRAW_Device_CreateClipper = HRESULT(WINAPI*)(IDirectDraw7*, DWORD, LPDIRECTDRAWCLIPPER*, IUnknown*);
using PFN_DDRAW_Device_CreatePalette = HRESULT(WINAPI*)(IDirectDraw7*, DWORD, LPPALETTEENTRY, LPDIRECTDRAWPALETTE*, IUnknown*);
using PFN_DDRAW_Device_CreateSurface = HRESULT(WINAPI*)(IDirectDraw7*, LPDDSURFACEDESC2, LPDIRECTDRAWSURFACE7*, IUnknown*);
using PFN_DDRAW_Device_DuplicateSurface = HRESULT(WINAPI*)(IDirectDraw7*, LPDIRECTDRAWSURFACE7, LPDIRECTDRAWSURFACE7*);
using PFN_DDRAW_Device_EnumDisplayModes = HRESULT(WINAPI*)(IDirectDraw7*, DWORD, LPDDSURFACEDESC2, LPVOID, LPDDENUMMODESCALLBACK2);
using PFN_DDRAW_Device_EnumSurfaces = HRESULT(WINAPI*)(IDirectDraw7*, DWORD, LPDDSURFACEDESC2, LPVOID, LPDDENUMSURFACESCALLBACK7);
using PFN_DDRAW_Device_FlipToGDISurface = HRESULT(WINAPI*)(IDirectDraw7*);
using PFN_DDRAW_Device_GetCaps = HRESULT(WINAPI*)(IDirectDraw7*, LPDDCAPS, LPDDCAPS);
using PFN_DDRAW_Device_GetDisplayMode = HRESULT(WINAPI*)(IDirectDraw7*, LPDDSURFACEDESC2);
using PFN_DDRAW_Device_GetFourCCCodes = HRESULT(WINAPI*)(IDirectDraw7*, LPDWORD, LPDWORD);
using PFN_DDRAW_Device_GetGDISurface = HRESULT(WINAPI*)(IDirectDraw7*, LPDIRECTDRAWSURFACE7*);
using PFN_DDRAW_Device_GetMonitorFrequency = HRESULT(WINAPI*)(IDirectDraw7*, LPDWORD);
using PFN_DDRAW_Device_GetScanLine = HRESULT(WINAPI*)(IDirectDraw7*, LPDWORD);
using PFN_DDRAW_Device_GetVerticalBlankStatus = HRESULT(WINAPI*)(IDirectDraw7*, LPBOOL);
using PFN_DDRAW_Device_Initialize = HRESULT(WINAPI*)(IDirectDraw7*, GUID*);
using PFN_DDRAW_Device_RestoreDisplayMode = HRESULT(WINAPI*)(IDirectDraw7*);
using PFN_DDRAW_Device_SetCooperativeLevel = HRESULT(WINAPI*)(IDirectDraw7*, HWND, DWORD);
using PFN_DDRAW_Device_SetDisplayMode = HRESULT(WINAPI*)(IDirectDraw7*, DWORD, DWORD, DWORD, DWORD, DWORD);
using PFN_DDRAW_Device_WaitForVerticalBlank = HRESULT(WINAPI*)(IDirectDraw7*, DWORD, HANDLE);
using PFN_DDRAW_Device_GetAvailableVidMem = HRESULT(WINAPI*)(IDirectDraw7*, LPDDSCAPS2, LPDWORD, LPDWORD);
using PFN_DDRAW_Device_GetSurfaceFromDC = HRESULT(WINAPI*)(IDirectDraw7*, HDC, LPDIRECTDRAWSURFACE7*);
using PFN_DDRAW_Device_RestoreAllSurfaces = HRESULT(WINAPI*)(IDirectDraw7*);
using PFN_DDRAW_Device_TestCooperativeLevel = HRESULT(WINAPI*)(IDirectDraw7*);
using PFN_DDRAW_Device_GetDeviceIdentifier = HRESULT(WINAPI*)(IDirectDraw7*, LPDDDEVICEIDENTIFIER2, DWORD);
using PFN_DDRAW_Device_StartModeTest = HRESULT(WINAPI*)(IDirectDraw7*, LPSIZE, DWORD, DWORD);
using PFN_DDRAW_Device_EvaluateMode = HRESULT(WINAPI*)(IDirectDraw7*, DWORD, DWORD*);

// IDirectDrawSurface7
using PFN_DDRAW_Surface_QueryInterface = HRESULT(WINAPI*)(IDirectDrawSurface7*, REFIID, LPVOID*);
using PFN_DDRAW_Surface_AddRef = ULONG(WINAPI*)(IDirectDrawSurface7*);
using PFN_DDRAW_Surface_Release = ULONG(WINAPI*)(IDirectDrawSurface7*);
using PFN_DDRAW_Surface_AddAttachedSurface = HRESULT(WINAPI*)(IDirectDrawSurface7*, LPDIRECTDRAWSURFACE7);
using PFN_DDRAW_Surface_AddOverlayDirtyRect = HRESULT(WINAPI*)(IDirectDrawSurface7*, LPCRECT);
using PFN_DDRAW_Surface_Blt = HRESULT(WINAPI*)(IDirectDrawSurface7*, LPCRECT, IDirectDrawSurface7*, LPCRECT, DWORD, LPDDBLTFX);
using PFN_DDRAW_Surface_BltBatch = HRESULT(WINAPI*)(IDirectDrawSurface7*, LPDDBLTBATCH, DWORD, DWORD);
using PFN_DDRAW_Surface_BltFast = HRESULT(WINAPI*)(IDirectDrawSurface7*, DWORD, DWORD, IDirectDrawSurface7*, LPCRECT, DWORD);
using PFN_DDRAW_Surface_DeleteAttachedSurface = HRESULT(WINAPI*)(IDirectDrawSurface7*, DWORD, LPDIRECTDRAWSURFACE7);
using PFN_DDRAW_Surface_EnumAttachedSurfaces = HRESULT(WINAPI*)(IDirectDrawSurface7*, LPVOID, LPDDENUMSURFACESCALLBACK7);
using PFN_DDRAW_Surface_EnumOverlayZOrders = HRESULT(WINAPI*)(IDirectDrawSurface7*, DWORD, LPVOID, LPDDENUMSURFACESCALLBACK7);
using PFN_DDRAW_Surface_Flip = HRESULT(WINAPI*)(IDirectDrawSurface7*, IDirectDrawSurface7*, DWORD);
using PFN_DDRAW_Surface_GetAttachedSurface = HRESULT(WINAPI*)(IDirectDrawSurface7*, LPDDSCAPS2, LPDIRECTDRAWSURFACE7*);
using PFN_DDRAW_Surface_GetBltStatus = HRESULT(WINAPI*)(IDirectDrawSurface7*, DWORD);
using PFN_DDRAW_Surface_GetCaps = HRESULT(WINAPI*)(IDirectDrawSurface7*, LPDDSCAPS2);
using PFN_DDRAW_Surface_GetClipper = HRESULT(WINAPI*)(IDirectDrawSurface7*, LPDIRECTDRAWCLIPPER*);
using PFN_DDRAW_Surface_GetColorKey = HRESULT(WINAPI*)(IDirectDrawSurface7*, DWORD, LPDDCOLORKEY);
using PFN_DDRAW_Surface_GetDC = HRESULT(WINAPI*)(IDirectDrawSurface7*, HDC*);
using PFN_DDRAW_Surface_GetFlipStatus = HRESULT(WINAPI*)(IDirectDrawSurface7*, DWORD);
using PFN_DDRAW_Surface_GetOverlayPosition = HRESULT(WINAPI*)(IDirectDrawSurface7*, LPLONG, LPLONG);
using PFN_DDRAW_Surface_GetPalette = HRESULT(WINAPI*)(IDirectDrawSurface7*, LPDIRECTDRAWPALETTE*);
using PFN_DDRAW_Surface_GetPixelFormat = HRESULT(WINAPI*)(IDirectDrawSurface7*, LPDDPIXELFORMAT);
using PFN_DDRAW_Surface_GetSurfaceDesc = HRESULT(WINAPI*)(IDirectDrawSurface7*, LPDDSURFACEDESC2);
using PFN_DDRAW_Surface_Initialize = HRESULT(WINAPI*)(IDirectDrawSurface7*, LPDIRECTDRAW, LPDDSURFACEDESC2);
using PFN_DDRAW_Surface_IsLost = HRESULT(WINAPI*)(IDirectDrawSurface7*);
using PFN_DDRAW_Surface_Lock = HRESULT(WINAPI*)(IDirectDrawSurface7*, LPCRECT, LPDDSURFACEDESC2, DWORD, HANDLE);
using PFN_DDRAW_Surface_ReleaseDC = HRESULT(WINAPI*)(IDirectDrawSurface7*, HDC);
using PFN_DDRAW_Surface_Restore = HRESULT(WINAPI*)(IDirectDrawSurface7*);
using PFN_DDRAW_Surface_SetClipper = HRESULT(WINAPI*)(IDirectDrawSurface7*, IDirectDrawClipper*);
using PFN_DDRAW_Surface_SetColorKey = HRESULT(WINAPI*)(IDirectDrawSurface7*, DWORD, LPDDCOLORKEY);
using PFN_DDRAW_Surface_SetOverlayPosition = HRESULT(WINAPI*)(IDirectDrawSurface7*, LONG, LONG);
using PFN_DDRAW_Surface_SetPalette = HRESULT(WINAPI*)(IDirectDrawSurface7*, LPDIRECTDRAWPALETTE);
using PFN_DDRAW_Surface_Unlock = HRESULT(WINAPI*)(IDirectDrawSurface7*, LPRECT);
using PFN_DDRAW_Surface_UpdateOverlay = HRESULT(WINAPI*)(IDirectDrawSurface7*, LPCRECT, LPDIRECTDRAWSURFACE7, LPCRECT, DWORD, LPDDOVERLAYFX);
using PFN_DDRAW_Surface_UpdateOverlayDisplay = HRESULT(WINAPI*)(IDirectDrawSurface7*, DWORD);
using PFN_DDRAW_Surface_UpdateOverlayZOrder = HRESULT(WINAPI*)(IDirectDrawSurface7*, DWORD, LPDIRECTDRAWSURFACE7);
using PFN_DDRAW_Surface_GetDDInterface = HRESULT(WINAPI*)(IDirectDrawSurface7*, LPVOID*);
using PFN_DDRAW_Surface_PageLock = HRESULT(WINAPI*)(IDirectDrawSurface7*, DWORD);
using PFN_DDRAW_Surface_PageUnlock = HRESULT(WINAPI*)(IDirectDrawSurface7*, DWORD);
using PFN_DDRAW_Surface_SetSurfaceDesc = HRESULT(WINAPI*)(IDirectDrawSurface7*, LPDDSURFACEDESC2, DWORD);
using PFN_DDRAW_Surface_SetPrivateData = HRESULT(WINAPI*)(IDirectDrawSurface7*, REFGUID, LPVOID, DWORD, DWORD);
using PFN_DDRAW_Surface_GetPrivateData = HRESULT(WINAPI*)(IDirectDrawSurface7*, REFGUID, LPVOID, LPDWORD);
using PFN_DDRAW_Surface_FreePrivateData = HRESULT(WINAPI*)(IDirectDrawSurface7*, REFGUID);
using PFN_DDRAW_Surface_GetUniquenessValue = HRESULT(WINAPI*)(IDirectDrawSurface7*, LPDWORD);
using PFN_DDRAW_Surface_ChangeUniquenessValue = HRESULT(WINAPI*)(IDirectDrawSurface7*);
using PFN_DDRAW_Surface_SetPriority = HRESULT(WINAPI*)(IDirectDrawSurface7*, DWORD);
using PFN_DDRAW_Surface_GetPriority = HRESULT(WINAPI*)(IDirectDrawSurface7*, LPDWORD);
using PFN_DDRAW_Surface_SetLOD = HRESULT(WINAPI*)(IDirectDrawSurface7*, DWORD);
using PFN_DDRAW_Surface_GetLOD = HRESULT(WINAPI*)(IDirectDrawSurface7*, LPDWORD);

// IDirectDrawClipper
using PFN_DDRAW_Clipper_QueryInterface = HRESULT(WINAPI*)(IDirectDrawClipper*, REFIID, LPVOID*);
using PFN_DDRAW_Clipper_AddRef = ULONG(WINAPI*)(IDirectDrawClipper*);
using PFN_DDRAW_Clipper_Release = ULONG(WINAPI*)(IDirectDrawClipper*);
using PFN_DDRAW_Clipper_GetClipList = HRESULT(WINAPI*)(IDirectDrawClipper*, LPRECT, LPRGNDATA, LPDWORD);
using PFN_DDRAW_Clipper_GetHWnd = HRESULT(WINAPI*)(IDirectDrawClipper*, HWND*);
using PFN_DDRAW_Clipper_Initialize = HRESULT(WINAPI*)(IDirectDrawClipper*, LPDIRECTDRAW, DWORD);
using PFN_DDRAW_Clipper_IsClipListChanged = HRESULT(WINAPI*)(IDirectDrawClipper*, BOOL*);
using PFN_DDRAW_Clipper_SetClipList = HRESULT(WINAPI*)(IDirectDrawClipper*, LPRGNDATA, DWORD);
using PFN_DDRAW_Clipper_SetHWnd = HRESULT(WINAPI*)(IDirectDrawClipper*, DWORD, HWND);
