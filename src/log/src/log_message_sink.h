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

#pragma once

#include "logging_attributes.h"
#include <sstream>
#include <string>

class Logger_C;

namespace SN {
namespace Log {

class LogMessageShink_C {
 public:
  LogMessageShink_C(LogSeverityLevel_TP level,
                    const std::string& file,
                    const std::string& func,
                    uint32_t line);
  LogMessageShink_C(const LogMessageShink_C& rhs);
  ~LogMessageShink_C();

  std::ostream& GetStream();

 private:
  LogSeverityLevel_TP m_log_severity_level; //! < Log severity level

  std::string m_file_name;      //!< file name of log location
  std::string m_function_name;  //!< function name of log location
  uint32_t m_line_number;       //!< line count of log location

  std::ostringstream m_stream; //!< internal stream of the sink
};

}  // namespace Log
}  // namespace SN
