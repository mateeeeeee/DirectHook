#pragma once
#include "../directhook.h"

namespace directhook
{
	class MethodTable;

	namespace d3d11
	{
		Status Initialize(MethodTable& methodTable);
	}
}