
#ifndef SDL3Lite_ShortStr_hpp
#define SDL3Lite_ShortStr_hpp

class ShortString
{
public:
	enum
	{
		Max = 64
	};

	ShortString();
	void Clear();
	void Append(const char* source);
	const char* Str();
private:
	char _message[Max];
};

#endif
