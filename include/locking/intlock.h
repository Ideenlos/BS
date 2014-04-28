/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                 I N T E R R U P T L O C K                                     *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __InterruptLock_include__
#define __InterruptLock_include__

#include <object/cpu.h>

/** \~german
 *
 * \~english
 * \brief Concurrancy lock of global interrupts
 *
 * the constructor of this class locks global interrupts to disable interrupt caused concurrancy.
 */
class IntLock {
  private:
    const bool oldState;
  public: 
    /** \~german
     *  \~english
     *  \brief Constructor locking all interrupts and saving old interrupt state
     **/
    IntLock() : oldState(cpu.disable_int()){
    }
    
    /** \~german
     *  \~english
     *  \brief Desctructor restoring interrupt state
     **/
    ~IntLock(){
      if(oldState)
        cpu.enable_int();
    }
};

#endif
