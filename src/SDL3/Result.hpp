
#ifndef SDL3Lite_Result_hpp
#define SDL3Lite_Result_hpp

#include <SDL3/Types.h>
#include <SDL3/ShortStr.hpp>

class Result
{
public:
	Result();
	bool Ok();
	const char* Message();
	void Message(const char* message);
	void Message(const char* message, const char* detail);
private:
	void Clear();
	bool        _ok;
	ShortString _message;
};

#endif
