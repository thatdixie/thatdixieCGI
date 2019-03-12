/* 
******************************************************************************************
Title:       phonebook.cpp 
Author:      megan 
Created on:  Thu May 3 17:56:22 EDT 2018
 
Description: Implementation file for PhoneBook class. 
 
Modified: 
--------- 
03-09-19     dixie   Removed login requirement
*******************************************************************************************
*/
#include "phonebook.h" 
 
void PhoneBook::cgiResponse() 
{ 
    //-------------------------------------------
    // if we are not loggged in then go to login
    //-------------------------------------------
    //if(session.get("isLoggedIn") !="yes")
    //{
    //    redirect("/admin/login.cgi?dest=phonebook.cgi");
    //    return;
    //}
    //-------------------------------------------
    // The Following is the entry point to our
    // controller logic."mode" determines the
    // function we are executing
    //-------------------------------------------
    if(formEntry.get("mode") == "search")
	searchContact();
    else if(formEntry.get("mode") == "add")
	addContact();
    else if(formEntry.get("mode") == "edit")
	editContact();
    else if(formEntry.get("mode") == "delete")
	deleteContact();
    else
        menu();
}
/*
**********************************************************************************************
                                          CONTROLLER

 The Following functions represent the Controller in our Model View Controller design pattern 

 -- menu()
 -- searchContact()
 -- addContact()
 -- editContact()
 -- deleteContact()

 *********************************************************************************************
*/
void PhoneBook::menu()
{
    viewMenu();
}
void PhoneBook::searchContact()
{
    if(formEntry.get("type") == "view")
    {
	viewSearchMenu("Phonebook Search","search","result");
    }
    else
    {
	string searchkey = formEntry.get("searchkey");
	PhoneContact contact;
        try
        {
	    contact = searchDatabase(searchkey);
	    viewSearchResults(contact);
	}
        catch(std::exception &e)
        {
            kissyFace("Contact Not Found!");
        }
    }
}

void PhoneBook::addContact()
{
    PhoneContact contact;
    if(formEntry.get("type") != "add")
    {
	contact.name="";
	contact.nickname="";	
	contact.phone="";
	contact.email="";
	contact.key1="";
	contact.key2="";
	contact.key3="";
	contact.key4="";

	viewAddContact(contact);
    }
    else
    {
	contact.name    =formEntry.get("name");
	contact.nickname=formEntry.get("nickname");	
	contact.phone   =formEntry.get("phone");
	contact.email   =formEntry.get("email");
	contact.key1    =formEntry.get("nickname1");
	contact.key2    =formEntry.get("nickname2");
	contact.key3    =formEntry.get("nickname3");
	contact.key4    =formEntry.get("nickname4");

        if(contact.name=="" || contact.phone=="" ||
          (contact.key1=="" && contact.key2=="" && contact.key3=="" && contact.key4==""))
        {
	    viewAddContact(contact);
        }
        else
        {
	    addToDatabase(contact);
	    kissyFace("Contact Added!");
        }
    }
}

void PhoneBook::editContact()
{
    if(formEntry.get("type") == "view")
    {
	viewSearchMenu("Phonebook Search", "edit", "edit");
    }
    else if(formEntry.get("type") == "edit")
    {
	string searchkey = formEntry.get("searchkey");
	PhoneContact contact;
        try
        {
	    contact = searchDatabase(searchkey);
	    viewEditContact(contact);
	}
        catch(std::exception &e)
        {
	    kissyFace("Contact Not Found");
        }
    }
    else if(formEntry.get("type") == "update")
    {
	PhoneContact contact;
	contact.name     =formEntry.get("name");
	contact.nickname =formEntry.get("nickname");
	contact.phone    =formEntry.get("phone");
	contact.email    =formEntry.get("email");
	contact.key1     =formEntry.get("nickname1");
	contact.key2     =formEntry.get("nickname2");
	contact.key3     =formEntry.get("nickname3");
	contact.key4     =formEntry.get("nickname4");

	updateDatabase(contact);
	kissyFace("Contact Updated");
    }
    else
    {
	kissyFace("***UPDATE FAILED***");
    }
}

void PhoneBook::deleteContact()
{
    if(formEntry.get("type") == "view")
    {
	viewSearchMenu("Phonebook Delete Contact", "delete", "find");
    }
    else if(formEntry.get("type") == "find")
    {
	string searchkey = formEntry.get("searchkey");
	PhoneContact contact;
        try
        {
	    contact = searchDatabase(searchkey);
	    viewDeleteContact(contact);
	}
        catch(std::exception &e)
        {
	    kissyFace("Contact Not Found");
        }
    }
    else if(formEntry.get("type") == "delete")
    {
	PhoneContact contact;
	contact.key1 = formEntry.get("key1");
	contact.key2 = formEntry.get("key2");
	contact.key3 = formEntry.get("key3");
	contact.key4 = formEntry.get("key4");
	deleteFromDatabase(contact);
        kissyFace("Contact Deleted!");	
    }
}
/*
******************************************************************************************
                                            VIEW

 The Following functions represent the View in our Model View Controller design pattern 

 -- kissyFace()
 -- viewMenu()
 -- viewSearchMenu()
 -- viewSearchResults()
 -- viewEditContact()
 -- viewAddContact()
 -- viewDeleteContact()
 -- viewTopNav()
 -- viewFooter()
 -- makeDeleteUrl()
 -- makeEditUrl()
 *****************************************************************************************
*/

void PhoneBook::kissyFace(string header)
{
    addHeader("<meta http-equiv=\"Refresh\" content=\"3; url=/admin/phonebook.cgi?mode=menu\">");
    startHtml("phonebook.cgi"); 
    addHtml("<br/><br/>");
    addHtml("<center>");
    addHtml("<table border=0>");   
    addHtml("<tr><td>");
    addHtml("<font size=+3>"+header+"</font>");
    addHtml("<br><br>");
    addHtml("<center>");
    addHtml("<img src=\"/images/kiss.jpg\">");
    addHtml("</center>");
    addHtml("</font>");
    addHtml("</td></tr>");
    addHtml("</table>");
    addHtml("</center>");
    addHtml("<br/><br/>");
    endHtml();
}

void PhoneBook::viewMenu()
{
    startHtml("phonebook.cgi"); 
    viewTopNav();
    addHtml("<section id=\"admin\">");
    addHtml("<div class=\"admin-page\">");
    addHtml("<div class=\"container\">");
    addHtml("<div class=\"center\">");
    addHtml("<h2>Phonebook</h2>");
    addHtml("</div>");
    addHtml("<div class=\"row admin-wrap\">");
    addHtml("<div class=\"status alert alert-success\" style=\"display: none\"></div>");
    addHtml("<div class=\"wow fadeInDown\">");
    addHtml("<div class=\"col-sm-5 col-sm-offset-4\">");

    addHtml("<h3>Hi "+session.get("username")+"! What do you want to do: ");
    addHtml("<br>");
    addHtml("<h3><a href=\"/admin/phonebook.cgi?mode=search&type=view\">SEARCH CONTACTS</a>");
    addHtml("<br>");
    addHtml("<a href=\"/admin/phonebook.cgi?mode=add&type=view\">ADD A CONTACT</a>");
    addHtml("<br>");
    addHtml("<a href=\"/admin/phonebook.cgi?mode=edit&type=view\">EDIT CONTACT</a>");
    addHtml("<br>");
    addHtml("<a href=\"/admin/phonebook.cgi?mode=delete&type=view\">DELETE CONTACT</a></h3>");
    addHtml("<br>");
    addHtml("</div>");
    addHtml("</div>");
    addHtml("</div>");
    addHtml("</div>");
    addHtml("</div>");
    addHtml("</section>");
    viewFooter();
    endHtml();
}

void PhoneBook::viewSearchMenu(string header, string mode, string type)
{
    startHtml("phonebook.cgi"); 
    viewTopNav();
    addHtml("<section id=\"admin\">");
    addHtml("<div class=\"admin-page\">");
    addHtml("<div class=\"container\">");
    addHtml("<div class=\"center\">");
    addHtml("<h2>Phonebook Home</h2>");
    addHtml("</div>");
    addHtml("<div class=\"row admin-wrap\">");
    addHtml("<div class=\"status alert alert-success\" style=\"display: none\"></div>");
    addHtml("<form id=\"main-admin-form\" class=\"admin-form\" name=\"admin-form\" method=\"get\" action=\"/admin/phonebook.cgi\">");
    addHtml("<div class=\"wow fadeInDown\">");
    addHtml("<div class=\"col-sm-5 col-sm-offset-4\">");
    addHtml("<h3>Hi "+session.get("username")+"! Please enter a Search Key: </h3>");
    addHtml("<br>");
    
    addHtml("<div class=\"form-group\">");
    addHtml(" <label>Name *</label>");
    addHtml("<input type=\"text\" name=\"searchkey\" class=\"form-control\" required=\"required\">");
    addHtml("</div>");
    addHtml("<div class=\"form-group\">");
    addHtml("<input type=hidden name=mode value="+mode+">");
    addHtml("<input type=hidden name=type value="+type+">");    
    addHtml("<button type=\"submit\" name=\"submit\" class=\"btn btn-primary btn-lg\" required=\"required\">Search</button>");
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

void PhoneBook::viewSearchResults(PhoneContact contact)
{
    startHtml("phonebook.cgi"); 
    viewTopNav();
    addHtml("<section id=\"admin\">");
    addHtml("<div class=\"admin-page\">");
    addHtml("<div class=\"container\">");
    addHtml("<div class=\"center\">");
    addHtml("<h2>Phonebook Contact</h2>");
    addHtml("</div>");
    addHtml("<div class=\"row admin-wrap\">");
    addHtml("<div class=\"status alert alert-success\" style=\"display: none\"></div>");
    addHtml("<div class=\"wow fadeInDown\">");
    addHtml("<div class=\"col-sm-5 col-sm-offset-4\">");
    addHtml("<h3>");
    addHtml("Name:");
    addHtml("<b>"+contact.name+"</b><br>");
    addHtml("Nickname:");
    addHtml("<b>"+contact.nickname+"</b><br>");
    addHtml("Phone:");
    addHtml("<b>"+contact.phone+"</b><br>");
    addHtml("Email:");
    addHtml("<b>"+contact.email+"</b>");
    addHtml("</h3>");
    addHtml(makeEditUrl(contact,"Edit"));
    addHtml(makeDeleteUrl(contact,"Delete"));
    addHtml("</div>");
    addHtml("</div>");
    addHtml("</div>");
    addHtml("</div>");
    addHtml("</div>");
    addHtml("</section>");
    viewFooter();
    endHtml();
}

void PhoneBook::viewEditContact(PhoneContact contact)
{
    startHtml("phonebook.cgi"); 
    viewTopNav();
    addHtml("<section id=\"admin\">");
    addHtml("<div class=\"admin-page\">");
    addHtml("<div class=\"container\">");
    addHtml("<div class=\"center\">");
    addHtml("<h2>Phonebook Edit Contact</h2>");
    addHtml("</div>");
    addHtml("<div class=\"row admin-wrap\">");
    addHtml("<div class=\"status alert alert-success\" style=\"display: none\"></div>");
    addHtml("<form id=\"main-admin-form\" class=\"admin-form\" name=\"admin-form\" method=\"get\" action=\"/admin/phonebook.cgi\">");
    addHtml("<div class=\"wow fadeInDown\">");
    addHtml("<div class=\"col-sm-5 col-sm-offset-3\">");

    addHtml("<div class=\"form-group\">");
    addHtml(" <label>Name *</label>");
    addHtml("<input type=\"text\" name=\"name\" value=\""+contact.name+"\" class=\"form-control\" required=\"required\">");
    addHtml("</div>");    
    addHtml("<div class=\"form-group\">");
    addHtml(" <label>Nickname *</label>");
    addHtml("<input type=\"text\" name=\"nickname\" value=\""+contact.nickname+"\" class=\"form-control\" required=\"required\">");
    addHtml("</div>");
    addHtml("<div class=\"form-group\">");
    addHtml(" <label>Phone *</label>");
    addHtml("<input type=\"text\" name=\"phone\" value=\""+contact.phone+"\" class=\"form-control\" required=\"required\">");
    addHtml("</div>");    
    addHtml("<div class=\"form-group\">");
    addHtml(" <label>Email *</label>");
    addHtml("<input type=\"text\" name=\"email\" value=\""+contact.email+"\" class=\"form-control\" required=\"required\">");
    addHtml("</div>");
    addHtml("<div class=\"form-group\">");
    addHtml(" <label>Search Key 1 *</label>");
    addHtml("<input type=\"text\" name=\"nickname1\" value=\""+contact.key1+"\" class=\"form-control\" required=\"required\">");
    addHtml("</div>");
    addHtml("<div class=\"form-group\">");
    addHtml(" <label>Search Key 2</label>");
    addHtml("<input type=\"text\" name=\"nickname2\" value=\""+contact.key2+"\" class=\"form-control\">");
    addHtml("</div>");
    addHtml("<div class=\"form-group\">");
    addHtml(" <label>Search Key 3</label>");
    addHtml("<input type=\"text\" name=\"nickname3\" value=\""+contact.key3+"\" class=\"form-control\">");
    addHtml("</div>");
    addHtml("<div class=\"form-group\">");
    addHtml(" <label>Search Key 4</label>");
    addHtml("<input type=\"text\" name=\"nickname4\" value=\""+contact.key4+"\" class=\"form-control\">");
    addHtml("</div>");    
    addHtml("<div class=\"form-group\">");
    addHtml("<input type=hidden name=mode value=edit>");
    addHtml("<input type=hidden name=type value=update><br>");    
    addHtml("<button type=\"submit\" name=\"submit\" class=\"btn btn-primary btn-lg\" required=\"required\">Update</button>");

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
void PhoneBook::viewAddContact(PhoneContact contact)
{
    startHtml("phonebook.cgi"); 
    viewTopNav();
    addHtml("<section id=\"admin\">");
    addHtml("<div class=\"admin-page\">");
    addHtml("<div class=\"container\">");
    addHtml("<div class=\"center\">");
    addHtml("<h2>Phonebook Add Contact</h2>");
    addHtml("</div>");
    addHtml("<div class=\"row admin-wrap\">");
    addHtml("<div class=\"status alert alert-success\" style=\"display: none\"></div>");
    addHtml("<form id=\"main-admin-form\" class=\"admin-form\" name=\"admin-form\" method=\"get\" action=\"/admin/phonebook.cgi\">");
    addHtml("<div class=\"wow fadeInDown\">");
    addHtml("<div class=\"col-sm-5 col-sm-offset-3\">");
    addHtml("<div class=\"form-group\">");
    addHtml(" <label>Name *</label>");
    addHtml("<input type=\"text\" name=\"name\" value=\""+contact.name+"\" class=\"form-control\" required=\"required\">");
    addHtml("</div>");    
    addHtml("<div class=\"form-group\">");
    addHtml(" <label>Nickname *</label>");
    addHtml("<input type=\"text\" name=\"nickname\" value=\""+contact.nickname+"\" class=\"form-control\" required=\"required\">");
    addHtml("</div>");
    addHtml("<div class=\"form-group\">");
    addHtml(" <label>Phone *</label>");
    addHtml("<input type=\"text\" name=\"phone\" value=\""+contact.phone+"\" class=\"form-control\" required=\"required\">");
    addHtml("</div>");    
    addHtml("<div class=\"form-group\">");
    addHtml(" <label>Email *</label>");
    addHtml("<input type=\"text\" name=\"email\" value=\""+contact.email+"\" class=\"form-control\" required=\"required\">");
    addHtml("</div>");
    addHtml("<h3><b>You must enter at least ONE search key<br></b></h3>");
    addHtml("<div class=\"form-group\">");
    addHtml(" <label>Search Key 1 *</label>");
    addHtml("<input type=\"text\" name=\"nickname1\" value=\""+contact.key1+"\" class=\"form-control\" required=\"required\">");
    addHtml("</div>");
    addHtml("<div class=\"form-group\">");
    addHtml(" <label>Search Key 2</label>");
    addHtml("<input type=\"text\" name=\"nickname2\" value=\""+contact.key2+"\" class=\"form-control\">");
    addHtml("</div>");
    addHtml("<div class=\"form-group\">");
    addHtml(" <label>Search Key 3</label>");
    addHtml("<input type=\"text\" name=\"nickname3\" value=\""+contact.key3+"\" class=\"form-control\">");
    addHtml("</div>");
    addHtml("<div class=\"form-group\">");
    addHtml(" <label>Search Key 4</label>");
    addHtml("<input type=\"text\" name=\"nickname4\" value=\""+contact.key4+"\" class=\"form-control\">");
    addHtml("</div>");    
    addHtml("<div class=\"form-group\">");
    addHtml("<input type=hidden name=mode value=add>");
    addHtml("<input type=hidden name=type value=add><br>");    
    addHtml("<button type=\"submit\" name=\"submit\" class=\"btn btn-primary btn-lg\" required=\"required\">Add</button>");
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
void PhoneBook::viewDeleteContact(PhoneContact contact)
{
    startHtml("phonebook.cgi"); 
    viewTopNav();
    addHtml("<section id=\"admin\">");
    addHtml("<div class=\"admin-page\">");
    addHtml("<div class=\"container\">");
    addHtml("<div class=\"center\">");
    addHtml("<h2>Phonebook Delete Contact</h2>");
    addHtml("</div>");
    addHtml("<div class=\"row admin-wrap\">");
    addHtml("<div class=\"status alert alert-success\" style=\"display: none\"></div>");
    addHtml("<div class=\"wow fadeInDown\">");
    addHtml("<div class=\"col-sm-5 col-sm-offset-4\">");
    addHtml("<h3>");
    addHtml("Name:");
    addHtml("<b>"+contact.name+"</b><br>");
    addHtml("Nickname:");
    addHtml("<b>"+contact.nickname+"</b><br>");
    addHtml("Phone:");
    addHtml("<b>"+contact.phone+"</b><br>");
    addHtml("Email:");
    addHtml("<b>"+contact.email+"</b>");
    addHtml("</h3>");
    addHtml("<b>Do you want to remove THIS contact?&nbsp;&nbsp;</b>"); 
    addHtml(makeDeleteUrl(contact,"YES"));
    addHtml("<a href=\"/admin/phonebook.cgi\">NO</a>");
    addHtml("</div>");
    addHtml("</div>");
    addHtml("</div>");
    addHtml("</div>");
    addHtml("</div>");
    addHtml("</section>");
    viewFooter();
    endHtml();    
}

void PhoneBook::viewTopNav()
{
    addHtml("<nav class=\"navbar navbar-default navbar-fixed-top\">");
    addHtml("<div class=\"container\">");
    addHtml("<div class=\"row\">");
    addHtml("<div class=\"col-md-2\">");
    addHtml("<div class=\"site-logo\">");
    addHtml("<a href=\"/\" class=\"brand\">ThatDixie.com</a>");
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
    addHtml("<li><a href=\"/admin/phonebook.cgi\">Phonebook Home</a></li>");
    addHtml("<li><a href=\"/#portfolio\">C++ Projects</a></li>");
    addHtml("<li><a target=\"capstone\" href=\"https://github.com/thatdixie/thatdixieCGI/blob/master/admin/phonebook.cpp\">Phonebook Source</a></li>");
    addHtml("<li><a target=\"capstone\" href=\"https://github.com/thatdixie/libdixie\">libdixie Source</a></li>");
    addHtml("</ul>");
    addHtml("</div>");
    addHtml("</div>");
    addHtml("</div>");
    addHtml("</div>");		
    addHtml("</nav>");
    addHtml("<p></p>");
    addHtml("<br><br<br><br>");
}

void PhoneBook::viewFooter()
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

string PhoneBook::makeDeleteUrl(PhoneContact contact, string text)
{
    string delkeys="key1="+contact.key1+
	          "&key2="+contact.key2+
	          "&key3="+contact.key3+
	          "&key4="+contact.key4;

    string delstr="<a href=\"/admin/phonebook.cgi?mode=delete&type=delete&"+delkeys+"\">"+text+"</a>&nbsp;&nbsp;";

    return(delstr);
}
string PhoneBook::makeEditUrl(PhoneContact contact, string text)
{
    return("<a href=\"/admin/phonebook.cgi?mode=edit&type=edit&searchkey="+contact.key1+"\">"+text+"</a>&nbsp;&nbsp;");
}
/*
******************************************************************************************
                                            MODEL

 The Following functions represent the Model in our Model View Controller design pattern 

 -- searchDatabase()
 -- updateDatabase()
 -- addToDatabase()
 -- deleteFromDatabase()

 *****************************************************************************************
*/
PhoneContact PhoneBook::searchDatabase(string searchKey)
{
    string dataFile = config.get("phonebook_data");
    PhoneContact contact;
    PhoneDatabase *db = new PhoneDatabase();
    db->open(dataFile, this);
    db->load();
    try
    {
	contact = db->searchPhoneBook(searchKey);
	return(contact);
	
    }
    catch(std::exception &e)
    {
	throw(e);
    }
    
}
void PhoneBook::updateDatabase(PhoneContact contact)
{
    string dataFile = config.get("phonebook_data");
    PhoneDatabase *db = new PhoneDatabase();
    db->open(dataFile, this);
    db->load();
    db->updateContact(contact);
    db->save();
}

void PhoneBook::addToDatabase(PhoneContact contact)
{
    string dataFile = config.get("phonebook_data");
    PhoneDatabase *db = new PhoneDatabase();
    db->open(dataFile, this);
    db->load();
    db->addContact(contact);
    db->save();
}

void PhoneBook::deleteFromDatabase(PhoneContact contact)
{
    string dataFile = config.get("phonebook_data");
    PhoneDatabase *db = new PhoneDatabase();
    db->open(dataFile, this);
    db->load();
    db->removeContact(contact);
    db->save();
}
/*
*****************************************************************************************
 Here we set the headers to use the css and javascript so that any bootstrap 
 templates or bootstrap elements may be used to style our look and feel.

 See https://www.w3schools.com/bootstrap/default.asp for details on bootstrap templates

*****************************************************************************************
*/

void PhoneBook::makeHeader()
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

/*
**************************************************************
 This sets the directory for where the CGI's
 configuration information resides CONF_DIR is defined
 in build_dir.h
**************************************************************
*/
string PhoneBook::getConfPath()
{
    return(CONF_DIR);
}
 
//-----------------------------------------------------------------
// Here's main() -- main is not part of the PhoneBook class but 
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
    PhoneBook *main = new PhoneBook();// We use new because we want this to be allocated memory
    main->start(argc, argv);          // the object will use exit() so there's no dangling pointers 
                                      // to concern ourselves with :-)  
    return (0);                       // This return(0) will never happen -- it's just to make the 
                                      // compiler happy :-)
}
