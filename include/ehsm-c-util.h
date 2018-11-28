/*
 * Copyright (c) 2018 ellipticSecure - https://ellipticsecure.com
 *
 * All rights reserved.
 *
 * You may only use this code under the terms of the ellipticSecure software license.
 *
 */

/*
 *
 * C Utility library for eHSM Hardware Security Module
 * @author Kobus Grobler
 *
 */

#ifndef _EHSM_UTIL_C_H
#define _EHSM_UTIL_C_H

#include <cryptoki.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EHSM_FPTR(func) s_ptr->func

/**
 * Gets a pointer to the PKCS#11 functions from the library.
 * @param module the library path
 * @param ppVoid a pointer to the handle of the library. Call vCloseLibrary when done.
 * @return a pointer to the exposed C_xxx Functions
 */
CK_FUNCTION_LIST_PTR pGetFunctionListPtr(const char *module, void **ppVoid);

/**
 * Loads a dynamic library
 * @param module the library path
 * @return NULL if the load failed or otherwise a handle to the library.
 */
void *pLoadLibrary(const char *module);

/**
 * Closes a library opened by pLoadLibrary.
 * @param pLib the handle to the library.
 */
void vCloseLibrary(void *pLib);

#ifdef __cplusplus
}
#endif

#endif

