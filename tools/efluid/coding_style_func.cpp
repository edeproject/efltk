#include <efltk/Fl_Window.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Fl_Type.h"	// for indent() prototype
#if defined(_WIN32) && !defined (__GNUC__)
#	define strcasecmp  stricmp
#else
#	include <config.h> // for strcasecmp
#endif

// these two are in the FLUID output from coding_style.fl									  
extern Fl_Window *make_codingstyle_window();
extern void load_codingstyle_window();

int gbrace_style = 1;
int gno_space_parens = 0;
int gbrace_functions = 0;
int gindent_tabs = 0;
int gtab_size = 2;
int galways_return_parens = 0;
int gindent_code = 1;

struct coding_style_option {
	const char *name;
	int *value;
};

coding_style_option options[] = {
	{ "Brace_Style", &gbrace_style },
	{ "No_Space_Parens", &gno_space_parens },
	{ "Brace_Functions", &gbrace_functions },
	{ "Indent_Tabs", &gindent_tabs },
	{ "Tab_Size", &gtab_size },
	{ "Force_Return_Parens", &galways_return_parens },
	//	{ "Indent_Code", &gindent_code },
	{ NULL, NULL }
};

		
static FILE *get_coding_style_file(const char *mode)
{
#ifdef _WIN32
  FILE *fp = fopen("fluid_coding_style", mode);
#else
  char s[256];
  sprintf(s, "%s/.fluid_coding_style", getenv("HOME"));
  FILE *fp = fopen(s, mode);
#endif
  return(fp);
}


void load_coding_style()
{
  FILE *fp = get_coding_style_file("r");
  if(fp){
    char buffer[256];
    while(!feof(fp)){
  	  fgets(buffer, sizeof(buffer), fp);
  	  char *p = strtok(buffer, "=");
	  for(int i=0; options[i].name; i++)
		  if(strcasecmp(options[i].name, buffer) == 0)
			  *(options[i].value) = atol(p + strlen(p) + 1);
    }
    fclose(fp);
   }
}

void save_coding_style()
{
	FILE *fp = get_coding_style_file("w");
	if(fp){
      for(int i=0; options[i].name; i++)
		fprintf(fp, "%s=%d\n", options[i].name, *(options[i].value));
	  fclose(fp);
	 }
}

const char *get_indent_string(int level)
{
	static char buffer[256];

	if(gindent_tabs) {
		int i;
		for(i = 0; i < level && i < (int)sizeof(buffer) - 2; i++) {
			buffer[i] = '\t';
		}
		buffer[i] = '\0';
	}
	else {
		int pos = 0;
		for(int i=0; i < level && pos < (int)sizeof(buffer) - 2; i++) {
			for(int j=0; j < gtab_size && pos < (int)sizeof(buffer) - 2; j++, pos++)
				buffer[pos] = ' ';
		}
		buffer[pos] = '\0';
	}
	return (buffer);
}


const char *get_opening_brace(int isfunction)
{
	static char buffer[256];
	if(isfunction && !gbrace_functions)
		return " {\n";
	if(gbrace_style == 1)
		if(isfunction)
			return " {\n";
		else
			return " {";
	if(gbrace_style == 2)
	{
		sprintf(buffer, "\n%s{\n", indent());
		return buffer;
	}
	if(gbrace_style == 3) {
	   static char buffer[20];
	   sprintf(buffer, "\n%s{\n", get_indent_string(1));
	   return(buffer);
    }
	return " {\n";
}

void show_coding_style_cb(Fl_Widget *, void *)
{
	static Fl_Window *pWindow = NULL;

	if(!pWindow)
		pWindow = make_codingstyle_window();
	if(pWindow)
	{
		load_codingstyle_window();
		pWindow->show();
	}
}

