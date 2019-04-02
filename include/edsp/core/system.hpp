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
* Filename: system.hpp
* Author: Mohammed Boujemaoui
* Date: 07/10/18
*/

#ifndef EDSP_SYSTEM_HPP
#define EDSP_SYSTEM_HPP

#include <edsp/core/internal/config.hpp>
#include <edsp/types/string_view.hpp>
#include <edsp/types/expected.hpp>
#include <edsp/meta/expects.hpp>
#include <edsp/meta/is_null.hpp>
#include <edsp/meta/empty.hpp>
#include <mutex>

namespace edsp { inline namespace core {

    /**
     * @brief Represents the OS running the library.
     */
    enum class systems {
        windows, /*!< Microsoft Windows OS */
        linux,   /*!< Linux distribution */
        freeBSD, /*!< Free BSD distribution */
        macOS,   /*!< Mac OS X system */
        iOS,     /*!< iOS system */
        android, /*!< Android system */
        unknown  /*!< Unknown system */
    };

    inline logger& operator<<(logger& stream, systems sys) {
        switch (sys) {
            case systems::windows:
                return stream << "Microsoft Windows OS";
            case systems::linux:
                return stream << "Linux distribution";
            case systems::freeBSD:
                return stream << "Free BSD distribution";
            case systems::macOS:
                return stream << "Mac OS X system";
            case systems::iOS:
                return stream << "iOS system";
            case systems::android:
                return stream << "Android system";
            default:
                return stream << edsp::red << "unknown" << edsp::endc;
        }
    }

    /**
     * @brief Represents the architecture of the processor running the library.
     */
    enum class processors {
        x86,    /*!< x86 architecture */
        x64,    /*!< x64 architecture */
        arm,    /*!< arm architecture */
        unknown /*!< unknown architecture */
    };

    inline logger& operator<<(logger& stream, processors proc) {
        switch (proc) {
            case processors::x86:
                return stream << "x86 architecture";
            case processors::x64:
                return stream << "x64 architecture";
            case processors::arm:
                return stream << "arm architecture";
            default:
                return stream << edsp::red << "unknown" << edsp::endc;
        }
    }

    /**
     * @brief Represents the type of Operative System running the library.
     * @brief Represents the OS running the library.
     */
    enum class compilers {
        gcc,    /*!< GCC compiler */
        clang,  /*!< Clang compiler */
        mvsc,   /*!< MVSC compiler */
        unknown /*!< Unknown compiler */
    };

    inline logger& operator<<(logger& stream, compilers comp) {
        switch (comp) {
            case compilers::gcc:
                return stream << "gcc";
            case compilers::clang:
                return stream << "clang";
            case compilers::mvsc:
                return stream << "mvsc";
            default:
                return stream << edsp::red << "unknown" << edsp::endc;
        }
    }

    struct system_info {
        // clang-format off
        static constexpr compilers compiler() noexcept {
            #if defined(COMPILER_GNU) && !defined(COMPILER_CLANG)
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
        static constexpr systems os() noexcept {
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
        static constexpr processors processor() noexcept {
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
        enum class error {
            no_error = 0,              /*!< No error */
            empty,                    /*!< Variable name is empty */
            not_found,                 /*!< Variable not found */
            invalid_argument = EINVAL, /*!< Invalid argument */
            no_memory        = ENOMEM, /*!< Out of memory */
            unknown         = -1      /*!< Unknown error */
        };

        /**
        * @brief Searches in the system environment for the value of the variable name.
        * @param variable_name Variable name
        * @return If it fails, the associated error. If not, the value of the variable.
        */
        static edsp::expected<edsp::string_view, error>
            get_env(const edsp::string_view& variable_name) noexcept {
            std::lock_guard<std::mutex> lock(mutex());
            const char* env_p = std::getenv(variable_name.data());
            if (meta::empty(variable_name)) {
                return edsp::make_unexpected(error::empty);
            } else {
                if (!meta::is_null(env_p)) {
                    return env_p;
                } else {
                    return edsp::make_unexpected(error::not_found);
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
        static error set_env(const edsp::string_view& variable_name,
                                              const edsp::string_view& variable_value, bool overwrite = true) noexcept {
            std::lock_guard<std::mutex> lock(mutex());
            if (meta::empty(variable_name)) {
                return error::empty;
            } else {
                const auto result = setenv(meta::data(variable_name), meta::data(variable_value), overwrite);
                return static_cast<error>(result);
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
