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

#include "logger.h"

#include <stdlib.h>

#include <exception>

namespace SN {
namespace Log {

// Initialize static member variables
Logger_C* Logger_C::m_instance = nullptr;

LogStreamMap_TP Logger_C::m_stream_map = {
    {LogSeverityLevel_TP::LOG_TRACE, &std::cout},
    {LogSeverityLevel_TP::LOG_DEBUG, &std::cout},
    {LogSeverityLevel_TP::LOG_INFO, &std::cout},
    {LogSeverityLevel_TP::LOG_WARN, &std::cerr},
    {LogSeverityLevel_TP::LOG_ERROR, &std::cerr},
    {LogSeverityLevel_TP::LOG_FATAL, &std::cerr}};

// Logger_C class member definitions
Logger_C::Logger_C()
    : m_active_log_level(LogSeverityLevel_TP::LOG_INFO),
      m_time_stamp_mode(TimeStampMode_TP::DATE_TIME),
      m_log_file_name("supernova_log.txt"),
      m_format("[%T] [%F:%C %P] [%L] :: %S") {
    m_str_stream.str(std::string());
    m_str_stream.clear();
#ifdef _DEBUG
    m_log_severity_level = LogSeverityLevel_TP::LOG_TRACE;
    m_log_type = LogType_TP::BOTH;
#else
    m_log_severity_level = LogSeverityLevel_TP::LOG_INFO;
    m_log_type = LogType_TP::FILE_LOG;
#endif
}

void Logger_C::Init(const std::string& file_name, bool append /*= false*/) {
    if (m_log_type == LogType_TP::FILE_LOG || m_log_type == LogType_TP::BOTH) {
        if (!file_name.empty()) {
            try {
                m_file_stream.open(file_name.c_str(),
                                   append
                                       ? std::ofstream::out | std::ofstream::app
                                       : std::ofstream::out);
                if (!m_file_stream.is_open()) {
                    throw std::runtime_error("Couldn't open file " + file_name +
                                             " for write.");
                }
            } catch (std::exception& ex) {
                std::cerr << "[ERROR] : " << ex.what() << std::endl;
            }
        } else {
            std::cerr << "[ERROR] : No log file specified." << std::endl;
        }
    } else {
        std::cout
            << "[INFO] : Cannot log into the file. Log type is not a FILE_LOG"
            << std::endl;
    }
}

void Logger_C::FlushOut() {
    if (m_str_stream.str().size() != 0) {
        // For file logs
        if (m_log_type == LogType_TP::FILE_LOG ||
            m_log_type == LogType_TP::BOTH) {
            if (m_file_stream.is_open()) {
                m_file_stream << m_str_stream.str() << std::endl;
                // TODO (ayadav): Add some flushing policies to avoid overhead
                // of writting to a file TRACE and DEBUG are less imporant
                // messages than others. We need to think somethig in that
                // direction
                m_file_stream.flush();
            }
        }
        // For console logs
        if (m_log_type == LogType_TP::CONSOLE_LOG ||
            m_log_type == LogType_TP::BOTH) {
            auto& stream = m_stream_map[m_active_log_level];
            if (stream) {
                *stream << m_str_stream.str() << std::endl;
                stream->flush();
            }
        }
        // Abort if a fatal log has been encountered
        if (m_log_type != LogType_TP::NO_LOG &&
            m_active_log_level == LogSeverityLevel_TP::LOG_FATAL) {
#ifdef _DEBUG
            std::cerr << "[ERROR] : A fatal log has been encountered."
                      << std::endl;
#endif
            std::abort();
        }
    }
}

void Logger_C::LogWrite(LogSeverityLevel_TP level, std::string file,
                        std::string func, uint32_t line, std::string message) {
    // Compare with minimum log severity level
    if (m_log_severity_level <= level) {
        // Set the active log level
        m_active_log_level = level;
        // Crear the stream
        m_str_stream.str(std::string());
        m_str_stream.clear();
        // Write the log
        const char* format_ptr = m_format.c_str();
        while (*format_ptr != 0) {
            if (*format_ptr == '%') {
                switch (*++format_ptr) {
                    case 0:
                        m_str_stream << '%' << std::endl;
                        break;
                    case '%':
                        m_str_stream << '%';
                        break;
                    case 'T':
                        m_str_stream << m_time_stamp_mode;
                        break;
                    case 'F':
                        m_str_stream << file;
                        break;
                    case 'C':
                        if (line != 0) {
                            m_str_stream << line;
                        } else {
                            m_str_stream << "??";
                        }
                        break;
                    case 'P':
                        m_str_stream << func;
                        break;
                    case 'L':
                        m_str_stream << level;
                        break;
                    case 'S':
                        m_str_stream << message;
                        break;
                    default:
                        break;
                }
            } else {
                m_str_stream << *format_ptr;
            }
            ++format_ptr;
        }
        // flush out to avoid losing any log entry
        FlushOut();
    }
}

}  // end namespace Log
}  // namespace SN
