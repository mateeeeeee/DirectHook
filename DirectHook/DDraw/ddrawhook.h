#pragma once
#include "../directhook.h"

namespace directhook
{
	class MethodTable;

	namespace ddraw
	{
		DHStatus Initialize(MethodTable& methodTable);
	}
}