@class fxDeviceWrapper;

#import "Common.h"
#import "fxCRL.h"
#import "fxFile.h"
#import "fxArgs.h"
#import "fxFontFace.h"
#import "fxAudioStream.h"
#import "fxDeviceWrapper.h"

extern fxArgs* fxArgs::Args;
extern char* fxFile::filesPath;
extern char* fxFile::assetPath;

int main(int argc, char *argv[])
{
    int ret = -1;
    
    std::string documentsDir([[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0] fileSystemRepresentation]);
    documentsDir += "/";
    std::string bundleDir([[[NSBundle mainBundle] resourcePath] fileSystemRepresentation]);
    bundleDir += "/web/";
    LOGI("documentsDir: %s\nbundleDir: %s\n", documentsDir.c_str(), bundleDir.c_str());
    
    fxFile::init(documentsDir.c_str(), bundleDir.c_str());
    fxArgs::init("./args.txt");
	if(!fxArgs::Args)
	{
		fxFile::quit();
		return ret;
	}
    fxFontFace::init();
    fxAudioStream::init();
	
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    ret = UIApplicationMain(argc, argv, @"UIApplication",@"fxDeviceWrapper");
    [pool release];
    
    //@autoreleasepool { ret = UIApplicationMain(argc, argv, nil, NSStringFromClass([fxDeviceWrapper class])); }
    
    fxAudioStream::quit();
    fxFontFace::quit();
    fxArgs::quit();
    fxFile::quit();
    
    return ret;
}