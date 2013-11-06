#ifndef _fxGLWrap_h
#define _fxGLWrap_h

#include "fxCRL.h"

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

#endif
