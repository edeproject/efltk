#include <efltk/Fl_Printer.h>
#include <stdio.h>
#include <stdlib.h>

//const int Fl_Printer::NO_PAGE_FORMATS=30;


//const char * Fl_Printer::format_names = fl_printer_format_names_en;
const int Fl_Printer::page_formats[NO_PAGE_FORMATS+1][2]={

	// A* //
	{0,0},
	{2384, 3370},
	{1684, 2384},
	{1191, 1684},
	{842, 1191},
	{595, 842},
	{420, 595},
	{297, 420},
	{210, 297},
	{148, 210},
	{105, 148},
	
	// B* //
	{2920, 4127},
	{2064, 2920},
	{1460, 2064},
	{1032, 1460},
	{729, 1032},
	{516, 729},
	{316, 516},
	{258, 516},
	{181, 258},
	{127, 181},
	{91,127},
	
	// others (look at Fl_PostScript.H} //
	{462, 649},
	{312, 623},
	{541, 719},
	{595, 935},
	{1224, 790},
	{612, 1009},
	{612, 790},
	{791, 1224},
	{297, 683}

};
FL_API void Fl_Printer::fit(Fl_Widget * w, int align){fit(w->x(), w->y(), w->w(), w->h(), align);};
FL_API void Fl_Printer::fit(Fl_Widget * w, double dpi, int align){fit(w->x(), w->y(), w->w(), w->h(), dpi,  align);};

// it rerurns: 
// -2 - out of range
// -1  - syntax error
// 0  non-filled
// + n -converted numbers. If pages is not null , it fills it by a set of pages to be printed.

// This will  go in the foture to  Fl_Printer_Chooser...
/*

 static const char * fl_printer_format_names_en = "User defined|A0|A1|A2|A3|A4|A5|A6|A7|A8|A9|"
	"B0|B1|B2|B3|B4|B5|B6|B7|B8|B9|B10|C5 sheet|DLE|Executive|Folio|Ledger|Legal"
	"Letter|Tabloid|Common Envelope #9";


int get_number (const char **selection, int * number){

	int i;
	int ret = 0;
	const char * pos = strchr(*selection, ',');
	const char * pos2 = strchr(*selection, '-');
	if(!pos){
		pos = pos2;
		ret = 2; 
		if(!pos){
			pos = 0;
			ret = 0;
		}
	}else{
		ret = 1;
		if(pos2 && (pos2<pos)){
			ret = 2;
			pos = pos2;
		}
	}
	int state = 0;
	const char * c;
	int digits = 0;
	for(c = *selection; c<pos; c++){
		if(isspace(*c)){
			if(state == 1)
				state = 2;
			continue;
		}
		if(isdigit(*c)){
			if(state == 2){
				ret = -1;
				pos =0;
				break;
			}
			if(!state)
				state = 1;
			digits = 1;
			continue;
		}
		ret = -1;
		pos = 0;
		break;
	}
	
	if(digits)
		*number =  atoi(*selection);
	else
		*number =0;
	if(ret>0)
		pos++;
	*selection = pos;
	return ret;
}




int fl_validate_selection(const char * selection, int max, bool **pages=0){

	int i;
	const char *str = selection;
	int result = 0;
	int number;
	if(pages){
		if(*pages) delete[] *pages;
		* pages = new bool[max];
		for(i=0;i<max;i++)
			(*pages)[i] = 0;
	}
	int from = 0;
	int ret;
	while(1){
		ret = get_number(&str,&number);
		if (ret < 0){
			result = -1;
			break;
		}
		if(!number){
			if(from)
				result = -1;
			break;
		}
		result++;
		if(from){
			if(ret == 2 || number<from || number > max){
				result = -1;
				break;
			}
			if(pages)
				for(i=from; i<= number; i++)
					(*pages)[i-1] = 1;
			from = 0;
		}else{
			if(number>max){
				result = -1;
				break;
			}
			if(ret == 2)
				from = number;
			else 
				if(pages)
					(*pages)[number - 1] = 1;
		}
		if(!ret) break;
	}
	if(pages && (result <=0)) delete[] * pages;
	return result;
};







*/
