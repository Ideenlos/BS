/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                 S T R I N G B U F F E R                                       *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "common/strbuf.h"

/** \todo implement **/
Stringbuffer::Stringbuffer(){
  /* ToDo: Insert Your Code Here */
	pos_ = 0;
}
/** \todo implement **/
Stringbuffer::~Stringbuffer(){
  /* ToDo: Insert Your Code Here */
}
/** \todo implement **/
void Stringbuffer::put(char c) {
   if (pos_ >= BUFFERSIZE) {
      	flush();
   	} else {
    	buffer_[pos_] = c;
     	pos_++;
   }
}
