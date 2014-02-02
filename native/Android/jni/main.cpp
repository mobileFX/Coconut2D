#include "AssetFile.h"
#include "fxArgs.h"
#include "fxFontFace.h"
#include "fxAudioStream.h"
#include "fxDeviceWrapper.h"

extern AAssetManager* AssetFile::manager;
extern char* AssetFile::assetPath;
extern char* AssetFile::filesPath;
extern fxArgs* fxArgs::Args;

void android_main(android_app* app)
{
	app_dummy();

	/*AConfiguration* conf = AConfiguration_new();
	AConfiguration_fromAssetManager(conf, app->activity->assetManager);
	LOGI("Density: %d\n", AConfiguration_getDensity(conf));
	AConfiguration_delete(conf);*/

	LOGI("internalDataPath: %s\n", app->activity->internalDataPath);
	LOGI("externalDataPath: %s\n", app->activity->externalDataPath);
	AssetFile::init(app->activity->assetManager, "/data/data/com.mobilefx.cocoengine/files/");
	fxArgs::init("./args.txt");
	if(!fxArgs::Args)
	{
		AssetFile::quit();
		return;
	}
	fxFontFace::init();
	fxAudioStream::init();

	fxDeviceWrapper w(app);

	fxAudioStream::quit();
	fxFontFace::quit();
	fxArgs::quit();
	AssetFile::quit();
}

