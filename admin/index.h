#include <CGIDiaper.h>
#include "build_dir.h"

class Index : public CGIDiaper
{
    public:
    void   cgiResponse(void);
    void   viewTopNav(void);
    void   viewFooter(void);
    void   makeHeader(void);
    string getConfPath(void);
};
