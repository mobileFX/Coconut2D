#ifndef _Structs_h
#define _Structs_h

struct fxScreen
{
	int width;
	int height;
    int top;
	double pixelRatio;
    bool isPortrait;
    enum class Rotation
    {
		NONE = 0,
		RCW,
        RCCW,
        FULL
	} rotation;
};

template<typename T> struct fxPoint
{
    T x, y;
};

template<typename T> struct fxRect
{
    fxPoint<T> pos, size;
};

enum class ArgState : uint8_t
{
    NONE = 0,
    SCRIPTS = 1,
    FONTS = 2
};

#endif
