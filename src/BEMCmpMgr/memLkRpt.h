// SAC 10/3/16 - enabling memory leak detection & reporting
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>
#ifdef _DEBUG
   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif
#endif  // _DEBUG
//#if defined(WIN32) && defined(_DEBUG)
//  #define new DEBUG_NEW
//#endif
