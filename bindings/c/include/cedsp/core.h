/**
* eDSP, A cross-platform Digital Signal Processing library written in modern C++.
* Copyright (C) 2019 Mohammed Boujemaoui Boulaghmoudi, All rights reserved.
*
* This program is free software: you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the Free
* Software Foundation, either version 3 of the License, or (at your option)
* any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along width
* this program.  If not, see <http://www.gnu.org/licenses/>
*
* Filename: version.h
* Author: Mohammed Boujemaoui
* Date: 2019-03-31
*/

#ifndef EDSP_BINDING_C_VERSION_H
#define EDSP_BINDING_C_VERSION_H

#ifdef __cplusplus
extern "C" {
#endif

int get_minor_version();
int get_major_version();
int get_patch_version();
const char* get_version();
const char* get_build_date();
const char* get_build_time();
const char* get_fft_library();
const char* get_codec_library();
const char* get_resample_library();

const char* get_environment(const char* tag, int* error);
int set_environment(const char* tag, const char* data);
int exist_environment(const char* tag);

#ifdef __cplusplus
}
#endif

#endif //EDSP_BINDING_C_VERSION_H
