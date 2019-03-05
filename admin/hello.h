#include <CGIDiaper.h>
#include "build_dir.h"
 
class Hello : public CGIDiaper
{
    public:
 
    void   cgiResponse(void);
    string getConfPath(void);
};
