/* 
******************************************************************************************
Title:       cgigoo.cpp 
Author:      megan 
Created on:  Wed Feb 14 08:16:03 EST 2018
 
Description: Implementation file for CgiGoo class. 
 
Modified: 
--------- 
03-09-19     dixie   Removed login requirement   
*******************************************************************************************
*/
#include "cgigoo.h" 
 
void CgiGoo::cgiResponse() 
{ 
    //if(session.get("isLoggedIn") != "yes")
    //    redirect("/admin/login.cgi?dest=cgigoo.cgi");

    startHtml("CGI Goo");
    cgiGoo();
    endHtml();
}

    
void CgiGoo::cgiGoo()
{
    //addHtml("<a href=/admin/>ADMIN HOME</a><br>");
    addHtml("<br>");
    addHtml("<h1>CGI GOO</h1>");
    addHtml("<table border=\"1\" cellspacing=\"0\" cellpadding=\"10\"> ");

    addHtml("<tr>"); addHtml("<td>"); addHtml("SERVER SOFTWARE"); addHtml("</td>");
    addHtml("<td>"); addHtml(getServerSoftware()); addHtml("</td>"); addHtml("</tr>");

    addHtml("<tr>"); addHtml("<td>"); addHtml("SERVER NAME"); addHtml("</td>");
    addHtml("<td>"); addHtml(getServerName()); addHtml("</td>"); addHtml("</tr>");

    addHtml("<tr>"); addHtml("<td>"); addHtml("GATEWAY"); addHtml("</td>");
    addHtml("<td>"); addHtml(getGatewayInterface()); addHtml("</td>"); addHtml("</tr>");

    addHtml("<tr>"); addHtml("<td>"); addHtml("PROTOCOL"); addHtml("</td>");
    addHtml("<td>"); addHtml(getServerProtocol()); addHtml("</td>"); addHtml("</tr>");

    addHtml("<tr>"); addHtml("<td>"); addHtml("PORT"); addHtml("</td>");
    addHtml("<td>"); addHtml(dixieString(getServerPort()) ); addHtml("</td>"); addHtml("</tr>");

    addHtml("<tr>"); addHtml("<td>"); addHtml("REQUEST METHOD"); addHtml("</td>");
    addHtml("<td>"); addHtml(getRequestMethod()); addHtml("</td>"); addHtml("</tr>");
    
    addHtml("<tr>"); addHtml("<td>"); addHtml("DOCUMENT ROOT"); addHtml("</td>");
    addHtml("<td>"); addHtml(getDocumentRoot()); addHtml("</td>"); addHtml("</tr>");
    
    addHtml("<tr>"); addHtml("<td>"); addHtml("PATH INFO"); addHtml("</td>");
    addHtml("<td>"); addHtml(getPathInfo()); addHtml("</td>"); addHtml("</tr>");
    
    addHtml("<tr>"); addHtml("<td>"); addHtml("PATH TRANSLATED"); addHtml("</td>");
    addHtml("<td>"); addHtml(getPathTranslated()); addHtml("</td>"); addHtml("</tr>");

    addHtml("<tr>"); addHtml("<td>"); addHtml("SCRIPT-NAME"); addHtml("</td>");
    addHtml("<td>"); addHtml(getScriptName()); addHtml("</td>"); addHtml("</tr>");

    addHtml("<tr>"); addHtml("<td>"); addHtml("QUERY STRING"); addHtml("</td>");
    addHtml("<td>"); addHtml(getQueryString()); addHtml("</td>"); addHtml("</tr>");
    
    addHtml("<tr>"); addHtml("<td>"); addHtml("REMOTE HOST"); addHtml("</td>");
    addHtml("<td>"); addHtml(getRemoteHost()); addHtml("</td>"); addHtml("</tr>");

    addHtml("<tr>"); addHtml("<td>"); addHtml("REMOTE ADDRESS"); addHtml("</td>");
    addHtml("<td>"); addHtml(getRemoteAddr()); addHtml("</td>"); addHtml("</tr>");

    addHtml("<tr>"); addHtml("<td>"); addHtml("AUTH TYPE"); addHtml("</td>");
    addHtml("<td>"); addHtml(getAuthType()); addHtml("</td>"); addHtml("</tr>");
    
    addHtml("<tr>"); addHtml("<td>"); addHtml("REMOTE USER"); addHtml("</td>");
    addHtml("<td>"); addHtml(getRemoteUser()); addHtml("</td>"); addHtml("</tr>");
    
    addHtml("<tr>"); addHtml("<td>"); addHtml("REMOTE IDENT"); addHtml("</td>");
    addHtml("<td>"); addHtml(getRemoteIdent()); addHtml("</td>"); addHtml("</tr>");

    addHtml("<tr>"); addHtml("<td>"); addHtml("CONTENT TYPE"); addHtml("</td>");
    addHtml("<td>"); addHtml(getContentType()); addHtml("</td>"); addHtml("</tr>");

    addHtml("<tr>"); addHtml("<td>"); addHtml("CONTENT LENGTH"); addHtml("</td>");
    addHtml("<td>"); addHtml(dixieString(getContentLength())); addHtml("</td>"); addHtml("</tr>");
    
    addHtml("<tr>"); addHtml("<td>"); addHtml("ACCEPT"); addHtml("</td>");
    addHtml("<td>"); addHtml(getAccept()); addHtml("</td>"); addHtml("</tr>");

    addHtml("<tr>"); addHtml("<td>"); addHtml("USER AGENT"); addHtml("</td>");
    addHtml("<td>"); addHtml(getUserAgent()); addHtml("</td>"); addHtml("</tr>");

    addHtml("<tr>"); addHtml("<td>"); addHtml("REDIRECT REQUEST"); addHtml("</td>");
    addHtml("<td>"); addHtml(getRedirectRequest()); addHtml("</td>"); addHtml("</tr>");
    
    addHtml("<tr>"); addHtml("<td>"); addHtml("REDIRECT URL"); addHtml("</td>");
    addHtml("<td>"); addHtml(getRedirectURL()); addHtml("</td>"); addHtml("</tr>");

    addHtml("<tr>"); addHtml("<td>"); addHtml("REDIRECT STATUS"); addHtml("</td>");
    addHtml("<td>"); addHtml(getRedirectStatus()); addHtml("</td>"); addHtml("</tr>");

    addHtml("<tr>"); addHtml("<td>"); addHtml("REFERRER"); addHtml("</td>");
    addHtml("<td>"); addHtml(getReferrer()); addHtml("</td>"); addHtml("</tr>");

    addHtml("<tr>"); addHtml("<td>"); addHtml("COOKIE"); addHtml("</td>");
    addHtml("<td>"); addHtml(getCookie()); addHtml("</td>"); addHtml("</tr>");

    addHtml("<tr>"); addHtml("<td>"); addHtml("USING HTTPS"); addHtml("</td>");
    addHtml("<td>"); addHtml((getUsingHTTPS() ? "yes" :"no")  ); addHtml("</td>"); addHtml("</tr>");
    
    addHtml("</table>");
    addHtml("<br/>");
}


string CgiGoo::getConfPath()
{
    return(CONF_DIR);
}
 
//-----------------------------------------------------------------
// Here's main() -- main is not part of the CgiGoo class but 
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
    CgiGoo *main = new CgiGoo();// We use new because we want this to be allocated memory
    main->start(argc, argv);    // the object will use exit() so there's no dangling pointers 
                                // to concern ourselves with :-)  
    return (0);                 // This return(0) will never happen -- it's just to make the 
                                // compiler happy :-)
}
