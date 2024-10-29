#pragma once
#include <vector>
#include "directhook.h"

namespace directhook
{
	class MethodTable
	{
	public:
		MethodTable() {}

		template<typename DirectInterfaceT>
		void AddEntries(DirectInterfaceT* d3dInterface, uint32 vtableEntriesCount)
		{
			methods.reserve(methods.size() + vtableEntriesCount);
			void** vTableBase = *reinterpret_cast<void***>(d3dInterface);
			for (uint32 i = 0; i < vtableEntriesCount; ++i)
			{
				methods.push_back(vTableBase[i]);
			}
		}

		void AddEntry(void* entry)
		{
			methods.push_back(entry);
		}

		uint32 GetSize() const { return (uint32)methods.size(); }

		void* operator[](uint32 i) const
		{
			return methods[i];
		}

	private:
		std::vector<void*> methods;
	};
}