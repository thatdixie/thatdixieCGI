/* 
******************************************************************************************
Title:       upload.cpp 
Author:      megan 
Created on:  Thu Apr 5 17:00:41 EDT 2018
 
Description: Implementation file for Upload class. 
 
Modified: 
--------- 
 
*******************************************************************************************
*/
#include "upload.h" 
 
void Upload::cgiResponse() 
{ 
    //-------------------------------------------
    // if we are not loggged in then go to login
    //-------------------------------------------
    if(session.get("isLoggedIn") !="yes")
    {
        redirect("/admin/login.cgi?dest=cms.cgi");
        return;
    }

    if(!formFiles.isEmpty())
    {
	save();
	return;
    }
    else
    {
	menu();
	return;
    }
    

}

void Upload::menu()
{
    startHtml("upload.cgi");
    addHtml("<form action=\"upload.cgi\" method=\"post\" enctype=\"multipart/form-data\">");
    addHtml("<center>");
    addHtml("<table border=1>");
    addHtml("<tr>");
    addHtml("<td><h2>Select File to upload:</h2><br></td>");
    addHtml("</tr>");
    addHtml("<tr>");
    addHtml("<td><input type=\"file\" name=\"upload_image\"></td>");
    addHtml("</tr>");
    addHtml("<tr>");
    addHtml("<td><input type=\"submit\" value=\"Upload\" name=\"submit\"></td>");
    addHtml("</tr>");
    addHtml("</table>");
    addHtml("</center>");
    addHtml("</form>");
    endHtml();
}

void Upload::save()
{
    if(!formFiles.isEmpty())
    {
        startHtml("upload.cgi");
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
	writeFile(config.get("upload_dir")+filename, (char *)data.c_str(), len);
        addHtml("<br>Saved to upload directory and viewable <a href=/upload/"+filename+">HERE</a>");
        addHtml("</b></td></tr></table>");        
        addHtml("</center>");
        endHtml();    
    }
    else
    {
	redirect("/admin/");
    }
    
}

string Upload::getConfPath()
{
    return(CONF_DIR);
}
 
//-----------------------------------------------------------------
// Here's main() -- main is not part of the Upload class but 
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
    Upload *main = new Upload();    // We use new because we want this to be allocated memory
    main->start(argc, argv);    // the object will use exit() so there's no dangling pointers 
                                // to concern ourselves with :-)  
    return (0);                 // This return(0) will never happen -- it's just to make the 
                                // compiler happy :-)
}
