#ifndef __COCONUT2D_DEVICE_HPP__
#define __COCONUT2D_DEVICE_HPP__

struct fxScreen
{
    int32_t width;
    int32_t height;
    int32_t top;
    float pixelRatio;
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

#endif /* __COCONUT2D_DEVICE_HPP__ */
