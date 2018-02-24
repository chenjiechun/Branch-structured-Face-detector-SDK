#include "ippcv90legacy.h"
#include "ippi90legacy.h"
#include "ipps90legacy.h"
#include "ippcv90legacy_redef.h"
#include "ippi90legacy_redef.h"
#include "ipps90legacy_redef.h"

#if defined(_WIN32)
#pragma warning( disable : 4505 4996 )
#else
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#pragma GCC diagnostic ignored "-Wunused-function"
#endif

static void ippStaticInit()
{
    legacy90ippiInit();
    legacy90ippcvInit();
}

static void ippiHaarClassifierFree_32f(void* p)
{
    free(p);
}
