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


#ifndef _FL_BASE64_H_
#define _FL_BASE64_H_

#include "../Fl_String_List.h" 	/* needed for string operaions */
#include "../Fl_Buffer.h"		/* needed for buffer operations */

class FL_API Fl_Base64
{
public:
	Fl_Base64() { } 	/** Default constructor */
	~Fl_Base64() { } 	/** Default destructor */

	/**
	 * encode() method encodes (base64) given buffer bufSource
	 * to given destination buffer bufDest.
	 *
	 * @param bufDest Fl_Buffer Destination buffer
	 * @param bufSource Fl_Buffer Source buffer
	 * @see encode(Fl_String& strDest, const Fl_Buffer& bufSource)
	 * @author Dejan Lekic, http://dejan.nu6.org
	 */
	static void encode(Fl_Buffer& bufDest, const Fl_Buffer& bufSource);

	/**
	 * This encode() method encodes (base64) given buffer bufSource
	 * and returns Fl_String object.
	 *
	 * @param strDest Fl_String Destination string
	 * @param bufSource Fl_Buffer* Source buffer	 
	 * @see encode(Fl_Buffer& bufDest, const Fl_Buffer& bufSource)
	 * @author Dejan Lekic, http://dejan.nu6.org
	 */
	static void encode(Fl_String& strDest, const Fl_Buffer& bufSource);

	/** Decodes base64 encoded buffer "string" into buffer "bufDest" */
	static int decode(Fl_Buffer &bufDest, const Fl_Buffer &bufSource);
		
	/** Decodes base64 encoded string "sArg" into buffer "bufDest" */
	static int decode(Fl_Buffer &bufDest, const Fl_String &strSource);
}; /* class Fl_Base64 */

#endif

/***** $Id$
 *     Project: eFLTK
 ***   This source code is released under GNU LGPL License
 *     Copyright (c) EDE Team, 2000-DWYRT  (DWYRT = Date When You Read This)
 ***** Equinox Desktop Environment, http://ede.sf.net */
