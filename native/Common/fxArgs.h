/* ***** BEGIN LICENSE BLOCK *****
 *
 * Copyright (C) 2013 www.coconut2D.org
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.   
 *
 * ***** END LICENSE BLOCK ***** */

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

