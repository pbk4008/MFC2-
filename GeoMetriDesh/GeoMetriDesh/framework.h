// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// 기본 include
#include <map>
#include <list>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

#include "d3d9.h"
#pragma comment(lib, "d3d9.lib")

#include "d3dx9.h"
#pragma comment(lib, "d3dx9.lib")

// 추가 include
#include "Include.h"


#include <string>

/////////////////////////////////////////////////////////////////////////////
// 사운드
#include <io.h>
#include "fmod.h"
#include "fmod.hpp"
#pragma comment (lib, "fmodex_vc.lib")
///////////////////////////////////////////////////////////////////////////