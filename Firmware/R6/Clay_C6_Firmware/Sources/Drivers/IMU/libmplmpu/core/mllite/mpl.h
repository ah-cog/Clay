/*
 $License:
    Copyright (C) 2011-2012 InvenSense Corporation, All Rights Reserved.
    See included License.txt for License information.
 $
 */
#include "mltypes.h"

#ifndef INV_MPL_H__
#define INV_MPL_H__

#ifdef __cplusplus
extern "C" {
#endif

inv_error_t inv_init_mpl(void);
inv_error_t inv_start_mpl(void);
inv_error_t inv_get_version(char **version);

//these are included here because they appear to be missing from EABI c++ libs.
extern float cosf(float f);
extern float sinf(float f);
extern float acosf(float f);
extern long long int __aeabi_f2lz(float f);

#ifdef __cplusplus
}
#endif

#endif // INV_MPL_H__
