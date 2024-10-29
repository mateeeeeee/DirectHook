#pragma once
#include "../directhook.h"

namespace directhook
{
	class MethodTable;

	namespace d3d10
	{
		Status Initialize(MethodTable& methodTable);
	}
}