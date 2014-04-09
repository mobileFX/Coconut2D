#include "AssetFile.h"
#include "fxFontFace.h"
#include "fxAudioStream.h"
#include "fxDeviceWrapper.h"
#include <android/log.h>

extern AAssetManager* AssetFile::manager;
extern char* AssetFile::assetPath;
extern char* AssetFile::filesPath;
CocoEngine* engine;

void android_main(android_app* app)
{
	app_dummy();

	AssetFile::init(app->activity->assetManager, "/data/data/com.mobilefx.cocoengine/files/");
	fxFontFace::init();
	fxAudioStream::init();

	fxDeviceWrapper w(app);

	fxAudioStream::quit();
	fxFontFace::quit();
	AssetFile::quit();
}

void trace(const char* fmt, ...)
{
	char* buff = (char*) malloc(2048);
	va_list vl;
	va_start(vl, fmt);
	vsprintf(buff, fmt, vl);
	va_end(vl);
	__android_log_print(ANDROID_LOG_INFO, "Coconut2D", buff,"");
	free(buff);
}

