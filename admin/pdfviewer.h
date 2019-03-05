#include <CGIDiaper.h>
#include "build_dir.h"
 
class PDFviewer : public CGIDiaper
{
    public:
 
    void   cgiResponse(void);
    string getConfPath(void);
};
