#include <efltk/Fl_File_IO.h>
#include <string.h>

int main()
{
        char src[] = "The Quick Brown Fox Jumps Over The Lazy Dog";
        char dst[100];
	printf("Testing write|create...\n");
        {
                Fl_File_IO ftw("fl_tmp.txt", Fl_File_IO::IO_WRITE|Fl_File_IO::IO_CREATE);
                int len = ftw.write(src, strlen(src)+1);
                printf("  written %d bytes\n", len);
        }
        // ftw should be closed by now
	printf("Testing read...\n");
        {
                Fl_File_IO ftr("fl_tmp.txt", Fl_File_IO::IO_READ);
                int len = ftr.read(dst, 100);
                printf("  read %d bytes\n", len);
        }
        // ftr should be closed by now
        printf("  dst='%s'\n", dst);
	printf("Testing lock...\n");
        {
                Fl_File_IO f1("fl_tmp.txt", Fl_File_IO::IO_READ|Fl_File_IO::IO_LOCKED);
		printf("  handle1 = %p\n", f1.handle());
                Fl_File_IO f2("fl_tmp.txt", Fl_File_IO::IO_READ|Fl_File_IO::IO_LOCKED);
		printf("  handle2 = %p\n", f2.handle());
        }
	printf("Testing temp...\n");
        {
                Fl_File_IO ftw("fl_tmp.txt", Fl_File_IO::IO_WRITE|Fl_File_IO::IO_CREATE|Fl_File_IO::IO_TEMP);
        }
	printf("Done.\n");
        return 0;
}
