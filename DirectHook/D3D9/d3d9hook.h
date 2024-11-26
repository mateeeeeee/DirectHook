#pragma once
#include "../directhook.h"

namespace directhook
{
	class MethodTable;

	namespace d3d9
	{
		DH_Status Initialize(MethodTable& methodTable);
	}
}