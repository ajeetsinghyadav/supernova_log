/* ---------------------------------------------------------------------
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the Apache License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Apache License 2.0 for more details.
 *
 * You should have received a copy of the Apache License
 * along with this program.  If not, see
 * https://www.apache.org/licenses/LICENSE-2.0.
 *
 * Copyright (C) 2021 Ajeet Singh Yadav [ er.ajeetsinghyadav@gmail.com ]
 *
 * Author:    Ajeet Singh Yadav
 * Created:   JAN-2021
 *
 * Autodoc:   yes
 * ----------------------------------------------------------------------
 */

/**
 * @file logger.h
 *
 * @brief Logger_C is a core class of the Supernova logging system
 *
 * @author Ajeet Singh Yadav
 * Contact: er.ajeetsinghyadav@gmail.com
 *
 */

#pragma once

// Standards includes
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

// Log includes
#include "log_message_sink.h"
#include "logging_attributes.h"

// Outer namespace
namespace SN {
// Inner namespace
namespace Log {

/** Supernova logging System Core Class
 *
 * @b Description
 * This singleton class is used to log messages for a specific component of this
 * lib.
 *
 * Each log has a severity level associated with it. This class is also
 * support different formatting and filtering of the log.
 *
 * Using this class one can log the file name, function name, and line numbers
 * at point of log. This also supports console logs along with file logs in
 * Debug mode.
 *
 * @b Rationale
 * None
 *
 * @b Resource @b Ownership
 * None
 *
 * @note
 * None
 */

class Logger_C {
   private:
    /**
     * Construct a logger
     */
    Logger_C();

   public:
    /**
     * Copy ctor and assignment operator
     * forbidden by delete
     */
    Logger_C(const Logger_C& rhs) = delete;
    Logger_C& operator=(const Logger_C& rhs) = delete;

   public:
    /**
     * Get the singleton object of the logger class.
     *
     * @retval logger object
     */
    static Logger_C* GetInstance() {
        if (m_instance == nullptr) {
            m_instance = new Logger_C();
        }
        return m_instance;
    }

    /**
     * Open the log file and initialize the out file stream.
     *
     * Checks empty filename error and throws an exception
     * if any run-time error has occurred while opening the log file.
     *
     * @param file_name the name of a log file
     * @param append  a flag for opening mode append
     * @retval None
     */
    void Init(const std::string& file_name, bool append = false);

    /**
     * Flushes out the buffer to avoid any loss of entries upon a crash.
     *
     * @param None
     * @retval None
     */
    void FlushOut();

    /**
     * Writes log messages into the steam
     *
     * @param level log severity level
     * @param file file name at point of log
     * @param func function name at point of log
     * @param line line number at point of log
     * @param message message to be logged
     *
     * @retval None
     *
     */
    void LogWrite(LogSeverityLevel_TP level, std::string file, std::string func,
                  uint32_t line, std::string message);
    /**
     * Sets the minimum severity level of the logger.
     *
     * LOG_INFO is the default value in RELEASE build
     *
     * LOG_TRACE is the default value in the DEBUG build
     *
     * @param severity_level serverity to set
     */
    void SetLogSeverityLevel(LogSeverityLevel_TP severity_level) {
        m_log_severity_level = severity_level;
    }

    /**
     * Gets the minimum severity level of the logger.
     *
     * @retval minimum log severity level
     */
    LogSeverityLevel_TP GetLogSeverityLevel() { return m_log_severity_level; }

    /**
     * Checks if this logger accepts a given log severity level.
     *
     * This logger will only log messages a given severity level or higher.
     *
     * @param severity_level log level to check for
     * @retval true if the logger accepts the log level otherwise false
     */
    bool IsLogSeverityLevel(LogSeverityLevel_TP severity_level) const {
        return m_log_severity_level <= severity_level;
    }

    /**
     * Sets the mode to choose differnt time stamp format
     *
     * DATE_TIME is the default value for the log time format
     *
     * @param time_stamp_mode time stamp mode to set
     */
    void SetTimeStampMode(TimeStampMode_TP time_stamp_mode) {
        m_time_stamp_mode = time_stamp_mode;
    }

    /**
     * Gets the mode of the current timestamp.
     *
     * There are four timestamp modes:
     *
     * Epoch seconds
     *
     * Epoch milliseconds
     *
     * Epoch microseconds
     *
     * Epoch date and time
     *
     * @retval current timestamp mode
     */
    TimeStampMode_TP GetTimeStampMode() { return m_time_stamp_mode; }

    /**
     * Sets the type of log to display the log either on the console or save in
     * a log file
     *
     * FILE_LOG is the deafult value.
     *
     * @param log_type type of log to set
     */
    void SetLogType(LogType_TP log_type) { m_log_type = log_type; }

    /**
     * Enables the logger to display the logs on the console.
     *
     * Sets the m_log_type to CONSOLE_LOG
     *
     */
    void EnableConsoleLogging() { m_log_type = LogType_TP::CONSOLE_LOG; }

    /**
     * Enables the logger to save the log entries in the log file.
     *
     * Sets the m_log_type to FILE_LOG
     *
     */
    void EnableFileLogging() { m_log_type = LogType_TP::FILE_LOG; }

    /**
     * Sets the fullpath and name of the log file.
     *
     * "supernova_log.txt" is the deafult file name.
     *
     * @param file_name log file name to set
     */
    void SetLogFileName(const std::string& file_name) {
        m_log_file_name = file_name;
    }

    /**
     * Gets the log file name
     *
     * @retval current log file name
     *
     */
    const std::string& GetLogFileName() const { return m_log_file_name; }

    /**
     * Sets the log format string
     *
     * "[%T] [%F:%C %P] [%L] :: %S" is the deafult format string.
     *
     * @param format a format string to set
     *
     */
    void SetFormat(const std::string& format) { m_format = format; };

    /**
     * Gets the log format string
     *
     * @retval current format string
     *
     */
    const std::string& GetFormat() const { return m_format; }

    /**
     * Sets the underlying stream to stream map corresponding to log level
     *
     * @param level severity log level
     * @param stream underlying stream
     *
     */
    void SetStream(LogSeverityLevel_TP level, std::ostream& stream) {
        m_stream_map[level] = &stream;
    }

    /**
     * Gets the underlying stream
     *
     * @retval underlying stream
     *
     */
    std::ostream& GetStream() { return m_str_stream; }

   private:
    static Logger_C* m_instance;
    /** A map of default streams and corresponding terminal text color for each
     * log level */
    static LogStreamMap_TP m_stream_map;

    LogSeverityLevel_TP m_log_severity_level;
    LogSeverityLevel_TP m_active_log_level;
    TimeStampMode_TP m_time_stamp_mode;
    LogType_TP m_log_type;

    std::string m_log_file_name;

    std::ostringstream m_str_stream;
    std::ofstream m_file_stream;

    std::string m_format;

};  // end class Logger_C

}  // end namespace Log
}  // end namespace SN

/**
 * Standard predefined function macro
 *
 * @param __func__ The unqualified and unadorned name of encosing function as a
 * function local static const array of char.
 * @param __FUNCTION__ A pre-standard extention that some C compiler supports
 * (gcc and Visual C++)
 *
 */
#ifndef __FUNCTION_NAME__
#ifdef WIN32  // WINDOWS
#define __FUNCTION_NAME__ __FUNCTION__
#else  //*NIX
#define __FUNCTION_NAME__ __func__
#endif
#endif

/**
 * General logging preprocessor Macro
 *
 * @param level severity level to log at
 */
#define SN_LOG(level)                                                        \
    SN::Log::LogMessageShink_C(level, __FILE__, __FUNCTION_NAME__, __LINE__) \
        .GetStream()

#define SN_LOG_TRACE SN_LOG(SN::Log::LogSeverityLevel_TP::LOG_TRACE)
#define SN_LOG_DEBUG SN_LOG(SN::Log::LogSeverityLevel_TP::LOG_DEBUG)
#define SN_LOG_INFO SN_LOG(SN::Log::LogSeverityLevel_TP::LOG_INFO)
#define SN_LOG_WARN SN_LOG(SN::Log::LogSeverityLevel_TP::LOG_WARN)
#define SN_LOG_ERROR SN_LOG(SN::Log::LogSeverityLevel_TP::LOG_ERROR)
#define SN_LOG_FATAL SN_LOG(SN::Log::LogSeverityLevel_TP::LOG_FATAL)

/**
 * Custom assert macro. It evaluates the expr, if it is true continue execution
 * otherwise, crash and print the error message.
 *
 * @param expr a boolean expression for the assertion check
 */
#ifdef _DEBUG
#define SN_ASSERT(expr, ...)                              \
    {                                                     \
        if (!(expr)) {                                    \
            SN_LOG_FATAL << "Assertion Failed: " << #expr \
                         << " :: " << __VA_ARGS__;        \
            __debugbreak();                               \
        }                                                 \
    }
#else
#define SN_ASSERT(expr, ...)
#endif

#ifdef _DEBUG
#define ASSERT_RETURN(condition, ret_val) \
    if (!(condition)) {                   \
        assert(false && #condition);      \
        return ret_val;                   \
    }
#else
#define ASSERT_RETURN(condition, ret_val)
#endif  // _DEBUG

#define CHECK_CONDITION_RETURN(condition, ret_val) \
    do {                                           \
        if (!(condition)) {                        \
            return ret_val;                        \
        }                                          \
    } while (0)

#define CHECK_CONDITION_RETURN_FAILURE(condition) \
    CHECK_CONDITION_RETURN(condition, false)
