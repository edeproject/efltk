/**
  * Fl_Base64 test
  **/
#include <efltk/net/Fl_Base64.h>
#include <efltk/Fl_String.h>
#include <stdio.h>

int main(unsigned argc, char** argv)
{
    Fl_String strFN = argv[1];
    Fl_Buffer bufIn, bufDecoded;
    Fl_String strResult, strDecoded;
	Fl_Base64 oBase64;

    if (strFN.length() <= 0)
		strFN = "test.dat";
	/* Read binary data from given file */
    bufIn.read_file(strFN);
    printf("Size of buffer: %d\n", bufIn.bytes());
	/* Encode data */
    oBase64.encode(strResult, bufIn);
    printf("Encoded string: %s\n", strResult.c_str());
	/* Now let's try to decode encoded string */
	oBase64.decode(bufDecoded, strResult);
	/* And save result buffer to file */
	bufDecoded.save_file("test2.dat");
    return 0;
}
