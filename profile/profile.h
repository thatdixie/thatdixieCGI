#include <CGIDiaper.h>
#include "build_dir.h"

class Profile : public CGIDiaper
{
    public:
    void cgiResponse(void);
    void cgiGoo(void);
    void cgiSummary(void);
    void doState1(void);
    void doState2(void);
    void cgiCounter(void);
    string getConfPath(void);
    void makeHeader(void);
};


