/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                   Technische Informatik II                                    * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                                            P I C                                              * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __pic_include__
#define __pic_include__

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
#include "machine/io_port.h"

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    CLASSES                      #
\* * * * * * * * * * * * * * * * * * * * * * * * */
/** 
 * \~german
 * \brief Treiber für den %PIC (Programmable Interrupt Controller)
 * 
 * Der %PIC (programmierbarer Interruptkontroller) ermöglicht es dem System bestimmte Interrupts 
 * bzw. unterbrechungen zu erlauben oder zu verbieten. Wurden die Interrupts global aktiviert,
 * so legt der PIC fest, welche Interrupts weitergreicht werden um vom System behandelt zu werden. 
 * Es ist wichtig,d ass Interrupts nur behandelt werden, falls der entsprechende Interrupt erlaubt 
 * wurde und die Behandlung im allgemeinen aktiviert ist - siehe dazu die Klasse \ref CPU.
 * 
 * Der %PIC basiert auf Intels 8259 Chip und besteht aus einem Master-Slave %PIC-System.
 * Heutzutage werden sie meist nur "emuliert". Verwendet wird mittlerweile APIC, welcher für 
 * ein Mehrkernbetrieb notwendig ist.
 * 
 * \~english
 * \brief Driver for Programmable Interrupt Controller
 *
 * The %PIC or Programmable Interrupt Controller enables the system to 
 * allow/forbid interrupts. By allowing an interrupt the PIC defines which
 * interrupts are handled by the system. It is important that interrupts will
 * only be handled if the interrupt has been allowed and if the handling of 
 * interrupts is enabled (see class \ref CPU). 
 */
class PIC{
  public:

    /** 
     * \~german
     * \brief Standardkonstruktor
     * 
     * Er initialisiert den PIC und maskiert alle einkommenden Interrupt, damit wird keiner  an
     * die %CPU durchgereicht.
     * 
     * \~english
     * \brief Default Constructor
     *
     * Setting up the PIC and masking all incoming interrupt channels
     */
    PIC();
};

#endif
