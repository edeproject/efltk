/** 
  * Fl_Base64.h
  * This file contains interface to Fl_Base64 class .
  * 
  * The source below is under LGPL license.
  * Authors (sorted by time they worked on this source file):
  * 	Dejan Lekic <dejan§nu6.org>
  * Contributors (ie. people that have sent patches, ideas, suggestions):
  *     None
  **/


#ifndef _FL_BASE64_H
#define _FL_BASE64_H 1

#include <efltk/Fl_String_List.h> 	/* needed for string operaions */
#include <efltk/Fl_Buffer.h>		/* needed for buffer operations */

class FL_API Fl_Base64
{
	public:
		Fl_Base64(); 			/** Default constructor */
		virtual ~Fl_Base64(); 	/** Default destructor */
		void encode(Fl_Buffer* bufDest, Fl_Buffer* bufSource);
		Fl_String encode(Fl_Buffer bufSource);
		/** Decodes base64 encoded buffer "string" into buffer "bufDest" */
		int decode(Fl_Buffer* bufDest, Fl_Buffer* bufSource);
		/** Decodes base64 encoded string "sArg" into buffer "bufDest" */
		int decode(Fl_Buffer* bufDest, Fl_String_List* sArg);
}; /* class Fl_Base64 */


#endif

/***** $id$
 *     Project: eFLTK
 ***   This source code is released under GNU LGPL License
 *     Copyright (c) EDE Team, 2000-DWYRT  (DWYRT = Date When You Read This)
 ***** Equinox Desktop Environment, http://ede.sf.net */
