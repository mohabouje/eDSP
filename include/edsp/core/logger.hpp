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

#if USE_SPDLOG
#    include <spdlog/spdlog.h>
#else
#    include <iostream>
#endif

#include <edsp/types/string_view.hpp>
#include <type_traits>
#include <sstream>
#include <edsp/meta/unused.hpp>

namespace edsp { inline namespace core {

    class logger {
    public:
        /**
         * The MessageType enum describes the messages that can be sent
         * to a message handler
         */
        enum class MessageType {
            Info = 0, /*!< Information Message */
            Debug,    /*!< Debug Message */
            Warning,  /*!< Warning Message */
            Critical, /*!< Critical Message */
            Error     /*!< Error Message */
        };

        /**
         * @brief Constructs a logger to record log messages of @par message_type
         * for the @par file.
         * @param file File-path to stores the message. Use "console" to output the messages in the terminal.
         * @param message_type Type of the message.
         * @see MessageType
         */
        inline logger(const edsp::string_view& file, MessageType message_type);

        /**
         * @brief Constructs a logger to record log messages of @par message_type in a terminal.
         * @param message_type Type of the message.
         * @see MessageType
         */
        inline explicit logger(MessageType message_type);

        /**
         * @brief Default destructor.
         */
        inline ~logger();

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
#if USE_SPDLOG
        std::shared_ptr<spdlog::logger> logger_{nullptr};
#endif
        logger::MessageType type_{MessageType::Info};
        std::string msg_{""};
    };

    logger::logger(const edsp::string_view& file, logger::MessageType message_type) :
#if USE_SPDLOG
        logger_(spdlog::get(file.data())),
#endif
        type_(message_type),
        msg_() {
        meta::unused(file);
    }

    logger::logger(logger::MessageType message_type) :
#if USE_SPDLOG
        logger_(spdlog::get("console")),
#endif
        type_(message_type),
        msg_() {
    }

    logger::~logger() {
        msg_ += '\n';
#if USE_SPDLOG
        switch (type_) {
            case MessageType::Debug:
                logger_->debug(msg_);
                break;
            case MessageType::Info:
                logger_->info(msg_);
                break;
            case MessageType::Warning:
                logger_->warn(msg_);
                break;
            case MessageType::Critical:
                logger_->critical(msg_);
                break;
            case MessageType::Error:
                logger_->error(msg_);
                break;
        }
#else
        meta::unused(type_);
        std::cout << msg_;
#endif
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

}} // namespace edsp::core

#define eInfo() edsp::logger("console", logger::MessageType::Info)
#define eDebug() edsp::logger("console", logger::MessageType::Debug)
#define eWarning() edsp::logger("console", logger::MessageType::Warning)
#define eCritical() edsp::logger("console", logger::MessageType::Critical)
#define eError() edsp::logger("console", logger::MessageType::Error)

#endif //EDSP_LOGGER_HPP
