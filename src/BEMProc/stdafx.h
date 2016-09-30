// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define NOMINMAX                 // prevent:  warning C4003: not enough actual parameters for macro 'min'   w/ inclusion of QtCore\QDateTime.h
#define WIN32_LEAN_AND_MEAN      // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

#include <string>
#include <vector>
#include <ctype.h>
#include <assert.h>

#pragma warning(disable : 4100 4996)
#include <boost/algorithm/string.hpp>
#pragma warning(default : 4100 4996)
#include <boost/algorithm/string/compare.hpp>
#include <boost/format.hpp>

#pragma warning(disable : 4127)
#include <QtCore/QString.h>
#include <QtCore/QStringList.h>
#include <QtCore/QDateTime.h>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtCore/QVector>
#pragma warning(default : 4127)


// TODO: reference additional headers your program requires here
