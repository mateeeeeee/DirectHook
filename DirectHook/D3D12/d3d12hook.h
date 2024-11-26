#pragma once
#include "../directhook.h"

namespace directhook
{
	class MethodTable;

	namespace d3d12
	{
		DH_Status Initialize(MethodTable& methodTable);
	}
}