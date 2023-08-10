#include <boost/log/trivial.hpp>
#include <iostream>
#include <memory>

#include "gmock/gmock.h"
#include "gtest/gtest.h"


// Interface Class to interact with LogSystem and MockLogSystem

class ILogSystem {
public:
    virtual ~ILogSystem() {}
    virtual void trace(const std::string& message) = 0;
    virtual void debug(const std::string& message) = 0;
    virtual void info(const std::string& message) = 0;
    virtual void warning(const std::string& message) = 0;
    virtual void error(const std::string& message) = 0;
    virtual void fatal(const std::string& message) = 0;
};

/*
class LogSystem
{
public:
    virtual ~ILogSystem() {}
    ....
    virtual void fatal() override {}
};
*/

using MyLibPtr = std::shared_ptr < ILogSystem >;

class LogSystemMock : public ILogSystem
{
public:
    virtual ~LogSystemMock() {}
    MOCK_METHOD(void, trace, (const std::string& message), (override));
    MOCK_METHOD(void, debug, (const std::string& message), (override));
    MOCK_METHOD(void, info, (const std::string& message), (override));
    MOCK_METHOD(void, warning, (const std::string& message), (override));
    MOCK_METHOD(void, error, (const std::string& message), (override));
    MOCK_METHOD(void, fatal, (const std::string& message), (override));
};

class Myapp
{
    MyLibPtr m_mylib;
public:
    Myapp(MyLibPtr mylib) : m_mylib(mylib) {}
};

TEST(LoggingTest, TraceMessage) {
    LogSystemMock mockLog;
    EXPECT_CALL(mockLog, trace("This is a trace message")).Times(1);

    // Call the method that uses the logging functionality
    // and expects it to call the mock method trace("This is a trace message")
}

int main(int argc, char** argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}