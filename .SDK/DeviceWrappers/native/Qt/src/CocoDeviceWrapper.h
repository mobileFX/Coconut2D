#ifndef fxDeviceWrapper_h
#define fxDeviceWrapper_h

class CocoDeviceWrapper;

#include "CocoAudioStream.h"
#include "fxCRL.h"
#include <QtOpenGL/QGLWidget>
#include <QtGui/QMouseEvent>
#include <QTimer>
#include "CocoAssetFile.h"

class CocoDeviceWrapper : public QGLWidget
{
    Q_OBJECT

private:
    QTimer timer;
    int argc;
    char **argv;
    fxScreen screen;
    bool ready;

public:
    CocoDeviceWrapper(int argc, char *argv[]);
    ~CocoDeviceWrapper();

protected:
    void resizeGL(int, int);
    void initializeGL();
    void paintGL();
    bool event(QEvent*);

public slots:
    void tick();
};

#endif
