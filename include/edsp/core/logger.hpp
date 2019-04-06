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
* Filename: logger.hpp
* Author: Mohammed Boujemaoui
* Date: 07/10/18
*/

#ifndef EDSP_LOGGER_HPP
#define EDSP_LOGGER_HPP

#include <edsp/thirdparty/termcolor/termcolor.hpp>
#include <edsp/types/string_view.hpp>
#include <edsp/meta/unused.hpp>
#include <type_traits>
#include <sstream>
#include <functional>

namespace edsp { inline namespace core {

    inline namespace internal {
        struct logger_impl;
    }

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
         * @brief Updates the pattern of the displayed messages
         * @note Check the documentation of the fmt library.
         */
        inline static void set_pattern(const std::string& pattern);

        /**
         * @brief Constructs a logger to record log messages of message_type
         * for the file.
         * @param name Name or key of the logger.
         * @param file File-path to stores the message. Use "console" to output the messages in the terminal.
         * @param message_type Type of the message.
         * @see MessageLevelType
         */
        inline logger(const edsp::string_view& name, const edsp::string_view& file,
                      levels message_type = levels::trace);

        /**
         * @brief Constructs a logger to record log messages of message_type in a terminal.
         * @param name Name or key of the logger.
         * @param message_type Type of the message.
         * @see MessageLevelType
         */
        inline explicit logger(const edsp::string_view& name, levels message_type = levels::trace);

        /**
         * @brief Created the default logger to record log messages of message_type.
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
         * @brief Writes an space character to the stream and returns a reference to the stream.
         * @return A reference to the stream.
         */
        inline logger& space();

        /**
         * @brief Returns the name of the logger
         * @return Name of the logger
         */
        inline const std::string& name() const;

        /**
         * @brief Returns the current string buffer
         * @return String buffer holding the message.
         */
        inline std::string str() const;

        // clang-format off
        using logger_manipulator = std::function<edsp::core::logger&(edsp::core::logger&)>;
        inline logger& operator<<(logger_manipulator manipulator);
        inline logger& operator<<(std::uint8_t);
        inline logger& operator<<(std::uint16_t);
        inline logger& operator<<(std::uint32_t);
        inline logger& operator<<(std::uint64_t);
        inline logger& operator<<(std::int8_t);
        inline logger& operator<<(std::int16_t);
        inline logger& operator<<(std::int32_t);
        inline logger& operator<<(std::int64_t);
        inline logger& operator<<(float);
        inline logger& operator<<(double);
        inline logger& operator<<(const char*);

        template <typename Char>
        inline logger& operator<<(const std::basic_string<Char>& str);

        template <typename Char>
        inline logger& operator<<(const edsp::basic_string_view<Char>& str);
        // clang-format on

    private:
        /**
         * @brief Returns a reference to the global level used in all spdlog-loggers
         *
         * @note Avoids duplications of the initialization code in every place where the header is included.
         * @return Reference to the global level used in all spdlog-loggers
         */
        static levels& global_level() {
            static levels LEVEL = levels::trace;
            return LEVEL;
        }

        /**
         * @brief Returns a reference to the global file path used to save the spd-loggers
         *
         * @note Avoids duplications of the initialization code in every place where the header is included.
         * @return Reference to the global file path
         */
        static std::string& global_path() {
            static std::string FILE{};
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
        friend struct internal::logger_impl;
        logger::levels type_{levels::info};
        std::stringstream msg_;
        std::string name_;
        std::string file_;
    };

    inline namespace internal {
        struct logger_impl {
            inline static logger& tab(logger& stream) {
                return stream << '\t';
            }

            inline static logger& endl(logger& stream) {
                return stream << '\n';
            }

            inline static logger& red(logger& stream) {
                stream.msg_ << termcolor::colorize;
                stream.msg_ << termcolor::red;
                return stream;
            }

            inline static logger& yellow(logger& stream) {
                stream.msg_ << termcolor::colorize;
                stream.msg_ << termcolor::yellow;
                return stream;
            }

            inline static logger& blue(logger& stream) {
                stream.msg_ << termcolor::colorize;
                stream.msg_ << termcolor::blue;
                return stream;
            }

            inline static logger& cyan(logger& stream) {
                stream.msg_ << termcolor::colorize;
                stream.msg_ << termcolor::cyan;
                return stream;
            }

            inline static logger& white(logger& stream) {
                stream.msg_ << termcolor::colorize;
                stream.msg_ << termcolor::white;
                return stream;
            }

            inline static logger& magenta(logger& stream) {
                stream.msg_ << termcolor::colorize;
                stream.msg_ << termcolor::magenta;
                return stream;
            }

            inline static logger& green(logger& stream) {
                stream.msg_ << termcolor::colorize;
                stream.msg_ << termcolor::green;
                return stream;
            }

            inline static logger& grey(logger& stream) {
                stream.msg_ << termcolor::colorize;
                stream.msg_ << termcolor::grey;
                return stream;
            }

            inline static logger& bold(logger& stream) {
                stream.msg_ << termcolor::colorize;
                stream.msg_ << termcolor::bold;
                return stream;
            }

            inline static logger& endc(logger& stream) {
                stream.msg_ << termcolor::nocolorize;
                stream.msg_ << termcolor::reset;
                return stream;
            }

            inline static logger& reset(logger& stream) {
                stream.msg_ << termcolor::reset;
                return stream;
            }
        };
    } // namespace internal

    /**
     * @brief Inserts the tabular character ('\t') to the current streaming.
     * @param stream Streaming to be modified
     * @return A reference to the stream.
     */
    inline logger& tab(logger& stream) {
        return logger_impl::tab(stream);
    }

    /**
     * @brief Inserts the end line character ('\n') to the current streaming.
     * @note This function does not flush the buffer.
     * @param stream Streaming to be modified
     * @return A reference to the modified stream.
     */
    inline logger& endl(logger& stream) {
        return logger_impl::endl(stream);
    }

    /**
     * @brief Updates the logger output color to red.
     * @param stream Streaming to be modified.
     * @return A reference to the modified stream.
     */
    inline logger& red(logger& stream) {
        return logger_impl::red(stream);
    }

    /**
     * @brief Updates the logger output color to yellow.
     * @param stream Streaming to be modified.
     * @return A reference to the modified stream.
     */
    inline logger& yellow(logger& stream) {
        return logger_impl::yellow(stream);
    }

    /**
     * @brief Updates the logger output color to blue.
     * @param stream Streaming to be modified.
     * @return A reference to the modified stream.
     */
    inline logger& blue(logger& stream) {
        return logger_impl::blue(stream);
    }

    /**
    * @brief Updates the logger output color to cyan.
    * @param stream Streaming to be modified.
    * @return A reference to the modified stream.
    */
    inline logger& cyan(logger& stream) {
        return logger_impl::cyan(stream);
    }

    /**
    * @brief Updates the logger output color to white.
    * @param stream Streaming to be modified.
    * @return A reference to the modified stream.
    */
    inline logger& white(logger& stream) {
        return logger_impl::white(stream);
    }

    /**
     * @brief Updates the logger output color to magenta.
     * @param stream Streaming to be modified.
     * @return A reference to the modified stream.
     */
    inline logger& magenta(logger& stream) {
        return logger_impl::magenta(stream);
    }

    /**
     * @brief Updates the logger output color to green.
     * @param stream Streaming to be modified.
     * @return A reference to the modified stream.
     */
    inline logger& green(logger& stream) {
        return logger_impl::green(stream);
    }

    /**
     * @brief Updates the logger output color to grey.
     * @param stream Streaming to be modified.
     * @return A reference to the modified stream.
     */
    inline logger& grey(logger& stream) {
        return logger_impl::grey(stream);
    }

    /**
     * @brief Updates the logger output text style to bold style.
     * @param stream Streaming to be modified.
     * @return A reference to the modified stream.
     */
    inline logger& bold(logger& stream) {
        return logger_impl::bold(stream);
    }

    /**
     * @brief End of color, styled streaming.
     * @param stream Streaming to be modified.
     * @return A reference to the modified stream.
     */
    inline logger& endc(logger& stream) {
        return logger_impl::endc(stream);
    }

    /**
     * @brief Resets the logger to default configuration.
     * @param stream Streaming to be modified.
     * @return A reference to the modified stream.
     */
    inline logger& reset(logger& stream) {
        return logger_impl::reset(stream);
    }

    logger::logger(const edsp::string_view& name, const edsp::string_view& file, logger::levels message_type) :
        type_(message_type),
        msg_(),
        name_(name),
        file_(file) {}

    logger::logger(const edsp::string_view& name, logger::levels message_type) : logger(name, "", message_type) {}

    logger::logger(logger::levels message_type) : logger(global_name(), "", message_type) {}

    logger::~logger() {
        edsp::endc(*this);
        std::cout << msg_.str();
    }

    logger& logger::space() {
        msg_ << ' ';
        return *this;
    }

    logger::levels logger::default_level() {
        return global_level();
    }

    void logger::set_default_level(logger::levels type) {
        auto& LEVEL = global_level();
        LEVEL       = type;
    }

    void logger::set_level(logger::levels type) {
        type_ = type;
    }

    logger::levels logger::level() {
        return type_;
    }

    const std::string& logger::name() const {
        return name_;
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

    logger& logger::operator<<(logger::logger_manipulator manipulator) {
        return manipulator(*this);
    }

    std::string logger::str() const {
        return msg_.str();
    }

    template <typename Char>
    logger& logger::operator<<(const std::basic_string<Char>& str) {
        msg_ << str.data();
        return space();
    }

    template <typename Char>
    logger& logger::operator<<(const edsp::basic_string_view<Char>& str) {
        msg_ << str.data();
        return space();
    }

    logger& logger::operator<<(std::uint8_t value) {
        msg_ << value;
        return space();
    }

    logger& logger::operator<<(std::uint16_t value) {
        msg_ << value;
        return space();
    }

    logger& logger::operator<<(std::uint32_t value) {
        msg_ << value;
        return space();
    }

    logger& logger::operator<<(std::uint64_t value) {
        msg_ << value;
        return space();
    }

    logger& logger::operator<<(std::int8_t value) {
        msg_ << value;
        return space();
    }

    logger& logger::operator<<(std::int16_t value) {
        msg_ << value;
        return space();
    }

    logger& logger::operator<<(std::int32_t value) {
        msg_ << value;
        return space();
    }

    logger& logger::operator<<(std::int64_t value) {
        msg_ << value;
        return space();
    }

    logger& logger::operator<<(float value) {
        msg_ << value;
        return space();
    }

    logger& logger::operator<<(double value) {
        msg_ << value;
        return space();
    }

    logger& logger::operator<<(const char* str) {
        msg_ << str;
        return space();
    }

    void logger::set_pattern(const std::string& pattern) {
        meta::unused(pattern, "to be implemented");
    }

}} // namespace edsp::core

#define eTrace() edsp::logger(edsp::logger::levels::trace)
#define eInfo() edsp::logger(edsp::logger::levels::info)
#define eDebug() edsp::logger(edsp::logger::levels::debug)
#define eWarning() edsp::logger(edsp::logger::levels::warning)
#define eCritical() edsp::logger(edsp::logger::levels::critical)
#define eError() edsp::logger(edsp::logger::levels::error)

#endif //EDSP_LOGGER_HPP
