#pragma once
#include "directhook.h"
#include "method_table.h"
#include "d3d12hook_indices.h"
#include "d3d12hook_aliases.h"

DH_STATUS WINAPI DH_D3D12_Initialize(PDH_METHOD_TABLE pTable);
