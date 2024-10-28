#pragma once

#define ENTRY_COUNT(Class) (Class##_LastEntry - Class##_FirstEntry + 1)


namespace directhook::ddraw
{
	enum
	{
		Device_FirstEntry,
		Device_QueryInterface = Device_FirstEntry,
		Device_AddRef,
		Device_Release,
		Device_CreateSurface,
		Device_DuplicateSurface,
		Device_EnumDisplayModes,
		Device_EnumSurfaces,
		Device_ExitFullscreen,
		Device_GetAvailableVidMem,
		Device_GetDeviceIdentifier,
		Device_GetDisplayMode,
		Device_GetFourCCCodes,
		Device_GetGDISurface,
		Device_GetMonitorFrequency,
		Device_GetScanLine,
		Device_GetVerticalBlankStatus,
		Device_Initialize,
		Device_RestoreDisplayMode,
		Device_SetCooperativeLevel,
		Device_SetDisplayMode,
		Device_WaitForVerticalBlank,
		Device_LastEntry = Device_WaitForVerticalBlank,

		Surface_FirstEntry,
		Surface_QueryInterface = Surface_FirstEntry,
		Surface_AddRef,
		Surface_Release,
		Surface_AddAttachedSurface,
		Surface_AddOverlayDirtyRect,
		Surface_Blt,
		Surface_BltBatch,
		Surface_BltFast,
		Surface_DeleteAttachedSurface,
		Surface_EnumAttachedSurfaces,
		Surface_EnumOverlayZOrders,
		Surface_Flip,
		Surface_GetAttachedSurface,
		Surface_GetBltStatus,
		Surface_GetCaps,
		Surface_GetClipper,
		Surface_GetColorKey,
		Surface_GetDC,
		Surface_GetDesc,
		Surface_GetSurfaceDesc,
		Surface_Lock,
		Surface_ReleaseDC,
		Surface_SetClipper,
		Surface_SetColorKey,
		Surface_SetSurfaceDesc,
		Surface_Unlock,
		Surface_UnlockRect,
		Surface_LastEntry = Surface_UnlockRect,

		Clipper_FirstEntry, 
		Clipper_QueryInterface = Clipper_FirstEntry,
		Clipper_AddRef,
		Clipper_Release,
		Clipper_SetHWnd,
		Clipper_GetHWnd,
		Clipper_AddClipList,
		Clipper_GetClipList,
		Clipper_GetOverlap,
		Clipper_LastEntry = Clipper_GetOverlap
	};

	static constexpr int DEVICE_ENTRIES = ENTRY_COUNT(Device);
	static constexpr int SURFACE_ENTRIES = ENTRY_COUNT(Surface);
	static constexpr int CLIPPER_ENTRIES = ENTRY_COUNT(Clipper);
}