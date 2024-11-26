#pragma once
#include "../directhook.h"

namespace directhook
{
	class MethodTable;

	namespace ddraw
	{
		DH_Status Initialize(MethodTable& methodTable);
	}
}