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

#include "log/logger.h"

#include <gtest/gtest.h>

#include <type_traits>

using namespace SN;

namespace Log_Test {
TEST(Logger_Test, CanPrintLogLevelTrace) {
    std::ostringstream stream;
    Log::LogSeverityLevel_TP logLevel = Log::LogSeverityLevel_TP::LOG_TRACE;
    stream << logLevel;
    EXPECT_EQ("TRACE", stream.str());
}

TEST(Logger_Test, CanPrintLogLevelDebug) {
    std::ostringstream stream;
    Log::LogSeverityLevel_TP logLevel = Log::LogSeverityLevel_TP::LOG_DEBUG;
    stream << logLevel;
    EXPECT_EQ("DEBUG", stream.str());
}

TEST(Logger_Test, CanPrintLogLevelInfo) {
    std::ostringstream stream;
    Log::LogSeverityLevel_TP logLevel = Log::LogSeverityLevel_TP::LOG_INFO;
    stream << logLevel;
    EXPECT_EQ("INFO", stream.str());
}

TEST(Logger_Test, CanPrintLogLevelWarn) {
    std::ostringstream stream;
    Log::LogSeverityLevel_TP logLevel = Log::LogSeverityLevel_TP::LOG_WARN;
    stream << logLevel;
    EXPECT_EQ("WARN", stream.str());
}

TEST(Logger_Test, CanPrintLogLevelError) {
    std::ostringstream stream;
    Log::LogSeverityLevel_TP logLevel = Log::LogSeverityLevel_TP::LOG_ERROR;
    stream << logLevel;
    EXPECT_EQ("ERROR", stream.str());
}

TEST(Logger_Test, CanPrintLogLevelFatal) {
    std::ostringstream stream;
    Log::LogSeverityLevel_TP logLevel = Log::LogSeverityLevel_TP::LOG_FATAL;
    stream << logLevel;
    EXPECT_EQ("FATAL", stream.str());
}

TEST(DISABLED_Logger_Test, WhenLogLevelIsUnknown) {
    std::ostringstream stream;
    Log::LogSeverityLevel_TP level = static_cast<Log::LogSeverityLevel_TP>(6);
    typedef std::underlying_type<Log::LogSeverityLevel_TP>::type
        LogSeverityLevel_TP;
    stream << level;
    EXPECT_EQ("??", stream.str());
}

TEST(Logger_Test, WhenNoTimeStampIsSet) {
    std::ostringstream stream;
    Log::TimeStampMode_TP timeStampMode = Log::TimeStampMode_TP::NONE;
    stream << timeStampMode;
    EXPECT_EQ("", stream.str());
}

TEST(Logger_Test, SetTimeStamp) {
    std::ostringstream stream;
    Log::TimeStampMode_TP timeStampMode = Log::TimeStampMode_TP::DATE_TIME;
    stream << timeStampMode;
    // expected result
    auto now =
        std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string time = ctime(&now);
    time.erase(time.length() - 1);
    // Validation
    EXPECT_EQ(time, stream.str());
    ASSERT_EQ(size_t{24}, stream.str().size());
}

TEST(Logger_Test, CanCreateInstance) {
    Log::Logger_C* logger = Log::Logger_C::GetInstance();
    // logger->Log(Log::LogSeverityLevel_TP::LOG_INFO, "This is Info.");
    // EXPECT_EQ("", logger->Log(Log::LogSeverityLevel_TP::LOG_INFO, "This is
    // Info."));
}

TEST(Logger_DeathTest, assertionTest) {
    GTEST_SKIP() << "skipping assertion test.";
    int test_val = 5;
    SN_ASSERT(test_val < 0, "Value should not be less than zero.");
}

}  // namespace Log_Test