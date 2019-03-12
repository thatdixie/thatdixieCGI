/* 
******************************************************************************************
Title:       hello.cpp 
Author:      megan 
Created on:  Mon Feb 12 01:08:10 EST 2018
 
Description: Implementation file for Hello class. 
 
Modified: 
--------- 
03-09-19     dixie   Removed login requirement   
*******************************************************************************************
*/
#include "hello.h" 
 
void Hello::cgiResponse() 
{ 
    //-------------------------------------------
    // if we are not loggged in then go to login
    //-------------------------------------------
    //if(session.get("isLoggedIn") !="yes")
    //{
    //    redirect("/admin/login.cgi?dest=hello.cgi");
    //    return;
    //}

    startHtml("hello.cgi"); 
    addHtml("<a href=/admin/>ADMIN HOME</a><br><br>");
    addHtml("Hello World!"); 
    endHtml(); 
}

string Hello::getConfPath()
{
    return(CONF_DIR);
}
 
//-----------------------------------------------------------------
// Here's main() -- main is not part of the Hello class but 
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
    Hello *main = new Hello();    // We use new because we want this to be allocated memory
    main->start(argc, argv);    // the object will use exit() so there's no dangling pointers 
                                // to concern ourselves with :-)  
    return (0);                 // This return(0) will never happen -- it's just to make the 
                                // compiler happy :-)
}
