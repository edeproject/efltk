/***************************************************************************
                          Fl_Date_Time.h  -  description
                             -------------------
    begin                : Tue Dec 14 1999
    copyright            : (C) 1999 by Alexey Parshin
    email                : alexeyp@m7.tts-sf.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#ifndef __FL_DATE_TIME_H__
#define __FL_DATE_TIME_H__

#include "Fl_Export.h"
#include "Fl_String.h"

class FL_API Fl_Date_Time {
public:
	static char   dateFormat[32];
	static char   timeFormat[32];
	static char   datePartsOrder[4];
	static char   dateSeparator;
	static char   timeSeparator;
	static bool   time24Mode;

    Fl_Date_Time (short y,short m,short d,short hour=0,short minute=0,short second=0);
    Fl_Date_Time (const char * dat);
    Fl_Date_Time (const Fl_Date_Time &dt);
    Fl_Date_Time (const double dt=0);

    void format_date(char *str) const;
    void format_time(char *str, bool ampm=true) const;

	// These functions don't affect the actual system time.
	// You can only alter the time for the current program.
    static void Now(Fl_Date_Time dt);     // Sets to current date and time
    static Fl_Date_Time System();         // Gets to current system date and time
    static Fl_Date_Time Now();            // Gets to current date and time
    static Fl_Date_Time Date();           // Gets to current date
    static Fl_Date_Time Time();           // Gets to current time

    short days_in_month() const;				// Number of days in month (1..31)
    short day_of_week() const;				// (1..7)
    short day_of_year() const;				// returns relative date since Jan. 1

    Fl_String day_name() const;   // Character Day Of Week ('Sunday'..'Saturday')
    Fl_String month_name() const; // Character Month name

    unsigned date() const;                // Numeric date of date object
    short day() const;                    // Numeric day of date object
    short month() const;                  // Month number (1..12)
    short year() const;

    Fl_String date_string() const;
    Fl_String time_string() const;

    void decode_date(short *y,short *m,short *d) const;
    void decode_time(short *h,short *m,short *s,short *ms) const;

    operator double (void) const;

    void operator = (const Fl_Date_Time& date);
    void operator = (const char * dat);

    Fl_Date_Time  operator + (int i);
    Fl_Date_Time  operator - (int i);
    Fl_Date_Time  operator + (Fl_Date_Time& dt);
    Fl_Date_Time  operator - (Fl_Date_Time& dt);

    Fl_Date_Time& operator += (int i);
    Fl_Date_Time& operator -= (int i);
    Fl_Date_Time& operator += (Fl_Date_Time& dt);
    Fl_Date_Time& operator -= (Fl_Date_Time& dt);

    Fl_Date_Time& operator ++ ();     // Prefix increment
    Fl_Date_Time& operator ++ (int);  // Postfix increment
    Fl_Date_Time& operator -- ();     // Prefix decrement
    Fl_Date_Time& operator -- (int);  // Postfix decrement

    friend bool operator <  (const Fl_Date_Time &dt1, const Fl_Date_Time &dt2);
    friend bool operator <= (const Fl_Date_Time &dt1, const Fl_Date_Time &dt2);
    friend bool operator >  (const Fl_Date_Time &dt1, const Fl_Date_Time &dt2);
    friend bool operator >= (const Fl_Date_Time &dt1, const Fl_Date_Time &dt2);
    friend bool operator == (const Fl_Date_Time &dt1, const Fl_Date_Time &dt2);
    friend bool operator != (const Fl_Date_Time &dt1, const Fl_Date_Time &dt2);

protected:
    static void   decode_date(const double dt,short& y,short& m,short& d);
    static void   decode_time(const double dt,short& h,short& m,short& s,short& ms);
    static void   encode_date(double &dt,short y=0,short m=0,short d=0);
    static void   encode_date(double &dt,const char *dat);
    static void   encode_time(double &dt,short h=0,short m=0,short s=0,short ms=0);
    static void   encode_time(double &dt,const char *tim);
    static bool   is_leap_year(const short year);

	double        m_dateTime;
	static double dateTimeOffset;    // The offset from current' system time for synchronization
                                     // with outside system
};

bool operator <  (const Fl_Date_Time &dt1, const Fl_Date_Time &dt2);
bool operator <  (const Fl_Date_Time &dt1, const Fl_Date_Time &dt2);
bool operator <= (const Fl_Date_Time &dt1, const Fl_Date_Time &dt2);
bool operator >  (const Fl_Date_Time &dt1, const Fl_Date_Time &dt2);
bool operator >= (const Fl_Date_Time &dt1, const Fl_Date_Time &dt2);
bool operator == (const Fl_Date_Time &dt1, const Fl_Date_Time &dt2);
bool operator != (const Fl_Date_Time &dt1, const Fl_Date_Time &dt2);

#endif


