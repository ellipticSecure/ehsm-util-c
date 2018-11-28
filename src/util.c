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
#include "ehsm-c-util.h"
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>

void *pLoadLibrary(const char *module) {
    char *errMsg = NULL_PTR;
    void *pDynLib = dlopen(module, RTLD_NOW | RTLD_LOCAL);

    if (pDynLib == NULL_PTR) {
        errMsg = dlerror();
    }

    if (errMsg != NULL_PTR) {
        fprintf(stderr, "Failed to load library %s: %s\n", module, errMsg);
    }
    return pDynLib;
}

void vCloseLibrary(void *pLib) {
    if (pLib != NULL_PTR)
        dlclose(pLib);
}

CK_FUNCTION_LIST_PTR pGetFunctionListPtr(const char *module, void **ppVoid) {
    void *pDynLib = pLoadLibrary(module);
    if (pDynLib == NULL_PTR)
        return NULL_PTR;


    const CK_C_GetFunctionList pGFL = (CK_C_GetFunctionList) dlsym(pDynLib, "C_GetFunctionList");

    if (pGFL == NULL_PTR) {
        vCloseLibrary(pDynLib);
        fprintf(stderr, "Failed to load library: C_GetFunctionList not found.\n");
        return NULL_PTR;
    }

    CK_FUNCTION_LIST_PTR ptr = NULL_PTR;
    CK_RV retCode = pGFL(&ptr);
    if (!ptr && (retCode) != CKR_OK) {
        fprintf(stderr, "C_GetFunctionList failed...error no = 0x%lx\n", retCode);
        vCloseLibrary(pDynLib);
    }
    *ppVoid = pDynLib;
    return ptr;
}
