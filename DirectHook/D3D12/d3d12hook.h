#pragma once
#include "../directhook.h"

namespace directhook
{
	class MethodTable;

	namespace d3d12
	{
		Status Initialize(MethodTable& methodTable);
	}
}