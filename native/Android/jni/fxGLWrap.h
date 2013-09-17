#ifndef fxCore_fxGLWrap_h
#define fxCore_fxGLWrap_h

#include "Defines.h"

class fxDeviceWrapper;

class fxGLWrap
{
private:
    EGLContext context;
    EGLDisplay display;
    EGLSurface surface;
    fxScreen screen;
protected:
public:
    fxGLWrap(ANativeWindow*, fxDeviceWrapper*);
    ~fxGLWrap();
    void SetContext();
    void ClearContext();
    void SetBuffers();
    void SwapBuffers();
    inline const fxScreen& GetScreen() { return screen; }
};

#endif /* fxCore_fxGLWrap_h */
