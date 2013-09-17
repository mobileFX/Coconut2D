#ifndef fxCore_fxGLWrap_h
#define fxCore_fxGLWrap_h


@interface fxGLWrap : UIView
{
    EAGLContext* context;
    GLuint fbuff, rbuff;
    fxScreen screen;
}

- (void)InitGL;
- (void)QuitGL;
- (void)SetContext;
- (void)ClearContext;
- (void)SetBuffers;
- (void)SwapBuffers;
- (fxScreen)GetScreen;


@end

/*
class fxGLWrap
{
private:
    EAGLContext *context;
    GLuint fbuff, rbuff;
    GLuint width, height;
    float scale;
protected:
public:
    fxGLWrap(size_t, size_t, float);
    ~fxGLWrap();
    void SetContext();
	void ClearContext();
    void SetBuffers();
    void SwapBuffers();
    inline const GLuint& GetFrameBuffer() { return fbuff; }
    inline const GLuint& GetWidth() { return width; }
    inline const GLuint& GetHeight() { return height; }
    inline const float& GetScale() { return scale; }
};*/

#endif /* fxCore_fxGLWrap_h */