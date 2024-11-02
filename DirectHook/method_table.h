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
		void AddEntries(DirectInterfaceT* d3dInterface, Uint32 interfaceVTableEntriesCount, Uint32 maxInterfaceVTableEntriesCount = -1)
		{
			if (maxInterfaceVTableEntriesCount == Uint32(-1))
			{
				maxInterfaceVTableEntriesCount = interfaceVTableEntriesCount;
			}

			methods.reserve(methods.size() + maxInterfaceVTableEntriesCount);
			void** vTableBase = *reinterpret_cast<void***>(d3dInterface);
			for (Uint32 i = 0; i < interfaceVTableEntriesCount; ++i)
			{
				methods.push_back(vTableBase[i]);
			}
			for (Uint32 i = 0; i < max(maxInterfaceVTableEntriesCount - interfaceVTableEntriesCount, 0); ++i)
			{
				methods.push_back(nullptr);
			}
		}

		void AddEntry(void* entry)
		{
			methods.push_back(entry);
		}

		Uint32 GetSize() const { return (Uint32)methods.size(); }

		void* operator[](Uint32 i) const
		{
			return methods[i];
		}

	private:
		std::vector<void*> methods;
	};
}