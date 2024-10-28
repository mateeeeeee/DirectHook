#pragma once

namespace directhook::ddraw
{
	enum 
	{
		Device_QueryInterface,
		Device_AddRef,
		Device_Release,
		Device_EntriesCount
	};

	static constexpr int DEVICE_ENTRIES = Device_EntriesCount;
}