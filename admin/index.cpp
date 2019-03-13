/* 
******************************************************************************************
Title:       index.cpp 
Author:      megan 
Created on:  Sun Feb 11 22:22:36 EST 2018
 
Description: Implementation file for Index class. 
 
Modified: 
--------- 

*******************************************************************************************
*/
#include "index.h" 
 
void Index::cgiResponse() 
{
    //-------------------------------------------
    // if we are not loggged in then go to login
    //-------------------------------------------
    if(session.get("isLoggedIn") !="yes")
    {
        redirect("/admin/login.cgi?dest=index.cgi");
        return;
    }
    //-------------------------------------------
    // Load admin_apps.conf to see what 
    // configured apps are availiable to admins
    //-------------------------------------------
    Properties adminApps = Properties();
    adminApps.open(getConfPath()+"/admin/admin_apps.conf", this);
    adminApps.load();
    startHtml("Administration Apps"); 
    viewTopNav();
    addHtml("<section id=\"admin\">");
    addHtml("<div class=\"admin-page\">");
    addHtml("<div class=\"container\">");
    addHtml("<div class=\"center\">");
    addHtml("<h2>Admin. Tools</h2>");
    addHtml("</div>");
    addHtml("<div class=\"row admin-wrap\">");
    addHtml("<div class=\"status alert alert-success\" style=\"display: none\"></div>");
    addHtml("<div class=\"wow fadeInDown\">");
    addHtml("<div class=\"col-sm-5 col-sm-offset-4\">");
    addHtml("<h3>Hi "+session.get("username")+"! Here are your apps: </h3>");
    //-----------------------------------------------
    // get list of Apps available to this admin area
    //-----------------------------------------------
    Queue<NameValue> *q = adminApps.dump();
    while (!q->isEmpty())
    {
	NameValue nv = q->dequeue();
        addHtml("<h3><a href=\"/admin/"+nv.getValue()+"\">"+nv.getName()+"</a></h3>");
    }
    delete q;
    addHtml("</div>");
    addHtml("</div>");
    addHtml("</div>");
    addHtml("</div>");
    addHtml("</div>");
    addHtml("</section>");
    viewFooter();
    endHtml(); 

}

void Index::viewTopNav()
{
    addHtml("<nav class=\"navbar navbar-default navbar-fixed-top\">");
    addHtml("<div class=\"container\">");
    addHtml("<div class=\"row\">");
    addHtml("<div class=\"col-md-2\">");
    addHtml("<div class=\"site-logo\">");
    addHtml("<a href=\"index.html\" class=\"brand\">ThatDixie.com</a>");
    addHtml("</div>");
    addHtml("</div>");					  
    addHtml("<div class=\"col-md-10\">");	 
    addHtml("<div class=\"navbar-header\">");
    addHtml("<button type=\"button\" class=\"navbar-toggle\" data-toggle=\"collapse\" data-target=\"#menu\">");
    addHtml("<i class=\"fa fa-bars\"></i>");
    addHtml("</button>");
    addHtml("</div>");
    addHtml("<div class=\"collapse navbar-collapse\" id=\"menu\">");
    addHtml("<ul class=\"nav navbar-nav navbar-right\">");
    addHtml("<li><a href=\"/admin/login.cgi?logout=yes\">Logout</a></li>");
    addHtml("</ul>");
    addHtml("</div>");
    addHtml("</div>");
    addHtml("</div>");
    addHtml("</div>");		
    addHtml("</nav>");
    addHtml("<p></p>");
    addHtml("<br><br<br><br>");
}

void Index::viewFooter()
{
    addHtml("<footer id=\"footer\" class=\"midnight-blue\">");
    addHtml("<div class=\"container\">");
    addHtml("<div class=\"row\">");
    addHtml("<div class=\"col-md-6 col-md-offset-3\">");
    addHtml("<div class=\"text-center\">");
    addHtml("<a href=\"/\" class=\"scrollup\"><i class=\"fa fa-angle-up fa-3x\"></i></a>");
    addHtml("</div>");
    addHtml("Copyright &copy; 2019 Megan Williams");
    addHtml("</div>");
    addHtml("<div class=\"top-bar\">");
    addHtml("<div class=\"col-lg-12\">");
    addHtml("<div class=\"social\">");
    addHtml("<ul class=\"social-share\">");
    addHtml("<li><a href=\"https://www.facebook.com/profile.php?id=100005161504879\"><i class=\"fa fa-facebook\"></i></a></li>");
    addHtml("<li><a href=\"http://instagram.com/cyrusface\"><i class=\"fa fa-instagram\"></i></a></li>");
    addHtml("<li><a href=\"https://www.linkedin.com/in/megan-williams-58755935\"><i class=\"fa fa-linkedin\"></i></a></li>"); 
    addHtml("</ul>");
    addHtml("</div>");
    addHtml("</div>");
    addHtml("</div>");
    addHtml("</div>");
    addHtml("</div>");
    addHtml("</footer>");
    addHtml("<script src=\"/js/jquery.js\"></script>");
    //addHtml("<script src=\"/js/dixie.js\"></script>");
    addHtml("<script src=\"/js/bootstrap.min.js\"></script>");
    addHtml("<script src=\"/js/jquery.prettyPhoto.js\"></script>");
    addHtml("<script src=\"/js/jquery.isotope.min.js\"></script>");
    addHtml("<script src=\"/js/wow.min.js\"></script>");
    addHtml("<script src=\"/js/jquery.easing.min.js\"></script>");	
    addHtml("<script src=\"/js/main.js\"></script>");
}

void Index::makeHeader()
{
    addHeader("<meta charset=\"utf-8\">");
    addHeader("<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">");
    addHeader("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
    addHeader("<link href=\"/css/bootstrap.min.css\" rel=\"stylesheet\">");
    addHeader("<link rel=\"stylesheet\" href=\"/css/font-awesome.min.css\">");
    addHeader("<link href=\"/css/animate.css\" rel=\"stylesheet\" />");
    addHeader("<link href=\"/css/prettyPhoto.css\" rel=\"stylesheet\">");
    addHeader("<link href=\"/css/style.css\" rel=\"stylesheet\">");
    addHeader("<link href=\"/css/dixie.css\" rel=\"stylesheet\">");
}

string Index::getConfPath()
{
    return(CONF_DIR);
}
 
//-----------------------------------------------------------------
// Here's main() -- main is not part of the Index class but 
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
    Index *main = new Index();  // We use new because we want this to be allocated memory
    main->start(argc, argv);    // the object will use exit() so there's no dangling pointers 
                                // to concern ourselves with :-)  
    return (0);                 // This return(0) will never happen -- it's just to make the 
                                // compiler happy :-)
}
