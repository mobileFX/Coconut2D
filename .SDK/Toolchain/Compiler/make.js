/* ***** BEGIN LICENSE BLOCK *****
 *
 * Copyright (C) 2013-2014 www.coconut2D.org
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

// ==================================================================================================================================
//	   ______                             __ ___   ____     __  ___      __
//	  / ____/___  _________  ____  __  __/ /|__ \ / __ \   /  |/  /___ _/ /_____
//	 / /   / __ \/ ___/ __ \/ __ \/ / / / __/_/ // / / /  / /|_/ / __ `/ //_/ _ \
//	/ /___/ /_/ / /__/ /_/ / / / / /_/ / /_/ __// /_/ /  / /  / / /_/ / ,< /  __/
//	\____/\____/\___/\____/_/ /_/\__,_/\__/____/_____/  /_/  /_/\__,_/_/|_|\___/
//
// ==================================================================================================================================

var __global = this;
if(!this['window']) this.window = {};
if(!this['console']) this.console = {log:function(m){}}
if(!this['IDECallback']) this.IDECallback = function(){};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function __exists(collection, key)
{
	return (collection && Object.prototype.hasOwnProperty.call(collection, key)) || false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Object.defineProperty(Array.prototype, "insert", { enumerable:false, value: function(index)
{
    index = Math.min(index, this.length);
    arguments.length > 1
        && this.splice.apply(this, [index, 0].concat([].pop.call(arguments)))
        && this.insert.apply(this, arguments);
    return this;
}});

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Object.defineProperty(Array.prototype, "switch", { value: function(v)
{
	for(var i=this.length;i--;)
	{
		if(this[i]==v) return i;
	}
	return -1;
}});

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function CocoMake(command , params)
{
	var _this = this;
	__global.__coco_make = this;
	var TARGET = makefile.Config.TARGETS[makefile.Vars.TARGET];
	makefile.Vars["UCONFIGURATION"] = makefile.Vars.CONFIGURATION.toUpperCase();
	params = JSON.parse(params);

	// ==================================================================================================================================
	//	    ____        _ __    __
	//	   / __ )__  __(_) /___/ /__  __________
	//	  / __  / / / / / / __  / _ \/ ___/ ___/
	//	 / /_/ / /_/ / / / /_/ /  __/ /  (__  )
	//	/_____/\__,_/_/_/\__,_/\___/_/  /____/
	//
	// ==================================================================================================================================

    // =====================================================================
    // Build for CocoPlay
    // (Similar to Browsers with OpenGL and HTML5 native bindings)
    // =====================================================================
  	_this.Build_CocoPlayer = function(params)
  	{
  		if(params && params.mode=="compile")
  		{
	  		_this.generate_javascript();
  		}
  		else
  		{
	  		_this.clean();
	  		_this.apply_device_wrapper();
	  		_this.generate_icons();
	  		_this.copy_assets();
	  		_this.generate_javascript();
	  		_this.copy_framework_libs();
	  		_this.create_payload_js();
	  		_this.closure();
  		}
  	};

  	_this.Build_CocoScript = _this.Build_CocoPlayer;

    // =====================================================================
    // Build for HTML5 Browsers
    // =====================================================================
  	_this.Build_HTML5 = function(params)
  	{
  		if(params && params.mode=="compile")
  		{
	  		_this.generate_javascript();
  		}
  		else
  		{
	  		_this.clean();
	  		_this.apply_device_wrapper();
	  		_this.generate_icons();
	  		_this.copy_assets();
	  		_this.generate_javascript();
	  		_this.copy_framework_libs();
	  		_this.create_payload_js();
	  		_this.closure();
	  		_this.create_index_html();
  		}
  	};

    // =====================================================================
    // Build for Android Devices
    // =====================================================================
  	_this.Build_Android = function(params)
  	{
  		makefile.Vars["ANDROID_SDK_ESCAPED"] = makefile.Vars.PATH_3RD_PARTY_ANDROID_SDK.replace(/\x2f/mg, '\\\\');
  		makefile.Vars["PATH_SDK_LIBRARIES_ANDROID"] = relativePath(TARGET.TARGET_ROOT+"/jni", makefile.Vars.PATH_SDK_LIBRARIES+"/Android");

  		if(params && params.mode=="compile")
  		{
	  		_this.generate_cpp();
  		}
  		else
  		{
	  		_this.clean();
	  		_this.apply_device_wrapper();
	  		_this.generate_icons();
	  		_this.copy_assets();
	  		_this.generate_cpp();
	  		_this.compile_jni_static_lib();
	  		_this.compile_apk();
  		}
  	};

    // =====================================================================
    // Build for iOS Devices
    // =====================================================================
  	_this.Build_iOS = function(params)
  	{
  		if(params && params.mode=="compile")
  		{
	  		_this.generate_cpp();
  		}
  		else
  		{
	  		//_this.clean();
	  		_this.apply_device_wrapper();
	  		_this.generate_icons();
	  		_this.copy_assets();
	  		_this.generate_cpp();
	  		_this.compile_ipa();
  		}
  	};

    // =====================================================================
    // Build for Win32
    // =====================================================================
  	_this.Build_Win32 = function(params)
  	{
  		if(params && params.mode=="compile")
  		{
	  		_this.generate_cpp();
  		}
  		else
  		{
	  		//_this.clean();
	  		_this.apply_device_wrapper();
	  		_this.generate_icons();
	  		_this.copy_assets();
	  		_this.generate_cpp();
	  		_this.compile_x86();
  		}
  	};

	// ==================================================================================================================================
	//	   ______                      _ __
	//	  / ____/___  ____ ___  ____  (_) /__  __________
	//	 / /   / __ \/ __ `__ \/ __ \/ / / _ \/ ___/ ___/
	//	/ /___/ /_/ / / / / / / /_/ / / /  __/ /  (__  )
	//	\____/\____/_/ /_/ /_/ .___/_/_/\___/_/  /____/
	//	                    /_/
	// ==================================================================================================================================

    // =====================================================================
    // Compile JavaScript Classes to pure JavaScript
    // =====================================================================
	_this.generate_javascript = function()
	{
		// Get all source code (including externs)
		var code = _this.getSourceCode();

		// Parse source code and generate AST
		trace("\nParsing JavaScript Class files ...");
		narcissus.__messages = true;
		narcissus.__cpp = false;
		var ast = narcissus.jsparse(code);
		trace("+ Abstract Syntax Tree (AST) is generated.");

		// Compile AST
		trace("\nCompiling JavaScript Classes to JavaScript ...");
		var compiler = new Compiler(ast);
		compiler.compile(true,null,false);
		trace("+ Done.");
	};

    // =====================================================================
    // Compile JavaScript Classes to C++
    // =====================================================================
	_this.generate_cpp = function()
	{
		// Get all source code (including externs)
		var code = _this.getSourceCode();

		// Collect all non-generated C++ classes from Frameworks
		trace("\nScanning for non-generated C++ classes in Frameworks ...");
		var native_classes = [];
		var native_vartypes_includes = {};
		var paths = [makefile.Config.PROJECT_PATHS.NATIVE_COMMON].concat(TARGET.TARGET_ADDITIONAL_NATIVE_SOURCES.split(";"));
		var frameworks = makefile.Config.PROJECT_FRAMEWORKS.split(";");
		for(item in makefile.Components.Frameworks)
		{
			if(frameworks.indexOf(item)!=-1)
			{
				var path = makefile.Components.Frameworks[item].Path + "/$(PATH_SDK_FRAMEWORKS_NATIVE)/$(PATH_SDK_FRAMEWORKS_SRC)";
				paths.push(path);
			}
		}
		for(j=0;j<paths.length;j++)
		{
			path = paths[j];
			path = _this.replaceVars(path);
			var files = _this.FindFiles(path, "*.hpp;*.h", true);
			for(i=0;i<files.length;i++)
			{
				var fileName = files[i].substr(files[i].lastIndexOf("/")+1);
				if(fileName.toLowerCase()=="coconut2d.hpp") continue;

				native_vartypes_includes[fileName] = {};

				var buff = read(files[i]);
				buff = _this.removeComments(buff);
				var rx = /(?:\btemplate[^>]+>[\s\n\r\t]*?)?\b(class|struct)\s+([^\s\n\r\t\x7B\:]+)/g;
				while(match=rx.exec(buff))
				{
					var classDef  = match[0] + "";
					var className = match[2] + "";

					if(classDef.indexOf("template")!=-1) continue;
					if(classDef.indexOf(";")!=-1) continue;
					if(native_classes.indexOf(classDef+";")!=-1) continue;

					native_classes.push(classDef+";");
					native_vartypes_includes[fileName][className] = relativePath(path, files[i]).replace(fileName,"");
				}
			}
		}
		native_classes = native_classes.sort().join("\n");
		trace(native_classes.replace(/(class|struct) /g, "+ $1 ").replace(/;/g,''));

		// Parse source code and generate AST
		trace("\nParsing JavaScript Class files ...");
		narcissus.__messages = true;
		narcissus.__cpp = true;
		var ast = narcissus.jsparse(code);
		trace("+ Abstract Syntax Tree (AST) generated.");

		// Compile AST to C++
		trace("\nCompiling JavaScript Classes to C++ ...");
		var compiler = new Compiler(ast);
		compiler.native_vartypes_includes = native_vartypes_includes;
		compiler.compile(false,null,true);

		// Get all generated C++ classes from the compiler
		var generated_classes = compiler.getNativeClassList();

		// Update class forward declarations in Coconut2d.hpp
		var buff = read(makefile.Vars.FILE_PATH_SDK_CRL_COCONUT2D_HPP);
		buff = _this.replaceBuffer("//# Generated Classes Begin #//", "//# Generated Classes End #//", buff, generated_classes);
		//buff = _this.replaceBuffer("//# Native Classes Begin #//", "//# Native Classes End #//", buff, native_classes);
		_this.module(makefile.Vars.FILE_PATH_SDK_CRL_COCONUT2D_HPP, buff);

		trace("+ Done.");
	};

    // =====================================================================
    // Minimize JavaScript with Closure Compiler
    // =====================================================================
	_this.closure = function()
	{
		if(makefile.Config.CONFIGURATION=="Release")
		{
			trace("\nMinimizing JavaScript ...");

			// Shell to closure compiler
			var cmd = _this.replaceVars('"$(PATH_3RD_PARTY_JAVA)/bin/java.exe" -jar "$(PATH_3RD_PARTY_CLOSURE)/compiler.jar" --compilation_level=SIMPLE_OPTIMIZATIONS --js="$(TARGET_ROOT)/payload.js" --js_output_file="$(TARGET_ROOT)/payload_min.js"');
			_this.shell(cmd);

			// Load minimized payload to IDE
			if(fileExists(TARGET.TARGET_ROOT + "/payload_min.js"))
			{
				copyFile(TARGET.TARGET_ROOT + "/payload_min.js", TARGET.TARGET_ROOT + "/payload.js");
				_this.DeleteFile(TARGET.TARGET_ROOT + "/payload_min.js");
				_this.module(TARGET.TARGET_ROOT + "/payload.js", read(TARGET.TARGET_ROOT + "/payload.js"));
			}
		}
	}

    // =====================================================================
    // Compile Android C++ JNI to Static Library
    // =====================================================================
  	_this.compile_jni_static_lib = function()
  	{
  		trace("\nCompiling Android JNI Static Library ...");

		// Collect all C++ sources
  		var files = _this.collectSources(TARGET.TARGET_ROOT + "/jni",
  										 [ makefile.Config.PROJECT_PATHS.NATIVE_COMMON, TARGET.TARGET_ADDITIONAL_NATIVE_SOURCES ].join(";"),
  										 TARGET.TARGET_NATIVE_MASK,
  										 "/$(PATH_SDK_FRAMEWORKS_NATIVE)/$(PATH_SDK_FRAMEWORKS_GEN);" +
  										 "/$(PATH_SDK_FRAMEWORKS_NATIVE)/$(PATH_SDK_FRAMEWORKS_SRC)");

		// Make all paths relative to JNI folder
		files = _this.get_relative_cpp_hpp(files, TARGET.TARGET_ROOT + "/jni");
		makefile.Vars["NATIVE_CPP_SOURCES"] = files.CPP.join(" \\\n");
		makefile.Vars["NATIVE_CPP_INCLUDES"] = makefile.Vars.INCLUDE_PATHS.join(" \\\n");//files.HPP.join(" \\\n");

        // Create Android.mk
		var file = TARGET.TARGET_ROOT+"/jni/Android.mk";
		trace("\nCreating Android.mk makefile ...");
		trace("+ makefile: " + file);
        trace("+ replacing variables ...");
		var buff = read(file);
		buff = _this.replaceVars(buff, true, ["CLEAR_VARS", "TARGET_ARCH_ABI", "PREBUILT_STATIC_LIBRARY", "BUILD_SHARED_LIBRARY"]);
        _this.module(file, buff);

        // Create Application.mk
		var file = TARGET.TARGET_ROOT+"/jni/Application.mk";
		trace("\nCreating Application.mk makefile ...");
		trace("+ makefile: " + file);
        trace("+ replacing variables ...");
		var buff = read(file);
		buff = _this.replaceVars(buff, true);
        _this.module(file, buff);

        // Create a custom make_lib.bat (offers better control than relying on environment variables)
        var buff = [];
        var make_lib_cmd = TARGET.TARGET_ROOT + "/jni/make_lib.bat";
        buff.push('@echo off');
        buff.push('SET NDK_ROOT=' + _this.winPath(makefile.Vars.PATH_3RD_PARTY_ANDROID_NDK)+"\\");
        buff.push('SET NDK_PROJECT_PATH=$(TARGET_ROOT)');
        buff.push('call "%NDK_ROOT%find-win-host.cmd" NDK_WIN_HOST');
        buff.push('if ERRORLEVEL 1 (exit /b 1)');
        buff.push('SET NDK_MAKE=%NDK_ROOT%prebuilt/%NDK_WIN_HOST%/bin/make.exe');
		buff.push('"%NDK_MAKE%" -f "%NDK_ROOT%build/core/build-local.mk" SHELL=cmd clean');
		buff.push('"%NDK_MAKE%" -f "%NDK_ROOT%build/core/build-local.mk" SHELL=cmd -j %*');
		buff = _this.replaceVars(buff.join("\n"));
        _this.module(make_lib_cmd, buff);

        // Build the static libraries for arm and x86
        trace("\nCalling make ...");
        _this.shell(make_lib_cmd, TARGET.TARGET_ROOT+"/jni", "cc1plus.exe");
        _this.DeleteFile(make_lib_cmd);

        // Sanity check
        if(!fileExists(TARGET.TARGET_ROOT+"/libs/armeabi/libCoconut2D.so") ||
           !fileExists(TARGET.TARGET_ROOT+"/libs/armeabi-v7a/libCoconut2D.so") ||
           !fileExists(TARGET.TARGET_ROOT+"/libs/x86/libCoconut2D.so"))
        {
        	throw new Error("ERROR: Failed to compile Android static library");
        }
  	};

    // =====================================================================
    // Compile Android Java Activity
    // =====================================================================
  	_this.compile_apk = function()
  	{
  		trace("\nCalling ant ...");
  		var buff = [];
  		var make_cmd = TARGET.TARGET_ROOT + "/make.bat";
  		buff.push('@echo off');
  		buff.push(_this.winPath('SET ANT_HOME=' + makefile.Vars.PATH_3RD_PARTY_ANT));
  		buff.push(_this.winPath('SET JAVA_HOME=' + makefile.Vars.PATH_3RD_PARTY_JAVA));
  		buff.push(_this.winPath('SET ANDROID_SDK_HOME=' + makefile.Vars.PATH_3RD_PARTY_ANDROID_SDK+"\\"));
  		buff.push(_this.winPath('SET PATH=%ANT_HOME%;%ANT_HOME%/bin;%JAVA_HOME%;%JAVA_HOME%/bin;%PATH%'));
  		buff.push(_this.winPath('"%ANT_HOME%/bin/ant" -S ' + makefile.Vars.CONFIGURATION.toLowerCase()));
		buff = _this.replaceVars(buff.join("\n"));
        _this.module(make_cmd, buff);
        _this.shell(make_cmd, TARGET.TARGET_ROOT);
        _this.DeleteFile(make_cmd);
        _this.DeleteFolder(TARGET.TARGET_ROOT+"/obj");

        // Sanity check and output
        var intermediate_apk = _this.replaceVars("$(TARGET_ROOT)/bin/$(PROJECT_NAME)-$(CONFIGURATION).apk");
        var final_apk = _this.replaceVars("$(TARGET_ROOT)/bin/$(PROJECT_NAME).apk");
        var root_apk =  _this.replaceVars("$(TARGET_ROOT)/$(PROJECT_NAME).apk");
        if(!fileExists(intermediate_apk))
        {
        	throw new Error("Failed to compile Android application");
        }
        else
        {
        	copyFile(intermediate_apk, root_apk);
        	_this.cleanFolder(TARGET.TARGET_ROOT+"/bin");
        	_this.DeleteFolder(TARGET.TARGET_ROOT+"/libs");
        	_this.DeleteFolder(TARGET.TARGET_ROOT+"/assets");
        	copyFile(root_apk, final_apk);
        	deleteFile(root_apk);
        }
  	};

    // =====================================================================
    // Compile iOS Application
    // =====================================================================
  	_this.compile_ipa = function()
  	{
  		trace("\nCompiling iOS Application ...");

		// Collect all C++ sources
  		var sources = _this.collectSources(TARGET.TARGET_ROOT,
  										   [ makefile.Config.PROJECT_PATHS.NATIVE_COMMON, TARGET.TARGET_ADDITIONAL_NATIVE_SOURCES ].join(";"),
  										   TARGET.TARGET_NATIVE_MASK,
  										   "/$(PATH_SDK_FRAMEWORKS_NATIVE)/$(PATH_SDK_FRAMEWORKS_GEN);" +
  										   "/$(PATH_SDK_FRAMEWORKS_NATIVE)/$(PATH_SDK_FRAMEWORKS_SRC)");

		// Make all paths relative to target folder
		files = _this.get_relative_cpp_hpp(sources, TARGET.TARGET_ROOT);
		makefile.Vars["NATIVE_CPP_SOURCES"] = _this.winPath(files.CPP.join(" \\\n"));
		makefile.Vars["NATIVE_CPP_INCLUDES"] = _this.winPath(" -I" + makefile.Vars.INCLUDE_PATHS.join(" \\\n -I"));

		// Collect resources
		trace("\n Collecting Resources ...");
		var files = _this.FindFiles(TARGET.TARGET_ROOT, TARGET.TARGET_RESOURCES_MASK, false);
		for(var i=0;i<files.length;i++) { files[i] = relativePath(TARGET.TARGET_ROOT, files[i]); }
		files.push("./assets");
		makefile.Vars["NATIVE_RESOURCES"] = files.join(" \\\n");
		trace("+ Done.");

		// Patch main.m to load Fonts
		_this.loadFonts(TARGET.TARGET_ROOT + "/src/main.m", TARGET.TARGET_ASSETS);

		// Collect icons
		trace("\n Collecting Icons ...");
		var files = _this.FindFiles(TARGET.TARGET_ROOT, "*.png", false);
		for(i=0;i<files.length;i++)
		{
			files[i] = files[i].substr(files[i].lastIndexOf("/")+1);
			files[i] = "\t\t<string>" + files[i] + "</string>";
	  	}
		makefile.Vars["APP_ICONS"] = files.join("\n");
		trace("+ Done.");

		// Create Info.plist
		trace("\n Creating Info.plist ...");
        trace("+ replacing variables ...");
		var file = TARGET.TARGET_ROOT+"/Info.plist";
		var buff = read(file);
		buff = _this.replaceVars(buff, true);
        _this.module(file, buff);

        // Create Makefile
		var file = TARGET.TARGET_ROOT+"/Makefile.mk";
		trace("\nCreating iOS makefile ...");
		trace("+ makefile: " + file);
        trace("+ replacing variables ...");
		var buff = read(file);
		var excludeVars = TARGET.DEVICE_WRAPPER.TEMPLATE_EXCLUDE_VARS ? TARGET.DEVICE_WRAPPER.TEMPLATE_EXCLUDE_VARS.split(";") : null;
		buff = _this.replaceVars(buff, true, excludeVars);
        _this.module(file, buff);

        // Create a custom make_ios.bat (offers better control than relying on environment variables)  //--warn-undefined-variables
        var buff = [];
        var make_cmd = TARGET.TARGET_ROOT + "/make_ios.bat";
        buff.push('@echo off');
        buff.push('SET IOSBUILDENV_PATH=' + makefile.Vars.PATH_3RD_PARTY_IOS_BUILD_ENV);
        buff.push('SET IOS_PROJECT_PATH=$(TARGET_ROOT)');
		buff.push('SET IOS_MAKEFILE=%IOS_PROJECT_PATH%/Makefile.mk');
		buff.push('"%IOSBUILDENV_PATH%/Toolchain/make.exe" --directory="%IOS_PROJECT_PATH%" --makefile="%IOS_MAKEFILE%" SHELL=%ComSpec% prepare resources');
        buff.push('"%IOSBUILDENV_PATH%/Toolchain/make.exe" --directory="%IOS_PROJECT_PATH%" --makefile="%IOS_MAKEFILE%" --jobs SHELL=%ComSpec% compile');
        buff.push('"%IOSBUILDENV_PATH%/Toolchain/make.exe" --directory="%IOS_PROJECT_PATH%" --makefile="%IOS_MAKEFILE%" SHELL=%ComSpec% link codesign ipa end');
		buff = _this.replaceVars(_this.winPath(buff.join("\n")));
        _this.module(make_cmd, buff);

        // Build the static libraries for arm and x86
        trace("\nCalling iOS make ...");
        _this.shell(make_cmd, TARGET.TARGET_ROOT);
        _this.DeleteFile(make_cmd);
        //_this.DeleteFolder(TARGET.TARGET_ROOT+"/obj");
        _this.DeleteFolder(TARGET.TARGET_ROOT+"/assets");

        // Sanity check
        if(!fileExists(TARGET.TARGET_OUTPUT))
       		throw new Error("ERROR: Failed to compile iOS Application");
  	};

    // =====================================================================
    // Compile x86 Windows Application
    // =====================================================================
  	_this.compile_x86 = function()
  	{
  		trace("\nCompiling Windows x86 Application ...");

		// Collect all C++ sources
  		var sources = _this.collectSources(TARGET.TARGET_ROOT,
  										   [ makefile.Config.PROJECT_PATHS.NATIVE_COMMON, TARGET.TARGET_ADDITIONAL_NATIVE_SOURCES ].join(";"),
  										   TARGET.TARGET_NATIVE_MASK,
  										   "/$(PATH_SDK_FRAMEWORKS_NATIVE)/$(PATH_SDK_FRAMEWORKS_GEN);" +
  										   "/$(PATH_SDK_FRAMEWORKS_NATIVE)/$(PATH_SDK_FRAMEWORKS_SRC)");

		// Make all paths relative to target folder
		files = _this.get_relative_cpp_hpp(sources, TARGET.TARGET_ROOT);
		makefile.Vars["NATIVE_CPP_SOURCES"] = _this.winPath(files.CPP.join(" \\\n"));
		makefile.Vars["NATIVE_CPP_INCLUDES"] = _this.winPath(" -I" + makefile.Vars.INCLUDE_PATHS.join(" \\\n -I"));

		// Collect resources
		trace("\n Collecting Resources ...");
		var files = _this.FindFiles(TARGET.TARGET_ROOT, TARGET.TARGET_RESOURCES_MASK, false);
		for(i=0;i<files.length;i++) { files[i] = relativePath(TARGET.TARGET_ROOT, files[i]); }
		files.push("./assets");
		makefile.Vars["NATIVE_RESOURCES"] = files.join(" \\\n");
		trace("+ Done.");

        // Create Makefile
		var file = TARGET.TARGET_ROOT+"/Makefile.mk";
		trace("\nCreating Windows x86 makefile ...");
		trace("+ makefile: " + file);
        trace("+ replacing variables ...");
		var buff = read(file);
		var excludeVars = TARGET.DEVICE_WRAPPER.TEMPLATE_EXCLUDE_VARS ? TARGET.DEVICE_WRAPPER.TEMPLATE_EXCLUDE_VARS.split(";") : null;
		buff = _this.replaceVars(buff, true, excludeVars);
        _this.module(file, buff);

        // Create a custom make_x86.bat
        var buff = [];
        var make_cmd = TARGET.TARGET_ROOT + "/make_x86.bat";
        buff.push('@echo off');
        buff.push('SET PROJECT_PATH=$(TARGET_ROOT)');
		buff.push('SET MAKEFILE=%PROJECT_PATH%/Makefile.mk');
		buff.push('SET MINGW=$(PATH_3RD_PARTY_MINGW)');
		buff.push('SET PATH=%MINGW%;%MINGW%/bin;%PATH%');
		buff.push('"%MINGW%/bin/mingw32-make" --directory="%PROJECT_PATH%" --jobs --makefile="%MAKEFILE%"');
		buff = _this.replaceVars(_this.winPath(buff.join("\n")));
        _this.module(make_cmd, buff);

        // Build the static libraries for arm and x86
        trace("\nCalling Windows x86 make ...");
        _this.shell(make_cmd, TARGET.TARGET_ROOT);
        //_this.DeleteFile(make_cmd);

        // Sanity check
        if(!fileExists(TARGET.TARGET_OUTPUT))
       		throw new Error("ERROR: Failed to compile Windows x86 Application");
  	};

	// ==================================================================================================================================
	//	    ______                      __     _  ________          __
	//	   / ____/  ______  ____  _____/ /_   | |/ / ____/___  ____/ /__
	//	  / __/ | |/_/ __ \/ __ \/ ___/ __/   |   / /   / __ \/ __  / _ \
	//	 / /____>  </ /_/ / /_/ / /  / /_    /   / /___/ /_/ / /_/ /  __/
	//	/_____/_/|_/ .___/\____/_/   \__/   /_/|_\____/\____/\__,_/\___/
	//	          /_/
	// ==================================================================================================================================

	_this.EXPORT_XCODE_PROJECT = function(params)
	{
		// http://www.monobjc.net/xcode-project-file-format.html
		// An XCode project is a piece of (stupid) art!
		// Each file inserted in the project has a reference id in a hex form like 8C15xxxx1988089000F91C7B.
		// I am not sure what the prefix and suffix numbers mean but seems to work ok.
		// Source files added need to be added with what XCode calls "Group".
		// A group consists of file reference ids and if it contains other groups in it, then it should
		// also have the group ids in it.

		if(makefile.Vars.TARGET!="iOS")
		{
			throw "Please set target to iOS";
			return;
		}

		// Lets define a data structure to hold the lot.
        var SIG_SRC = "8C15";
        var SIG_END = "1988089000F91C7B";
        var FILE_REFS =
        {
        	src_REF: "",
        	GROUPS:{},
	        PBXBuildFile:[],
	        PBXFileReference:[],
	        PBXGroups:[],
	        PBXLibraries:[],
	        PBXFrameworksBuildPhase:[],
	        PBXSourcesBuildPhase:[]
        };

     	// ==========================================================================================================
     	// First lets take care of the files, copy template files, replace in-file variables, generate icons, etc.
     	// ==========================================================================================================

		// Get the template and destination folders
		var template_folder = makefile.Vars.PATH_SDK_TEMPLATE_XCODE;
		var destination_folder = makefile.Vars.PROJECT_ROOT + "/XCode";

		// Purge previous XCode project and recreate the folders
		deleteFolder(destination_folder);
		buildPath(destination_folder);
		copyFolder(template_folder, destination_folder);

		// Copy the Assets
		_this.copy_assets(destination_folder+"/assets");

		// Copy Libraries
		copyFolder(makefile.Vars.PATH_SDK_LIBRARIES +"/iOS", destination_folder+"/lib/libraries");
		copyFolder(makefile.Vars.PATH_SDK_INCLUDES, destination_folder+"/lib/includes");

		// Generate C++ files
  		_this.generate_cpp();

        // Update modules (text files)
        var files = _this.FindFiles(TARGET.TARGET_ROOT, makefile.Vars.TEXT_FILES, true);
		for(var i=0; i<files.length; i++)
		{
			trace("+ updating: " + files[i]);
			var buff = read(files[i]);
			_this.module(files[i], buff);
		}

		// Collect all C++ sources
  		var sources = _this.collectSources(destination_folder,
  										   makefile.Config.PROJECT_PATHS.NATIVE_COMMON + ";" +
  										   makefile.Vars.PATH_SDK_COMMON + ";" +
  										   TARGET.DEVICE_WRAPPER.PATH + "/src",
  										   TARGET.TARGET_NATIVE_MASK,
  										   "/$(PATH_SDK_FRAMEWORKS_NATIVE)/$(PATH_SDK_FRAMEWORKS_GEN);" +
  										   "/$(PATH_SDK_FRAMEWORKS_NATIVE)/$(PATH_SDK_FRAMEWORKS_SRC)");

 		// Copy C++ files to /src
		trace(sources.join("\n"));
		for(var i=0;i<sources.length;i++)
		{
			var fileName = sources[i].substr(sources[i].lastIndexOf("/")+1);
			var rel = relativePath(_this.ModuleFiles[sources[i]], sources[i]).replace(fileName, "").substr(2);
			buildPath(destination_folder+"/src/"+rel);
			copyFile(sources[i], destination_folder+"/src/"+rel+fileName);
		}

		// Process Template Files
		var templateFilesMask = TARGET.DEVICE_WRAPPER.TEMPLATES;
        if(templateFilesMask)
        {
  			var files = _this.FindFiles(destination_folder, templateFilesMask, true);
  			for(var i=0; i<files.length; i++)
  			{
				var buff = read(files[i]);
				buff = _this.replaceVars(buff, true, ["APP_ICONS", "SCRIPTS"]);
				write(files[i], buff);
  			}
        }

		// Patch main.m to load Fonts
		_this.loadFonts(destination_folder + "/src/main.m", destination_folder+"/assets");

		// Generate Icons
		_this.generate_icons(destination_folder);

		// Collect resources
		var files = _this.FindFiles(destination_folder, TARGET.TARGET_RESOURCES_MASK, false);
		for(i=0;i<files.length;i++) { files[i] = relativePath(destination_folder, files[i]); }
		files.push("./assets");
		makefile.Vars["NATIVE_RESOURCES"] = files.join(" \\\n");

		// Collect icons
		var files = _this.FindFiles(destination_folder, "*.png", false);
		for(i=0;i<files.length;i++)
		{
			files[i] = files[i].substr(files[i].lastIndexOf("/")+1);
			files[i] = "\t\t<string>" + files[i] + "</string>";
		}
		makefile.Vars["APP_ICONS"] = files.join("\n");

		// Create Info.plist
		var file = TARGET.DEVICE_WRAPPER.PATH+"/Info.plist";
		var buff = read(file);
		buff = _this.replaceVars(buff, true);
        write(destination_folder+"/Info.plist", buff);

     	// ==========================================================================================================
     	// Now we process the files and generate the XCode project file
     	// ==========================================================================================================

		// Get the src files, we will work on them...
		var group_index = (2*sources.length);
		sources = sources.sort(function(a,b){ a=a.toUpperCase(); b=b.toUpperCase(); if(a>b) return 1; else if(a==b) return 0; else return -1; });

		for(var i=0; i<sources.length; i++)
		{
			var fileName = sources[i].substr(sources[i].lastIndexOf("/")+1);
			var ext = fileName.substr(fileName.indexOf(".")).toLowerCase();

			// ==============================================
			// Record groups by splitting a file path
			// ==============================================
			var groups = relativePath(_this.ModuleFiles[sources[i]], sources[i]).replace(fileName, "").substr(2).split("/");
			var GROUP = null;
			var iGROUP = null;
			var cGROUP = null;
			for(var j=groups.length-1; j>=0; j--)
			{
				groupRelPath = "src/" + groups.slice(0,j).join("/");
				if(groupRelPath.charAt(groupRelPath.length-1)=="/") groupRelPath = groupRelPath.substr(0, groupRelPath.length-1);
				var groupName = groupRelPath.split("/");
				groupName = groupName[groupName.length-1];
				if(!(iGROUP=FILE_REFS.GROUPS[groupRelPath]))
				{
					iGROUP = FILE_REFS.GROUPS[groupRelPath]  =
					{
						name	: groupName,
						path	: groupRelPath,
						ID		: SIG_SRC + hex(++group_index) + SIG_END,
						ITEMS	: {}
					};
				}

				if(groupName=="src") FILE_REFS.src_REF = iGROUP.ID;
				if(!GROUP) GROUP = iGROUP;
				if(cGROUP) iGROUP.ITEMS[ cGROUP.ID ] = cGROUP;
				cGROUP = iGROUP;
			}

			// ==============================================
			// Record a file
			// ==============================================
			var FILE =
			{
				name	: fileName,
				path	: GROUP.path + "/" + fileName,
				source	: "sourcecode.cpp.cpp",
				ID		: SIG_SRC + hex(i) + SIG_END,
				REF		: SIG_SRC + hex(sources.length + i) + SIG_END
			};

			// Add file to group
			GROUP.ITEMS[ FILE.ID ] = FILE;

			// Generate additional XCode sections
			switch(ext)
			{
			case ".m":
				FILE.source = "sourcecode.c.objc";
				FILE_REFS.PBXSourcesBuildPhase.push("\t\t\t\t" + FILE.REF + " /* " + FILE.name + " in " + GROUP.name + " */,");
				FILE_REFS.PBXBuildFile.push("\t\t" + FILE.REF + " /* " + FILE.name + " in " + GROUP.name + " */ = {isa = PBXBuildFile; fileRef = " + FILE.ID + " /* " + FILE.name + " */; };");
				break;

			case ".cpp":
				FILE.source = "sourcecode.cpp.cpp";
				FILE_REFS.PBXSourcesBuildPhase.push("\t\t\t\t" + FILE.REF + " /* " + FILE.name + " in " + GROUP.name + " */,");
				FILE_REFS.PBXBuildFile.push("\t\t" + FILE.REF + " /* " + FILE.name + " in " + GROUP.name + " */ = {isa = PBXBuildFile; fileRef = " + FILE.ID + " /* " + FILE.name + " */; };");
				break;

			case ".hpp":
				FILE.source = "sourcecode.cpp.h";
				break;

			case ".h":
				if(sources.indexOf(FILE.name.replace(".h", ".m"))!=-1)
					FILE.source = "sourcecode.c.h";

				else if(sources.indexOf(FILE.name.replace(".h", ".cpp"))!=-1)
					FILE.source = "sourcecode.cpp.h";

				else if(sources.indexOf(FILE.name.replace(".h", ".c"))!=-1)
					FILE.source = "sourcecode.c.h";

				else
					FILE.source = "sourcecode.cpp.h";
				break;
			}

			FILE_REFS.PBXFileReference.push("\t\t" + FILE.ID +" /* " + FILE.name + " */ = {isa = PBXFileReference; fileEncoding = 4; lastKnownFileType = " + FILE.source + "; name = " + FILE.name + "; path = " + FILE.path + "; sourceTree = \"<group>\"; };");
		}

		// Generate Groups
		for(var group in FILE_REFS.GROUPS)
		{
			var GROUP = FILE_REFS.GROUPS[group];

			var list = [];
			for(item in GROUP.ITEMS)
			{
				var FILE = GROUP.ITEMS[item];
				list.push("\t\t\t\t" + FILE.ID + " /* " + FILE.name + " */");
			}

			FILE_REFS.PBXGroups.push("\t\t" + GROUP.ID + " /* " + GROUP.name + " */ = {\n\t\t\tisa = PBXGroup;\n\t\t\tchildren = (\n" + list.join(",\n") + "\n\t\t\t);\n\t\t\tname = " + GROUP.name + ";\n\t\t\tsourceTree = \"<group>\";\n\t\t};");
		}

        // Create project.pbxproj
        var pbxproj = read(destination_folder+"/project.pbxproj");
		pbxproj = pbxproj.replace("$(FILE_REFS.src_REF)", FILE_REFS.src_REF);
		pbxproj = pbxproj.replace("$(PBXBuildFile)", FILE_REFS.PBXBuildFile.join("\n"));
		pbxproj = pbxproj.replace("$(PBXFileReference)", FILE_REFS.PBXFileReference.join("\n"));
		pbxproj = pbxproj.replace("$(PBXGroups)", FILE_REFS.PBXGroups.join("\n"));
		pbxproj = pbxproj.replace("$(PBXLibraries)", FILE_REFS.PBXLibraries.join("\n"));
		pbxproj = pbxproj.replace("$(PBXFrameworksBuildPhase)", FILE_REFS.PBXFrameworksBuildPhase.join("\n"));
		pbxproj = pbxproj.replace("$(PBXSourcesBuildPhase)", FILE_REFS.PBXSourcesBuildPhase.join("\n"));
		pbxproj = pbxproj.replace(/\$\(PROJECT_NAME\)/g, makefile.Vars.PROJECT_NAME);
		buildPath(destination_folder+"/" + makefile.Vars.PROJECT_NAME + ".xcodeproj");
		write(destination_folder+"/" + makefile.Vars.PROJECT_NAME + ".xcodeproj/project.pbxproj", pbxproj);
		deleteFile(destination_folder+"/project.pbxproj");

		trace("XCode Project created in " + destination_folder);
	};

	// ==================================================================================================================================
	//	   ________                 _
	//	  / ____/ /__  ____ _____  (_)___  ____ _
	//	 / /   / / _ \/ __ `/ __ \/ / __ \/ __ `/
	//	/ /___/ /  __/ /_/ / / / / / / / / /_/ /
	//	\____/_/\___/\__,_/_/ /_/_/_/ /_/\__, /
	//	                                /____/
	// ==================================================================================================================================

    // =====================================================================
    // Clean target defined folders and generated code and resources
    // =====================================================================
	_this.clean = function()
	{
		trace("\nCleanning target ...");

		// Clean target defined folders
		trace("+ cleanning target defined folders ...");
		var folders = TARGET.TARGET_CLEAN.split(";");
		for(var i=0; i<folders.length; i++)
		{
			if(folderExists(folders[i]))
				_this.cleanFolder(folders[i]);
			else if(fileExists(folders[i]))
				_this.DeleteFile(folders[i]);
		}

		// Remove known deliverables
		_this.DeleteFile(TARGET.TARGET_ROOT + "/payload.js");

		// Remove generated C++ code from Frameworks
		trace("+ cleanning generated C++ sources ...");
		for(item in makefile.Components.Frameworks)
		{
			var path = makefile.Components.Frameworks[item].Path + "/$(PATH_SDK_FRAMEWORKS_NATIVE)/$(PATH_SDK_FRAMEWORKS_GEN)";
			path = _this.replaceVars(path);
			_this.cleanFolder(path);
		}

		// Remove generated C++ code from native common folder (user code)
		_this.cleanFolder(makefile.Vars["PROJECT_PATHS.NATIVE_COMMON"]);
	};

    // =====================================================================
	_this.cleanFolder = function(path)
	{
  		trace("  + cleanning: " + path);
  		buildPath(path);
  		var items = folderItems(path);
  		for(var i=0;i<items.length;i++)
  		{
  			if(fileExists(items[i]))
  				_this.DeleteFile(items[i]);
  			else if(folderExists(items[i]))
  				_this.DeleteFolder(items[i]);
		}
	};

	// ==================================================================================================================================
	//	  ______                     __      __
	//	 /_  __/__  ____ ___  ____  / /___ _/ /____  _____
	//	  / / / _ \/ __ `__ \/ __ \/ / __ `/ __/ _ \/ ___/
	//	 / / /  __/ / / / / / /_/ / / /_/ / /_/  __(__  )
	//	/_/  \___/_/ /_/ /_/ .___/_/\__,_/\__/\___/____/
	//	                  /_/
	// ==================================================================================================================================

    // =====================================================================
    // Copy source assets to target
    // =====================================================================
	_this.copy_assets = function(optDestination)
	{
		var src = makefile.Config.PROJECT_PATHS.ASSETS;
		var dst = optDestination||TARGET.TARGET_ASSETS;
		trace("\nCopying assets ...");
		trace("+ source: " + src);
		trace("+ destination: " + dst);
	  	if(!folderExists(src))
	  		throw new Error("Assets folder not found " + src);
	  	buildPath(dst);
		copyFolder(src, dst);
		deleteFolder(dst + "/animations"); // Contains binary animation files
		IDECallback("folder", dst);
	};

    // =====================================================================
    // Copy Device Wrapper Template to target
    // =====================================================================
	_this.apply_device_wrapper = function()
	{
		trace("\nApplying Device Wrapper Template ...");

		trace("+ source: " + TARGET.DEVICE_WRAPPER.PATH);
		trace("+ destination: " + TARGET.TARGET_ROOT);

		// Copy device wrapper template folder to target root
		copyFolder(TARGET.DEVICE_WRAPPER.PATH, TARGET.TARGET_ROOT);
		IDECallback("folder", TARGET.TARGET_ROOT);

		// We need to resolve path variables to actual paths
		// eg. $(PROJECT_PACKAGE) resolves to com/mobilefx/coconut2d
		var folders = _this.FindFolders(TARGET.TARGET_ROOT, "$*;$*.*", true);
		for(i=0;i<folders.length;i++)
		{
			var src = folders[i];
			var dst = folders[i];
			for(;;)
			{
				var match = /\$\(([^)]+?)\)/mg.exec(dst);
				if(!match) break;
				var value = makefile.Vars[match[1]];
				value = value.replace(/\./g, "/");
				dst = dst.replace(match[0], value);
			}
			if(src!=dst)
			{
				copyFolder(src, dst);
				deleteFolder(src);
			}
		}

		// Get a list of template files for this target and replace variables
		var templateFilesMask = TARGET.DEVICE_WRAPPER.TEMPLATES;
		trace("+ templates: " + (templateFilesMask ? templateFilesMask : "(none)"));
        if(templateFilesMask)
        {
  			trace("\nProcessing Templates ...");
  			var files = _this.FindFiles(TARGET.TARGET_ROOT, templateFilesMask, true);
  			for(var i=0; i<files.length; i++)
  			{
				trace("+ processing: " + files[i]);
				var buff = read(files[i]);
				buff = _this.replaceVars(buff, true, ["APP_ICONS", "SCRIPTS"]);
  				_this.module(files[i], buff);
  			}
        }

        // Update modules (text files)
        var files = _this.FindFiles(TARGET.TARGET_ROOT, makefile.Vars.TEXT_FILES, true);
		for(var i=0; i<files.length; i++)
		{
			trace("+ updating: " + files[i]);
			var buff = read(files[i]);
			_this.module(files[i], buff);
		}
	};

    // =====================================================================
    // Generate icons
    // =====================================================================
	_this.generate_icons = function(altFolder)
	{
		var list = TARGET.APP_ICONS;
		if(!list) return;

		trace("\nGenerating App Icons ...");

		var template = makefile.Config.PROJECT_PATHS.ICON_2048x2048;
		if(!template || !fileExists(template))
			throw new Error("Missing project template icon (2048x2048)");

		trace("+ template: " + template);

		for(size in list)
		{
			var exports = list[size].split(";");
			for(var i=0;i<exports.length;i++)
			{

				if(altFolder)
					exports[i] = altFolder + "/" + exports[i].substr(exports[i].lastIndexOf("/")+1);

				if(!fileExists(exports[i]))
				{
					trace("+ generating: " + exports[i]);
					resizeImage(template, exports[i], size);
				}
				else
				{
					trace("+ exists: " + exports[i]);
				}
			}
		}
	};

    // =====================================================================
    // Fonts Initialization Code
    // =====================================================================
	_this.loadFonts = function(file, assetsRoot)
	{
		var fonts = _this.FindFiles(assetsRoot+"/fonts", "*.ttf", true);
		var buff = read(file);
		for(var i=0;i<fonts.length;i++)
		{
			fonts[i] = relativePath(assetsRoot, fonts[i]);
			var fontFile = fonts[i].split("/");
			fontFile = fontFile[fontFile.length-1];
			fontName = /\w+/.exec(fontFile)[0];
			var style = "Regular";
			if(fonts[i].indexOf("Bold")!=-1) style = "Bold";
			if(fonts[i].indexOf("Italic")!=-1) style = "Italic";
			if(fonts[i].indexOf("BoldItalic")!=-1) style = "BoldItalic";
			fonts[i] = '\tCocoFontsCache::add("' + fontName + '", CocoFontsCache::FONT_STYLE::' + style + ', "' + fonts[i] + '");';
		}
		buff = buff.replace("\t$(IOS_FONTS_LIST)", fonts.join("\n"));
		_this.module(file, buff, false);
	};

	// ==================================================================================================================================
	//	   ______                _____           _       __     _____                               ______          __
	//	  / ____/___  _________ / ___/__________(_)___  / /_   / ___/____  __  _______________     / ____/___  ____/ /__
	//	 / /   / __ \/ ___/ __ \\__ \/ ___/ ___/ / __ \/ __/   \__ \/ __ \/ / / / ___/ ___/ _ \   / /   / __ \/ __  / _ \
	//	/ /___/ /_/ / /__/ /_/ /__/ / /__/ /  / / /_/ / /_    ___/ / /_/ / /_/ / /  / /__/  __/  / /___/ /_/ / /_/ /  __/
	//	\____/\____/\___/\____/____/\___/_/  /_/ .___/\__/   /____/\____/\__,_/_/   \___/\___/   \____/\____/\__,_/\___/
	//	                                      /_/
	// ==================================================================================================================================

  	// =====================================================================
    // Read all CocoScript source code into a huge buffer
    // =====================================================================
  	_this.getSourceCode = function()
  	{
  		var buff = [];

  		// Calculate source code dependencies
  		var files = _this.collectSources(TARGET.TARGET_ROOT,
  			                             makefile.Config.PROJECT_PATHS.SOURCES,
  										 makefile.Config.PROJECT_PATHS.SOURCES_MASK,
  										 "/$(PATH_SDK_FRAMEWORKS_WEB)/$(PATH_SDK_FRAMEWORKS_SRC)");

  		files = _this.calculateDependencies(files);

  		// Externs
		var file = makefile.Vars.PATH_SDK_COMPILER + "/externs.jspp";
	  	if(!fileExists(file))
	  		throw new Error("Externs file not found " + file);
		trace("\nLoading externs ...");
		trace("+ externs: " + file);
		var externs = read(file);
  		buff.push("\"script_begin:///externs.jspp\";\n" + externs + "\n\"script_end:///externs.jspp\";\n");

  		// Source Code
		for(var i=0;i<files.length;i++)
		{
			var file = files[i];
		    var code = read(file);
		    buff.push('"script_begin:///' + file + '";\n' + code + '\n"script_end:///' + file + '";\n');
		}

		buff = buff.join("\n");
		return buff;
  	};

    // =====================================================================
    // Analyze CocoScript classes and derive compilation order
    // =====================================================================
  	_this.calculateDependencies = function(files, postProcess)
  	{
  		if(postProcess)
  			trace("+ Deriving scripts order ...");
  		else
  			trace("\nCalculating dependencies ...");

  		var errors = false;
  		var g = new Graph();

  		// Create an id-file map for all files
  		var sources_map = {};
  		for(var i=0; i<files.length; i++)
  		{
  			var name = files[i].substr(files[i].lastIndexOf("/")+1);
  			name = name.replace(/\.j\w+/g, "");
  			sources_map[name] = files[i];
  			g.addV(name);
  		}

  		// Create graph matrix
  		for(var i=0; i<files.length; i++)
  		{
  			var found = false;
  			var name = files[i].substr(files[i].lastIndexOf("/")+1);
  			name = name.replace(/\.j\w+/g, "");
  			buff = read(files[i]);
  			var rx = new RegExp("\\x22\\#include ([^\\x22]+)\\x22", "mg");
  			while(match=rx.exec(buff))
  			{
  				var inc = match[1];
  				inc = inc.replace(/\.(jobj|jspp)/g, "");
  				if(!postProcess && !sources_map[inc])
  				{
  					trace("> !ERROR: Include file [" + inc + "] not found in module " + files[i]);
  					errors=true;
  				}
				g.addE(name, inc);
				found = true;
  			}
  			if(!found && name!="Constants")
  			{
				g.addE(name, "Constants");
  			}
  		}

  		if(errors)
  			throw new Error("Errors resolving dependencies");

  		// Sort the acuclic graph
  		files = g.sort();
  		if(!files) throw new Error("Failed to resolve dependencies");

  		// Generate dependencies list
  		for(var i=0; i<files.length; i++)
  		{
  			files[i] = sources_map[ files[i] ];
  		}

  		if(!postProcess)
  		{
  			trace("+ dependency order:");
  			trace("+ "+files.join("\n+ "));
  		}

  		return files;
  	};

	// ==================================================================================================================================
	//	       __                  _____           _       __     _____                               ______          __
	//	      / /___ __   ______ _/ ___/__________(_)___  / /_   / ___/____  __  _______________     / ____/___  ____/ /__
	//	 __  / / __ `/ | / / __ `/\__ \/ ___/ ___/ / __ \/ __/   \__ \/ __ \/ / / / ___/ ___/ _ \   / /   / __ \/ __  / _ \
	//	/ /_/ / /_/ /| |/ / /_/ /___/ / /__/ /  / / /_/ / /_    ___/ / /_/ / /_/ / /  / /__/  __/  / /___/ /_/ / /_/ /  __/
	//	\____/\__,_/ |___/\__,_//____/\___/_/  /_/ .___/\__/   /____/\____/\__,_/_/   \___/\___/   \____/\____/\__,_/\___/
	//	                                        /_/
	// ==================================================================================================================================

    // =====================================================================
    // Copy Framework JavaScript Libraries to target/out
    // =====================================================================
	_this.copy_framework_libs = function()
	{
		var FileMasks = "*.js";
		var vFrameworksSrcSubPaths = "/$(PATH_SDK_FRAMEWORKS_WEB)/$(PATH_SDK_FRAMEWORKS_LIB)";

	    trace("\nCollecting JavaScript Libraries ...\n+ pattern: " + FileMasks);

	    // Collect source paths from frameworks
	    trace("+ scanning frameworks ...");
	    var vFrameworks = makefile.Config.PROJECT_FRAMEWORKS;
	    if(TARGET.TARGET_ADDITIONAL_FRAMEWORKS) vFrameworks += (";"+TARGET.TARGET_ADDITIONAL_FRAMEWORKS)
	    vFrameworks = vFrameworks.split(";");
	    vFrameworksSrcSubPaths = vFrameworksSrcSubPaths.split(";");
	    for(var i=0; i<vFrameworks.length; i++)
	    {
	    	if(!vFrameworks[i]) continue;
	    	var framework = makefile.Components.Frameworks[vFrameworks[i]];
	    	for(j=0;j<vFrameworksSrcSubPaths.length;j++)
	    	{
	        	var path = _this.replaceVars(framework.Path + vFrameworksSrcSubPaths[j]);
	        	if(folderExists(path))
	        	{
		    		trace("  + " + vFrameworks[i] + " -> " + path);
		        	var Files = _this.FindFiles(path, FileMasks, true);
			        for(var j=0;j<Files.length;j++)
			        {
			        	var file = Files[j];
			        	var fileName = file.substr(file.lastIndexOf("/")+1);
			     		copyFile(file, TARGET.TARGET_ROOT + "/obj/" + fileName);
			        }
	        	}
	    	}
	    }
	};

    // =====================================================================
    // Read compiled CocoScript code and create JavaScript payload.js
    // =====================================================================
	_this.create_payload_js = function()
	{
	    trace("\nCreating payload.js ...");

	    var file = TARGET.TARGET_ROOT + "/payload.js";
	    var BUFFER = ["if(!this['include']) this.include=function(f){};\n"];

	    // Collect scripts
	    var scripts = _this.FindFiles(TARGET.TARGET_ROOT + "/obj", "*.js;*.jobj", true);

	    // Order scripts
	    scripts = _this.calculateDependencies(scripts, true);

	    // === RELEASE MODE ===
	    if(makefile.Config.CONFIGURATION=="Release")
	    {
		    for(var i=0; i<scripts.length; i++)
		    {
		    	BUFFER.push(read(scripts[i]));
		    	_this.DeleteFile(scripts[i]);
		    }
			BUFFER = BUFFER.join("\n");
			BUFFER = BUFFER.replace(/\x22#(include|export)\s+[^\x22]+\x22;{0,1}/g, "");
			BUFFER = "/**\n * @fileoverview\n * @suppress {deprecated|globalThis|suspiciousCode|uselessCode}\n */\n\n" + BUFFER;
	    }
	    // === DEBUG MODE ===
	    else
	    {
		    for(var i=0; i<scripts.length; i++)
		    {
		    	var script = relativePath(TARGET.TARGET_ROOT,scripts[i]);
		    	BUFFER.push("include('" + script + "');");
		    }
		    BUFFER = BUFFER.join("\n");
	    }

	    // Get Coconut2D Runtime Bindings
	    BUFFER += "\n\n" + read(makefile.Vars.PATH_SDK_COMPILER + "/bindings.jspp");

	    _this.module(file, BUFFER, false);
		trace("+ created: " + file);
	};

    // =====================================================================
	_this.create_index_html = function()
	{
	    var HTML = [];

	    trace("\nGenerating Index.html ...");

        // Create Fonts List
	    HTML.push("<style>");
	    trace("+ Processing Fonts ...");
	    var fonts = _this.FindFiles(TARGET.TARGET_ASSETS, "*.ttf", true);
	    for(var i=0;i<fonts.length;i++)
	    {
	        var fontName = /[\w\-]+\.ttf/i.exec(fonts[i])+"";
	    	if(/([^\-]+)(?:\-(\w+))*/img.test(fontName))
	    	{
	    		trace("  > font: " + fontName);
	    		var match = /([^\-\.]+)(?:\-(\w+))*/img.exec(fontName);
	            HTML.push('\t@font-face {');
	            HTML.push('\t\tfont-family: "' + RegExp.$1 + '";');
	            HTML.push('\t\tsrc: url("' + relativePath(TARGET.TARGET_ROOT,fonts[i]) + '");');
	            switch(RegExp.$2.toLowerCase())
	            {
	            case "bold":
	                HTML.push("\t\tfont-weight: bold;");
	                break;

	            case "italic":
	                HTML.push("\t\tfont-style: italic;");
	                break;

	            case "oblique":
	                HTML.push("\t\tfont-style: oblique;");
	                break;

	            case "bolditalic":
	                HTML.push("\t\tfont-weight: bold;");
	                HTML.push("\t\tfont-style: italic;");
	                break;

	            case "boldoblique":
	                HTML.push("\t\tfont-weight: bold;");
	                HTML.push("\t\tfont-style: italic, oblique;");
	                break;
	            }
	            HTML.push("\t}");
	    	}
	    }
	    HTML.push("\t</style>\n");

	    // Add Scripts
	    var scripts = _this.FindFiles(TARGET.TARGET_ROOT, "*.js;*.jobj", true);
	    scripts = _this.calculateDependencies(scripts, true);
	    trace("+ Processing Scripts ...");
	    for(var i=0; i<scripts.length; i++)
	    {
	    	var script = relativePath(TARGET.TARGET_ROOT,scripts[i]);
	    	HTML.push("\t<script type='application/javascript' language='javascript' src='" + script + "' charset='utf-8'></script>");
	    }

       	// Get index.html template (copied from device wrapper)
	    var template = read(TARGET.TARGET_ROOT + "/index.html");
	    HTML = template.replace("$(SCRIPTS)", HTML.join("\n"));
	    _this.module(TARGET.TARGET_ROOT + "/index.html", HTML, false);

	    trace("+ created: " + TARGET.TARGET_ROOT + "/index.html");
	};

	// ==================================================================================================================================
	//	    __  __     __                   __  ___
	//	   / / / /__  / /___  ___  _____   /  |/  /___ _______________  _____
	//	  / /_/ / _ \/ / __ \/ _ \/ ___/  / /|_/ / __ `/ ___/ ___/ __ \/ ___/
	//	 / __  /  __/ / /_/ /  __/ /     / /  / / /_/ / /__/ /  / /_/ (__  )
	//	/_/ /_/\___/_/ .___/\___/_/     /_/  /_/\__,_/\___/_/   \____/____/
	//	            /_/
	// ==================================================================================================================================

  	// =====================================================================
    // Find source files from target and frameworks
    // =====================================================================
  	_this.collectSources = function(root, Sources, FileMasks, vFrameworksSrcSubPaths)
  	{
	    trace("\nCollecting Sources ...\n+ pattern: " + FileMasks);

	    var SourcePaths = {};

	    // Collect source paths from frameworks
	    trace("+ scanning frameworks ...");
	    var vFrameworks = makefile.Config.PROJECT_FRAMEWORKS;
	    if(TARGET.TARGET_ADDITIONAL_FRAMEWORKS) vFrameworks += (";"+TARGET.TARGET_ADDITIONAL_FRAMEWORKS)
	    vFrameworks = vFrameworks.split(";");
	    vFrameworksSrcSubPaths = vFrameworksSrcSubPaths.split(";");
	    for(var i=0; i<vFrameworks.length; i++)
	    {
	    	if(!vFrameworks[i]) continue;
	    	var framework = makefile.Components.Frameworks[vFrameworks[i]];
	    	for(j=0;j<vFrameworksSrcSubPaths.length;j++)
	    	{
	        	var path = _this.replaceVars(framework.Path + vFrameworksSrcSubPaths[j]);
	    		trace("  + " + vFrameworks[i] + " -> " + path);
	        	SourcePaths[path] = true;
	    	}
	    }

	    // Collect additional source paths
	    trace("+ scanning target paths ...");
	    var vSourcePaths = Sources.split(";");
	    for(var i=0; i<vSourcePaths.length; i++)
	    {
	        trace("  + from source path: " + vSourcePaths[i]);
	        SourcePaths[vSourcePaths[i]] = true;
	    }

	    // Create a list of include paths that will be used with the compiler
	    makefile.Vars.INCLUDE_PATHS = [ root ? relativePath(root, makefile.Vars.PATH_SDK_INCLUDES) : makefile.Vars.PATH_SDK_INCLUDES ];
	    for(var item in SourcePaths)
	    	makefile.Vars.INCLUDE_PATHS.push( root ? relativePath(root, item) : item);

	    // Collect modules from each path
	    var files = [];
	    _this.ModuleFiles = {};
	    for(var path in SourcePaths)
	    {
	        var Files = _this.FindFiles(path, FileMasks, true);
	        for(var i=0;i<Files.length;i++)
	        {
	        	var file = Files[i];
	        	if(ModuleFiles[file]) continue;
        		files.push(file);
				ModuleFiles[file] = path;
	        }
	    }

	    if(!files.length)
	    	throw new Error("No source files found");

	    trace("+ found: " + files.length + " files");
	    return files;
  	};

  	// =====================================================================
	// Extract C++ .cpp and .hpp files relative to a root folder
	// =====================================================================
  	_this.get_relative_cpp_hpp = function(files, root)
  	{
		var includes = root ? relativePath(root, makefile.Vars.PATH_SDK_INCLUDES) :  makefile.Vars.PATH_SDK_INCLUDES;
		var CPP = [];
		var HPP = [includes];
		var HPPmap = {};
		HPPmap[includes] = true;
		for(i=0;i<files.length;i++)
		{
			files[i] = root ? relativePath(root, files[i]) : files[i];
			if(/\.(cpp|m)$/i.test(files[i]))
			{
				if(files[i].indexOf("./")==0)
					files[i] = files[i].substr(2);
				CPP.push(files[i]);
			}
			if(/\.h[p]*?$/i.test(files[i]))
			{
				var path = files[i].substr(0, files[i].lastIndexOf("/"));
				if(!HPPmap[path])
				{
					HPPmap[path] = true;
					HPP.push(path);
				}
			}
		}
		HPP =  HPP.sort();//.reverse();
		CPP = CPP.sort();//.reverse();
		return { CPP:CPP, HPP:HPP };
  	};

  	// =====================================================================
	// Send a module to IDE
	// =====================================================================
	_this.module = function(fileName, buffer, substitute_variables)
	{
		if(substitute_variables)
		{
			trace("\nProcessing file: " + fileName);
			buffer = _this.replaceVars(buffer);
		}

		// Save module
		IDECallback("module", fileName, 0, 0, buffer);
	};

    // =====================================================================
    // Resolve $(xxx) vars in a buffer
    // =====================================================================
	_this.replaceVars = function(buffer, logReplacedVars, exceptions)
	{
		var unresolved = [];
		for(;;)
		{
			var rx = new RegExp("\\$\\(([\\w\\.]+)\\)", "g");
			match=rx.exec(buffer);
			if(!match) break;
			var name = match[1];
			var value = _this.getVar(name);
			if(!value)
			{
				unresolved.push(name);
				var r = new RegExp("\\$\\("+name+"\\)", "g");
				buffer = buffer.replace(r, "@@@"+name+"@@@");
			}
			else
			{
				var r = new RegExp("\\$\\("+name+"\\)", "g");
				buffer = buffer.replace(r, value);
				if(logReplacedVars)
					trace("  + variable: " + name + " = " + value);
			}
		}

		// Restore uresolved variables to buffer
		for(i=0;i<unresolved.length;i++)
		{
			var r = new RegExp("@@@"+unresolved[i]+"@@@", "g");
			buffer = buffer.replace(r, "$("+unresolved[i]+")");
			if(exceptions && exceptions.indexOf(unresolved[i])!=-1) continue;
			trace("  !WARNING: Variable not found: " + unresolved[i]);
		}

		return buffer;
	};

    // =====================================================================
    // Resolves a single var by name
    // =====================================================================
	_this.getVar = function(name)
	{
		try
		{
			if(makefile.Vars[name])
				return makefile.Vars[name];
			var path  = "makefile." + name;
			return eval(path);
		}
		catch(e)
		{
			return null;
		}
	};

    // =====================================================================
    // Convert file pattern to regular expression
    // =====================================================================
	_this.toRegExpPattern = function(filePattern)
	{
		var pattern = [];
		var terms = filePattern.split(";");
		for(var i=0; i<terms.length; i++)
		{
			if(i>0) pattern.push("|");
			pattern.push("(?:");
			for(var c=0; c<terms[i].length; c++)
			{
				switch(terms[i][c])
				{
				case "*":	pattern.push("(?:[^:./\\\\]*?)"); break;
				case "?":	pattern.push("(?:[^:./\\\\])"); break;
				case "$":	pattern.push("\\$"); break;
				case "(":	pattern.push("\\("); break;
				case ")":	pattern.push("\\)"); break;
				case "{":	pattern.push("\\{"); break;
				case "}":	pattern.push("\\}"); break;
				case "[":	pattern.push("\\["); break;
				case "]":	pattern.push("\\]"); break;
				case "+":	pattern.push("\\+"); break;
				case "!":	pattern.push("\\!"); break;
				case "^":	pattern.push("\\^"); break;
				case ".":	pattern.push("\\."); break;
				case "-":	pattern.push("\\-"); break;
				case "\\":  pattern.push("/"); break;
				case "/":   pattern.push("/"); break;
				default:
							pattern.push(terms[i][c]);
				}
			}
			pattern.push(")");
		}
		pattern = pattern.join("");
		pattern = "^(?:" + pattern + ")$";
		//trace("+ file pattern: " + filePattern + " -> " + pattern);
		//test here: https://www.debuggex.com/
		return pattern;
	};

    // =====================================================================
    // Replace code withing a bugger enclosed by an opening and closing tag
    // =====================================================================
	_this.replaceBuffer = function(openTag, closeTag, buffer, fragment)
	{
        var pattern = openTag + "[\\s\\r\\n]*(?:[.\\s\\r\\n\\w\\W\\S]*?)" + closeTag;
		var rx = new RegExp(pattern, "g");
		var match = rx.exec(buffer);
	    if(!match) return buffer;
	    buffer = buffer.replace(rx, openTag + "\n" + fragment + "\n" + closeTag)
	    return buffer;
	};

    // =====================================================================
    // Remove C style comments from a buffer
    // =====================================================================
	_this.removeComments = function(buff)
	{
     	var pattern, rx, match;

     	// Multi-line Comments
     	pattern = "/\\*([^*]|[\\r\\n]|(\\*+([^*/]|[\\r\\n])))*\\*+/";
 		rx = new RegExp(pattern, "mg");
	    buff = buff.replace(rx, "");

		// Replace Strings with empty Strings
     	pattern = "([\\x22'])(?:(?!\\1)[^\\\\n\\r]|\\.)*\\1";
 		rx = new RegExp(pattern, "g");
		while(match=rx.exec(buff))
		{
			buff = buff.replace(match[0], "\"\"");
		}

		// Single line Comments
     	pattern = "(//[^\\n\\r]*)";
 		rx = new RegExp(pattern, "g");
 		buff = buff.replace(rx, "");

	    return buff;
	};

    // =====================================================================
    // Scan a folder for files using a file mask
    // =====================================================================
	_this.FindFiles = function(path, mask, recursive)
	{
		if(mask=="") mask = "*.*";
		var files = findFiles(path, ".*?", recursive);
		var out=[];
		var pattern = _this.toRegExpPattern(mask);
		for(var i=0;i<files.length;i++)
		{
			var fileName = files[i].substr(files[i].lastIndexOf("/")+1);
			if((new RegExp(pattern, "i")).test(fileName))
				out.push(files[i]);
		}
		return out;
	};

    // =====================================================================
    // Scan a folder for folders using a file mask
    // =====================================================================
	_this.FindFolders = function(path, mask, recursive)
	{
		var out = [];
	  	var folders = folderItems(path, ".*", recursive);
	  	var pattern = _this.toRegExpPattern(mask);
  		for(var i=0;i<folders.length;i++)
  		{
  			if(folderExists(folders[i]))
  			{
  				var folderName = folders[i].substr(folders[i].lastIndexOf("/")+1);
  				if((new RegExp(pattern, "i")).test(folderName))
  					out.push(folders[i]);
  				out = out.concat(_this.FindFolders(folders[i], mask, recursive));
  			}
  		}
  		return out;
	};

    // =====================================================================
    // Delete a file physically and from the IDE
    // =====================================================================
	_this.DeleteFile = function(path)
	{
		deleteFile(path);
		IDECallback("delete", path);
	};

    // =====================================================================
    // Delete a folder physically and from the IDE
    // =====================================================================
	_this.DeleteFolder = function(path)
	{
		deleteFolder(path);
		IDECallback("delete", path);
	};

    // =====================================================================
    // Unix Path
    // =====================================================================
	_this.unixPath = function(path)
	{
		return _this.replaceVars(path).replace(/\x5c/g, '/');
	};

    // =====================================================================
    // Unix Path
    // =====================================================================
	_this.winPath = function(path)
	{
		return _this.replaceVars(path).replace(/\x2f/g, '\\');
	};

    // =====================================================================
    // Execute a shell command in the IDE
    // =====================================================================
	_this.shell = function(command, path, wait_process)
	{
		var json = JSON.stringify({command:command, path:path, wait_process:wait_process});
		trace(command);
		IDECallback("shell", command,0,0,json);
	}

	// ==================================================================================================================================
	//	   _____ __        __          __  ___           __    _               __  ____  _ __
	//	  / ___// /_____ _/ /____     /  |/  /___ ______/ /_  (_)___  ___     / / / / /_(_) /____
	//	  \__ \/ __/ __ `/ __/ _ \   / /|_/ / __ `/ ___/ __ \/ / __ \/ _ \   / / / / __/ / / ___/
	//	 ___/ / /_/ /_/ / /_/  __/  / /  / / /_/ / /__/ / / / / / / /  __/  / /_/ / /_/ / (__  )
	//	/____/\__/\__,_/\__/\___/  /_/  /_/\__,_/\___/_/ /_/_/_/ /_/\___/   \____/\__/_/_/____/
	//
	// ==================================================================================================================================

	_this.exportStateMachine = function()
	{
		var code = _this.getSourceCode();
		narcissus.__messages = true;
		narcissus.__cpp = false;
		var ast = narcissus.jsparse(code);
		var compiler = new Compiler(ast, false);
		compiler.compile();
		var stateMachine = compiler.exportGameStateMachine();
		trace(stateMachine);
	}

    // =====================================================================
	// Load Plugins
    // =====================================================================

	__make_plugin_emscripten(this);

    // =====================================================================
    // Make!
    // =====================================================================
    /*@@ make @@*/
    try
    {
		var builder = null;
		if(command)
		{
			builder = this[command];
		}
		else
		{
			builder = this["Build_" + makefile.Vars.TARGET];
		}

		if(!builder)
		{
			trnace("Build function not found for [" + makefile.Vars.TARGET + "] target");
			throw new Error("Build function not found for [" + makefile.Vars.TARGET + "] target");
		}

	    builder(params);
	    trace("\nDone.\n");
	}
	catch(e)
	{
		e.fileName = e.fileName || makefile.Vars.PATH_SDK_COMPILER + "/make.js";
		var rx = new RegExp("\\(\\<.*?\\>\\:(\\d+)\\:(\\d+)\\)", "i");
		rx.exec(e.stack+"");
		e.lineNumber = e.lineNumber || RegExp.$1;
		trace("@@" + e.stack);
		IDECallback("error", e.fileName, e.lineNumber, 0, e);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function Graph()
{
	var v = [];
	var m = null;
	var o = null;

	var _this = this;
	_this.errors = [];

	this.addV = function(n)
	{
		v.push(n);
	}

	this.addE = function(v1, v2)
	{
		if(!m)
		{
			o = new Array(v.length);
			m = new Array(v.length);
			for(var i=0;i<v.length;i++)
			{
				o[i] = -1;
				m[i] = new Array(v.length);
				for(var j=0;j<v.length;j++)
					m[i][j] = 0;
			}
		}
	    var s = v2i(v1);
    	var e = v2i(v2);
    	if(s!=-1 && e!=-1)
        	m[s][e] = 1;
	}

	var v2i = function(n)
	{
    	for(var i=0; i<v.length; i++)
        	if(v[i]==n)
            	return i;
    	return -1;
	}

	var ni = function()
	{
	    for(var i=0; i<v.length; i++)
	    {
	        var c = 0;
	        var t = 0;
	        for(var j=0; j<v.length; j++)
	        {
	            if(m[i][j]==0) c++;
	            if(m[i][j]==2) t++;
	        }
	        if(t==v.length)
	        {
	        	continue;
	        }
	        else if(c+t == v.length)
	        {
	            return i;
	        }
	    }
	    return -1;
	}

	var cy = function(i)
	{
    	var Dic = {};
    	cyi(i, Dic);
	}

	var cyi = function(i, Dic)
	{
    	if(!Dic) return;
    	if(Dic[v[i]])
    	{
    		var first = null;
			var last = null;
			var path = [];
    		for(last in Dic)
    		{
    			path.push(last);
    			if(!first) first = last;
    		}

    		path = path.reverse().concat(last);
			var msg = "Cyclic reference between [" + first + "] and [" + last + "]. References Cycle: " + path.join(" -> ");
			_this.errors.push( { file:last, cylce:path, error:msg } );
			IDECallback("warning", path.join(" -> "), 0, 0, msg);
        	return;
    	}
    	Dic[v[i]] = true;
    	for(var j=0; j<v.length; j++)
    	{
        	if(m[i][j]==1)
        	{
            	cyi(j, Dic);
            	if(!Dic) return;
        	}
    	}
	}

	this.sort = function()
	{
    	if(!v) return;
	    for(var i=0; i<v.length; i++)
	    {
	        var e = ni();
	        if(e == -1) cy(i);
	        if(e != -1)
	        {
		        o[i] = v[e];
		        for(var j=0; j<v.length; j++)
		        {
		            m[j][e] = 2;
		            m[e][j] = 2;
		        }
	        }
	    }
    	return o||[];
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function parse_jspp(code, className)
{
	try
	{
		// Parse source code
		narcissus.__messages = false;
		narcissus.__cpp = false;
		var ast = narcissus.jsparse(code);

		// Compile ast
		var compiler = new Compiler(ast);
		compiler.compile(true, className, false);
	}
	catch(e)
	{
		//trace("ERROR: " +e);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function ____JSONtoXML(json, rootNode)
{
	if(!rootNode) rootNode = "XML";

	var ____isArray 	= function(obj) {return (Object.prototype.toString.apply(obj) === '[object Array]');}
	var ____isObject	= function(obj) {return (Object.prototype.toString.apply(obj) === '[object Object]');}
	var ____isFunction	= function(obj) {return (Object.prototype.toString.apply(obj) === '[object Function]');}

	var obj = (typeof json == 'string') ? JSON.parse(json) : json;

	var xml = "<" + rootNode + ">" +
			  __JSONtoXML(obj) +
			  "</" + rootNode + ">";

	function __addItem(v,k)
	{
		var x = '';

		if(v==null)
			x= "<" + k + ">null</" + k + ">";
		else
		{
			switch(typeof v)
			{
				case 'object':
					x= "<" + k + ">" + __JSONtoXML(v) + "</" + k + ">";
					break;

				case 'string':
					x= "<" + k + "><![CDATA[" + v + "]]></" + k + ">";
					break;

				default:
					x= "<" + k + ">" + v + "</" + k + ">";
					break;
			}
		}

		return x;
	}

	function __JSONtoXML(obj)
	{
		var x = '';

		if(____isArray(obj))
		{
			for(var i=0;i<obj.length;i++)
			{
				var v = obj[i];
				var k = '_' + i;
				x+= __addItem(v,k);
			}
		}
		else
		{
			for(var k in obj)
			{
				var v = obj[k];
				if(!isNaN(k)) k = '_' + k;
				x+= __addItem(v,k);
			}
		}

		return x;
	}

	return xml;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function RxReplace(buff, patt, opts, repl, single_line)
{
	if(!buff)
	{
		return null;
	}
	var rx = new RegExp(patt, opts);
	if(single_line)
	{
		var arr;
		var out = buff;
		while(arr=rx.exec(buff))
		{
			if(arr[0].indexOf("//")==-1)
				out = out.replace(arr[0], arr[0].replace(/[\n\r\t\s]+/mg, " "));
		}
		return out;
	}
	else
	{
		return buff.replace(rx, repl);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function formatCPP(buff)
{
	if(!buff) return "";
	buff = RxReplace(buff, "[\s\t\n\r]+\\{[\s\t\n\r]+\\};", "mg", "{};");
	buff = RxReplace(buff, "Array\\s*\\<\\s*([\\w\\*]+)\\s*\\>\\s*", "mg", "Array<$1> ");
	buff = RxReplace(buff, "Dictionary \\< (\\w+) \\> ", "mg", "Dictionary<$1> ");
	buff = RxReplace(buff, "\\bFloat\\b", "mg", "float");
	buff = RxReplace(buff, "\\bInteger\\b", "mg", "int");
	buff = RxReplace(buff, "\\bBoolean\\b", "mg", "bool");
	buff = RxReplace(buff, "\\bTime\\b", "mg", "float");
	buff = RxReplace(buff, "\\bNumber\\b", "mg", "float");
	buff = RxReplace(buff, "\\bFunction\\b", "mg", "void");
	buff = RxReplace(buff, "\\bObject\\b", "mg", "void");
	buff = RxReplace(buff, "\\s*//<<(.*)>>//", "mg", "$1");
	buff = RxReplace(buff, "\\bMath::floor\\(", "mg", "floor(");
	buff = RxReplace(buff, "\\bMath::ceil\\(", "mg", "ceil(");
	buff = RxReplace(buff, "\\bMath::round\\(", "mg", "round(");
	buff = RxReplace(buff, "\\bMath::pow\\(", "mg", "pow(");
	buff = RxReplace(buff, "\\bMath::log\\(", "mg", "log(");
	buff = RxReplace(buff, "\\bMath::min\\(", "mg", "std::min(");
	buff = RxReplace(buff, "\\bMath::max\\(", "mg", "std::max(");
	buff = RxReplace(buff, "\\bMath::sin\\(", "mg", "sin(");
	buff = RxReplace(buff, "\\bMath::cos\\(", "mg", "cos(");
	buff = RxReplace(buff, "\\bMath::abs\\(", "mg", "abs(");
	buff = RxReplace(buff, "\\bMath::sqrt\\(", "mg", "sqrt(");
	buff = RxReplace(buff, "\\bMath::random\\(\\)", "mg", "((float)rand()/(float)RAND_MAX)");
	buff = RxReplace(buff, "\\btrace\\s*\\((.*)\\)\\s*;\\s*$", "mg", "trace(($1).c_str());");
	buff = RxReplace(buff, "([\\x22\\x27])\\x2e\\x2fassets\\x2f", "mg", "$1./");
	buff = RxReplace(buff, "_ENUM\\.(\\w+)", "mg", "_ENUM::$1");
	buff = RxReplace(buff, "__currentFrame\\->action\\.call\\(scene\\);", "mg", "(scene->*__currentFrame->action)();");
	return buff;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function fileName(f)
{
	 sources[i].substr(sources[i].lastIndexOf("/")+1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function hex(n)
{
	var s = n.toString(16).toUpperCase();
	if(s.length==1) s = "000" + s;
	else if(s.length==2) s = "00" + s;
	else if(s.length==3) s = "0" + s;
	return s;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function figlet(text)
{
	if(!__global.makefile) return "";

	try
	{
		if(!__global.__figlet)
		{
			include(makefile.Vars.PATH_3RD_PARTY_FIGLET + "/figlet.js");
			__global.__figlet = new Figlet();
			__global.__figlet.load(read(makefile.Vars.PATH_3RD_PARTY_FIGLET + "/slant.flf"));
		}

	    var v = __figlet.getText(text).split('\n');
	    for(var i = 0; i<v.length; i++)
	        v[i] = "//\t" + v[i];
	    v = v.join('\n');
	    v = "\n// ==================================================================================================================================\n" + v + "\n// ==================================================================================================================================\n\n"
	    return v;
	}
	catch(e)
	{
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
