#include <CGIDiaper.h>
#include "build_dir.h"
 
class CgiGoo : public CGIDiaper
{
    public:
 
    void   cgiGoo(void);
    void   cgiResponse(void);
    string getConfPath(void);
};
