//
//  main.m
//  fxCore
//
//  Created by Administrator on 4/2/13.
//  Copyright (c) 2013 mobileFX. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "fxDeviceWrapper.h"

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
    fxFontFace::init();
    fxAudio::init();
    
    @autoreleasepool { ret = UIApplicationMain(argc, argv, nil, NSStringFromClass([fxDeviceWrapper class])); }
    
    fxAudio::quit();
    fxFontFace::quit();
    fxArgs::quit();
    fxFile::quit();
    
    return ret;
}
