/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                         M A I N                                               *
 *                                                                                               *
 \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* INCLUDES */

#include "machine/multiboot.h"
#include "machine/cpu.h"
#include "machine/pic.h"
#include "machine/keyctrl.h"
#include "device/cgastr.h"
#include "user/task1.h"

/* MACROS */

/// \~german  festlegen, welche Aufgabenanwendung verwendet werden soll
/// \~english define which task is desired
#define USE_TASK           10

//load the necessary header and define the class name of the task
#if USE_TASK == 10
#include "user/task1.h"
typedef Task1 TaskClass;

#endif

/* GLOBAL OBJECTS */

PIC pic;
CGA_Stream kout;
Keyboard_Controller keyboard;
CPU cpu;

/* METHODS  */

extern "C" void kernel(uint32_t magic, const Multiboot_Info* info);

/** \brief kernel entry point
 *
 * \param magic bootloader magic value
 * \param info address of multiboot info structure
 *
 * This is the entry point of the operating system.  If this function returns
 * all interrupts will be disabled and the cpu will be halted.
 * 
 **/
void kernel(uint32_t magic, const Multiboot_Info* info) {



	TaskClass task(magic, info);

	task.action();

}
