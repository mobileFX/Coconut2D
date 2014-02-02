@class fxDeviceWrapper;

#import <UIKit/UIKit.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <libgen.h>

#import "Coconut2D.hpp"
#import "AssetFile.h"
//#import "fxArgs.h"
#import "fxFontFace.h"
#import "fxAudioStream.h"
#import "fxDeviceWrapper.h"

//extern fxArgs* fxArgs::Args;
extern char* AssetFile::filesPath;
extern char* AssetFile::assetPath;
CocoEngine* engine;

//#define DEBUG_LOG_TO_REMOTE_CONSOLE "192.168.1.166"

int main(int argc, char *argv[])
{
    int ret = -1;

	#if defined DEBUG_LOG_TO_FILE

	   // redirect the standard error stream to a log file
	   char logfile_path[128];
	   sprintf (logfile_path, "%s/Documents/" DEBUG_LOG_TO_FILE, dirname (dirname (argv[0])));
	   if (freopen (logfile_path, "w", stderr) == NULL)
	      freopen ("/var/mobile/" DEBUG_LOG_TO_FILE, "w", stderr); // fallback

	#elif defined DEBUG_LOG_TO_REMOTE_CONSOLE

	   // redirect the standard error stream to a remote console
	   int debug_socket;
	   struct sockaddr_in debugserver_sockaddr = { AF_INET, 0, 0x8813, { 0 }, { 0 } };
	   debugserver_sockaddr.sin_addr.s_addr = inet_addr (DEBUG_LOG_TO_REMOTE_CONSOLE);
	   if (((debug_socket = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP)) != -1) && (connect (debug_socket, (struct sockaddr *) &debugserver_sockaddr, sizeof (debugserver_sockaddr)) != -1))
	      dup2 (debug_socket, STDERR_FILENO);

	#endif

    std::string documentsDir([[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0] fileSystemRepresentation]);
    documentsDir += "/";
    std::string bundleDir([[[NSBundle mainBundle] resourcePath] fileSystemRepresentation]);
    bundleDir += "/web/";
    LOGI("documentsDir: %s\nbundleDir: %s\n", documentsDir.c_str(), bundleDir.c_str());

    AssetFile::init(documentsDir.c_str(), bundleDir.c_str());
    /*fxArgs::init("./args.txt");
	if(!fxArgs::Args)
	{
		AssetFile::quit();
		return ret;
	}*/
    fxFontFace::init();
    fxAudioStream::init();

    @autoreleasepool { ret = UIApplicationMain(argc, argv, nil, NSStringFromClass([fxDeviceWrapper class])); }

    fxAudioStream::quit();
    fxFontFace::quit();
    //fxArgs::quit();
    AssetFile::quit();

    return ret;
}