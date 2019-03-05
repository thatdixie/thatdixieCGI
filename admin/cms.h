#include <CGIDiaper.h>
#include "build_dir.h"
 
class Cms : public CGIDiaper
{
    public:
 
    void   cgiResponse(void);
    void   menu(void);
    void   edit(void);
    void   save(void);
    string getConfPath(void);
};
