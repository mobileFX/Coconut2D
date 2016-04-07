struct fxScreen
{
    uint32_t width;
    uint32_t height;
    uint32_t top;
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
