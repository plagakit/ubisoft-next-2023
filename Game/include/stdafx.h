// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>


// TODO: reference additional headers your program requires here
// essential
#include <string>
#include <math.h>
#include <assert.h>
#include <random>

// containers
#include <unordered_map>
#include <array>
#include <bitset>
#include <queue>

// ecs
#include <memory>
#include <typeindex>
#include <algorithm>

#include "App\app.h"

using Entity = std::uint32_t;
using ComponentID = unsigned char;
const ComponentID MAX_COMPONENT_TYPES = 32;
using Signature = std::bitset<MAX_COMPONENT_TYPES>;