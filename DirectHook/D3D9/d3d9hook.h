#pragma once
#include "../directhook.h"

namespace directhook
{
	class MethodTable;

	namespace d3d9
	{
		Status Initialize(MethodTable& methodTable);
	}
}