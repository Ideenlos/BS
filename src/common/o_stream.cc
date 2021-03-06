/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                      O _ S T R E A M                                          *
 *                                                                                               *
 \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "common/o_stream.h"

O_Stream::O_Stream() : Stringbuffer(), fgColor(WHITE), bgColor(BLACK), blink(false), base(dec) {}

O_Stream::~O_Stream() {}

char* revStr(char* s) {
	char c;
	char* s0 = s - 1;
	char* s1 = s;

	while (*s1)
		++s1;
	/* Reverse it */
	while (s1-- > ++s0) {
		c = *s0;
		*s0 = *s1;
		*s1 = c;
	}
	return s;
}

char* toString(char* s, unsigned long value, int base) {
	int i = 0;

	if (value == 0) {
		s[0] = '0';
		++i;
	}

	while (value) {
		s[i] = value % base;
		s[i] = s[i] + ((s[i] > 9) ? 87 : 48); //normal numbers: 48-57; lowercase letters from: 97-122
		i++;
		value = value / base;
	}

	switch (base) { // prefix of string
	case 2:
		s[i++] = 'b';
		s[i++] = '0';
		break;
	case 8:
		s[i++] = '0'; //oktal starts with 0
		break;
	case 16:
		s[i++] = 'x'; //hexadezimal starts with 0x
		s[i++] = '0';
		break;
	default:
		break;
	}
	return revStr(s);
}

// Operationen auf Text:

O_Stream& O_Stream::operator <<(char value) {
	put(value);
	flush();
	return *this;
}

O_Stream& O_Stream::operator <<(unsigned char value) {
	put((char) value);
	flush();
	return *this;
}

O_Stream& O_Stream::operator <<(char* value) {
	int i = 0;
	while (value[i] != 0) {
		put(value[i]);
		i++;
	}
	return *this;
}

O_Stream& O_Stream::operator <<(const char* value) {
	return *this << (char*) (value);
}

O_Stream& O_Stream::operator <<(short value) {
	return *this << (int) (value);
}

O_Stream& O_Stream::operator <<(unsigned short value) {
	return *this << (unsigned int) (value);
}

O_Stream& O_Stream::operator <<(int value) {
	return *this << (long) (value);
}

O_Stream& O_Stream::operator <<(unsigned int value) {
	return *this << (unsigned long) (value);
}

O_Stream& O_Stream::operator <<(long value) {
	char text[TEXT_SIZE] = { 0 };
	if (value < 0) {
		value = (-value);
		return *this << '-' << toString(text, (unsigned long) value, base);
	}
	return *this << toString(text, (unsigned long) value, base);
}

O_Stream& O_Stream::operator <<(unsigned long value) {
	char text[TEXT_SIZE] = { 0 };
	return *this << toString(text, value, base) << '\0';
}

O_Stream& O_Stream::operator <<(void* value) {
	char text[POINTER_SIZE] = { 0 };
	return *this << toString(text, (unsigned long) (value), hex);
}

O_Stream& O_Stream::operator <<(FGColor color) {
	flush();
	fgColor = color.color;
	setAttributes(fgColor, bgColor, blink);
	return *this;
}

O_Stream& O_Stream::operator <<(BGColor color) {
	flush();
	bgColor = color.color;
	setAttributes(fgColor, bgColor, blink);
	return *this;
}

O_Stream& O_Stream::operator <<(Blink blink) {
	flush();
	this->blink = blink.blink;
	setAttributes(fgColor, bgColor, this->blink);
	return *this;
}


O_Stream& endl(O_Stream& os) {
	os.flush();
	return os << '\n';
}

O_Stream& bin(O_Stream& os) {
	os.base = O_Stream::bin;
	return os;
}

O_Stream& oct(O_Stream& os) {
	os.base = O_Stream::oct;
	return os;
}

O_Stream& dec(O_Stream& os) {
	os.base = O_Stream::dec;
	return os;
}

O_Stream& hex(O_Stream& os) {
	os.base = O_Stream::hex;
	return os;
}

O_Stream& O_Stream::operator <<(O_Stream& (*f)(O_Stream&)) {
	return f(*this);
}
