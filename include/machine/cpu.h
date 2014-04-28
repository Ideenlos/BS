/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                           C P U                                               *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __CPU_include__
#define __CPU_include__

/** \~german
 *
 * \~english
 * \brief Hardware accessor for %CPU specific instructions
 *
 * implementing an abstraction of the processor. It provides methods to
 * enable/disable interrupts globally and to halt the processor.
 */
class CPU {
  public:  
    /** \~german
     *  \~english
     *  \brief globally enable interrupts 
     **/
    inline void enable_int () {
      asm("sti");
    }
    
    /** \~german
     *  \~english
     *  \brief globally dissable interrupts and return previous state
     *  \return previous interrupt state
     **/
    inline bool disable_int () {
      long temp;
      asm(
        "pushf\n\t"
        "cli\n\t"
        "movl (%%esp), %0\n\t"
        "add $4, %%esp \n\t"
        :"=r"(temp)
      );
      return temp;
    }
    
    /** \~german
     *  \~english
     *  \brief halt the cpu
     *
     * When the cpu is halted the program counter will not increase until an
     * interrupt occurs.  If an interrupt occurs the cpu will handle the
     * interrupt and continue with the execution after the hlt command.
     **/
    inline void halt () {
      asm("hlt");
    }
};

#endif
