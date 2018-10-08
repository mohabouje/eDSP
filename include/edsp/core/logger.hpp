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
        enum class MessageLevelType {
            Info = 0, /*!< Information Message */
            Debug,    /*!< Debug Message */
            Warning,  /*!< Warning Message */
            Critical, /*!< Critical Message */
            Error,    /*!< Error Message */
            Off       /*!< Disable the logger */
        };

        /**
         * @brief Updates the minimum level to be logged.
         * @param type Level that triggers the logger.
         */
        inline static void set_default_level(MessageLevelType type);

        /**
         * @brief Returns the default level
         * @return Current level that triggers the logger.
         */
        inline static MessageLevelType default_level();

        /**
         * @brief Constructs a logger to record log messages of @par message_type
         * for the @par file.
         * @param file File-path to stores the message. Use "console" to output the messages in the terminal.
         * @param message_type Type of the message.
         * @see MessageLevelType
         */
        inline logger(const edsp::string_view& file, MessageLevelType message_type);

        /**
         * @brief Constructs a logger to record log messages of @par message_type in a terminal.
         * @param message_type Type of the message.
         * @see MessageLevelType
         */
        inline explicit logger(MessageLevelType message_type);

        /**
         * @brief Default destructor.
         */
        inline ~logger();

        /**
         * @brief Updates the minimum level to be logged.
         * @param type Level that triggers the logger.
         */
        inline void set_level(MessageLevelType type);

        /**
         * @brief Returns the default level
         * @return Current level that triggers the logger.
         */
        inline MessageLevelType level();

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

    private:
        std::shared_ptr<spdlog::logger> logger_{nullptr};
        logger::MessageLevelType type_{MessageLevelType::Info};
        std::string msg_{""};
    };

    logger::logger(const edsp::string_view& file, logger::MessageLevelType message_type) :
        logger_(spdlog::get(file.data())),
        type_(message_type),
        msg_() {
        set_level(default_level());
    }

    logger::logger(logger::MessageLevelType message_type) :
        logger_(spdlog::get("console")),
        type_(message_type),
        msg_() {
        set_level(default_level());
    }

    logger::~logger() {
        msg_ += '\n';
        switch (type_) {
            case MessageLevelType::Debug:
                logger_->debug(msg_);
                break;
            case MessageLevelType::Info:
                logger_->info(msg_);
                break;
            case MessageLevelType::Warning:
                logger_->warn(msg_);
                break;
            case MessageLevelType::Critical:
                logger_->critical(msg_);
                break;
            case MessageLevelType::Error:
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

    logger::MessageLevelType logger::default_level() {
        switch (global_level()) {
            case spdlog::level::debug:
                return MessageLevelType::Debug;
            case spdlog::level::info:
                return MessageLevelType::Info;
            case spdlog::level::warn:
                return MessageLevelType::Warning;
            case spdlog::level::critical:
                return MessageLevelType::Critical;
            case spdlog::level::err:
                return MessageLevelType::Error;
            default:
                return MessageLevelType::Off;
        }
    }

    void logger::set_default_level(logger::MessageLevelType type) {
        auto& LEVEL = global_level();
        switch (type) {
            case MessageLevelType::Debug:
                LEVEL = spdlog::level::debug;
                break;
            case MessageLevelType::Info:
                LEVEL = spdlog::level::info;
                break;
            case MessageLevelType::Warning:
                LEVEL = spdlog::level::warn;
                break;
            case MessageLevelType::Critical:
                LEVEL = spdlog::level::critical;
                break;
            case MessageLevelType::Error:
                LEVEL = spdlog::level::err;
                break;
            default:
                LEVEL = spdlog::level::off;
                break;
        }
    }

    void logger::set_level(logger::MessageLevelType type) {
        switch (type) {
            case MessageLevelType::Debug:
                logger_->set_level(spdlog::level::debug);
                break;
            case MessageLevelType::Info:
                logger_->set_level(spdlog::level::info);
                break;
            case MessageLevelType::Warning:
                logger_->set_level(spdlog::level::warn);
                break;
            case MessageLevelType::Critical:
                logger_->set_level(spdlog::level::critical);
                break;
            case MessageLevelType::Error:
                logger_->set_level(spdlog::level::err);
                break;
            default:
                logger_->set_level(spdlog::level::off);
                break;
        }
    }

    logger::MessageLevelType logger::level() {
        switch (logger_->level()) {
            case spdlog::level::debug:
                return MessageLevelType::Debug;
            case spdlog::level::info:
                return MessageLevelType::Info;
            case spdlog::level::warn:
                return MessageLevelType::Warning;
            case spdlog::level::critical:
                return MessageLevelType::Critical;
            case spdlog::level::err:
                return MessageLevelType::Error;
            default:
                return MessageLevelType::Off;
        }
    }

}} // namespace edsp::core

#define eInfo() edsp::logger("console", logger::MessageLevelType::Info)
#define eDebug() edsp::logger("console", logger::MessageLevelType::Debug)
#define eWarning() edsp::logger("console", logger::MessageLevelType::Warning)
#define eCritical() edsp::logger("console", logger::MessageLevelType::Critical)
#define eError() edsp::logger("console", logger::MessageLevelType::Error)

#endif //EDSP_LOGGER_HPP
