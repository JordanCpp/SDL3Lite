
#include <SDL3/Result.hpp>

Result::Result()
{
	Clear();
}

bool Result::Ok()
{
	return _ok;
}

const char* Result::Message()
{
	return _message.Str();
}

void Result::Message(const char* message)
{
	Message(message, "");
}

void Result::Message(const char* message, const char* detail)
{
	Clear();

	_message.Append(message);
	_message.Append(detail);
}

void Result::Clear()
{
	_ok = true;
	_message.Clear();
}
