#ifndef EXCEPTION_EXCEPTION_H
#define EXCEPTION_EXCEPTION_H

#include <string>

/**
* @brief 用于游戏的异常类
*/
class Exception
{
private:
	std::string message_;
public:

	Exception() : message_{} {}

	Exception(const std::string &message) : message_{message} {}

	Exception(const std::string &message, const Exception &parent)
	{
		message_ = message + ":\n" + parent.message_;
	}

	Exception(const Exception &obj) : message_{obj.message_} {}

	~Exception() = default;

	const char *what()
	{
		return message_.c_str();
	}
};

#endif // !EXCEPTION_EXCEPTION_H
