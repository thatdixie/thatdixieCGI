#include <CGIDiaper.h>
#include "build_dir.h"

class Contact : public CGIDiaper
{
    public:
    void   cgiResponse(void);
    string getConfPath(void);
};


