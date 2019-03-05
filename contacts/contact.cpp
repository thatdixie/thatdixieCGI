/*
*******************************************************************************************
*/
#include "contact.h"


void Contact::cgiResponse()
{
    //--------------------------------------
    // get contact form inputs...
    //--------------------------------------    
    string name    = formEntry.get("name");
    string email   = formEntry.get("email");
    string subject = formEntry.get("subject");
    string message = formEntry.get("message");
            
    //-----------------------------------------
    // create a cool filename based on
    // contacts name that's also unique
    // and contains no spaces :-)
    //-----------------------------------------
    string f = name;
    replace(f.begin(), f.end(), ' ', '-');
    f = getConfPath()+"/contacts/data/"+f+"-"+randomString(3)+".txt";

    //-------------------------------------------
    // setup file data for contact record...
    //-------------------------------------------
    string contact = "";

    contact = contact + "name: "   +name+"\n";
    contact = contact + "email: "  +email+"\n";
    contact = contact + "subject: "+subject+"\n";
    contact = contact + "message: "+message+"\n";

    //------------------------------------------
    // Write the contact record...
    //------------------------------------------
    this->writeFile(f, (char *)contact.c_str());
    
    //------------------------------
    // Redirect to Thank You page
    //------------------------------
    redirect("http://www"+config.get("domain")+"/thankyou.html");
}




string Contact::getConfPath()
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
    Contact *contact = new Contact(); // We use "new' because we want this to be allocated memory
    contact->start(argc, argv);       // the object will use exit() so there's no dangling pointers 
    return (0);                       // This return(0) will never happen -- it's just to make the
                                      // compiler happy :-)
}

