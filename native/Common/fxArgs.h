#ifndef _fxArgs_h
#define _fxArgs_h

#include "fxFile.h"

class fxArgs : public fxFile
{
protected:
    int argc;
    char** argv;
    
public:
    static fxArgs* Args;
    static void init(const char* str, bool isAsset = true)
    {
		if(fxFile::exists(str, isAsset)) Args = new fxArgs(str, isAsset);
		else
		{
			Args = nullptr;
			LOGW("Could not find args file: \"%s\"\n", str);
		}
    }
    static void quit()
    {
        if(Args)
		{
			delete Args;
			Args = nullptr;
		}
    }
    fxArgs(const char* str, bool isAsset = true) : fxFile(str, isAsset), argc(1), argv(nullptr)
    {
        argv = (char**)malloc(sizeof(char*));
        argv[0] = nullptr;
        
        char* data = getData();
        char* pos;
        while((pos = strchr(data, '\n')))
        {
            *pos = 0;
            argv = (char**)realloc(argv, sizeof(char*) * (argc + 1));
            argv[argc] = data;
            argc++;
            data = pos + 1;
        }
    }
    ~fxArgs()
    {
        free(argv);
    }
    inline int getArgc() { return argc; }
    inline char** getArgv() { return argv; }
};

#endif
