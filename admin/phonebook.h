#include <CGIDiaper.h>
#include "build_dir.h"
#include <PhoneDatabase.h>

class PhoneBook : public CGIDiaper
{
    public:
    //----------------------------
    // Controller Logic
    //----------------------------
    void cgiResponse(void);
    void menu(void);
    void searchContact(void);
    void addContact(void);
    void editContact(void);
    void deleteContact(void);
    //----------------------------
    // Views
    //----------------------------
    void kissyFace(string);
    void viewMenu(void);
    void viewSearchMenu(string,string,string);
    void viewSearchResults(PhoneContact);
    void viewEditContact(PhoneContact);
    void viewAddContact(PhoneContact);
    void viewDeleteContact(PhoneContact);
    void viewTopNav();
    void viewFooter();
    string makeDeleteUrl(PhoneContact, string);
    string makeEditUrl(PhoneContact, string);
    //----------------------------
    // Model
    //----------------------------
    PhoneContact searchDatabase(string);
    void updateDatabase(PhoneContact);
    void addToDatabase(PhoneContact);
    void deleteFromDatabase(PhoneContact);
    //----------------------------
    // CGI Configuration
    //----------------------------
    string getConfPath(void);
    void   makeHeader(void);
};
