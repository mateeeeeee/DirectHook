#pragma once
#include <vector>
#include "directhook.h"

namespace directhook
{
	class MethodTable
	{
	public:
		MethodTable() {}

		template<typename ObjectT>
		void AddEntries(ObjectT* d3dObject, unsigned int interfaceVTableEntriesCount, unsigned int maxInterfaceVTableEntriesCount = -1)
		{
			if (maxInterfaceVTableEntriesCount == UINT_MAX)
			{
				maxInterfaceVTableEntriesCount = interfaceVTableEntriesCount;
			}

			methods.reserve(methods.size() + maxInterfaceVTableEntriesCount);
			void** vTableBase = *reinterpret_cast<void***>(d3dObject);
			for (unsigned int i = 0; i < interfaceVTableEntriesCount; ++i)
			{
				methods.push_back(vTableBase[i]);
			}
			for (unsigned int i = 0; i < max(maxInterfaceVTableEntriesCount - interfaceVTableEntriesCount, 0); ++i)
			{
				methods.push_back(nullptr);
			}
		}

		void AddEntry(void* entry)
		{
			methods.push_back(entry);
		}

		unsigned int GetSize() const { return (unsigned int)methods.size(); }

		void* operator[](unsigned int i) const
		{
			return methods[i];
		}

	private:
		std::vector<void*> methods;
	};
}