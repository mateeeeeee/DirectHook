#pragma once
#include "../directhook.h"

namespace directhook
{
	class MethodTable;

	namespace d3d11
	{
		DHStatus Initialize(MethodTable& methodTable);
	}
}