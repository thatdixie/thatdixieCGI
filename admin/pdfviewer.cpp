/* 
******************************************************************************************
Title:       pdfviewer.cpp 
Author:      megan
Created on:  Tue Feb 20 11:37:03 EST 2018
 
Description: Implementation file for PDFviewer class. 
 
Modified: 
--------- 
03-09-19     dixie   Removed login requirement
*******************************************************************************************
*/
#include "pdfviewer.h" 
 
void PDFviewer::cgiResponse() 
{
    //-------------------------------------------
    // if we are not loggged in then go to login
    //-------------------------------------------
    //if(session.get("isLoggedIn") !="yes")
    //{
    //    redirect("/admin/login.cgi?dest=pdfviewer.cgi");
    //    return;
    //}
    //----------------------------------------------------------------------
    // filepath = directory where pdf files are located plus document name
    // passed on URL -- we then look for that file and bugout if not found.
    //----------------------------------------------------------------------
    string filepath =config.get("pdf_doc_root")+formEntry.get("doc");
    if(!this->isFile(filepath))
    {
        redirect("/admin/index.cgi");
	return;
    }
    //------------------------------------------------------------
    // here we:
    //
    // 1) check the file size
    // 2) read file into a buffer
    // 3) set http headers for Content-Length and Content-Type
    // 4) write the file contents to browser.
    //-------------------------------------------------------------
    long  len    = this->fileSize(filepath);
    char *buffer = this->readFile(filepath);
    print("Content-Length: "+dixieString(len));
    print("Content-Type: application/pdf\n");
    print(buffer, len);
    delete buffer; // actually, we really don't *have* to delete this
    return;        // this process is gonna exit and free it anyway lol 
}



string PDFviewer::getConfPath()
{
    return(CONF_DIR);
}
 
//-----------------------------------------------------------------
// Here's main() -- main is not part of the PDFviewer class but 
// main is needed to be the entry point for all running programs 
// (on linux, mac osx, and  windows operating systems) 
// It is for this reason main shoud be a minimal function :-)
// 
// 1) Creates the object we created for our application
// 2) Invoke start() (and passing argc and argv)
// 3) return(0) -- actually main will never return and 
//    one of our object's functions will perform an orderly exit :-) 
//------------------------------------------------------------------
int main(int argc, char **argv)
{   
    PDFviewer *main = new PDFviewer();    // We use new because we want this to be allocated memory
    main->start(argc, argv);    // the object will use exit() so there's no dangling pointers 
                                // to concern ourselves with :-)  
    return (0);                 // This return(0) will never happen -- it's just to make the 
                                // compiler happy :-)
}
