/***************************************************************************
                          Fl_Directory_DS.cpp  -  description
                             -------------------
    begin                : Thu Nov 28 2002
    copyright            : (C) 2002 by Alexey Parshin
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

#include <config.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <efltk/filename.h>
#include <efltk/Fl_Directory_DS.h>
#include <efltk/Fl_Exception.h>
#include <efltk/Fl_Pixmap.h>

static const char * exec_xpm[] = {
"16 16 158 2",
"  	c None",
". 	c #2D2D52",
"+ 	c #454584",
"@ 	c #555589",
"# 	c #6A6A91",
"$ 	c #262655",
"% 	c #4A4A8C",
"& 	c #595995",
"* 	c #5D5D9B",
"= 	c #6969A6",
"- 	c #7E7EB3",
"; 	c #9898C8",
"> 	c #5E5E81",
", 	c #39396B",
"' 	c #2F2F68",
") 	c #414184",
"! 	c #63639A",
"~ 	c #7272A6",
"{ 	c #7E7EB1",
"] 	c #8787B9",
"^ 	c #8C8CBC",
"/ 	c #AFAFD2",
"( 	c #ACACD7",
"_ 	c #21214E",
": 	c #2E2E62",
"< 	c #3F3F84",
"[ 	c #50508B",
"} 	c #9E9EC5",
"| 	c #C4C4DF",
"1 	c #C0C0DC",
"2 	c #A9A9CF",
"3 	c #9595C2",
"4 	c #9A9AC6",
"5 	c #A6A6CD",
"6 	c #AAAAD2",
"7 	c #6C6C99",
"8 	c #28285D",
"9 	c #555591",
"0 	c #B8B8D5",
"a 	c #BEBEDB",
"b 	c #8989BB",
"c 	c #6868A4",
"d 	c #8B8BB6",
"e 	c #AEAED2",
"f 	c #ADADD1",
"g 	c #BDBDDB",
"h 	c #D7D7F0",
"i 	c #7676A1",
"j 	c #202045",
"k 	c #4B4B8A",
"l 	c #A8A8CC",
"m 	c #BBBBDA",
"n 	c #7878B1",
"o 	c #464681",
"p 	c #29295A",
"q 	c #38385A",
"r 	c #ADADD7",
"s 	c #BCBCDB",
"t 	c #C5C5DF",
"u 	c #DDDDEE",
"v 	c #A8A8D3",
"w 	c #1A1A36",
"x 	c #2F2F54",
"y 	c #555596",
"z 	c #7272A7",
"A 	c #C6C6E0",
"B 	c #8383B8",
"C 	c #474785",
"D 	c #0C0C1E",
"E 	c #2E2E4D",
"F 	c #B2B2DC",
"G 	c #CCCCE4",
"H 	c #D1D1E7",
"I 	c #C3C3DE",
"J 	c #ABABD1",
"K 	c #52528E",
"L 	c #555597",
"M 	c #6A6AA3",
"N 	c #9191BE",
"O 	c #B5B5D7",
"P 	c #565692",
"Q 	c #0A0A1D",
"R 	c #8787AF",
"S 	c #CACAE5",
"T 	c #B4B4D6",
"U 	c #8B8BBB",
"V 	c #7171AA",
"W 	c #42427D",
"X 	c #464676",
"Y 	c #8E8EBC",
"Z 	c #454582",
"` 	c #8E8EB9",
" .	c #D2D2EC",
"..	c #DADAEB",
"+.	c #CDCDE4",
"@.	c #8A8ABB",
"#.	c #5B5B99",
"$.	c #3A3A76",
"%.	c #7171AC",
"&.	c #9898C5",
"*.	c #A0A0CA",
"=.	c #57578F",
"-.	c #373758",
";.	c #8A8AB1",
">.	c #D3D3ED",
",.	c #D3D3E7",
"'.	c #E6E6F2",
").	c #E7E7F3",
"!.	c #7C7CB1",
"~.	c #353570",
"{.	c #8181B6",
"].	c #9F9FC9",
"^.	c #A6A6CB",
"/.	c #7878A2",
"(.	c #BBBBE1",
"_.	c #D1D1E9",
":.	c #DEDEEE",
"<.	c #F6F6FB",
"[.	c #F3F3FA",
"}.	c #8383B2",
"|.	c #111125",
"1.	c #6C6C8E",
"2.	c #A1A1CF",
"3.	c #B7B7D8",
"4.	c #B5B5D6",
"5.	c #BCBCDA",
"6.	c #C8C8E5",
"7.	c #D5D5E9",
"8.	c #D7D7EA",
"9.	c #D2D2E7",
"0.	c #EFEFF7",
"a.	c #EEEEF7",
"b.	c #B1B1D4",
"c.	c #9898C7",
"d.	c #40406E",
"e.	c #5B5B7F",
"f.	c #AEAED9",
"g.	c #B5B5D8",
"h.	c #CFCFE8",
"i.	c #D4D4E8",
"j.	c #D8D8EA",
"k.	c #B2B2D4",
"l.	c #ABABD3",
"m.	c #9797C7",
"n.	c #6666A5",
"o.	c #28285B",
"p.	c #313160",
"q.	c #BBBBD6",
"r.	c #EEEEFB",
"s.	c #363672",
"t.	c #454576",
"u.	c #333364",
"v.	c #2A2A5D",
"w.	c #9999C4",
"x.	c #7070A9",
"y.	c #393975",
"z.	c #52528F",
"A.	c #41417D",
"            . +     @ #         ",
"          $ % & * = - ; >       ",
"      , ' ) ! ~ { ] ^ / ( _     ",
"    : < [ } | 1 2 3 4 5 6 7     ",
"    8 9 0 a b c [ d e f g h i   ",
"  j k l m n o p   q r s t u v w ",
"x y z A B C D     E F G H I J K ",
"L M N O P Q       R S H T U V W ",
"X V Y 5 Z       `  ...+.@.#.$.  ",
"  %.&.*.=.  -.;.>.,.'.).!.~.    ",
"  {.].2 ^./.(._.:.'.<.[.}.|.    ",
"1.2.3.4.5.6.7.8.9.0.a.b.c.d.    ",
"  e.f.g.h.i.j.k.U ^ l.m.n.o.    ",
"    p.=.q.r.I @.#.s.t.u.v.      ",
"          w.6 x.y.              ",
"            z.A.                "};

static const char * document_xpm[] = {
"16 16 69 1",
" 	c None",
".	c #C6C6D5",
"+	c #9494AD",
"@	c #FBFBFC",
"#	c #F8F8FA",
"$	c #F4F4F7",
"%	c #EEEEF2",
"&	c #EAEAF0",
"*	c #DEDEE7",
"=	c #E0E0E9",
"-	c #C1C8D5",
";	c #BEC5D3",
">	c #BBC1CF",
",	c #B8BFCE",
"'	c #AFB5C7",
")	c #C9C9D7",
"!	c #F5F5F8",
"~	c #F0F0F4",
"{	c #E4E4EB",
"]	c #C0C7D4",
"^	c #BBC2D0",
"/	c #B9C0CE",
"(	c #B3B9CA",
"_	c #DBDBE5",
":	c #CDCDDA",
"<	c #BFBFD0",
"[	c #F7F7F9",
"}	c #F2F2F6",
"|	c #E7E7EE",
"1	c #E3E3EA",
"2	c #D0D0DC",
"3	c #C4C4D3",
"4	c #C2C2D1",
"5	c #FAFAFB",
"6	c #BDC3D1",
"7	c #B4BACB",
"8	c #AEB4C7",
"9	c #9EA3B9",
"0	c #9BA1B6",
"a	c #F9F9FA",
"b	c #DCDCE5",
"c	c #D6D6E1",
"d	c #D2D2DE",
"e	c #D1D1DD",
"f	c #CECEDB",
"g	c #BCC3D1",
"h	c #B6BDCD",
"i	c #B0B7C7",
"j	c #AAB0C3",
"k	c #AAAFC2",
"l	c #A6ACBF",
"m	c #A5ABBF",
"n	c #E5E5EC",
"o	c #DFDFE8",
"p	c #DDDDE6",
"q	c #DADAE4",
"r	c #D7D7E2",
"s	c #B5BBCB",
"t	c #B1B8C8",
"u	c #ADB3C6",
"v	c #A9AFC1",
"w	c #EFEFF3",
"x	c #E8E8EE",
"y	c #E6E6ED",
"z	c #B6BCCC",
"A	c #B2B8C9",
"B	c #ABB1C3",
"C	c #F3F3F6",
"D	c #E1E1E9",
"  ........+     ",
"  .@#$%&*=.+    ",
"  .@-;>,'=.)+   ",
"  .@#!~%{=++++  ",
"  .@];^/(=_:<+  ",
"  .@[!}~|1234+  ",
"  .5];6>7890.+  ",
"  .a$}%&bcdef+  ",
"  .!g^hijklmd+  ",
"  .!$%n1opqrc+  ",
"  .[^s(t8ujvc+  ",
"  .[wxy{=obqr+  ",
"  .$z7(AiuBkr+  ",
"  .Cx|n{Do_qr+  ",
"  .~xxyt8obqr+  ",
"  ++++++++++++  "};

static const char * folder_xpm[] = {
"16 16 136 2",
"  	c None",
". 	c #469FFF",
"+ 	c #4193FF",
"@ 	c #4499FF",
"# 	c #2C63AC",
"$ 	c #4DA0FF",
"% 	c #B5D9FB",
"& 	c #AAD3FB",
"* 	c #ADD3FB",
"= 	c #89C4FF",
"- 	c #184888",
"; 	c #4495FF",
"> 	c #AED5FB",
", 	c #6DB3F9",
"' 	c #6FB2F9",
") 	c #6BAEF8",
"! 	c #67ABF6",
"~ 	c #549FF9",
"{ 	c #3E91FF",
"] 	c #ACD4FB",
"^ 	c #6BAEF9",
"/ 	c #6CAFF8",
"( 	c #66AAF7",
"_ 	c #5DA3F6",
": 	c #74AEF7",
"< 	c #9EC4F8",
"[ 	c #92BCF7",
"} 	c #8DB5F5",
"| 	c #88B1F3",
"1 	c #83ABF2",
"2 	c #80A8F0",
"3 	c #87AEF5",
"4 	c #0940B7",
"5 	c #AAD2FB",
"6 	c #67ACF8",
"7 	c #68ABF8",
"8 	c #61A4F7",
"9 	c #5B9FF5",
"0 	c #5399F3",
"a 	c #498FF1",
"b 	c #3F85EF",
"c 	c #367CEB",
"d 	c #2E73E8",
"e 	c #286BE6",
"f 	c #2164E2",
"g 	c #2163E5",
"h 	c #023AB6",
"i 	c #4394FF",
"j 	c #A7D0FA",
"k 	c #63A9F7",
"l 	c #61A7F7",
"m 	c #5BA0F6",
"n 	c #5499F4",
"o 	c #4B90F2",
"p 	c #4186EF",
"q 	c #377DEB",
"r 	c #2E73E7",
"s 	c #266AE5",
"t 	c #2062E2",
"u 	c #1C5DDF",
"v 	c #1A5CE2",
"w 	c #A4CEF9",
"x 	c #5DA5F7",
"y 	c #5DA1F6",
"z 	c #559AF4",
"A 	c #4C91F3",
"B 	c #4489F1",
"C 	c #3A7FED",
"D 	c #3075E9",
"E 	c #276BE5",
"F 	c #2062E1",
"G 	c #1B5CDE",
"H 	c #1758DB",
"I 	c #1857DE",
"J 	c #0239B6",
"K 	c #A1CBF9",
"L 	c #589FF6",
"M 	c #559BF5",
"N 	c #4F96F3",
"O 	c #478CF2",
"P 	c #3D84F0",
"Q 	c #3378EB",
"R 	c #2B6EE7",
"S 	c #2265E3",
"T 	c #1C5DDE",
"U 	c #1757DB",
"V 	c #1554DA",
"W 	c #1555DD",
"X 	c #0139B5",
"Y 	c #4696FF",
"Z 	c #FFFFFF",
"` 	c #FBFBFB",
" .	c #F2F2F2",
"..	c #E9E9E9",
"+.	c #E0E0E0",
"@.	c #D7D7D7",
"#.	c #D4D4D4",
"$.	c #A9A9A9",
"%.	c #BABABA",
"&.	c #9E9990",
"*.	c #0A3DAF",
"=.	c #FEFEFE",
"-.	c #F8F8F8",
";.	c #F1F1F1",
">.	c #E8E8E8",
",.	c #DCDCDC",
"'.	c #D6D6D6",
").	c #D2D2D2",
"!.	c #A7A7A7",
"~.	c #B7B7B7",
"{.	c #929292",
"].	c #BAB6AC",
"^.	c #0E41B3",
"/.	c #F0F0F0",
"(.	c #E5E5E5",
"_.	c #DDDDDD",
":.	c #D3D3D3",
"<.	c #D0D0D0",
"[.	c #ABABAB",
"}.	c #B5B5B5",
"|.	c #939393",
"1.	c #ADADAD",
"2.	c #938E85",
"3.	c #0A3DAE",
"4.	c #FFFFFE",
"5.	c #F4F4F4",
"6.	c #EDEDED",
"7.	c #DBDBDB",
"8.	c #AEAEAE",
"9.	c #969696",
"0.	c #878787",
"a.	c #AFABA1",
"b.	c #0D40B2",
"c.	c #0037B2",
"d.	c #0034A8",
"e.	c #0038B6",
"                                ",
"    . + @ #                     ",
"  $ % & * = -                   ",
"; > , ' ) ! ~ { + + + + + .     ",
"; ] ^ / ( _ : < [ } | 1 2 3 4   ",
"; 5 6 7 8 9 0 a b c d e f g h   ",
"i j k l m n o p q r s t u v h   ",
"i w x y z A B C D E F G H I J   ",
"i K L M N O P Q R S T U V W X   ",
"Y Z Z Z Z `  ...+.@.#.$.%.&.*.  ",
"Y Z Z =.-.;.>.,.'.).!.~.{.].^.  ",
"Y Z =.-./.(._.:.<.[.}.|.1.2.3.  ",
"Y 4.5.6.(.7.#.<.1.8.9.!.0.a.b.  ",
"  c.d.d.d.d.d.d.d.d.d.d.d.e.    ",
"                                ",
"                                "};

static const Fl_Pixmap folderPixmap(folder_xpm);
static const Fl_Pixmap executablePixmap(exec_xpm);
static const Fl_Pixmap documentPixmap(document_xpm);

#ifdef _WIN32

# include <windows.h>
# include <io.h>
# include <direct.h>

# define S_ISLNK(m)      (false)
# define S_ISEXEC(m)     (((m) & _S_IFMT) == _S_IEXEC)
#ifndef __GNUC__
# define S_ISREG(m)      (((m) & _S_IFMT) == _S_IFREG)
# define S_ISDIR(m)      (((m) & _S_IFMT) == _S_IFDIR)
# define S_ISBLK(m)      (((m) & _S_IFMT) == _S_IFBLK)
#endif /* __GNUC__ */

# define lstat stat

#else /* _WIN32 */

# include <dirent.h>

#ifndef S_ISEXEC
# define S_ISEXEC(m)	  (((m) & S_IEXEC) == S_IEXEC)
#endif
#ifndef S_ISREG
# define S_ISREG(m) 	 (((m) & S_IFMT) == S_IFREG)
#endif
#ifndef S_ISDIR
# define S_ISDIR(m) 	 (((m) & S_IFMT) == S_IFDIR)
#endif
#ifndef S_ISBLK
# define S_ISBLK(m) 	 (((m) & S_IFMT) == S_IFBLK)
#endif

#endif /* _WIN32 */

#define checkDSopen(ds) if (!ds) fl_throw("Dataset isn't open") 

   // access to the field by name
const Fl_Variant& Fl_Directory_DS::operator [] (const char *field_name) const {
   checkDSopen(m_current);
   return (*m_current)[field_name];
}

Fl_Variant& Fl_Directory_DS::operator [] (const char *field_name) {
   checkDSopen(m_current);
   return (*m_current)[field_name];
}

const Fl_Data_Field& Fl_Directory_DS::field (int field_index) const {
   checkDSopen(m_current);
   return m_current->field(field_index);
}

Fl_Data_Field& Fl_Directory_DS::field (int field_index) {
   checkDSopen(m_current);
   return m_current->field(field_index);
}

// how many fields do we have in the current record?
unsigned Fl_Directory_DS::field_count() const {
   checkDSopen(m_current);
   return m_current->count();
}

int Fl_Directory_DS::field_index(const char *field_name) const {
   checkDSopen(m_current);
   return m_current->field_index(field_name);
}

// access to the field by number, 0..field_count()-1
const Fl_Variant& Fl_Directory_DS::operator [] (int index) const {
   checkDSopen(m_current);
   return (*m_current)[index];
}

Fl_Variant& Fl_Directory_DS::operator [] (int index) {
   checkDSopen(m_current);
   return (*m_current)[index];
}

// read this field data into external value
bool Fl_Directory_DS::read_field(const char *fname,Fl_Variant& fvalue) {
   fl_try {
      fvalue = (*this)[fname];      
   }
   fl_catch(exc) {
      return false;
   }
   return true;
}

// write this field data from external value
bool Fl_Directory_DS::write_field(const char *fname,const Fl_Variant& fvalue) {
   fl_try {
      (*this)[fname] = fvalue;      
   }
   fl_catch(exc) {
      return false;
   }
   return true;
}

// dataset navigation

// read the directory() and move item into the first entry
bool Fl_Directory_DS::open() {

   clear();

   int dlen = m_directory.length();
   if (dlen) {
      dlen--;
      if (m_directory[dlen] != '\\' && m_directory[dlen] != '/') {
#ifdef _WIN32
         m_directory += "\\";
#else
         m_directory += "/";
#endif
      }
   }

   unsigned num_files = 0;

   dirent **files;
   num_files = fl_filename_list(m_directory.c_str(), &files);

   struct stat st;
   if(num_files) {
      for (unsigned n = 0; n < num_files; n ++) {
         Fl_Data_Fields&  df = *(new Fl_Data_Fields);
         dirent          *file = files[n];
         Fl_String        fullName = m_directory + file->d_name;
         lstat(fullName.c_str(),&st);

         bool executable = S_ISEXEC(st.st_mode);
         const Fl_Pixmap *pixmapPtr = &documentPixmap;

         Fl_String modeName;
         if(S_ISDIR(st.st_mode)) {
            modeName = "directory";
            executable = false;
            pixmapPtr = &folderPixmap;
         }
         if(S_ISREG(st.st_mode)) {
            if (executable)
                  modeName = "program";
            else  modeName = "file";
         }
#ifndef _WIN32
         if ((st.st_mode & S_IFLNK) == S_IFLNK) {
            stat(fullName.c_str(),&st);
            if ((st.st_mode & S_IFDIR) == S_IFDIR) {
               modeName = "directory";
               pixmapPtr = &folderPixmap;
               executable = false;
            }
            else if ((st.st_mode & S_IFREG) == S_IFREG) {
               pixmapPtr = &documentPixmap;
               if (executable)
                     modeName = "program";
               else  modeName = "file";
            }
            modeName += " link";
         }
#endif
         if (executable) {
            pixmapPtr = &executablePixmap;
         }

         df.add("*") = pixmapPtr;
         df.add("name") = file->d_name;
         df.add("size") = (int) st.st_size;
         df.add("modified") = Fl_Date_Time::convert(st.st_mtime);
         df.add("type") = modeName.c_str();

         if (n==0) {
            m_current = &df;
            field(0).align = FL_ALIGN_LEFT;
            field(0).width = 3;
            field(1).align = FL_ALIGN_LEFT;
            field(1).width = 30;
            field(2).align = FL_ALIGN_RIGHT;
            field(2).width = 10;
            field(3).align = FL_ALIGN_LEFT;
            field(3).width = 16;
            field(4).align = FL_ALIGN_LEFT;
            field(4).width = 16;
         }

         m_list.append(&df);

         free(file);
      }
   }

   free(files);
   first();

   return (m_list.count()>0);
}

bool Fl_Directory_DS::close() {
   clear();
   return true;
}

bool Fl_Directory_DS::first() {
   if (m_list.count()) {
      m_currentIndex = 0;
      m_current = (Fl_Data_Fields *)m_list[m_currentIndex];
      m_eof = false;
      return true;
   }
   m_eof = true;
   return false;
}

bool Fl_Directory_DS::last() {
   unsigned cnt = m_list.count();
   if (cnt) {
      m_currentIndex = cnt - 1;
      m_current = (Fl_Data_Fields *)m_list[m_currentIndex];
      m_eof = false;
      return true;
   }
   m_eof = true;
   return false;
}

bool Fl_Directory_DS::next() {
   unsigned cnt = m_list.count();
   if (m_currentIndex + 1 < (int)cnt) {
      m_currentIndex++;
      m_current = (Fl_Data_Fields *)m_list[m_currentIndex];
      m_eof = false;
      return true;
   }
   m_eof = true;
   return false;
}

bool Fl_Directory_DS::prior() {
   if (m_currentIndex > 0) {
      m_currentIndex--;
      m_current = (Fl_Data_Fields *)m_list[m_currentIndex];
      m_eof = false;
      return true;
   }
   m_eof = true;
   return false;
}

bool Fl_Directory_DS::find(Fl_Variant position) {
   unsigned    cnt = m_list.count();
   Fl_String   name;
   unsigned i;
   switch (position.type()) {
   case VAR_INT:  if (position.get_int() < (int)cnt) {
                     m_currentIndex = position.get_int();
                     m_current = (Fl_Data_Fields *)m_list[m_currentIndex];
                     return true;
                  }
                  break;
   case VAR_STRING:
                  name = position.get_string();
                  for (i = 0; i < cnt; i++) {
                     Fl_Data_Fields& entry = *(Fl_Data_Fields *)m_list[i];
                     if (entry["name"] == name.c_str()) {
                        m_currentIndex = i;
                        m_current = (Fl_Data_Fields *)m_list[m_currentIndex];
                        return true;
                     }
                  }
                  break;
   default:       break;
   }
   return false;
}

void Fl_Directory_DS::clear() {
   unsigned cnt = m_list.count();
   for (unsigned i = 0; i < cnt; i++) {
      Fl_Data_Fields *df = (Fl_Data_Fields *) m_list[i];
      delete df;
   }
   m_list.clear();
   m_current = 0L;
   m_currentIndex = -1;
   m_eof = true;
}
