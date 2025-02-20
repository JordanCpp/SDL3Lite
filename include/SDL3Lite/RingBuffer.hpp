/*
Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

#ifndef SDL3Lite_Shared_RingBuffer_hpp
#define SDL3Lite_Shared_RingBuffer_hpp

#include <stddef.h>
#include <string.h>

namespace SDL
{
	template<class T, size_t COUNT>
	class RingBuffer
	{
	public:
		RingBuffer() :
			_head(-1),
			_tail(0),
			_length(0),
			_capacity(COUNT)
		{
			memset(&_content, 0, sizeof(T) * COUNT);
		}

		bool IsEmpty()
		{
			return _length == 0;
		}

		bool IsFull()
		{
			return _length == _capacity;
		}

		int NextPosition(int position)
		{
			return (position + 1) % _capacity;
		}

		bool Dequeue(T& element)
		{
			if (!IsEmpty())
			{
				element = _content[_tail];
				_tail = NextPosition(_tail);
				_length--;

				return true;
			}

			return false;
		}

		void Enqueue(const T& element)
		{
			_head = NextPosition(_head);

			_content[_head] = element;

			if (IsFull())
			{
				_tail = NextPosition(_tail);
			}
			else
			{
				_length++;
			}
		}
	private:
		T   _content[COUNT];
		int _head;
		int _tail;
		int _length;
		int _capacity;
	};
}

#endif