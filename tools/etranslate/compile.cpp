#include "compile.h"

void Compiler::compile(Fl_String infile, Fl_String outfile)
{
    FILE *fpin = fopen(infile.c_str(), "r");
    if(!fpin) {
        return;
    }
	Fl_XmlDoc *doc = 0;
    try {
        doc = Fl_XmlParser::create_dom(fpin);
    } catch(Fl_Exception &exp) {
        fclose(fpin);
        Fl::fatal(exp.text().c_str());
    }
    fclose(fpin);
    FILE *fpout = fopen(outfile.c_str(), "wb");
    if(fpout) {
        save_hash(doc->root_node(), fpout);
        fclose(fpout);
    } else
        save_hash(doc->root_node(), stdout);
}

void Compiler::save_hash(Fl_XmlNode *root, FILE *outfp)
{
    Fl_XmlNode *node;

    int numstrings=0;
    Fl_Int_List lengths;
    Fl_String_List strings;

    for(unsigned n=0; n<root->children(); n++) {
        node = root->child(n);
        Fl_XmlNode *orig = node->child("Original", false);
        Fl_XmlNode *tr = node->child("Translation", false);

		Fl_String tr_text, orig_text;
		tr->text(tr_text); orig->text(orig_text);

        if(!tr || !orig || tr_text=="" || orig_text=="") continue;

        if(node->get_attribute("Finished")=="1") {
            numstrings++;

            lengths.append(orig_text.length());
            strings.append(orig_text);
 
            lengths.append(tr_text.length());
            strings.append(tr_text);
        }
    }

    Compiler::compile(outfp, numstrings, lengths, strings);
}

//////////////////////////////////////////////////
//////////////////////////////////////////////////

typedef struct {
    uint32 magic;
    uint32 version;
    uint32 hashsize;
    uint32 numstrings;
} etb_header;

static const uint32 magic = 0xF4382150;
static const uint32 version = 0x10000001;
void Compiler::compile(FILE *fp, uint numstrings, Fl_Int_List &lengths, Fl_String_List &strings)
{
    Fl_Int_List indexes;
    uint n;
    uint size_ = numstrings;
    if(size_<100) size_ = 100;

    // Generate indexes
    for(n=0; n<strings.size(); n+=2) {
        indexes.append(Fl_String_Hash::hash(strings[n], size_));
    }

    if(numstrings != indexes.size()) {
        Fl::warning("String indexes consistency check failed..");
        return;
    }

    etb_header head;
    head.magic = magic;
    head.version = version;
    head.hashsize = size_;
    head.numstrings = numstrings;

    //Write header
    fwrite(&head, sizeof(head), 1, fp);
    //Write string lengths
    fwrite((int*)lengths.data(), lengths.size()*sizeof(int), 1, fp);
    //Write string indexes
    fwrite((int*)indexes.data(), indexes.size()*sizeof(int), 1, fp);

    //Write strings
    Fl_String orig, tr;
    for(n=0; n<strings.size(); n+=2) {
        orig = strings[n];
        tr = strings[n+1];
        fwrite(orig.c_str(), orig.length(), 1, fp);
        fwrite(tr.c_str(), tr.length(), 1, fp);
    }

}
