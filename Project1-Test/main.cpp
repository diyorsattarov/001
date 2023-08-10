#include <iostream>
#include <memory>

#include "gmock/gmock.h"
#include "gtest/gtest.h"


class MylibInterface
{
public:
	virtual ~MylibInterface() {}
	virtual int func() = 0;
};

class Mylib : public MylibInterface
{
public:
	virtual ~Mylib() {}
	int func() override
	{
		return 123;
	}
};

using MyLibPtr = std::shared_ptr<MylibInterface>;

class MylibMock : public MylibInterface
{
public:
	virtual ~MylibMock() {}
	MOCK_METHOD(int, func, (), (override));
};

class Myapp {
	// this pointer will be injected by the injector either with pointing
	// to the real object or to the mock object. The interface ensures that both
	// objects have the same method calls.
	// MylibInterface* m_mylib;
	MyLibPtr m_mylib;

public:
	Myapp(MyLibPtr mylib) : m_mylib(mylib) {}
	bool func() {
		int ret = m_mylib->func();
		std::cout << "mylib.func returns: '" << ret << "'\n";
		return true;
	}
};

TEST(MylibTestSuite, mock_mylib_func)
// this test macro can be seen as the injector. It determins what object
// is injected to myapp.
{
	using ::testing::Return;

	// inject a real mylib object to myapp and exersize it
	Myapp myapp(std::make_shared<Mylib>());
	std::cout << "  real ";
	EXPECT_TRUE(myapp.func());

	// inject a mocked mylib object to myapp
	//MylibMock mylib_mock;
	auto lp = std::make_shared<MylibMock>();
	Myapp myapp_mock(lp);

	//EXPECT_CALL(mylib_mock, func())
	EXPECT_CALL(*lp, func())
		.WillOnce(Return(456));

	// and exersize it
	std::cout << "mocked ";
	EXPECT_TRUE(myapp_mock.func());
}

int main(int argc, char** argv) {
	::testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}