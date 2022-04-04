#pragma once


#include <cstddef>
#include <cstdint>

//todo !!must deprecated
//char* itoa(int num, char* buffer, int base);



//winuser.h
void OemToAnsi(const char* in, char* out);
void OemToCharBuff(const char* in, char* out, size_t s);
void CharToOemBuff(const char* in, char* out, size_t s);
