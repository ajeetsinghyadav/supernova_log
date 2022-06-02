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
 * Created:   DEC-2020
 *
 * Autodoc:   yes
 * ----------------------------------------------------------------------
 */

#include "logger.h"
#include "log_message_sink.h"

namespace SN {
namespace Log {

LogMessageShink_C::LogMessageShink_C(LogSeverityLevel_TP level,
                                     const std::string& file,
                                     const std::string& func,
                                     uint32_t line)
    : m_log_severity_level(level),
      m_file_name(file),
      m_function_name(func),
      m_line_number(line) {
}

LogMessageShink_C::LogMessageShink_C(const LogMessageShink_C& rhs)
    : m_log_severity_level(rhs.m_log_severity_level),
      m_file_name(rhs.m_file_name),
      m_function_name(rhs.m_function_name),
      m_line_number(rhs.m_line_number) {
}

LogMessageShink_C::~LogMessageShink_C() {
  Logger_C::GetInstance()->LogWrite(m_log_severity_level,
                                    m_file_name,
                                    m_function_name,
                                    m_line_number,
                                    m_stream.str());
}

std::ostream& LogMessageShink_C::GetStream() { return m_stream; }

}  // namespace Log
}  // namespace SN
