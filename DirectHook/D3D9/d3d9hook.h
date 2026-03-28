#pragma once
#include "directhook.h"
#include "method_table.h"
#include "d3d9hook_indices.h"
#include "d3d9hook_aliases.h"

DH_STATUS WINAPI DH_D3D9_Initialize(PDH_METHOD_TABLE pTable);
