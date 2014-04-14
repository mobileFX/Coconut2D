#include "AssetFile.h"
#include "fxFontFace.h"
#include "fxAudioStream.h"
#include "fxDeviceWrapper.h"

extern AAssetManager* AssetFile::manager;
extern char* AssetFile::assetPath;
extern char* AssetFile::filesPath;

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
