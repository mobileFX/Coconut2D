#ifndef fxDeviceWrapper_h
#define fxDeviceWrapper_h

class fxDeviceWrapper;

#include "fxAudioStream.h"
#include "fxCRL.h"
#include <QtOpenGL/QGLWidget>
#include <QtGui/QMouseEvent>
#include <QTimer>
#include "AssetFile.h"

class fxDeviceWrapper : public QGLWidget
{
    Q_OBJECT

private:
    QTimer timer;
    int argc;
    char **argv;
    fxScreen screen;
    bool ready;

public:
    fxDeviceWrapper(int argc, char *argv[]);
    ~fxDeviceWrapper();

protected:
    void resizeGL(int, int);
    void initializeGL();
    void paintGL();
    bool event(QEvent*);

public slots:
    void tick();
};

#endif
