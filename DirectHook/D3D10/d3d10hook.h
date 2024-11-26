#pragma once
#include "../directhook.h"

namespace directhook
{
	class MethodTable;

	namespace d3d10
	{
		DH_Status Initialize(MethodTable& methodTable);
	}
}