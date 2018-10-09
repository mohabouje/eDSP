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
* You should have received a copy of the GNU General Public License along withº
* this program.  If not, see <http://www.gnu.org/licenses/>
*
* Filename: system.hpp
* Author: Mohammed Boujemaoui
* Date: 07/10/18
*/

#ifndef EDSP_SYSTEM_HPP
#define EDSP_SYSTEM_HPP

#include <edsp/core/internal/config.hpp>
#include <edsp/types/enum.hpp>
#include <edsp/types/string_view.hpp>
#include <edsp/types/expected.hpp>
#include <edsp/meta/expects.hpp>
#include <edsp/meta/is_null.hpp>
#include <edsp/meta/empty.hpp>
#include <edsp/thirdparty/nonstd/string_view.hpp>
#include <edsp/thirdparty/nonstd/expected.hpp>
#include <edsp/thirdparty/better-enums/enum.h>
#include <mutex>

namespace edsp { inline namespace core {

    /**
     * @brief Represents the OS running the library.
     */
    EDSP_SMART_ENUM(systems, int, windows, linux, freeBSD, macOS, iOS, android, unknown)

    /**
     * @brief Represents the architecture of the processor running the library.
     */
    EDSP_SMART_ENUM(processors, int, x86, x64, arm, unknown)

    /**
     * @brief Represents the compiler used to compile the library.
     */
    EDSP_SMART_ENUM(compilers, int, gcc, clang, mvsc, unknown)

    struct system_info {
        // clang-format off
        static compilers compiler() noexcept {
            #if defined(COMPILER_GNU)
                return compilers::gcc;
            #elif defined(COMPILER_CLANG)
                return compilers::clang;
            #elif defined(COMPILER_MVSC)
                return compilers::mvsc;
            #else
                return compilers::unknown;
            #endif
        }
        // clang-format on

        // clang-format off
        static systems os() noexcept {
            #if defined(OS_WINDOWS)
               return systems::windows;
            #elif defined(OS_LINUX)
               return systems::linux;
            #elif defined(OS_MACOS)
               return systems::macOS;
            #elif defined(OS_IOS)
               return systems::iOS;
            #elif defined(OS_FREEBSD)
               return systems::freeBSD;
            #elif defined(OS_ANDROID)
               return systems::android;
            #else
               return systems::unknown;
            #endif
        }
        // clang-format on

        // clang-format off
        static processors processor() noexcept {
            #if defined(PROCESSOR_X86_32)
               return processors::x86;
            #elif defined(PROCESSOR_X86_64)
               return processors::x64;
            #elif defined(PROCESSOR_ARM)
               return processors::arm;
            #else
               return processors::unknown;
            #endif
        }
        // clang-format on

    };

    struct system_env {
        /**
        * The SystemEnvironmentError describes the possible error while reading/writting
        * variables in the system environment.
        */
        enum SystemEnvironmentError {
            NoError = 0,              /*!< No error */
            Empty,                    /*!< Variable name is empty */
            NotFound,                 /*!< Variable not found */
            InvalidArgument = EINVAL, /*!< Invalid argument */
            NoMemory        = ENOMEM, /*!< Out of memory */
            Unknown         = -1      /*!< Unknown error */
        };

        /**
        * @brief Searches in the system environment for the value of the @par variable name.
        * @param variable_name Variable name
        * @return If it fails, the associated error. If not, the value of the variable.
        */
        static edsp::expected<std::string, SystemEnvironmentError>
            get_env(const edsp::string_view& variable_name) noexcept {
            std::lock_guard<std::mutex> lock(mutex());
            const char* env_p = std::getenv(variable_name.data());
            if (meta::empty(variable_name)) {
                return edsp::make_unexpected(SystemEnvironmentError::Empty);
            } else {
                if (!meta::is_null(env_p)) {
                    return env_p;
                } else {
                    return edsp::make_unexpected(SystemEnvironmentError::NotFound);
                }
            }
        }

        /**
        * @brief Shall update or add a variable in the environment of the calling process.
        * @param variable_name Variable name.
        * @param variable_value Variable value.
        * @param overwrite If true, overwrites the existing value.
        * @return If it fails, the error associated with the operation.
        */
        static SystemEnvironmentError set_env(const edsp::string_view& variable_name,
                                              const edsp::string_view& variable_value, bool overwrite = true) noexcept {
            std::lock_guard<std::mutex> lock(mutex());
            if (meta::empty(variable_name)) {
                return SystemEnvironmentError::Empty;
            } else {
                const auto result = setenv(meta::data(variable_name), meta::data(variable_value), overwrite);
                return static_cast<SystemEnvironmentError>(result);
            }
        }

        /**
        * @brief Checks if a variable name is defined in the system environment.
        * @param variable_name Variable name.
        * @return true if the variable exist in the system environment.
        */
        static bool exist(const edsp::string_view& variable_name) noexcept {
            std::lock_guard<std::mutex> lock(mutex());
            return !meta::is_null(std::getenv(meta::data(variable_name)));
        }

    private:
        /**
         * @brief Returns a reference to the global mutex used in all the instances of the system environment class.
         *
         * @note Avoids duplications of the initialization code in every place where the header is included.
         * @return Reference to the global mutex.
         */
        static std::mutex& mutex() {
            static std::mutex environment_mutex;
            return environment_mutex;
        }
    };

}} // namespace edsp::core

#endif //EDSP_SYSTEM_HPP
