#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/expressions.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <iostream>
#include <memory>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace logging = boost::log;


// Interface Class to interact with LogSystem and MockLogSystem

class ILogSystem 
{
public:
    virtual ~ILogSystem() {}
    virtual void trace(const std::string& message) = 0;
    virtual void debug(const std::string& message) = 0;
    virtual void info(const std::string& message) = 0;
    virtual void warning(const std::string& message) = 0;
    virtual void error(const std::string& message) = 0;
    virtual void fatal(const std::string& message) = 0;
};

class LogSystem : public ILogSystem 
{
public:
    LogSystem()
    {
        logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::trace);
    }

    void trace(const std::string& message) override 
    {
        BOOST_LOG_TRIVIAL(trace) << message;
    }

    void debug(const std::string& message) override 
    {
        BOOST_LOG_TRIVIAL(debug) << message;
    }

    void info(const std::string& message) override 
    {
        BOOST_LOG_TRIVIAL(info) << message;
    }

    void warning(const std::string& message) override 
    {
        BOOST_LOG_TRIVIAL(warning) << message;
    }

    void error(const std::string& message) override 
    {
        BOOST_LOG_TRIVIAL(error) << message;
    }

    void fatal(const std::string& message) override 
    {
        BOOST_LOG_TRIVIAL(fatal) << message;
    }
};

using MyLibPtr = std::shared_ptr < ILogSystem >;

class LogSystemMock : public ILogSystem
{
public:
    LogSystemMock()
    {
        std::cout << "test123" << std::endl;
        logging::add_file_log(
            logging::keywords::file_name = "my_log.log",
            logging::keywords::rotation_size = 10 * 1024 * 1024,
            logging::keywords::auto_flush = true,
            logging::keywords::format = (
                logging::expressions::stream << logging::trivial::severity << ": "
                << logging::expressions::smessage
                )
        );
    }

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
protected:
    MyLibPtr m_mylib;
public:
    Myapp(MyLibPtr mylib) : m_mylib(mylib) 
    {
        std::cout << "test123" << std::endl;
        logging::add_file_log(
            logging::keywords::file_name = "my_log1.log",
            logging::keywords::rotation_size = 10 * 1024 * 1024,
            logging::keywords::auto_flush = true,
            logging::keywords::format = (
                logging::expressions::stream << logging::trivial::severity << ": "
                << logging::expressions::smessage
                )
        );
    }
    void triggerTrace() 
    {
        m_mylib->trace("This is a trace message");
    }

    void triggerDebug() 
    {
        m_mylib->debug("This is a debug message");
    }

    void triggerInfo() 
    {
        m_mylib->info("This is an info message");
    }

    void triggerWarning() 
    {
        m_mylib->warning("This is a warning message");
    }

    void triggerError() 
    {
        m_mylib->error("This is an error message");
    }

    void triggerFatal() 
    {
        m_mylib->fatal("This is a fatal message");
    }
};

TEST(LoggingTest, TriggerLoggingLevels)
{
    auto mockLog = std::make_shared<LogSystemMock>();
    Myapp app(mockLog);

    // Set expectations for each logging level
    EXPECT_CALL(*mockLog, trace("This is a trace message")).Times(1);
    EXPECT_CALL(*mockLog, debug("This is a debug message")).Times(1);
    EXPECT_CALL(*mockLog, info("This is an info message")).Times(1);
    EXPECT_CALL(*mockLog, warning("This is a warning message")).Times(1);
    EXPECT_CALL(*mockLog, error("This is an error message")).Times(1);
    EXPECT_CALL(*mockLog, fatal("This is a fatal message")).Times(1);

    app.triggerTrace();
    app.triggerDebug();
    app.triggerInfo();
    app.triggerWarning();
    app.triggerError();
    app.triggerFatal();

    // Verify the expected method calls on the mock
    ::testing::Mock::VerifyAndClearExpectations(mockLog.get());
}


int main(int argc, char** argv) 
{
	::testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}