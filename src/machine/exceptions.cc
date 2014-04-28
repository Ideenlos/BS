/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                     G U A R D I A N                                           *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* INCLUDES */

#include "object/kout.h"
#include "object/cpu.h"

#include <stdint.h>

/* GLOBAL OBJECTS */

/* declare methods as c-like  */
extern "C" void exception(unsigned short slot, void** esp);

struct Exception{
  const char* const name;
  bool isReserved;
  bool hasErrorCode;
};

static const Exception exceptions[32]={
  {"Divide Error"                 , false, false},
  {"RESERVED"                     , true , false},
  {"NMI"                          , true , false},
  {"Breakpoint"                   , false, false},
  {"Overflow"                     , false, false},
  {"BOUND Range Exceeded"         , false, false},
  {"Invalid Opcode"               , false, false},
  {"No Math Coprocessor"          , false, false},
  {"Double Fault"                 , false, true },
  {"Coprocessor Segment Overrun"  , false, false},
  {"Invalid TSS"                  , false, true },
  {"Segment Not Present"          , false, true },
  {"Stack-Segment Fault"          , false, true },
  {"General Protection"           , false, true },
  {"Page Fault"                   , false, true },
  {"RESERVED"                     , true , false},
  {"Divide Error"                 , false, false},
  {"x87 FPU Floating Point Error" , false, false},
  {"Alignement Check"             , false, true },
  {"Machine Check"                , false, false},
  {"SIMD Floating-Point Exception", false, false},
  {"Virtualization Exception"     , false, false},
  {"RESERVED"                     , true , false},
  {"RESERVED"                     , true , false},
  {"RESERVED"                     , true , false},
  {"RESERVED"                     , true , false},
  {"RESERVED"                     , true , false},
  {"RESERVED"                     , true , false},
  {"RESERVED"                     , true , false},
  {"RESERVED"                     , true , false},
  {"RESERVED"                     , true , false},
  {"RESERVED"                     , true , false}
};

/* METHODS  */

void printException(unsigned short slot, void** esp){
  const Exception& e=exceptions[slot];
  //Fehler melden
  kout.clear();
  kout.setpos(0,0);
  kout.flush();
  kout << "Exception "    << slot << ": " << e.name << " occured" << endl;
  if(!e.isReserved){
    esp+=e.hasErrorCode?4:3;
    uint32_t eflags = reinterpret_cast<uint32_t>(*--esp);
    uint32_t cs     = reinterpret_cast<uint32_t>(*--esp);
    void*    eip    = *--esp;

    kout << " eip                   : " << hex << eip    << endl;
    kout << " cs                    : " << dec << cs     << endl;
    kout << " eflags                : " << bin << eflags << endl;

    if(e.hasErrorCode){
      union ErroCode{
        uint32_t value;
        struct{
          uint8_t ext : 1;
          uint8_t idt : 1;
          uint8_t ti  : 1;
          uint16_t segmentSelectorIndex : 13;
        };
      } ec;
      ec.value = *reinterpret_cast<uint32_t*>(*--esp);
      kout << " Segment Selector Index: " << dec << ec.segmentSelectorIndex   << endl;
      kout << " External              : " << (ec.ext?"true":"false")          << endl;
      kout << " Location              : " << (ec.idt?"IDT":ec.ti?"GDT":"LDT") << endl;
    }
  }
  //und anhalten
  cpu.disable_int();
  cpu.halt();
}

/** \brief Entry point for exceptions
 *
 * \param slot number of occurred exception
 * \param esp value of stack pointer on entering of exception
 *
 */
void exception(unsigned short slot, void** esp) {
  if(slot < 32 && slot != 2) {
    printException(slot, esp);
  }
  kout.clear();
  kout.setpos(0,0);
  kout.flush();
  kout << "Unhandled Interrupt: " << slot << " occured" << endl;
}
