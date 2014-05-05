/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                    C G A _ S C R E E N                                        *
 *                                                                                               *
 \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "machine/io_port.h"
#include "machine/cgascr.h"
#include "config.h"

char *pos;

IO_Port Indexregister = IO_Port(0x3d4);
IO_Port Dataregister = IO_Port(0x3d5);

CGA_Screen::CGA_Screen() {
	/* Speicherbereich setzen */
	CGAstart = (char *) 0xb8000;
	clear();
	setpos(0, 0);

	/* siehe include/config.h */
	attribute = DEFAULT_SCREEN_ATTRIB;
}

CGA_Screen::~CGA_Screen() {}

void CGA_Screen::setpos(unsigned short x, unsigned short y) {
	/* macht zeilenumbrüche und scrollt automatisch weiter */
	if (y > 24 || (x >= 80 && y == 24)) {
		scrollup();
		x = 0;
		y = 24;
	}
	if (x >= 80 && y < 24) {
		x = 0;
		++y;
	}

	/************************************************
	 * Der Displaykontroller verlangt die Position
	 * des Cursors nach dem Schema y * 80 + x.
	 * Um den Wert zu speichern gibt es zwei Register.
	 * LOW - die unteren 8bit
	 * HIGH - die oberen 6bit
	 *
	 * Bsp: x = 79, y = 24
	 * 24 * 80 + 79 = 1999 (0b11111001111)
	 * Wert im unsigned short: [00000111|11001111]
	 * Wert LOW ist: [11001111]
	 * Wert HIGH ist: [000111]
	 *
	 * Info: http://www.reenigne.org/crtc/mc6845.pdf
	 */
	unsigned short pos;
	pos = (y * 80) + x;

	/* Cursor LOW port */
	Indexregister.outb(15);
	Dataregister.outb((unsigned char) pos); //write new x coordinate

	/* Cursor HIGH port */
	Indexregister.outb(14);
	Dataregister.outb((unsigned char) (pos >> 8)); //write new y coordinate
}

void CGA_Screen::getpos(unsigned short& x, unsigned short& y) const {

	unsigned short x_, y_, pos;

	/* Cursor LOW port */
	Indexregister.outb(15); //get x coordinate
	x_ = Dataregister.inb();

	/* Cursor HIGH port */
	Indexregister.outb(14); //get y coordinate
	y_ = Dataregister.inb();
	y_ = (y_ << 8);

	pos = x_ | y_; //get the position out of the x_(high byte) and y_(low byte)

	x = pos % 80; //get the x back from position
	y = pos / 80; //get the y back from position
}

void CGA_Screen::show(unsigned short x, unsigned short y, char character, unsigned char attribute) {

	unsigned short pos = y * 80 + x;
	CGAstart[pos * 2] = character;
	CGAstart[pos * 2 + 1] = attribute;
}

void CGA_Screen::print(const char* string, unsigned int n) { // n is length

	unsigned short x, y;

	for (unsigned int i = 0; i < n; i++) {
		getpos(x, y);

		if (string[i] == '\n') { //new line
			setpos(0, y + 1);

		} else if (string[i] == '\b') {	//backspace

			if (x == 0 && y != 0) { //backspace at the beginning of line
				show(79, y - 1, 0, attribute);
				setpos(79, y - 1);

			} else if (x != 0) { //backspace in normal cases
				show(x - 1, y, 0, attribute);
				setpos(x - 1, y);
			}

		} else { //print out char
			show(x, y, string[i], attribute);

			if (x > 79) setpos(0, y + 1); //next line
			else setpos(x + 1, y);

		}
	}
}

void CGA_Screen::scrollup() {

	//copy the next column to the higher
	for (int i = 0; i < 3840; i++) { // 3840 - everything except last line
		*(CGAstart + i) = *(CGAstart + i + (80 * 2));
	}

	//fill last line with black spaces
	for (int i = 3840; i < 4000; i++) {
		if (i % 2 == 0) { //even - letters
			*(CGAstart + i) = ' ';
		} else { //odd - attribute
			*(CGAstart + i) = 0x0f;
		}
	}
}

void CGA_Screen::clear() {

	//clear screen and reset the cursor
	unsigned short i, j;
	for (i = 0; i < 80; i++) {
		for (j = 0; j < 25; j++) {
			show(i, j, ' ', 0x0f);
		}
	}
	setpos(0, 0);
}

void CGA_Screen::setAttributes(int fgColor, int bgColor, bool blink) {
	if (fgColor > 15 || fgColor < 0)
	        setAttributes(0xF, bgColor, blink);

	    else {
			unsigned char fgC = (unsigned char) fgColor;
			unsigned char bgC = (unsigned char) bgColor;
			unsigned char bnk = (blink ? 0x80 : 0x00);

			bgC = bgC << 4;

			attribute = bnk | bgC | fgC;
		}
}
