/**
  * Fl_Base64 test
  **/
#include <efltk/net/Fl_Base64.h>
#include <efltk/Fl_String.h>
#include <stdio.h>

int main(unsigned argc, char** argv)
{
    Fl_String strFN = argv[1];
    Fl_Buffer bufIn;
    Fl_String strResult;
	Fl_Base64 oBase64;

    if (strFN.length() <= 0)
	strFN = "test.dat";
    bufIn.read_file(strFN);
    printf("Size of buffer: %d\n", bufIn.bytes());
    oBase64.encode(strResult, bufIn);
    printf("Encoded string: %s\n", strResult.c_str());

    return 0;
}
