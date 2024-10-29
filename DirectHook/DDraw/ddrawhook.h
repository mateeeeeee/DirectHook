#pragma once
#include "../directhook.h"

namespace directhook
{
	class MethodTable;

	namespace ddraw
	{
		Status Initialize(MethodTable& methodTable);
	}
}