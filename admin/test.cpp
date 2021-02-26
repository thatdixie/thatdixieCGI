/*
*******************************************************************************************
*/
#include "test.h"



void Test::cgiResponse()
{

    if(!formFiles.isEmpty())
    {
        startHtml("test.cgi");
        FormFile ff = formFiles.dequeue();
	string filename = ff.getFilename();
	string fileType = ff.getDataType();
	int    len      = ff.getDataLength();
        
        addHtml("<center>");
        addHtml("<table border=1><tr><td>");        
        addHtml("<h2>Upload Complete!</h2>");
        addHtml("<br>filename="+filename);
	addHtml("<br>fileType="+fileType);
	addHtml("<br>file length="+dixieString(len)+"");
        string data = ff.getData();
        writeFile("/home/mgill/www/thatdixiebitch/upload/"+filename, (char *)data.c_str(), len);
        addHtml("<br>Saved to upload directory and viewable <a href=http://thatdixiebitch/upload/"+filename+">HERE</a>");
        addHtml("</b></td></tr></table>");        
        addHtml("</center>");
        endHtml();    
    }
    else
    {
	redirect("/index.html");
    }
    
}

string Test::getConfPath()
{
    return(CONF_DIR);
}

//-----------------------------------------------------------------
// Here's main() -- main is not part of the Test class but 
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
    Test *test = new Test();          // We use "new' because we want this to be allocated memory
    test->start(argc, argv);          // the object will use exit() so there's no dangling pointers 
    return (0);                       // This return(0) will never happen -- it's just to make the
                                      // compiler happy :-)
}

