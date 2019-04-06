/*
* eDSP, A cross-platform Digital Signal Processing library written in modern C++.
* Copyright (C) 2018 Mohammed Boujemaoui Boulaghmoudi, All rights reserved.
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
* Filename: config.hpp
* Author: Mohammed Boujemaoui
* Date: 07/10/18
*/

#ifndef EDSP_CONFIG_HPP
#define EDSP_CONFIG_HPP

// Detecting the os
#if defined(_MSC_VER) || defined(_WIN32)
#    define OS_WIN32
#elif defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__)
#    if defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE
#        define OS_IOS
#    else
#        define OS_MACOS
#    endif
#elif defined(__FreeBSD__) || defined(__DragonFly__) || defined(__FreeBSD_kernel__)
#    define OS_FREEBSD
#elif defined(__ANDROID__) || defined(ANDROID)
#    define OS_ANDROID
#elif defined(__linux__) || defined(__linux)
#    define OS_LINUX
#else
#    error "eDSP has not been ported to this platform"
#endif

// Detecting the architecture
#if defined(__arm__) || defined(__TARGET_ARCH_ARM) || defined(_M_ARM) || defined(__aarch64__) || defined(__ARM64__)
#    if defined(__aarch64__) || defined(__ARM64__)
#        define PROCESSOR_ARM_64
#    else
#        define PROCESSOR_ARM_32
#    endif
#elif defined(__i386) || defined(__i386__) || defined(_M_IX86)
#    define PROCESSOR_X86_32
#elif defined(__x86_64) || defined(__x86_64__) || defined(__amd64) || defined(_M_X64)
#    define PROCESSOR_X86_64
#endif

#if defined(__GNUC__)
#    define COMPILER_GNU
#    if defined(__MINGW32__)
#        define COMPILER_MINGW
#    elif defined(__clang__)
#        define COMPILER_CLANG
#    endif
#elif defined(_MSC_VER)
#    define COMPILER_MSVC
#endif

// Define export qualifier
#if defined(COMPILER_MVSC)
#    define DLLEXPORT __declspec(dllexport)
#    define DLLIMPORT __declspec(dllimport)
#    define DLLHIDE
#elif defined(COMPILER_GNU)
#    define DLLEXPORT __attribute__((visibility("default")))
#    define DLLIMPORT __attribute__((visibility("default")))
#    define DLLHIDE __attribute__((visibility("hidden")))
#else
#    define DLLEXPORT
#    define DLLIMPORT
#    define DLLHIDE
#endif

#if (__cplusplus == 201103L)
#    define E_STANDARD_11
#elif (__cplusplus == 201402L)
#    define E_STANDARD_14
#elif (__cplusplus == 201703L)
#    define E_STANDARD_17
#else
#    error "eDSP does not support this standard"
#endif

#if defined(__clang__) || defined(__GNUC__)
#    define E_LIKELY(x) __builtin_expect(!!(x), 1)
#    define E_UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
#    define E_LIKELY(x) (!!(x))
#    define E_UNLIKELY(x) (!!(x))
#endif

#define E_BUILD_DATE __DATE__
#define E_BUILD_TIME __TIME__

#define E_VERSION_MAJOR 0
#define E_VERSION_MINOR 0
#define E_VERSION_PATCH 1
#define E_VERSION_STR "0.0.1"

#endif //EDSP_CONFIG_HPP
