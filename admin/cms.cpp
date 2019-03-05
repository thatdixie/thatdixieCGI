/* 
******************************************************************************************
Title:       cms.cpp 
Author:      megan 
Created on:  Thu Mar 22 17:44:48 EDT 2018
 
Description: Implementation file for Cms class. 
 
Modified: 
--------- 
 
*******************************************************************************************
*/
#include "cms.h" 

void Cms::cgiResponse() 
{ 
    //-------------------------------------------
    // if we are not loggged in then go to login
    //-------------------------------------------
    if(session.get("isLoggedIn") !="yes")
    {
        redirect("/admin/login.cgi?dest=cms.cgi");
        return;
    }
    
    if(formEntry.get("mode") == "edit")
    {
	edit();
	return;
    }
    else if(formEntry.get("mode") == "save")
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
void Cms::menu()
{
    //-------------------------------------------
    // Load cms_sections.conf to see what 
    // configured sections can be edited 
    //-------------------------------------------
    Properties cmsSections = Properties();
    cmsSections.open(getConfPath()+"/admin/cms_sections.conf", this);
    cmsSections.load();
    
    startHtml("cms.cgi"); 
    addHtml("<br/><br/>");
    addHtml("<center>");
    addHtml("<table border=1>");   
    addHtml("<tr><td>");
    addHtml("<font size=+3>Content Management</font>");
    addHtml("<br><br>");
    addHtml("Hi " +session.get("username")+ "! What do you want to edit?:");
    addHtml("<a href=\"/admin/\">or Admin Home here</a>");
    addHtml("<br><br>");
    //-----------------------------------------------
    // get list of configured Sections to edit 
    //-----------------------------------------------
    Queue<NameValue> *q = cmsSections.dump();
    while (!q->isEmpty())
    {
	NameValue nv = q->dequeue();
        addHtml("<a href=/admin/cms.cgi?mode=edit&filename="+nv.getValue()+">"+nv.getName()+"</a>");
        addHtml("<br>");
    }
    delete q;    
    addHtml("</td></tr>");
    addHtml("</table>");
    addHtml("</center>");
    addHtml("<br/><br/>");
    endHtml();
}

void Cms::edit()
{
    string filename;
    string content = "";
    string path    = getDocumentRoot();
    
    if(formEntry.get("filename") == "")
    {
	redirect("/admin/cms.cgi?mode=menu");
	return;
    }
    else
    {
	filename = formEntry.get("filename");
    }
    //--------------------------------------
    // Get contents of section to edit
    //--------------------------------------
    char *b = readFile(path+"/"+filename);
    content = string(b);
    
    startHtml("cms.cgi");
    addHtml("<br/><br/>");
    addHtml("<center>");
    addHtml("<table border=1>");
    addHtml("<tr><td>");
    addHtml("<font size=+3>Content Management</font>");
    addHtml("<br><br>");
    addHtml("Hi "+session.get("username")+ "! Edit the section: <b>" +filename+"</b>");
    addHtml("<a href=\"/admin/cms.cgi?mode=menu\">or Cms Home here</a>");
    addHtml("<br><br>");
    addHtml("<form name=\"content\" method=\"post\" action=\"/admin/cms.cgi\">");
    addHtml("<textarea rows=\"8\" cols=\"80\" name=\"content\">"+content+"</textarea>");
    addHtml("<br>");
    addHtml("<input type=\"hidden\" name=\"mode\" value=\"save\">");
    addHtml("<input type=\"hidden\" name=\"filename\" value=\""+filename+"\">");
    addHtml("<button type=\"submit\" name=\"submit\" >Update Content</button>");
    addHtml("</form>");
    addHtml("<br>");
    addHtml("</td></tr>");
    addHtml("</table>");
    addHtml("</center>");
    addHtml("<br/><br/>");
    endHtml();
}

void Cms::save()
{
    string filename;
    string content = "";
    string path    = getDocumentRoot();
    
    if(formEntry.get("filename") == "")
    {
	redirect("/admin/cms.cgi?mode=menu");
	return;
    }
    else
    {
	filename = formEntry.get("filename");
    }
    if(formEntry.get("content") == "")
    {
	redirect("/admin/cms.cgi?mode=menu");
	return;
    }
    else
    {
	content = formEntry.get("content");
    }
    
    writeFile(path+"/"+filename,(char *)content.c_str());
    
    startHtml("cms.cgi"); 
    addHtml("<br/><br/>");
    addHtml("<center>");
    addHtml("<table border=1>");
    addHtml("<tr><td>");
    addHtml("<font size=+3>Content Management</font>");
    addHtml("<br><br>");
    addHtml("Hi "+session.get("username")+ "! <b>" +filename+"</b> has been saved!<br>");
    addHtml("<a href=\"/admin/\"> Admin Home here</a>");
    addHtml("<br><br>");
    addHtml("<br>");
    addHtml("</td></tr>");
    addHtml("</table>");
    addHtml("</center>");
    addHtml("<br/><br/>");
    endHtml();
}

string Cms::getConfPath()
{
    return(CONF_DIR);
}
 
//-----------------------------------------------------------------
// Here's main() -- main is not part of the Cms class but 
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
    Cms *main = new Cms();    // We use new because we want this to be allocated memory
    main->start(argc, argv);    // the object will use exit() so there's no dangling pointers 
                                // to concern ourselves with :-)  
    return (0);                 // This return(0) will never happen -- it's just to make the 
                                // compiler happy :-)
}
