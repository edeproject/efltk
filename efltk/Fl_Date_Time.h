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

#include <Fl_String.h>

class Fl_Date_TimeFormat {
public:
   Fl_Date_TimeFormat();
   Fl_String dateFormat();
   Fl_String timeFormat();
   void    weekDayNames(Fl_String wdn[7]);
};

class Fl_Date_Time;

bool operator <  (const Fl_Date_Time &dt1, const Fl_Date_Time &dt2);
bool operator <  (const Fl_Date_Time &dt1, const Fl_Date_Time &dt2);
bool operator <= (const Fl_Date_Time &dt1, const Fl_Date_Time &dt2);
bool operator >  (const Fl_Date_Time &dt1, const Fl_Date_Time &dt2);
bool operator >= (const Fl_Date_Time &dt1, const Fl_Date_Time &dt2);
bool operator == (const Fl_Date_Time &dt1, const Fl_Date_Time &dt2);
bool operator != (const Fl_Date_Time &dt1, const Fl_Date_Time &dt2);

enum cdtdate_format_type {cdtMDY, cdtDAY, cdtMONTH, cdtFULL, cdtEUROPEAN};

class Fl_Date_Time {
	friend class Fl_Date_TimeFormat;
protected:
   SP_EXPORT static void   decodeDate(const double dt,short& y,short& m,short& d);
   SP_EXPORT static void   decodeTime(const double dt,short& h,short& m,short& s,short& ms);
   SP_EXPORT static void   encodeDate(double &dt,short y=0,short m=0,short d=0);
   SP_EXPORT static void   encodeDate(double &dt,const char *dat);
   SP_EXPORT static void   encodeTime(double &dt,short h=0,short m=0,short s=0,short ms=0);
   SP_EXPORT static void   encodeTime(double &dt,const char *tim);
   SP_EXPORT static int    isLeapYear(const short year);
protected:
   double        m_dateTime;
   static double dateTimeOffset;    // The offset from current' system time for synchronization
                                    // with outside system
public:
   static char   dateFormat[32];
   static char   timeFormat[32];
   static char   datePartsOrder[4];
   static char   dateSeparator;
   static char   timeSeparator;
   static bool   time24Mode;
public:
   SP_EXPORT Fl_Date_Time (short y,short m,short d,short hour=0,short minute=0,short second=0);
   SP_EXPORT Fl_Date_Time (const char * dat);
   SP_EXPORT Fl_Date_Time (const Fl_Date_Time &dt);
   SP_EXPORT Fl_Date_Time (const double dt=0);

   SP_EXPORT operator double (void) const;

   SP_EXPORT void operator = (const Fl_Date_Time& date);
   SP_EXPORT void operator = (const char * dat);

   SP_EXPORT Fl_Date_Time  operator + (int  i);
   SP_EXPORT Fl_Date_Time  operator - (int  i);
   SP_EXPORT Fl_Date_Time  operator + (Fl_Date_Time& dt);
   SP_EXPORT Fl_Date_Time  operator - (Fl_Date_Time& dt);

   SP_EXPORT Fl_Date_Time& operator += (int i);
   SP_EXPORT Fl_Date_Time& operator -= (int i);
   SP_EXPORT Fl_Date_Time& operator += (Fl_Date_Time& dt);
   SP_EXPORT Fl_Date_Time& operator -= (Fl_Date_Time& dt);

   SP_EXPORT Fl_Date_Time& operator ++ ();     // Prefix increment
   SP_EXPORT Fl_Date_Time& operator ++ (int);  // Postfix increment
   SP_EXPORT Fl_Date_Time& operator -- ();     // Prefix decrement
   SP_EXPORT Fl_Date_Time& operator -- (int);  // Postfix decrement

   SP_EXPORT friend bool operator <  (const Fl_Date_Time &dt1, const Fl_Date_Time &dt2);
   SP_EXPORT friend bool operator <= (const Fl_Date_Time &dt1, const Fl_Date_Time &dt2);
   SP_EXPORT friend bool operator >  (const Fl_Date_Time &dt1, const Fl_Date_Time &dt2);
   SP_EXPORT friend bool operator >= (const Fl_Date_Time &dt1, const Fl_Date_Time &dt2);
   SP_EXPORT friend bool operator == (const Fl_Date_Time &dt1, const Fl_Date_Time &dt2);
   SP_EXPORT friend bool operator != (const Fl_Date_Time &dt1, const Fl_Date_Time &dt2);

   SP_EXPORT void formatDate(char *str) const;
   SP_EXPORT void formatTime(char *str,bool ampm=true) const;

   // These functions don't affect the actual system time.
   // You can only alter the time for the current program.
   SP_EXPORT static void Now(Fl_Date_Time dt);     // Sets to current date and time
   SP_EXPORT static Fl_Date_Time System();         // Gets to current system date and time
   SP_EXPORT static Fl_Date_Time Now();            // Gets to current date and time
   SP_EXPORT static Fl_Date_Time Date();           // Gets to current date
   SP_EXPORT static Fl_Date_Time Time();           // Gets to current time

   SP_EXPORT short daysInMonth() const;            // Number of days in month (1..31)
   SP_EXPORT short dayOfWeek(void) const;          // (1..7)
   SP_EXPORT short dayOfYear()  const;             // returns relative date since Jan. 1

   SP_EXPORT Fl_String dayOfWeekName(void) const;  // Character Day Of Week ('Sunday'..'Saturday')
   SP_EXPORT Fl_String monthName() const ;         // Character Month name

   SP_EXPORT unsigned date() const;                // Numeric date of date object
   SP_EXPORT short day() const;                    // Numeric day of date object
   SP_EXPORT short month() const;                  // Month number (1..12)
   SP_EXPORT short year() const;
public:
   SP_EXPORT Fl_String dateString() const;
   SP_EXPORT Fl_String timeString() const;
public:
   SP_EXPORT void decodeDate(short *y,short *m,short *d) const;
   SP_EXPORT void decodeTime(short *h,short *m,short *s,short *ms) const;
};
#endif

