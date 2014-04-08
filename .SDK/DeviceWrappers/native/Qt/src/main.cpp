#include <QApplication>
#include <QDesktopWidget>
#include <cstdlib>

class fxDeviceWrapper;

#import "Common.h"
#import "fxCRL.h"
#import "AssetFile.h"
#import "fxFontFace.h"
#import "fxAudioStream.h"
#import "fxDeviceWrapper.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
    int ret = -1;
    QApplication app(argc, argv);

    int width = 320;
    int height = 480;
    int zoom = 100;
    std::string dir = QApplication::applicationDirPath().toUtf8().constData();
    LOGI("Application folder: %s\n", dir.c_str());

    for(int i = 1; i < argc; i++)
    {
        if(strcmp(argv[i], "--device_width") == 0) width = atoi(argv[i + 1]);
        else if(strcmp(argv[i], "--device_height")== 0) height = atoi(argv[i + 1]);
        else if(strcmp(argv[i], "--device_zoom") == 0) zoom = atoi(argv[i + 1]);
        else if(strcmp(argv[i], "--root_folder") == 0) dir = argv[i + 1];
    }

    AssetFile::init((dir + "/local/").c_str(), (dir + "/web/").c_str());
    fxFontFace::init();
    fxAudioStream::init();

    fxDeviceWrapper w(argc, argv);
    w.setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
    w.setFixedSize(width * zoom / 100, height * zoom / 100);
    w.move(QApplication::desktop()->width() - w.frameSize().width(), 0);
    w.show();

    ret = app.exec();

    fxAudioStream::quit();
    fxFontFace::quit();
    AssetFile::quit();

    return ret;
}
