/*
*******************************************************************************************
*/
#include "profile.h"


void Profile::cgiResponse()
{
    startHtml("Profile App");
    cgiCounter();
    endHtml();
}


void Profile::cgiCounter()
{
    //-----------------------------------
    // get current session counter...
    //------------------------------------
    int count = session.getInt("count");
    
    addHtml("<h2>The running session counter for this CGI is "+dixieString(count)+"</h2>");

    //--------------------------------------
    // Increment counter and store it back
    // to the current session...
    //--------------------------------------
    count++;
    session.put("count", dixieString(count));
}





void Profile::makeHeader()
{
    addHeader("<link rel=\"stylesheet\" href=\"css/layout.css\" type=\"text/css\" />");
    addHeader("<meta name=\"keywords\" content=\"Hunter Collage, C++, Computer Science Major, Megan Williams\" />");
    addHeader("<meta name=\"description\" content=\"Dixie Bitches in da house holla!\" />");
}


string Profile::getConfPath()
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
    Profile *profile = new Profile(); // We use "new' because we want this to be allocated memory
    profile->start(argc, argv);       // the object will use exit() so there's no dangling pointers 
    return (0);                       // This return(0) will never happen -- it's just to make the
                                      // compiler happy :-)
}

