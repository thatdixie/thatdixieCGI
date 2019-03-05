#include <CGIDiaper.h>
#include "build_dir.h"
 
class Upload : public CGIDiaper
{
    public:
 
    void   cgiResponse(void);
    void   menu(void);
    void   save(void);
    string getConfPath(void);
};
