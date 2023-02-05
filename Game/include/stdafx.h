// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>


// TODO: reference additional headers your program requires here
#include <string>
#include <math.h>
#include <iostream>
#include <unordered_map>
#include <assert.h>
#include <bitset>
#include <typeindex>

#include "App\app.h"

using Entity = std::uint32_t;
using ComponentType = unsigned char;
const ComponentType MAX_COMPONENT_TYPES = 32;
using Signature = std::bitset<MAX_COMPONENT_TYPES>;