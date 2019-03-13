/* 
******************************************************************************************
Title:       login.cpp 
Author:      megan 
Created on:  Sun Feb 11 23:30:07 EST 2018
 
Description: Implementation file for Login class. 
 
Modified: 
--------- 
 
*******************************************************************************************
*/
#include "login.h" 
 
void Login::cgiResponse() 
{
    //---------------------------------------
    // if this is a logout request
    // then logout...
    //---------------------------------------
    if(formEntry.get("logout") == "yes")
    {
        session.put("isLoggedIn", "no");
        redirect("/admin/");
    }
    //--------------------------------------------
    // if this is a REST request for dixie session
    // existance...
    //--------------------------------------------
    if(formEntry.get("restRequest") == "isDixieSession")
    {
        string sessionKey = formEntry.get("sessionKey");
        Properties *temp  = new Properties();
	temp->open(config.get("session_dir")+sessionKey+".txt", this);
	temp->load();
	string resp = temp->get("isLoggedIn");
        string user = temp->get("username");
        print("Content-Type: application/json\n\n");
	print("{\"response\":\""+ resp +"\", \"user\":\""+ user +"\" }\n");
	
	return;
    }
    
    //-------------------------------------
    // get form entry to where to redirect
    //-------------------------------------
    string dest = formEntry.get("dest");
    
    if(formEntry.get("login_form") == "yes")
    {
	//---------------------------------------
	// get username and password...
	//---------------------------------------
        string username = formEntry.get("username");
	string password = formEntry.get("password");

	//--------------------------------------
	// Load admin_users.conf and see if user
	// entered valid login info.
	//---------------------------------------
	Properties adminUsers = Properties();
	adminUsers.open(getConfPath()+"/admin/admin_users.conf", this);
	adminUsers.load();
	if(adminUsers.get(username) == password)
	{   //------------------------------------------------
	    // this is a valid login so we isLoggedIn to true
	    // in session and redirect to dest page.
	    //------------------------------------------------
	    session.put("isLoggedIn", "yes");
            session.put("username", username);
            redirect("/admin/"+dest);
            return;
	}
    }
    //-------------------------------------------------
    // if we're not processing the form data then we
    // are rendering the login form...
    //-------------------------------------------------
    startHtml("Login"); 
    viewTopNav();
    addHtml("<section id=\"admin\">");
    addHtml("<div class=\"admin-page\">");
    addHtml("<div class=\"container\">");
    addHtml("<div class=\"center\">");
    addHtml("<h2>Administrative Login</h2>");
    addHtml("</div>");
    addHtml("<div class=\"row admin-wrap\">");
    addHtml("<div class=\"status alert alert-success\" style=\"display: none\"></div>");
    addHtml("<form id=\"main-admin-form\" class=\"admin-form\" name=\"admin-form\" method=\"post\" action=\"/admin/login.cgi\">");
    addHtml("<div class=\"wow fadeInDown\">");
    addHtml("<div class=\"col-sm-5 col-sm-offset-3\">");
    addHtml("<div class=\"form-group\">");
    addHtml(" <label>Username *</label>");
    addHtml("<input type=\"text\" name=\"username\" class=\"form-control\" required=\"required\">");
    addHtml("</div>");
    addHtml("<div class=\"form-group\">");
    addHtml("<label>Password *</label>");
    addHtml("<input type=\"text\" name=\"password\" class=\"form-control\" required=\"required\">");
    addHtml("</div>");
    addHtml("<div class=\"form-group\">");
    addHtml("<input type=hidden name=dest value="+dest+">");
    addHtml("<input type=hidden name=login_form value=yes>");    
    addHtml("<button type=\"submit\" name=\"submit\" class=\"btn btn-primary btn-lg\" required=\"required\">Login</button>");
    addHtml("</div>");
    addHtml("</div>");
    addHtml("</div>");
    addHtml("</form>");
    addHtml("</div>");
    addHtml("</div>");
    addHtml("</div>");    
    addHtml("</section>");
    viewFooter();
    endHtml(); 
}

void Login::viewTopNav()
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
    //addHtml("<li><a href=\"/admin/\">Admin Home</a></li>");
    //addHtml("<li><a href=\"/admin/phonebook.cgi\">Phonebook Home</a></li>");
    //addHtml("<li><a href=\"/admin/login.cgi?logout=yes\">Logout</a></li>");
    addHtml("</ul>");
    addHtml("</div>");
    addHtml("</div>");
    addHtml("</div>");
    addHtml("</div>");		
    addHtml("</nav>");
    addHtml("<p></p>");
    addHtml("<br><br<br><br>");
}

void Login::viewFooter()
{
    addHtml("<footer id=\"footer\" class=\"midnight-blue\">");
    addHtml("<div class=\"container\">");
    addHtml("<div class=\"row\">");
    addHtml("<div class=\"col-md-6 col-md-offset-3\">");
    addHtml("<div class=\"text-center\">");
    addHtml("<a href=\"/\" class=\"scrollup\"><i class=\"fa fa-angle-up fa-3x\"></i></a>");
    addHtml("</div>");
    addHtml("Copyright &copy; 2018 Megan Williams");
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

void Login::makeHeader()
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

string Login::getConfPath()
{
    return(CONF_DIR);
}
 
//-----------------------------------------------------------------
// Here's main() -- main is not part of the Login class but 
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
    Login *main = new Login();  // We use new because we want this to be allocated memory
    main->start(argc, argv);    // the object will use exit() so there's no dangling pointers 
                                // to concern ourselves with :-)  
    return (0);                 // This return(0) will never happen -- it's just to make the 
                                // compiler happy :-)
}
