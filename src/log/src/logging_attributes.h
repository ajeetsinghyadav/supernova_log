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
 * Created:   MAY-2021
 *
 * Autodoc:   yes
 * ----------------------------------------------------------------------
 */

#pragma once

// Standard Includes
#include <chrono>
#include <ctime>
#include <iostream>
#include <map>
#include <string>

namespace SN {
namespace Log {

/**
 * @enum LogSeverityLevel_TP
 *
 * @brief Log severity levels
 *
 */
enum class LogSeverityLevel_TP {
    LOG_TRACE = 0,  //!< Trace level message(0)
    LOG_DEBUG = 1,  //!< Debug-level message(1)
    LOG_INFO = 2,   //!< Info-level message(2)
    LOG_WARN = 3,   //!< Warning-level message(3)
    LOG_ERROR = 4,  //!< Error-level message(4)
    LOG_FATAL = 5   //!< Fatal-level message(5)
};

/**
 * Stream operator<< for the log severity level
 *
 * @param stream output stream
 * @param log_severity_level enum
 * 
 * @retval output stream
 *
 */
inline std::ostream& operator<<(std::ostream& stream,
                                const LogSeverityLevel_TP& log_severity_level) {
    switch (log_severity_level) {
        case LogSeverityLevel_TP::LOG_TRACE:
            stream << "TRACE";
            break;
        case LogSeverityLevel_TP::LOG_DEBUG:
            stream << "DEBUG";
            break;
        case LogSeverityLevel_TP::LOG_INFO:
            stream << "INFO";
            break;
        case LogSeverityLevel_TP::LOG_WARN:
            stream << "WARN";
            break;
        case LogSeverityLevel_TP::LOG_ERROR:
            stream << "ERROR";
            break;
        case LogSeverityLevel_TP::LOG_FATAL:
            stream << "FATAL";
            break;
        default:
            stream << "??";
            std::cerr << "Unknown log level: " << log_severity_level
                      << std::endl;
            break;
    }
    return stream;
}

/**
 * @enum TimeStampMode_TP
 *
 * @brief Time stamp options fo log messages
 *
 */
enum class TimeStampMode_TP {
    NONE = 0,                 //!< No time stamp in log messages(0)
    EPOCH_SECONDS = 1,        //!< Epoch seconds count time stamp(1)
    EPOCH_MILLI_SECONDS = 2,  //!< Epoch milliseconds count time stamp(2)
    EPOCH_MICRO_SECONDS = 3,  //!< Epoch microseconds count time stamp(3)
    DATE_TIME = 4             //!< Date and time in time stamp(4)
};

/**
 * Stream operator<< for the time stamp mode
 *
 * @param stream output stream
 * @param time_stamp_mode TimeStampMode_TP enum
 * 
 * @retval output stream
 *
 */
inline std::ostream& operator<<(std::ostream& stream,
                                const TimeStampMode_TP& time_stamp_mode) {
    using std::chrono::duration_cast;
    using std::chrono::system_clock;
    std::string time_stamp_str;
    switch (time_stamp_mode) {
        case TimeStampMode_TP::NONE:
            break;
        case TimeStampMode_TP::EPOCH_SECONDS:
            time_stamp_str =
                std::to_string(duration_cast<std::chrono::seconds>(
                                   system_clock::now().time_since_epoch())
                                   .count());
            break;
        case TimeStampMode_TP::EPOCH_MILLI_SECONDS:
            time_stamp_str =
                std::to_string(duration_cast<std::chrono::milliseconds>(
                                   system_clock::now().time_since_epoch())
                                   .count());
            break;
        case TimeStampMode_TP::EPOCH_MICRO_SECONDS:
            time_stamp_str =
                std::to_string(duration_cast<std::chrono::milliseconds>(
                                   system_clock::now().time_since_epoch())
                                   .count());
            break;
        case TimeStampMode_TP::DATE_TIME: {
            auto now = system_clock::to_time_t(system_clock::now());
            time_stamp_str = ctime(&now);
            time_stamp_str.erase(time_stamp_str.length() - 1);
            break;
        }
        default:
            std::cerr << "Wrong time stamp mode: " << time_stamp_mode
                      << std::endl;
            break;
    }
    if (!time_stamp_str.empty()) {
        stream << time_stamp_str;
    }
    return stream;
}

/**
 * @enum LogType_TP
 *
 * @brief Options to log messages on console and file.
 *
 */
enum class LogType_TP {
    NO_LOG = 0,       //!< Disable both console and file logs(0)
    CONSOLE_LOG = 1,  //!< Enable console log(1)
    FILE_LOG = 2,     //!< Enable file log(2)
    BOTH = 3          //!< Enable both console and file logs(3)
};

/**
 * Typedef to store ostream corresponding to the log severity level
 *
 */
typedef std::map<LogSeverityLevel_TP, std::ostream*> LogStreamMap_TP;

}  // end namespace Log
}  // end namespace SN
