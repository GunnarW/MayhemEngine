#include "MayhemGameHelper.h"

char* MGH::sprintf(const char* message, ...)
{
	va_list args;
	va_start(args, message);

	char* buffer;
	int length = _vscprintf(message, args) + 1;
	buffer = (char*)malloc(length * sizeof(char));
	vsprintf_s(buffer, length, message, args);

	va_end(args);

	return buffer;
}