#ifndef fxCore_fxSLWrap_h
#define fxCore_fxSLWrap_h

#include "Defines.h"

class fxSLWrap
{
private:
	SLObjectItf engineObj;
	SLEngineItf engineItf;
	SLObjectItf outputObj;
	SLVolumeItf volumeItf;
protected:
public:
    fxSLWrap(ANativeWindow*);
    ~fxSLWrap();
};

#endif /* fxCore_fxSLWrap_h */
