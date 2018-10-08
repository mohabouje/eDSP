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
* Filename: logger.hpp
* Author: Mohammed Boujemaoui
* Date: 07/10/18
*/

#ifndef EDSP_LOGGER_HPP
#define EDSP_LOGGER_HPP

#include <edsp/thirdparty/spdlog/spdlog.h>
#include <edsp/thirdparty/spdlog/sinks/stdout_color_sinks.h>
#include <edsp/thirdparty/spdlog/sinks/basic_file_sink.h>

#include <edsp/types/string_view.hpp>
#include <type_traits>
#include <sstream>
#include <edsp/meta/unused.hpp>

namespace edsp { inline namespace core {

    class logger {
    public:
        /**
         * The MessageLevelType enum describes the messages that can be sent
         * to a message handler
         */
        enum levels {
            trace = 0, /*!< Trace Message */
            debug,     /*!< Debug Message */
            info,      /*!< Information Message */
            warning,   /*!< Warning Message */
            error,     /*!< Error Message */
            critical,  /*!< Critical Message */
            off        /*!< Disable the logger */
        };

        /**
         * @brief Updates the minimum level to be logged.
         * @param type Level that triggers the logger.
         */
        inline static void set_default_level(levels type);

        /**
         * @brief Returns the default level
         * @return Current level that triggers the logger.
         */
        inline static levels default_level();

        /**
         * @brief Updates the default file path of the file holding the default logger.
         * @param path Path of the file that will store the message from the default logger.
         */
        inline static void set_default_path(const std::string& path);

        /**
         * @brief Returns the current file path of the default logger.
         *
         * An empty path means the the messages are printed directly into the console of the system.
         * @return Path of the file that is holding the messages from the default logger.
         */
        inline static const std::string& default_path();

        /**
         * @brief Updates the name of the default logger.
         * @param name New name or alias associated with the default logger.
         */
        inline static void set_default_name(const std::string& name);

        /**
         * @brief Returns the name of the default logger.
         * @return Name or alias of the default logger.
         */
        inline static const std::string& default_name();

        /**
         * @brief Constructs a logger to record log messages of @par message_type
         * for the @par file.
         * @param name Name or key of the logger.
         * @param file File-path to stores the message. Use "console" to output the messages in the terminal.
         * @param message_type Type of the message.
         * @see MessageLevelType
         */
        inline logger(const edsp::string_view& name, const edsp::string_view& file,
                      levels message_type = levels::trace);

        /**
         * @brief Constructs a logger to record log messages of @par message_type in a terminal.
         * @param name Name or key of the logger.
         * @param message_type Type of the message.
         * @see MessageLevelType
         */
        inline logger(const edsp::string_view& name, levels message_type = levels::trace);

        /**
         * @brief Created the default logger to record log messages of @par message_type.
         * @param message_type Type of the message.
-        * @see MessageLevelType
         */
        inline explicit logger(levels message_type = levels::trace);

        /**
         * @brief Default destructor.
         */
        inline ~logger();

        /**
         * @brief Updates the minimum level to be logged.
         * @param type Level that triggers the logger.
         */
        inline void set_level(levels type);

        /**
         * @brief Returns the default level
         * @return Current level that triggers the logger.
         */
        inline levels level();

        /**
         * @brief Writes the character to the stream and returns a reference to the stream.
         * @return A reference to the stream.
         */
        inline logger& operator<<(char);

        /**
         * @brief Writes the boolean to the stream and returns a reference to the stream.
         * @return A reference to the stream.
         */
        inline logger& operator<<(bool);

        /**
         * @brief Writes the numeric value to the stream and returns a reference to the stream.
         * @return A reference to the stream.
         */
        template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
        inline logger& operator<<(T);

        /**
         * @brief Serialize the object of type T to the stream and returns a reference to the stream.
         * @return A reference to the stream.
         */
        template <typename T, typename = typename std::enable_if<!std::is_arithmetic<T>::value>::type>
        inline logger& operator<<(const T&);

        /**
         * @brief Writes the string to the stream and returns a reference to the stream.
         * @return A reference to the stream.
         */
        inline logger& operator<<(const edsp::string_view&);

        /**
         * @brief Writes the error message to the stream and returns a reference to the stream.
         * @return A reference to the stream.
         */
        inline logger& operator<<(const std::error_code&);

        /**
         * @brief Writes an space character to the stream and returns a reference to the stream.
         * @return A reference to the stream.
         */
        inline logger& space();

        /**
         * @brief Returns the name of the logger
         * @return Name of the logger
         */
        inline const std::string& name() const;

    private:
        /**
         * @brief Returns a reference to the global level used in all spdlog-loggers
         *
         * @note Avoids duplications of the initialization code in every place where the header is included.
         * @return Reference to the global level used in all spdlog-loggers
         */
        static spdlog::level::level_enum& global_level() {
            static spdlog::level::level_enum LEVEL = spdlog::level::trace;
            return LEVEL;
        }

        /**
         * @brief Returns a reference to the global file path used to save the spd-loggers
         *
         * @note Avoids duplications of the initialization code in every place where the header is included.
         * @return Reference to the global file path
         */
        static std::string& global_path() {
            static std::string FILE = "";
            return FILE;
        }

        /**
         * @brief Returns a reference to the global name used to access the spd-loggers
         *
         * @note Avoids duplications of the initialization code in every place where the header is included.
         * @return Reference to the global name
         */
        static std::string& global_name() {
            static std::string NAME = "console";
            return NAME;
        }

    private:
        std::shared_ptr<spdlog::logger> logger_{nullptr};
        logger::levels type_{levels::info};
        std::string msg_{""};
    };

    logger::logger(const edsp::string_view& name, const edsp::string_view& file, logger::levels message_type) :
        type_(message_type),
        msg_() {
        logger_ = spdlog::get(name.data());
        if (!logger_) {
            logger_ = spdlog::basic_logger_mt(name.data(), file.data());
        }
    }

    logger::logger(const edsp::string_view& name, logger::levels message_type) : type_(message_type), msg_() {
        logger_ = spdlog::get(name.data());
        if (!logger_) {
            logger_ = spdlog::stdout_color_mt(name.data());
        }
    }

    logger::logger(logger::levels message_type) : type_(message_type), msg_() {
        const auto& name = global_name();
        logger_          = spdlog::get(name);
        if (!logger_) {
            const auto& path = global_path();
            if (path.empty()) {
                logger_ = spdlog::stdout_color_mt(name);
            } else {
                logger_ = spdlog::basic_logger_mt(name, path);
            }
        }
        set_level(default_level());
    }

    logger::~logger() {
        switch (type_) {
            case levels::trace:
                logger_->debug(msg_);
                break;
            case levels::debug:
                logger_->debug(msg_);
                break;
            case levels::info:
                logger_->info(msg_);
                break;
            case levels::warning:
                logger_->warn(msg_);
                break;
            case levels::critical:
                logger_->critical(msg_);
                break;
            case levels::error:
                logger_->error(msg_);
                break;
            default:
                break;
        }
    }

    logger& logger::operator<<(char character) {
        msg_ += character;
        return space();
    }

    logger& logger::operator<<(bool state) {
        msg_ += (state ? "true" : "false");
        return space();
    }

    logger& logger::operator<<(const edsp::string_view& text) {
        msg_ += text.data();
        return space();
    }

    logger& logger::operator<<(const std::error_code& code) {
        msg_ += code.message();
        return space();
    }

    logger& logger::space() {
        msg_ += ' ';
        return *this;
    }

    template <typename T, typename>
    logger& logger::operator<<(T number) {
        msg_ += std::to_string(number);
        return space();
    }

    template <typename T, typename>
    logger& logger::operator<<(const T& object) {
        std::stringstream serialized;
        serialized << object;
        msg_ += serialized.str();
        return space();
    }

    logger::levels logger::default_level() {
        switch (global_level()) {
            case spdlog::level::trace:
                return levels::trace;
            case spdlog::level::debug:
                return levels::debug;
            case spdlog::level::info:
                return levels::info;
            case spdlog::level::warn:
                return levels::warning;
            case spdlog::level::critical:
                return levels::critical;
            case spdlog::level::err:
                return levels::error;
            default:
                return levels::off;
        }
    }

    void logger::set_default_level(logger::levels type) {
        auto& LEVEL = global_level();
        switch (type) {
            case levels::trace:
                LEVEL = spdlog::level::trace;
                break;
            case levels::debug:
                LEVEL = spdlog::level::debug;
                break;
            case levels::info:
                LEVEL = spdlog::level::info;
                break;
            case levels::warning:
                LEVEL = spdlog::level::warn;
                break;
            case levels::critical:
                LEVEL = spdlog::level::critical;
                break;
            case levels::error:
                LEVEL = spdlog::level::err;
                break;
            default:
                LEVEL = spdlog::level::off;
                break;
        }
    }

    void logger::set_level(logger::levels type) {
        switch (type) {
            case levels::trace:
                logger_->set_level(spdlog::level::trace);
                break;
            case levels::debug:
                logger_->set_level(spdlog::level::debug);
                break;
            case levels::info:
                logger_->set_level(spdlog::level::info);
                break;
            case levels::warning:
                logger_->set_level(spdlog::level::warn);
                break;
            case levels::critical:
                logger_->set_level(spdlog::level::critical);
                break;
            case levels::error:
                logger_->set_level(spdlog::level::err);
                break;
            default:
                logger_->set_level(spdlog::level::off);
                break;
        }
    }

    logger::levels logger::level() {
        switch (logger_->level()) {
            case spdlog::level::trace:
                return levels::trace;
            case spdlog::level::debug:
                return levels::debug;
            case spdlog::level::info:
                return levels::info;
            case spdlog::level::warn:
                return levels::warning;
            case spdlog::level::critical:
                return levels::critical;
            case spdlog::level::err:
                return levels::error;
            default:
                return levels::off;
        }
    }

    const std::string& logger::name() const {
        return logger_->name();
    }

    void logger::set_default_path(const std::string& path) {
        global_path() = path;
    }

    const std::string& logger::default_path() {
        return global_path();
    }

    const std::string& logger::default_name() {
        return global_name();
    }

    void logger::set_default_name(const std::string& name) {
        global_name() = name;
    }

}} // namespace edsp::core

#define eTrace() edsp::logger(edsp::logger::levels::trace)
#define eInfo() edsp::logger(edsp::logger::levels::info)
#define eDebug() edsp::logger(edsp::logger::levels::debug)
#define eWarning() edsp::logger(edsp::logger::levels::warning)
#define eCritical() edsp::logger(edsp::logger::levels::critical)
#define eError() edsp::logger(edsp::logger::levels::error)

#endif //EDSP_LOGGER_HPP
