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
		void AddEntries(DirectInterfaceT* d3dInterface, uint32 interfaceVTableEntriesCount, uint32 maxInterfaceVTableEntriesCount = -1)
		{
			if (maxInterfaceVTableEntriesCount == uint32(-1))
			{
				maxInterfaceVTableEntriesCount = interfaceVTableEntriesCount;
			}

			methods.reserve(methods.size() + maxInterfaceVTableEntriesCount);
			void** vTableBase = *reinterpret_cast<void***>(d3dInterface);
			for (uint32 i = 0; i < interfaceVTableEntriesCount; ++i)
			{
				methods.push_back(vTableBase[i]);
			}
			for (uint32 i = 0; i < max(maxInterfaceVTableEntriesCount - interfaceVTableEntriesCount, 0); ++i)
			{
				methods.push_back(nullptr);
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