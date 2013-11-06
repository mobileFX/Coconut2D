#include "fxDeviceWrapper.h"

extern char* fxFile::filesPath;
extern char* fxFile::assetPath;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
fxDeviceWrapper::fxDeviceWrapper(int i_argc, char *i_argv[]) :  timer(this), argc(i_argc), argv(i_argv), ready(false)
{}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
fxDeviceWrapper::~fxDeviceWrapper()
{}

void fxDeviceWrapper::resizeGL(int w, int h)
{
    screen.width = w;
    screen.height = h;
    screen.pixelRatio = 1.0;
    screen.isPortrait = true;
    screen.rotation = fxScreen::Rotation::NONE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void fxDeviceWrapper::initializeGL()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void fxDeviceWrapper::paintGL()
{
    if(!ready) return;
    fxCRL::paint();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool fxDeviceWrapper::event(QEvent* e)
{
    //LOGI("QEvent::Type(%d)\n", e->type());
    switch(e->type())
    {
        case QEvent::MouseButtonPress:
        {
        fxCRL::handleEvent(0, fxCRL::fxEvent::BLUR);
            QMouseEvent* mouse = (QMouseEvent*)e;
            switch(mouse->button())
            {
                case Qt::LeftButton:
                    fxCRL::handleEvent(0, fxCRL::fxEvent::TOUCHSTART, e);
                    break;
                default:;
            }
            break;
        }

        case QEvent::MouseMove:
        {
            fxCRL::handleEvent(0, fxCRL::fxEvent::TOUCHMOVE, e);
            break;
        }

        case QEvent::MouseButtonRelease:
        {
        fxCRL::handleEvent(0, fxCRL::fxEvent::FOCUS);
            QMouseEvent* mouse = (QMouseEvent*)e;
            switch(mouse->button())
            {
                case Qt::LeftButton:
                    fxCRL::handleEvent(0, fxCRL::fxEvent::TOUCHEND, e);
                    break;
                default:;
            }
            break;
        }

        case QEvent::KeyPress:
        {
            QKeyEvent* press = (QKeyEvent*)e;
            switch(press->key())
            {
                case Qt::Key_Escape:
                    close();
                    break;
                default:;
            }
            break;
        }

        case QEvent::ShowToParent:
        {
            fxCRL::init(argc, argv, screen, this);
            connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));
            timer.start(4);
            fxCRL::handleEvent(0, fxCRL::fxEvent::LOAD, e);
            ready = true;
            break;
        }

        case QEvent::Close:
        {
            fxCRL::handleEvent(0, fxCRL::fxEvent::UNLOAD);
            fxCRL::quit();
            break;
        }

        default:
            return QWidget::event(e);
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void fxDeviceWrapper::tick()
{
    static std::chrono::steady_clock::time_point now, last_tick = std::chrono::steady_clock::now(), last_draw = std::chrono::steady_clock::now();
    static std::chrono::duration<double, std::milli> tick_dif = std::chrono::duration<double, std::milli>::zero();
    static std::chrono::duration<double, std::milli> draw_dif = std::chrono::duration<double, std::milli>::zero();

    // Mark time and calc difference since last call
    now = std::chrono::steady_clock::steady_clock::now();
    draw_dif = now - last_draw;
    tick_dif = now - last_tick;

    // If the time ellapsed is grater than 16ms we flush OpenGL trying to achieve 60 fps.
    if((draw_dif + tick_dif).count() > 16.0)
    {
        last_draw = now;
        updateGL();

        now = std::chrono::steady_clock::steady_clock::now();
    }

    // Tick the HTML5 timers
    last_tick = now;
    fxCRL::tick();
    fxAudioStream::tick();
}
