#include "fxDeviceWrapper.h"

void android_main(android_app* app)
{
	app_dummy();

	/*AConfiguration* conf = AConfiguration_new();
	AConfiguration_fromAssetManager(conf, app->activity->assetManager);
	LOGI("Density: %d\n", AConfiguration_getDensity(conf));
	AConfiguration_delete(conf);*/

	fxDeviceWrapper w(app);
}

