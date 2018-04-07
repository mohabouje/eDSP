//
// Created by Mohammed Boujemaoui on 08/10/2017.
//

#ifndef EDSP_CONFIG_EDSP_H
#define EDSP_CONFIG_EDSP_H

// Check windows
#if _WIN32 || _WIN64
#if _WIN64
#define EDSP_X64
#else
#define EDSP_X86
#endif
#endif

#if __GNUC__
#if __x86_64__ || __ppc64__
#define EDSP_X64
#else
#define EDSP_X86
#endif
#endif

#define EDSP_NOEXCEPT noexcept
#define EDSP_INLINE   inline
#define EDSP_OVERRIDE override
#define EDSP_UNUSED(x) (void)x;

#define EDSP_VERSION_MAJOR     0
#define EDSP_VERSION_MINOR     0
#define EDSP_VERSION_BUILD     0
#define EDSP_VERSION_LABEL     ""

#define EDSP_BEGIN_NAMESPACE  namespace edsp {
#define EDSP_END_NAMESPACE      }




#define _In_
#define _Out_
#define _InOut_


#endif //EDSP_CONFIG_EDSP_H
