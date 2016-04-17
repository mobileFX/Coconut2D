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
	var TARGET = makefile.Config.TARGETS[makefile.Vars['TARGET']];
	TARGET.NAME = makefile.Vars['TARGET'];
	__global.TARGET = TARGET;
	__global.TARGET_NAME = TARGET.NAME;
	makefile.Vars["UCONFIGURATION"] = makefile.Vars.CONFIGURATION.toUpperCase();
	makefile.Vars["DEBUGGABLE"] = makefile.Vars.CONFIGURATION.toLowerCase()=="debug" ? "true" : "false";

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
    // Build for node.js
    // =====================================================================
    /*@@ node.js @@*/
  	_this.Build_node_js = function(params)
  	{
  		if(params && params.mode=="generate")
  		{
	  		_this.generate_javascript(true);
  		}
  		else
  		{
	  		_this.apply_device_wrapper();
	  		_this.generate_icons();
	  		_this.generate_javascript(true);
	  		_this.copy_framework_libs();
	  		_this.npm();
	  		_this.closure();
  		}
  	};

    // =====================================================================
    // Build for CocoNode (node.js with Coconut2D Native Addin for Web Sites)
    // =====================================================================
    /*@@ CocoNode @@*/
  	_this.Build_CocoNode = function(params)
  	{
  		if(params && params.mode=="generate")
  		{
	  		_this.generate_javascript(true);
  		}
  		else
  		{
	  		_this.apply_device_wrapper();
	  		_this.generate_icons();
	  		_this.generate_javascript(true);
	  		_this.copy_framework_libs();
	  		_this.npm();
	  		_this.closure();

	  		// We need to switch target to ASP
	  		if(TARGET.ASP)
	  		{
	  			// Replace target vars
	  			for(var item in TARGET.ASP)
	  			{
	  				TARGET[item] = TARGET.ASP[item];
	  			}

	  			// Reset precompiler vars
				TARGET_NAME = TARGET.NAME;
				target = makefile.Vars.TARGET = TARGET.NAME;

				_this.set_framework_vars();

				// Compile for ASP
				_this.generate_javascript(false);
	  		}
  		}
  	};

    // =====================================================================
    // Build for CocoPlay
    // (Similar to Browsers with OpenGL and HTML5 native bindings)
    // =====================================================================
  	/*@@ CocoPlayer @@*/
  	_this.Build_CocoPlayer = function(params)
  	{
  		if(params && params.mode=="generate")
  		{
	  		_this.generate_javascript(true);
  		}
  		else
  		{
	  		_this.clean();
	  		_this.apply_device_wrapper();
	  		_this.generate_icons();
	  		_this.copy_assets();
	  		_this.generate_javascript(true);
	  		_this.copy_framework_libs();
	  		_this.create_payload_js();
	  		_this.closure();
  		}
  	};

  	_this.Build_CocoScript = _this.Build_CocoPlayer;

    // =====================================================================
    // Build for HTML5 Browsers
    // =====================================================================
    /*@@ HTML5 @@*/
  	_this.Build_HTML5 = function(params)
  	{
  		if(params && params.mode=="generate")
  		{
	  		_this.generate_javascript(true);
  		}
  		else
  		{
	  		_this.clean();
	  		_this.apply_device_wrapper();
	  		_this.generate_icons();
	  		_this.copy_assets();
	  		_this.generate_javascript(true);
	  		_this.copy_framework_libs();
	  		_this.create_payload_js();
	  		_this.closure();
	  		_this.create_index_html();
  		}
  	};

    // =====================================================================
    // Build for Android Devices
    // =====================================================================
    /*@@ Android @@*/
  	_this.Build_Android = function(params)
  	{
  		var JNI_FOLDER = TARGET.TARGET_JNI || TARGET.TARGET_ROOT + "/jni";

  		makefile.Vars["ANDROID_SDK_ESCAPED"] = makefile.Vars.PATH_3RD_PARTY_ANDROID_SDK.replace(/\x2f/mg, '\\\\');
  		makefile.Vars["PATH_SDK_LIBRARIES_ANDROID"] = relativePath(JNI_FOLDER, makefile.Vars.PATH_SDK_LIBRARIES+"/Android");

  		if(params && params.mode=="generate")
  		{
	  		_this.generate_cpp();
  		}
  		else if(params && params.mode=="compile")
  		{
	  		_this.compile_jni_static_lib();
	  		_this.compile_apk();
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
    /*@@ iOS @@*/
  	_this.Build_iOS = function(params)
  	{
  		if(params && params.mode=="generate")
  		{
	  		_this.generate_cpp();
  		}
  		else if(params && params.mode=="compile")
  		{
  			_this.compile_ipa();
  		}
  		else
  		{
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
  	/*@@ Win32 @@*/
  	_this.Build_Win32 = function(params)
  	{
  		if(params && params.mode=="generate")
  		{
	  		_this.generate_cpp();
  		}
  		else if(params && params.mode=="compile")
  		{
  			_this.compile_x86();
  		}
  		else
  		{
	  		_this.apply_device_wrapper();
	  		_this.generate_icons();
	  		_this.copy_assets();
	  		_this.generate_cpp();
	  		_this.compile_x86();
  		}
  	};

    // =====================================================================
    // Build for Win64
    // =====================================================================
  	/*@@ Win64 @@*/
  	_this.Build_Win64 = function(params)
  	{
  		if(params && params.mode=="generate")
  		{
	  		_this.generate_cpp();
  		}
  		else if(params && params.mode=="compile")
  		{
  			_this.compile_x64();
  		}
  		else
  		{
	  		_this.apply_device_wrapper();
	  		_this.generate_icons();
	  		_this.copy_assets();
	  		_this.generate_cpp();
	  		_this.compile_x64();
  		}
  	};

    // =====================================================================
    // Build for Linux
    // =====================================================================
  	/*@@ Linux @@*/
  	_this.Build_Linux = function(params)
  	{
  		if(params && params.mode=="generate")
  		{
	  		_this.generate_cpp();
  		}
  		else if(params && params.mode=="compile")
  		{
  			_this.compile_linux();
  		}
  		else
  		{
	  		_this.apply_device_wrapper();
	  		_this.generate_icons();
	  		_this.copy_assets();
	  		_this.generate_cpp();
	  		_this.compile_linux();
  		}
  	};

    // =====================================================================
    // Build for OSX
    // =====================================================================
  	/*@@ OSX @@*/
  	_this.Build_OSX = function(params)
  	{
  		if(params && params.mode=="generate")
  		{
	  		_this.generate_cpp();
  		}
  		else if(params && params.mode=="compile")
  		{
  			_this.compile_OSX();
  		}
  		else
  		{
	  		_this.apply_device_wrapper();
	  		_this.generate_icons();
	  		_this.copy_assets();
	  		_this.generate_cpp();
	  		_this.compile_OSX();
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
	_this.generate_javascript = function(exportSymbols)
	{
		// Get all source code (including externs)
		var code = _this.getSourceCode();
		if(!code) return;

		// Parse source code and generate AST
		trace("\nParsing JavaScript Class files ...");
		narcissus.__messages = true;
		narcissus.__cpp = false;
		var ast = narcissus.jsparse(code);
		trace("+ Abstract Syntax Tree (AST) is generated.");

		// Compile AST
		trace("\nCompiling JavaScript Classes to JavaScript ...");
		var compiler = new Compiler(ast);
		compiler.compile(exportSymbols,false);
		trace("+ Done.");
	};

    // =====================================================================
    // Compile JavaScript Classes to C++
    // =====================================================================
	_this.generate_cpp = function()
	{
		// Get all source code (including externs)
		var code = _this.getSourceCode();
		if(!code) return;

		// Collect all non-generated C++ classes from Frameworks
		trace("\nScanning for non-generated C++ classes in Frameworks ...");
		var native_classes = [];
		var native_vartypes_includes = {};
		var paths = [makefile.Config.PROJECT_PATHS.NATIVE_COMMON].concat(TARGET.TARGET_ADDITIONAL_NATIVE_SOURCES.split(";"));
		var frameworks = _this.TARGET_FRAMEWORKS().join(";");
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
				var fileName = _this.fileName(files[i]);
				if(fileName.toLowerCase()=="coconut2d.hpp") continue;

				native_vartypes_includes[fileName] = {};

				var buff = read(files[i]);
				buff = _this.removeComments(buff);
				var rx = /(?:\btemplate[^>]+>[\s\n\r\t]*?)?\b(enum class|class|struct)\s+([^\s\n\r\t\x7B\:]+)/g;
				while(match=rx.exec(buff))
				{
					var classDef  = match[0] + "";
					var className = match[2] + "";

					if(classDef.indexOf("template")!=-1) continue;
					if(classDef.indexOf("enum class")!=-1) continue;
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
		compiler.compile(false,true);

		// Get all generated C++ classes from the compiler
		var generated_classes = compiler.getNativeClassList();

		// Update class forward declarations in Coconut2d.hpp
		var buff = read(makefile.Vars.FILE_PATH_SDK_CRL_COCONUT2D_HPP);
		buff = _this.replaceBuffer("//# Generated Classes Begin #//", "//# Generated Classes End #//", buff, generated_classes);
		buff = _this.replaceBuffer("//# Native Classes Begin #//", "//# Native Classes End #//", buff, native_classes);
		_this.module(makefile.Vars.FILE_PATH_SDK_CRL_COCONUT2D_HPP, buff);

		trace("+ Done.");
	};

    // =====================================================================
    // Minimize JavaScript with Closure Compiler
    // =====================================================================
	_this.closure = function()
	{
		if(makefile.Config.CONFIGURATION.toLowerCase()=="release")
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

  		var JNI_FOLDER = TARGET.TARGET_JNI || TARGET.TARGET_ROOT + "/jni";

  		_this.DeleteFolder(TARGET.TARGET_OBJ);
  		_this.DeleteFolder(TARGET.TARGET_LIBS || TARGET.TARGET_ROOT+"/libs");

		// Collect all C++ sources
  		_this.collectSources(JNI_FOLDER,
							 [ makefile.Config.PROJECT_PATHS.NATIVE_COMMON, TARGET.TARGET_ADDITIONAL_NATIVE_SOURCES ].join(";"),
							 TARGET.TARGET_NATIVE_MASK,
							 "/$(PATH_SDK_FRAMEWORKS_NATIVE)/$(PATH_SDK_FRAMEWORKS_GEN);" +
							 "/$(PATH_SDK_FRAMEWORKS_NATIVE)/$(PATH_SDK_FRAMEWORKS_SRC)");

		// Patch main.cpp to load Fonts
		_this.loadFonts(JNI_FOLDER + "/src/main.cpp", TARGET.TARGET_ASSETS);

        // Create Android.mk
		var file = JNI_FOLDER + "/Android.mk";
		trace("\nCreating Android.mk makefile ...");
		trace("+ makefile: " + file);
        trace("+ replacing variables ...");
		var buff = makefile.Vars.SOURCES.CREATE_MAKEFILE(file, JNI_FOLDER, null, ["CLEAR_VARS", "TARGET_ARCH_ABI", "PREBUILT_STATIC_LIBRARY", "BUILD_SHARED_LIBRARY"]);
        _this.module(file, buff);

        // Create Application.mk
		var file = JNI_FOLDER + "/Application.mk";
		trace("\nCreating Application.mk makefile ...");
		trace("+ makefile: " + file);
        trace("+ replacing variables ...");
		var buff = read(file);
		buff = _this.replaceVars(buff, true);
        _this.module(file, buff);

        // Create a custom make_lib.bat (offers better control than relying on environment variables)
        var buff = [];
        var make_lib_cmd = JNI_FOLDER + "/make_lib.bat";
        buff.push('@echo off');
        buff.push('SET NDK_ROOT=' + _this.winPath(makefile.Vars.PATH_3RD_PARTY_ANDROID_NDK)+"\\");
		buff.push('SET ANDROID_SDK_ROOT=' + _this.winPath(makefile.Vars.PATH_3RD_PARTY_ANDROID_SDK));
		buff.push('SET ANDROID_HOME=' + _this.winPath(makefile.Vars.PATH_3RD_PARTY_ANDROID_SDK) + '/platform-tools');
		buff.push('SET ANDROID_NDK_HOME=' + _this.winPath(makefile.Vars.PATH_3RD_PARTY_ANDROID_NDK));
		buff.push('SET NDK_BUILD_CMD=' + _this.winPath(makefile.Vars.PATH_3RD_PARTY_ANDROID_NDK) + '/ndk-build');
		buff.push('SET NDK_PROJECT_PATH=$(TARGET_ROOT)');
        buff.push('call "%NDK_ROOT%find-win-host.cmd" NDK_WIN_HOST');
        buff.push('if ERRORLEVEL 1 (exit /b 1)');
        buff.push('SET NDK_MAKE=%NDK_ROOT%prebuilt/%NDK_WIN_HOST%/bin/make.exe');
		buff.push('"%NDK_MAKE%" -f "%NDK_ROOT%build/core/build-local.mk" SHELL=cmd clean');

		var params = [];
		params.push('NDK_LOG=true');
		params.push('SHELL=cmd');
		params.push('APP_PLATFORM="' + 			(TARGET.APP_SETTINGS.ANDROID_PLATFORM||'android-10')+'"');
		params.push('NDK_TOOLCHAIN_VERSION="' +	(TARGET.APP_SETTINGS.NDK_TOOLCHAIN_VERSION||'4.9')+'"');
		params.push('APP_ABI="' + 				(TARGET.APP_SETTINGS.APP_ABI||'armeabi armeabi-v7a x86')+'"');

		// Release or Debug compilation
		if(makefile.Config.CONFIGURATION.toLowerCase()=="release")
		{
			params.push('APP_OPTIM=release');
			params.push('APP_CFLAGS=-O3');
		}
		else
		{
			params.push('APP_OPTIM=debug');
			params.push('NDK_DEBUG=1');
			params.push('APP_CFLAGS="-O0 -g -ggdb3 -DNDEBUG"');
		}

		buff.push('"%NDK_MAKE%" -f "%NDK_ROOT%build/core/build-local.mk" ' + params.join(" ") + ' -j %*');
		buff = _this.replaceVars(buff.join("\n"));
        _this.module(make_lib_cmd, buff);

        // Build the static libraries for arm and x86
        trace("\nCalling make ...");
        _this.shell(make_lib_cmd, JNI_FOLDER, "cc1plus.exe|arm-linux-androideabi-g++.exe|i686-linux-android-g++.exe");
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
  		buff.push('@echo off');
  		buff.push(_this.winPath('SET ANT_HOME=' + makefile.Vars.PATH_3RD_PARTY_ANT));
  		buff.push(_this.winPath('SET JAVA_HOME=' + makefile.Vars.PATH_3RD_PARTY_JAVA));
  		buff.push(_this.winPath('SET ANDROID_SDK_HOME=' + makefile.Vars.PATH_3RD_PARTY_ANDROID_SDK+"\\"));
  		buff.push(_this.winPath('SET PATH=%ANT_HOME%;%ANT_HOME%/bin;%JAVA_HOME%;%JAVA_HOME%/bin;%PATH%'));

  		var configuration = makefile.Config.CONFIGURATION.toLowerCase();
  		var keystore = TARGET.TARGET_ROOT + "/" + configuration + ".keystore";

  		// Create debug/release keystores
  		if(!fileExists(keystore))
  		{
  			var cmd = '"%JAVA_HOME%/bin/keytool.exe" -genkeypair -validity 10000 -dname "CN=$COMPANY_NAME,O=$ORGANIZATION_NAME,C=$COUNTRY" -keystore "$FILENAME" -storepass $PASSWORD -keypass $PASSWORD -alias "$ALIAS" -keyalg RSA';
			cmd = cmd.replace(/\$COMPANY_NAME/g, TARGET.CODE_SIGNING.COMPANY)
			cmd = cmd.replace(/\$ORGANIZATION_NAME/g, TARGET.CODE_SIGNING.ORGANIZATION)
			cmd = cmd.replace(/\$COUNTRY/g, TARGET.CODE_SIGNING.COUNTRY)
			cmd = cmd.replace(/\$PASSWORD/g, TARGET.CODE_SIGNING.PASSWORD)
			cmd = cmd.replace(/\$FILENAME/g, keystore)
			cmd = cmd.replace(/\$ALIAS/g, makefile.Vars.PROJECT_PACKAGE + "." + configuration)
			buff.push(cmd);
  		}

  		// Compile
  		buff.push(_this.winPath('"%ANT_HOME%/bin/ant" -S ' + configuration));

  		// Save build file
  		var make_cmd = TARGET.TARGET_ROOT + "/make.bat";
		buff = _this.replaceVars(buff.join("\n"));
        _this.module(make_cmd, buff);
        _this.shell(make_cmd, TARGET.TARGET_ROOT);
        //_this.DeleteFile(make_cmd);

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
        	_this.DeleteFolder(TARGET.TARGET_ROOT+"/assets");
        	copyFile(root_apk, final_apk);
        	deleteFile(root_apk);
        	copyFile(TARGET.TARGET_ROOT +"/debugger-config.gdb", TARGET.TARGET_ROOT+"/libs/armeabi-v7a/gdb.setup");
        }
  	};

    // =====================================================================
    // Compile iOS Application
    // =====================================================================
  	_this.compile_ipa = function()
  	{
  		trace("\nCompiling iOS Application ...");

		// Collect all C++ sources
  		_this.collectSources(  TARGET.TARGET_ROOT,
							   [ makefile.Config.PROJECT_PATHS.NATIVE_COMMON, TARGET.TARGET_ADDITIONAL_NATIVE_SOURCES ].join(";"),
							   TARGET.TARGET_NATIVE_MASK,
							   "/$(PATH_SDK_FRAMEWORKS_NATIVE)/$(PATH_SDK_FRAMEWORKS_GEN);" +
							   "/$(PATH_SDK_FRAMEWORKS_NATIVE)/$(PATH_SDK_FRAMEWORKS_SRC)");

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
			files[i] = _this.fileName(files[i]);
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
		var buff = makefile.Vars.SOURCES.CREATE_MAKEFILE(file, TARGET.TARGET_ROOT);
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

        // Build
        trace("\nCalling iOS make ...");
        _this.shell(make_cmd, TARGET.TARGET_ROOT);
        _this.DeleteFile(make_cmd);
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
  		_this.collectSources(  TARGET.TARGET_ROOT,
							   [ makefile.Config.PROJECT_PATHS.NATIVE_COMMON, TARGET.TARGET_ADDITIONAL_NATIVE_SOURCES ].join(";"),
							   TARGET.TARGET_NATIVE_MASK,
							   "/$(PATH_SDK_FRAMEWORKS_NATIVE)/$(PATH_SDK_FRAMEWORKS_GEN);" +
							   "/$(PATH_SDK_FRAMEWORKS_NATIVE)/$(PATH_SDK_FRAMEWORKS_SRC)");


		// Collect resources
		trace("\n Collecting Resources ...");
		var files = _this.FindFiles(TARGET.TARGET_ROOT, TARGET.TARGET_RESOURCES_MASK, false);
		for(i=0;i<files.length;i++) { files[i] = relativePath(TARGET.TARGET_ROOT, files[i]); }
		files.push("./assets");
		makefile.Vars["NATIVE_RESOURCES"] = files.join(" \\\n");
		trace("+ Done.");

		// Patch main.cpp to load Fonts
		_this.loadFonts(TARGET.TARGET_ROOT + "/src/main.cpp", TARGET.TARGET_ASSETS);

		// Release or Debug compilation
		var CFLAGS = [];
		if(makefile.Config.CONFIGURATION.toLowerCase()=="release")
		{
			CFLAGS.push('-O3');
		}
		else
		{
			CFLAGS.push('-O0 -g -ggdb3');// -gdwarf-2 -gstrict-dwarf
		}

        // Create Makefile
		var file = TARGET.TARGET_ROOT+"/Makefile.mk";
		trace("\nCreating Windows x86 makefile ...");
		trace("+ makefile: " + file);
        trace("+ replacing variables ...");
		var buff = makefile.Vars.SOURCES.CREATE_MAKEFILE(file, TARGET.TARGET_ROOT, CFLAGS.join(" "));
        _this.module(file, buff);

        // Create a custom make_x86.bat
        var buff = [];
        var make_cmd = TARGET.TARGET_ROOT + "/make_x86.bat";
        buff.push('@echo off');
        buff.push('SET SHELL=cmd.exe');
        buff.push('SET LANG=en_US.UTF-8');
        buff.push('SET LANGUAGE=en_US.UTF-8');
        buff.push('SET LC_ALL=en_US.UTF-8');
        buff.push('SET PROJECT_PATH=$(TARGET_ROOT)');
		buff.push('SET MAKEFILE=%PROJECT_PATH%/Makefile.mk');
		buff.push('SET MINGW=$(PATH_3RD_PARTY_MINGW)');
		buff.push('SET PATH=%MINGW%;%MINGW%/bin;');
		buff.push('"%MINGW%/bin/mingw32-make" --directory="%PROJECT_PATH%" --jobs --makefile="%MAKEFILE%"');
		buff = _this.replaceVars(_this.winPath(buff.join("\n")));
        _this.module(make_cmd, buff);

        // Build the static libraries for arm and x86
        trace("\nCalling Windows x86 make ...");
        _this.shell(make_cmd, TARGET.TARGET_ROOT, "g++.exe");
        //_this.DeleteFile(make_cmd);

        // Sanity check
        if(!fileExists(TARGET.TARGET_OUTPUT))
       		throw new Error("ERROR: Failed to compile Windows x86 Application");
  	};

// ==================================================================================================================================
//	    ______                      __     ______              _____
//	   / ____/  ______  ____  _____/ /_   / ____/__    __     / ___/____  __  _______________  _____
//	  / __/ | |/_/ __ \/ __ \/ ___/ __/  / /  __/ /___/ /_    \__ \/ __ \/ / / / ___/ ___/ _ \/ ___/
//	 / /____>  </ /_/ / /_/ / /  / /_   / /__/_  __/_  __/   ___/ / /_/ / /_/ / /  / /__/  __(__  )
//	/_____/_/|_/ .___/\____/_/   \__/   \____//_/   /_/     /____/\____/\__,_/_/   \___/\___/____/
//	          /_/
// ==================================================================================================================================

  	_this.EXPORT_CPP = function(template_folder, destination_folder)
  	{
     	// ==========================================================================================================
     	// First lets take care of the files, copy template files, replace in-file variables, generate icons, etc.
     	// ==========================================================================================================

     	if(!folderExists(template_folder))
     	{
     		trace("ERROR: Template folder " + template_folder + " not found");
     		return;
     	}

		// Purge previous XCode project and recreate the folders
		deleteFolder(destination_folder);
		buildPath(destination_folder);
		copyFolder(template_folder, destination_folder);

		// Copy the Assets
		_this.copy_assets(null, destination_folder + "/assets");

		// Generate C++ files
  		_this.generate_cpp();

        // Update modules (text files)
        var files = _this.FindFiles(TARGET.TARGET_ROOT, makefile.Vars.TEXT_FILES, true);
		for(var i=0; i<files.length; i++)
		{
			var buff = read(files[i]);
			_this.module(files[i], buff);
		}

		// Collect all C++ sources
  		_this.collectSources(  destination_folder,
							   makefile.Config.PROJECT_PATHS.NATIVE_COMMON + ";" +
							   makefile.Vars.PATH_SDK_COMMON + ";" +
							   TARGET.DEVICE_WRAPPER.PATH + "/src",
							   TARGET.TARGET_NATIVE_MASK,
							   "/$(PATH_SDK_FRAMEWORKS_NATIVE)/$(PATH_SDK_FRAMEWORKS_GEN);" +
							   "/$(PATH_SDK_FRAMEWORKS_NATIVE)/$(PATH_SDK_FRAMEWORKS_SRC)");

  		buildPath(destination_folder + "/lib/bin");
  		buildPath(destination_folder + "/lib/include");

  		// Copy libraries
  		for(var i=0; i<makefile.Vars.SOURCES.LIB_BIN_PATHS.length; i++)
  		{
  			copyFolder(makefile.Vars.SOURCES.LIB_BIN_PATHS[i], destination_folder + "/lib/bin");
  		}

 		// Copy C++ files to /src
		for(var file in makefile.Vars.SOURCES.SourceFiles)
		{
			var File = makefile.Vars.SOURCES.SourceFiles[file];

			if(File.Framework)
			{
				File.dst_file = destination_folder + "/src/.SDK/" + File.Framework.id + File.Rel;
			}
			else if(File.Library)
			{
				File.dst_file = destination_folder + "/lib/include" + File.Rel;
			}
			else if(File.Root==makefile.Config.PROJECT_PATHS.NATIVE_COMMON)
			{
				File.dst_file = destination_folder + "/src" + File.Rel;
			}
			else if(File.Root==makefile.Vars.PATH_SDK_COMMON, file)
			{
				File.dst_file = destination_folder + "/src/.SDK/.device" + File.Rel;
			}
			else
			{
				File.dst_file = destination_folder + "/src" + File.Rel;
			}

			File.dst_path = File.dst_file.substr(0, File.dst_file.lastIndexOf("/"));
			File.rel_path = relativePath(destination_folder, File.dst_file).substr(2);
			File.rel_parent = File.rel_path.substr(0, File.rel_path.lastIndexOf("/"));
			File.ext = File.FileName.substr(File.FileName.indexOf(".")).toLowerCase();

			buildPath(File.dst_path);

			var buff = read(file);
			_this.module("UNIX:" + File.dst_file, buff);
		}

		// Process Template Files
		var templateFilesMask = TARGET.DEVICE_WRAPPER.TEMPLATES;
		var excludeVars = TARGET.DEVICE_WRAPPER.TEMPLATE_EXCLUDE_VARS ? TARGET.DEVICE_WRAPPER.TEMPLATE_EXCLUDE_VARS.split(";") : ["APP_ICONS", "SCRIPTS"];
        if(templateFilesMask)
        {
  			var files = _this.FindFiles(destination_folder, templateFilesMask, true);
  			for(var i=0; i<files.length; i++)
  			{
				var buff = read(files[i]);
				buff = _this.replaceVars(buff, true, excludeVars);
				write(files[i], buff);
  			}
        }
  	};

	// ==================================================================================================================================
	//	    ______                      __     __  _________    ________
	//	   / ____/  ______  ____  _____/ /_   /  |/  / ___/ |  / / ____/
	//	  / __/ | |/_/ __ \/ __ \/ ___/ __/  / /|_/ /\__ \| | / / /
	//	 / /____>  </ /_/ / /_/ / /  / /_   / /  / /___/ /| |/ / /___
	//	/_____/_/|_/ .___/\____/_/   \__/  /_/  /_//____/ |___/\____/
	//	          /_/
	// ==================================================================================================================================
  	/*@@ [MSVC 2013] @@*/
  	_this.EXPORT_VISUAL_STUDIO_PROJECT = function(params)
  	{
		if(makefile.Vars.TARGET!="Win32" && makefile.Vars.TARGET!="Win64")
		{
			throw "Please set target to Win32 or Win64";
			return;
		}

        var FILE_REFS =
        {
        	FILTERS:{},
        	VCXPROJ_Files:[],
        	VCXPROJ_Filters:[],
        	VCXPROJ_FilterFiles:[],
        	IncludePaths: []
        };

		// Get the template and destination folders
		var template_folder = makefile.Vars.PATH_SDK_TEMPLATE_MSVC2010;
		var destination_folder = makefile.Config.PROJECT_PATHS.TARGETS + "/MSVC";

		// Export C++ sourcers and libraries
		_this.EXPORT_CPP(template_folder, destination_folder);

		// Generate Icons
		var icons_folder = destination_folder;
		_this.generate_icons(icons_folder);

		// Collect icons
		var files = _this.FindFiles(icons_folder, "*.png", false);
		makefile.Vars["APP_ICONS"] = files.join("\n");

		// Collect resources
		trace("\n Collecting Resources ...");
		var files = _this.FindFiles(destination_folder, TARGET.TARGET_RESOURCES_MASK, false);
		for(i=0;i<files.length;i++) { files[i] = relativePath(destination_folder, files[i]); }
		files.push("./" + makefile.Config.PROJECT_PATHS.APP_ASSETS);
		makefile.Vars["NATIVE_RESOURCES"] = files.join(" \\\n");
		trace("+ Done.");

		// Patch main.cpp to load Fonts
		_this.loadFonts(destination_folder + "/src/.SDK/.device/main.cpp", makefile.Config.PROJECT_PATHS.APP_ASSETS);

     	// ==========================================================================================================
     	// Now we process the files and generate the XCode project file
     	// ==========================================================================================================

		for(var key in makefile.Vars.SOURCES.SourceFiles)
		{
			// Get file descriptor
			var File = makefile.Vars.SOURCES.SourceFiles[key];

			// Record include path
			if(FILE_REFS.IncludePaths.indexOf(File.rel_parent)==-1)
			{
				 FILE_REFS.IncludePaths.push("$(ProjectDir)/"+File.rel_parent);
			}

			// ==============================================
			// Record filters by splitting a file path
			// Each folder in a file path becomes a filter
			// ==============================================

			var FILTER = null;		// The inner-most filter of where this file resides
			var iFILTER = null;		// Filter iterator during processing file path
			var cFILTER = null;		// Filter carry to make available child filter to its parent

			// Split file's path
			var vFilePath = File.rel_parent.split("/");
			var FilterKey = File.rel_parent;

			// Start from inner to outer sub folder and create filters
			for(var i=vFilePath.length-1; i>=0; i--)
			{
				// Get grpup if it exists
				iFILTER = FILE_REFS.FILTERS[FilterKey];

				// Create new filter if it does not exist
				if(!iFILTER)
				{
					iFILTER = FILE_REFS.FILTERS[FilterKey] =
					{
						name	: vFilePath[i],
						path	: vFilePath.slice(0, i+1).join("\\"),
						ID		: GUID(),
						FILES	: {},
						FILTERS	: {}
					};

					FILE_REFS.VCXPROJ_Filters.push("\t\t<Filter Include=\"" + iFILTER.path + "\">\n\t\t\t<UniqueIdentifier>" + iFILTER.ID.toLowerCase() + "</UniqueIdentifier>\n\t\t</Filter>");
				}

				// Store the inner-most filter for use outside this loop
				if(!FILTER) FILTER = iFILTER;

				// If we are carrying a child filter, add it to this filter's items
				if(cFILTER) iFILTER.FILTERS[cFILTER.ID] = cFILTER;

				// Store current filter, we will need it in next loop iteration
				cFILTER = iFILTER;

				// Remove inner-filter from filter key and proceed to next filter
				FilterKey = FilterKey.substr(0, FilterKey.lastIndexOf("/"));
			}

			// ==============================================
			// Record the file
			// ==============================================
			var FILE =
			{
				name	: File.FileName,
				path	: File.rel_path,
				ID		: GUID(),
				REF		: GUID()
			};

			// Add file to filter
			FILTER.FILES[ FILE.ID ] = FILE;

			// Generate additional XCode sections
			switch(File.ext)
			{
			case ".c":
				FILE_REFS.VCXPROJ_Files.push("\t<ClCompile Include=\"" + File.rel_path + "\" />");
				FILE_REFS.VCXPROJ_FilterFiles.push("\t<ItemGroup><ClCompile Include=\"" + FILE.path + "\"><Filter>" + FILTER.path + "</Filter></ClCompile></ItemGroup>");
				buff = read(File.dst_file);
				_this.module("UNIX:" + File.dst_file, buff);
				break;

			case ".cpp":
				FILE_REFS.VCXPROJ_Files.push("\t<ClCompile Include=\"" + File.rel_path + "\" />");
				FILE_REFS.VCXPROJ_FilterFiles.push("\t<ItemGroup><ClCompile Include=\"" + FILE.path + "\"><Filter>" + FILTER.path + "</Filter></ClCompile></ItemGroup>");
				buff = read(File.dst_file);
				buff = "#include \"StdAfx.h\"\n\n" + buff;
				_this.module("UNIX:" + File.dst_file, buff);
				break;

			case ".h":
			case ".hpp":
				FILE_REFS.VCXPROJ_Files.push("\t<ClInclude Include=\"" + File.rel_path + "\" />");
				FILE_REFS.VCXPROJ_FilterFiles.push("\t<ItemGroup><ClInclude Include=\"" + FILE.path + "\"><Filter>" + FILTER.path + "</Filter></ClInclude></ItemGroup>");
				buff = read(File.dst_file);
				_this.module("UNIX:" + File.dst_file, buff);
				break;
			}
		}

        // Create "CocoProject.vcxproj"
        var project_file = destination_folder + "/CocoProject.vcxproj";
        var buff = read(project_file);
		buff = buff.replace("$(ClInclude)", FILE_REFS.VCXPROJ_Files.join("\n"));
		buff = buff.replace(/\$\(SourcePath\)/g, FILE_REFS.IncludePaths.join(";") + ";$(SourcePath)");
		buff = buff.replace(/\$\(IncludePath\)/g, FILE_REFS.IncludePaths.join(";") + ";$(IncludePath)");
		write(project_file, buff);

        // Create "CocoProject.vcxproj.filters"
        var filters_file = destination_folder + "/CocoProject.vcxproj.filters";
        var buff = read(filters_file);
		buff = buff.replace("$(FILTERS)", FILE_REFS.VCXPROJ_Filters.join("\n"));
		buff = buff.replace("$(FILTER_ITEMS)", FILE_REFS.VCXPROJ_FilterFiles.join("\n"));
		write(filters_file, buff);

		trace("Microsoft Visual Studio Project created in " + destination_folder);
  	}

	// ==================================================================================================================================
	//	    ______                      __     _  ________          __
	//	   / ____/  ______  ____  _____/ /_   | |/ / ____/___  ____/ /__
	//	  / __/ | |/_/ __ \/ __ \/ ___/ __/   |   / /   / __ \/ __  / _ \
	//	 / /____>  </ /_/ / /_/ / /  / /_    /   / /___/ /_/ / /_/ /  __/
	//	/_____/_/|_/ .___/\____/_/   \__/   /_/|_\____/\____/\__,_/\___/
	//	          /_/
	// ==================================================================================================================================
	/*@@ [XCode 7] @@*/
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
        	lib_REF: "",
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
		var destination_folder = makefile.Config.PROJECT_PATHS.TARGETS + "/XCode";

		// Export C++ sourcers and libraries
		_this.EXPORT_CPP(template_folder, destination_folder);

		// Set assets folder
		makefile.Vars["NATIVE_RESOURCES"] = "./assets \\\n./Images.xcassets";

		// Patch main.m to load Fonts
		_this.loadFonts(destination_folder + "/src/.SDK/.device/main.m", makefile.Config.PROJECT_PATHS.APP_ASSETS);

		// Generate Icons
		var icons_folder = destination_folder + "/Images.xcassets/AppIcon.appiconset";
		_this.generate_icons(icons_folder);

		// Generate Splash Screens
		var splash_folder = destination_folder + "/Images.xcassets/Brand Assets.launchimage";
		_this.generate_splashes(splash_folder);

		// Collect icons
		var files = _this.FindFiles(icons_folder, "*.png", false);
		for(i=0;i<files.length;i++)
		{
			files[i] = _this.fileName(files[i]);
			files[i] = "\t\t<string>" + files[i] + "</string>";
		}
		makefile.Vars["APP_ICONS"] = files.join("\n");

		// Create Info.plist
		var file = TARGET.DEVICE_WRAPPER.PATH + "/Info.plist";
		var buff = read(file);
		buff = _this.replaceVars(buff, true);
        write(destination_folder + "/Info.plist", buff);

     	// ==========================================================================================================
     	// Now we process the files and generate the XCode project file
     	// ==========================================================================================================

		// Get the src files, we will work on them...
		var sources_length = makefile.Vars.SOURCES.FILES.length;

		var file_index = 0;
		var group_index = (2* sources_length);

		for(var key in makefile.Vars.SOURCES.SourceFiles)
		{
			// Get file descriptor
			var File = makefile.Vars.SOURCES.SourceFiles[key];

			// ==============================================
			// Record groups by splitting a file path
			// Each folder in a file path becomes a group
			// ==============================================

			var GROUP = null;		// The inner-most group of where this file resides
			var iGROUP = null;		// Group iterator during processing file path
			var cGROUP = null;		// Group carry to make available child group to its parent

			// Split file's path
			var vFilePath = File.rel_parent.split("/");
			var GroupKey = File.rel_parent;

			// Start from inner to outer sub folder and create groups
			for(var i=vFilePath.length-1; i>=0; i--)
			{
				// Get grpup if it exists
				iGROUP = FILE_REFS.GROUPS[GroupKey];

				// Create new group if it does not exist
				if(!iGROUP)
				{
					iGROUP = FILE_REFS.GROUPS[GroupKey] =
					{
						name	: vFilePath[i],
						ID		: SIG_SRC + hex(++group_index) + SIG_END,
						FILES	: {},
						GROUPS	: {}
					};
				}

				// If found either 'src' or 'lib' groups, keep their referece
				if(iGROUP.name=="src") FILE_REFS.src_REF = iGROUP.ID;
				if(iGROUP.name=="lib") FILE_REFS.lib_REF = iGROUP.ID;

				// Store the inner-most group for use outside this loop
				if(!GROUP) GROUP = iGROUP;

				// If we are carrying a child group, add it to this group's items
				if(cGROUP) iGROUP.GROUPS[cGROUP.ID] = cGROUP;

				// Store current group, we will need it in next loop iteration
				cGROUP = iGROUP;

				// Remove inner-group from group key and proceed to next group
				GroupKey = GroupKey.substr(0, GroupKey.lastIndexOf("/"));
			}

			// ==============================================
			// Record the file
			// ==============================================
			var FILE =
			{
				name	: File.FileName,
				path	: File.rel_path,
				source	: null,
				ID		: SIG_SRC + hex(++file_index) + SIG_END,
				REF		: SIG_SRC + hex(sources_length + file_index) + SIG_END
			};

			// Add file to group
			GROUP.FILES[ FILE.ID ] = FILE;

			// Generate additional XCode sections
			switch(File.ext)
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

				// For header files we need to select the appropriate C/C++ compiler by checking if a .m / .c / .cpp file exists
				if(makefile.Vars.SOURCES.SourceFiles[FILE.name.replace(".h", ".m")])
					FILE.source = "sourcecode.c.h";

				else if(makefile.Vars.SOURCES.SourceFiles[FILE.name.replace(".h", ".c")])
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
			// Get a group
			var GROUP = FILE_REFS.GROUPS[group];

			// Sort files and sub-groups
			var files = _this.dicSort(GROUP.FILES, "name");
			var groups = _this.dicSort(GROUP.GROUPS, "name");

			// Generate group items lists (sorted by folders and files)
			var list = [];
			for(var i=0; i<groups.length; i++)
			{
				var ITEM = groups[i];
				list.push("\t\t\t\t" + ITEM.ID + " /* " + ITEM.name + " */");
			}
			for(var i=0; i<files.length; i++)
			{
				var ITEM = files[i];
				list.push("\t\t\t\t" + ITEM.ID + " /* " + ITEM.name + " */");
			}

			FILE_REFS.PBXGroups.push("\t\t" + GROUP.ID + " /* " + GROUP.name + " */ = {\n\t\t\tisa = PBXGroup;\n\t\t\tchildren = (\n" + list.join(",\n") + "\n\t\t\t);\n\t\t\tname = " + GROUP.name + ";\n\t\t\tsourceTree = \"<group>\";\n\t\t};");
		}

        // Create project.pbxproj
        var project_root = destination_folder + "/" + makefile.Vars.PROJECT_NAME + ".xcodeproj";
        var project_file = project_root + "/project.pbxproj";
        var project_template = destination_folder + "/project.pbxproj";

        var pbxproj = read(project_template);
		pbxproj = pbxproj.replace("$(FILE_REFS.src_REF)", FILE_REFS.src_REF);
		pbxproj = pbxproj.replace("$(FILE_REFS.lib_REF)", FILE_REFS.lib_REF);
		pbxproj = pbxproj.replace("$(PBXBuildFile)", FILE_REFS.PBXBuildFile.join("\n"));
		pbxproj = pbxproj.replace("$(PBXFileReference)", FILE_REFS.PBXFileReference.join("\n"));
		pbxproj = pbxproj.replace("$(PBXGroups)", FILE_REFS.PBXGroups.join("\n"));
		pbxproj = pbxproj.replace("$(PBXLibraries)", FILE_REFS.PBXLibraries.join("\n"));
		pbxproj = pbxproj.replace("$(PBXFrameworksBuildPhase)", FILE_REFS.PBXFrameworksBuildPhase.join("\n"));
		pbxproj = pbxproj.replace("$(PBXSourcesBuildPhase)", FILE_REFS.PBXSourcesBuildPhase.join("\n"));
		pbxproj = pbxproj.replace(/\$\(PROJECT_NAME\)/g, makefile.Vars.PROJECT_NAME);

		buildPath(project_root);
		write(project_file, pbxproj);
		deleteFile(project_template);

		trace("XCode Project created in " + destination_folder);
	};

	// ==================================================================================================================================
	//	    ____                           __     ______     __
	//	   /  _/___ ___  ____  ____  _____/ /_   / ____/  __/ /____  _________  _____
	//	   / // __ `__ \/ __ \/ __ \/ ___/ __/  / __/ | |/_/ __/ _ \/ ___/ __ \/ ___/
	//	 _/ // / / / / / /_/ / /_/ / /  / /_   / /____>  </ /_/  __/ /  / / / (__  )
	//	/___/_/ /_/ /_/ .___/\____/_/   \__/  /_____/_/|_|\__/\___/_/  /_/ /_/____/
	//	             /_/
	// ==================================================================================================================================

	_this.IMPORT_EXTERNS = function(params)
	{
		var externs = new ExternsParserPlugin(this);
		externs.import(params);
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
	_this.copy_assets = function(optSource, optDestination, contentsOnly)
	{
		// Each target can have its own assts defined in TARGET.TARGET_INPUT_ASSETS
		// Each target can copy assets to a different location defined in TARGET.TARGET_ASSETS
		// copy_assets function can override defaults by defining optSource and optDestination

		var src = optSource || TARGET.TARGET_INPUT_ASSETS || makefile.Config.PROJECT_PATHS.APP_ASSETS;
		var dst = optDestination|| TARGET.TARGET_ASSETS;

		trace("\nCopying assets ...");
		trace("+ source: " + src);
		trace("+ destination: " + dst);

	  	if(!folderExists(src))
	  		throw new Error("Assets folder not found " + src);

		if(contentsOnly)
		{
			var assets = _this.FindFiles(src, "*.*", true);
			for(var i=0; i<assets.length; i++)
			{
				var out = assets[i].replace(src, dst);
				var path = out.substr(0, out.lastIndexOf('/'));
				buildPath(path);
				copyFile(assets[i], out);
			}
		}
		else
		{
		  	buildPath(dst);
			copyFolder(src, dst);
			deleteFolder(dst + "/animations"); // Contains binary animation files
			IDECallback("folder", dst);
		}

		// Remove .rar files
		var files = _this.FindFiles(dst, "*.rar", true);
		for(var i=0; i<files.length; i++)
		{
			deleteFile(files[i]);
		}

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
				var match = /\$\{([^)]+?)\}/mg.exec(dst);
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
		var excludeVars = TARGET.DEVICE_WRAPPER.TEMPLATE_EXCLUDE_VARS ? TARGET.DEVICE_WRAPPER.TEMPLATE_EXCLUDE_VARS.split(";") : ["APP_ICONS", "SCRIPTS"];
		trace("+ templates: " + (templateFilesMask ? templateFilesMask : "(none)"));
        if(templateFilesMask)
        {
  			trace("\nProcessing Templates ...");
  			var files = _this.FindFiles(TARGET.TARGET_ROOT, templateFilesMask, true);
  			for(var i=0; i<files.length; i++)
  			{
				trace("+ processing: " + files[i]);
				var buff = read(files[i]);
				buff = _this.replaceVars(buff, true, excludeVars);
  				_this.module(files[i], buff);
  			}
        }
	};

    // =====================================================================
    // Generate Images from a template
    // =====================================================================
	_this.generate_images = function(list, template, altFolder, scale_to_fit, fill_bleed)
	{
		if(!list) return;

		if(!template || !fileExists(template))
			throw new Error("Missing image template");

		trace("+ template: " + template);

		if(altFolder)
			buildPath(altFolder);

		if(scale_to_fit===undefined)
			scale_to_fit = true;

		if(fill_bleed===undefined)
			fill_bleed = true;

		for(size in list)
		{
			var exports = list[size].split(";");
			for(var i=0;i<exports.length;i++)
			{
				if(altFolder)
					exports[i] = altFolder + "/" + _this.fileName(exports[i]);

				if(!fileExists(exports[i]))
				{
					var v = size.split("x");
					var width = v[0];
					var height = v.length==2 ? v[1] : width;
					trace("+ generating: " + exports[i]);
					resizeImage(template, exports[i], width, height, scale_to_fit, fill_bleed);
				}
				else
				{
					trace("+ exists: " + exports[i]);
				}
			}
		}
	};

    // =====================================================================
    // Generate icons
    // =====================================================================
	_this.generate_icons = function(altFolder)
	{
		if(!TARGET.APP_ICONS) return;
		trace("\nGenerating App Icons ...");
		_this.generate_images(TARGET.APP_ICONS, makefile.Config.PROJECT_FILES.ICON_TEMPLATE, altFolder, false, false);
	};

    // =====================================================================
    // Generate Splashes
    // =====================================================================
	_this.generate_splashes = function(altFolder)
	{
		if(!TARGET.APP_SPLASH_SCREENS) return;
		trace("\nGenerating App Splash Screens ...");
		_this.generate_images(TARGET.APP_SPLASH_SCREENS.Portrait, makefile.Config.PROJECT_FILES.SPLASH_PORTRAIT_TEMPLATE, altFolder, true, true);
		_this.generate_images(TARGET.APP_SPLASH_SCREENS.Landscape, makefile.Config.PROJECT_FILES.SPLASH_LANDSCAPE_TEMPLATE, altFolder, true, true);
	};

    // =====================================================================
    // Fonts Initialization Code
    // =====================================================================
	_this.loadFonts = function(file, assetsRoot)
	{
		var fonts = _this.FindFiles(assetsRoot+"/fonts", "*.ttf", true);
		var buff = read(file);
		if(buff)
		{
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
			buff = buff.replace("\t$(FONTS_LIST)", fonts.join("\n"));
			_this.module(file, buff, false);
		}
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

		var target_root				= TARGET.TARGET_ROOT;																// absolute path of target root folder
  		var src_paths	 			= TARGET.TARGET_INPUT_SOURCES || makefile.Config.PROJECT_PATHS.APP_SOURCES;			// semicolon separated list of paths
		var src_file_mask 			= TARGET.TARGET_SOURCES_MASK;														// semicolon separated file masks
		var framework_src_prefix	= "/$(PATH_SDK_FRAMEWORKS_WEB)/$(PATH_SDK_FRAMEWORKS_SRC)";							// path suffix for src files within a framework

  		// Collect sources from src paths and framrworks
		var files = _this.collectSources(target_root, src_paths, src_file_mask, framework_src_prefix);
  		if(files.length==0) return;

  		// Calculate source code dependencies
  		files = _this.calculateDependencies(files);

  		// Externs
		var file = makefile.Vars.PATH_SDK_COMPILER + "/externs.jspp";
	  	if(!fileExists(file)) throw new Error("Externs file not found " + file);

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
  			var name = _this.fileName(files[i]);
  			name = name.replace(/\.j\w+/g, "");
  			sources_map[name] = files[i];
  			g.addV(name);
  		}

  		// Create graph matrix
  		for(var i=0; i<files.length; i++)
  		{
  			var found = false;
  			var name = _this.fileName(files[i]);
  			name = name.replace(/\.j\w+/g, "");
  			buff = read(files[i]);
  			var rx = new RegExp("\\#include \\x22([^\\x22]+)\\x22", "mg");
  			while(match=rx.exec(buff))
  			{
  				var inc = match[1];
  				inc = inc.replace(/\.(jobj|jspp)/g, "");
  				if(!postProcess && !sources_map[inc])
  				{
  					//trace("> !ERROR: Include file [" + inc + "] not found in module " + files[i]);
  					//errors=true;
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
    // Set Framework Precompiler Vars
    // =====================================================================
	_this.set_framework_vars = function()
	{
	    // Reset Framework vars
	    for(var i in makefile.Components.Frameworks)
	    {
	    	var framework = makefile.Components.Frameworks[i];
	    	if(framework)
	    	{
	    		makefile.Vars[framework.PrecompilerVarName] = false;
	    		__global[framework.PrecompilerVarName] = false;
	    	}
	    }

	    var vFrameworks = _this.TARGET_FRAMEWORKS();
	    for(var i=0; i<vFrameworks.length; i++)
	    {
	    	if(!vFrameworks[i]) continue;
	    	var framework = makefile.Components.Frameworks[vFrameworks[i]];
	    	if(framework)
	    	{
	    		makefile.Vars[framework.PrecompilerVarName] = true;
	    		__global[framework.PrecompilerVarName] = true;
	    	}
	    }
	};

    // =====================================================================
    // Copy Framework JavaScript Libraries to target/out
    // =====================================================================
	_this.copy_framework_libs = function()
	{
		var FileMasks = "*.js;*.json";
		var vFrameworksSrcSubPaths = "/$(PATH_SDK_FRAMEWORKS_WEB)/$(PATH_SDK_FRAMEWORKS_LIB)";

	    trace("\nCollecting JavaScript Libraries ...\n+ pattern: " + FileMasks);

	    // Collect source paths from frameworks
	    trace("+ scanning frameworks ...");
	    var vFrameworks = _this.TARGET_FRAMEWORKS();
	    vFrameworksSrcSubPaths = vFrameworksSrcSubPaths.split(";");
	    for(var i=0; i<vFrameworks.length; i++)
	    {
	    	if(!vFrameworks[i]) continue;
	    	var framework = makefile.Components.Frameworks[vFrameworks[i]];
	    	if(framework)
	    	{
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
				        	var fileName = _this.fileName(file);
				     		copyFile(file, TARGET.TARGET_OBJ + "/" + fileName);
				        }
		        	}

		        	// Native node_modules?
		        	if(TARGET.NAME == "node.js" || TARGET.NAME == "CocoNode")
		        	{
			        	path = _this.replaceVars(framework.Path + "/native/node_modules");
			        	if(folderExists(path))
			        	{
				    		var addins = folderItems(path, ".*", false);
				    		for(k=0; k<addins.length; k++)
				    		{
				    			var bin = _this.FindFiles(addins[i] + "/gyp/build/Release", "*.node", false);
				    			if(!bin.length) continue;
			    				bin = bin[0];

			    				var addin_file = _this.fileName(bin);
			    				var addin_name = addin_file.replace(".node", "");
			    				var destination_folder = TARGET.TARGET_ROOT + "/node_modules/" + addin_name;

								// Copy node.js addon
								buildPath(destination_folder);
				    			copyFile(bin, destination_folder + "/bin/" + addin_file);

				    			// Copy package
				    			copyFile(addins[i] + "/gyp/package.json", destination_folder + "/package.json");
				    		}
			        	}
		        	}

		    	}
	    	}
	    }
	};

    // =====================================================================
    // Download npm packages to target
    // =====================================================================
	_this.npm = function()
	{
		var modules_root = TARGET.TARGET_ROOT + "/node_modules";
		var conf = makefile.Config.CONFIGURATION;
		if(conf.toLowerCase()!="release") conf="Debug";
		var packages = TARGET.SERVER[conf].npm;
		if(!packages) return;

		trace("\nDownloading npm packages, please wait ...");

		packages = packages.split(";");

		var node_root = makefile.Vars.PATH_3RD_PARTY_NODEJS;
		var npm = node_root + "/npm.cmd";

		for(var i=0; i<packages.length; i++)
		{
			if(folderExists(modules_root + "/" + packages[i])) continue;
			var command = npm + " install " + packages[i];

			trace("\nInstalling npm package " + packages[i] + " ...");
			_this.shell(command, TARGET.TARGET_ROOT);
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
	    var scripts = _this.FindFiles(TARGET.TARGET_OBJ, "*.js;*.jobj", true);

	    // Order scripts
	    scripts = _this.calculateDependencies(scripts, true);

	    // === RELEASE MODE ===
	    if(makefile.Config.CONFIGURATION.toLowerCase()=="release")
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
	            HTML.push('\t\tsrc: local(' + fontName + '), url("' + relativePath(TARGET.TARGET_ROOT,fonts[i]) + '");');
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
	    //HTML = HTML.replace("$(IMAGES)", html_images.join("\n"));

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
    // Collect all target frameworks
    // =====================================================================
	__global.TARGET_FRAMEWORKS = _this.TARGET_FRAMEWORKS = function()
	{
		return TARGET.TARGET_FRAMEWORKS ? TARGET.TARGET_FRAMEWORKS.split(";") : [];
	};

  	// =====================================================================
    // Target Sources Helper (resolve sources for libs, frameworks and target)
    // =====================================================================
	function TARGET_SOURCES()
	{
		this.Target					= null;
		this.TargetRoot             = null;
		this.TargetSources          = null;
		this.TargetFileMask         = null;
		this.Frameworks             = null;
		this.FRAMEWORKS             = [];
		this.FrameworkSubPaths      = null;
		this.Libraries              = [];
		this.LIBRARIES              = [];
		this.LIB_BIN_PATHS          = [];
		this.LIB_INC_PATHS          = [];
		this.LINK_LIBS		        = [];
		this.SourcePaths            = {};
		this.SourceFiles		    = {};
		this.INCLUDE_PATHS          = [];
		this.FILES                  = [];
		this.HPP                  	= [];
		this.CPP					= [];
	}

	// =====================================================================
	TARGET_SOURCES.prototype.CREATE_MAKEFILE = function(template, _ROOT, _CFLAGS, _ExcludeVars)
	{
		var $ = this;
		var SEPARATOR = " \\\n";
		var isAndroid = makefile.Vars.TARGET=="Android";
		var I_PREFIX = isAndroid ? "" : "-I";
		var L_PREFIX = "-L";

		var make_relative = function(files)
		{
			var out = [];
			for(var i=0; i<files.length; i++)
				out.push($.TargetRoot ? relativePath($.TargetRoot, files[i]) : files[i]);
			return out;
		};

		var CFLAGS = function()
		{
			var include_paths = make_relative($.INCLUDE_PATHS);
			include_paths = I_PREFIX + include_paths.join(SEPARATOR + I_PREFIX);
			include_paths = _this.winPath(include_paths);
			return _CFLAGS + SEPARATOR + include_paths;
		};

		var LDLIBS = function()
		{
			return $.LINK_LIBS.join(" ");
		};

		var LDFLAGS = function()
		{
			var lib_bin_paths = make_relative($.LIB_BIN_PATHS);
			lib_bin_paths = L_PREFIX + lib_bin_paths.join(SEPARATOR + L_PREFIX);
			lib_bin_paths = _this.winPath(lib_bin_paths);
			return lib_bin_paths;
		};

		var NATIVE_CPP_SOURCES = function()
		{
			var HPPmap = {};
			var files = [].concat($.FILES);
			var root = $.TargetRoot;

			for(i=0; i<files.length; i++)
			{
				// File relative to target root (if any)
				files[i] = root ? relativePath(root, files[i]) : files[i];

				if(/\.(cpp|m)$/i.test(files[i]))
				{
					if(files[i].indexOf("./")==0)
						files[i] = files[i].substr(2);

					$.CPP.push(files[i]);
				}

				if(/\.h[p]*?$/i.test(files[i]))
				{
					var path = files[i].substr(0, files[i].lastIndexOf("/"));

					if(!HPPmap[path])
					{
						HPPmap[path] = true;
						$.HPP.push(path);
					}
				}
			}

			$.HPP = $.HPP.sort();
			$.CPP = $.CPP.sort();

			return $.CPP.join(SEPARATOR);
		};

		var ANDROID_STATIC_LIBRARIES = function()
		{
			if(!isAndroid) return "";
			var out = [];
			for(var j=0; j<$.LIB_BIN_PATHS.length; j++)
			{
				var android_mk = ["LOCAL_PATH := $(call my-dir)\n"];
				var lib_bin_path = $.LIB_BIN_PATHS[j];
				var afiles = _this.FindFiles(lib_bin_path + "/x86", "*.a", false);
				for(var i=0; i<afiles.length; i++)
				{
					var afile = _this.fileName(afiles[i]);
					var aname = afile.substr(0, afile.lastIndexOf(".")).replace(/^lib/, '');

					var android_lib = "include $(CLEAR_VARS)\n";
					android_lib += "LOCAL_MODULE := " + aname + "\n";
					android_lib += "LOCAL_SRC_FILES := " + relativePath($.TargetRoot, lib_bin_path) + "/$(TARGET_ARCH_ABI)/" +  afile + "\n";
					android_lib += "include $(PREBUILT_STATIC_LIBRARY)\n";

					out.push(android_lib);
					android_mk.push(android_lib);
				}

				var path = $.LIBRARIES[j].Include;
				path = path.replace("$(LIBRARY_NAME)", $.LIBRARIES[j].id);
				path = path.replace("$(DEVICE_WRAPPER)", TARGET.NAME);
				path = _this.replaceVars(path, false);
				write(path + "/Android.mk", android_mk.join("\n"));
			}
			return out.join("\n");
		};

		// Read Makefile template
		var buff = read(template);

		// Substitute variables
		buff = buff.replace('$(APP_LDLIBS)', 				LDLIBS() 						);
		buff = buff.replace('$(APP_LDFLAGS)', 				LDFLAGS() 						);
		buff = buff.replace('$(APP_CFLAGS)', 				CFLAGS()						);
		buff = buff.replace('$(NATIVE_CPP_SOURCES)', 		NATIVE_CPP_SOURCES() 			);
		buff = buff.replace('$(ANDROID_STATIC_LIBRARIES)', 	ANDROID_STATIC_LIBRARIES()		);

		// Substitute variables
		var excludeVars = TARGET.DEVICE_WRAPPER.TEMPLATE_EXCLUDE_VARS ? TARGET.DEVICE_WRAPPER.TEMPLATE_EXCLUDE_VARS.split(";") : [];
		if(_ExcludeVars) excludeVars = excludeVars.concat(_ExcludeVars);
		buff = _this.replaceVars(buff, true, excludeVars);

		return buff;
	};

	// =====================================================================
    TARGET_SOURCES.prototype.AddSources = function(root, path, add_files, framework, library)
    {
    	this.INCLUDE_PATHS.push(path);

    	if(add_files)
    	{
	    	var files = this.SourcePaths[path] = _this.FindFiles(path, this.TargetFileMask, true);
	        for(var i=0; i<files.length; i++)
	        {
	        	var file = files[i];
	        	var fileName = _this.fileName(file);
	        	var filepath = file.substr(0, file.lastIndexOf("/"));
	        	var rel = file.replace((framework ? path : root), '');
	        	if(rel=="") rel = "/";
	        	this.SourceFiles[file] = { "FileName":fileName, "File":file, "Root":root, "Path":path, "Rel":rel, "Framework":framework, "Library":library };
	        	this.FILES.push(file);
	        }
    	}
    };

  	// =====================================================================
    // Find source files from target and frameworks
    // =====================================================================
    /*@@ collectSources @@*/

  	_this.collectSources = function(target_root, src_paths, src_file_mask, framework_src_prefix)
  	{
	    trace("\nCollecting Sources ...\n+ pattern: " + src_file_mask);

	    var SOURCES = makefile.Vars.SOURCES = new TARGET_SOURCES();

		SOURCES.Target				= makefile.Vars.TARGET;
		SOURCES.TargetRoot			= target_root;
		SOURCES.TargetSources		= src_paths.split(";");
		SOURCES.TargetFileMask		= src_file_mask;
		SOURCES.Frameworks			= _this.TARGET_FRAMEWORKS();
		SOURCES.FrameworkSubPaths	= _this.replaceVars(framework_src_prefix, false);

	   	// ==========================================================================
	    // A. Collect sources from Libraries
	   	// ==========================================================================
		var libs_path = makefile.Vars.PATH_SDK_LIBRARIES;
		var libs = read(libs_path + "/libs.json");
		libs = JSON.parse(libs)
		libs = libs.Libraries;
	    trace("+ libraries: " + Object.keys(libs).join(";"));
	    trace("+ scanning target libraries ...");
		function lib_repl_vars(lib, path)
		{
			path = path.replace("$(LIBRARY_NAME)", lib.id);
			path = path.replace("$(DEVICE_WRAPPER)", TARGET.NAME);
			path = _this.replaceVars(path, false);
			return path;
		}
		for(var lib_name in libs)
		{
			var lib = libs[lib_name];
			var library_targets = [];
			for(var t in lib.Targets) { library_targets.push(t); }
			library_targets = library_targets.join(";");
			if(library_targets.indexOf(TARGET.NAME)==-1) continue;

			lib.id = lib_name;
			SOURCES.Libraries.push(lib_name);
			SOURCES.LIBRARIES.push(lib);

			// Save library include path(s)
			var abs_lib_include_path = lib_repl_vars(lib, lib.Include);
			SOURCES.LIB_INC_PATHS.push(abs_lib_include_path);

			// Save library bin path(s)
			var abs_lib_bin_path = lib_repl_vars(lib, lib.Lib);
			SOURCES.LIB_BIN_PATHS.push(abs_lib_bin_path);

			// Save library link flags
			var lib_link_flags = lib.Targets[TARGET.NAME];
			SOURCES.LINK_LIBS.push(lib_link_flags);

			// Collect Library Sources
    		trace("  + " + lib_name + " -> " + abs_lib_include_path);
        	SOURCES.AddSources(abs_lib_include_path, abs_lib_include_path, lib.AddSources, null, lib);
		}

	   	// ==========================================================================
	    // B. Collect sources from Frameworks
	   	// ==========================================================================

	    if(SOURCES.Frameworks.length)
	    {
		    trace("+ frameworks: " + SOURCES.Frameworks.join(";"));
		    trace("+ scanning target frameworks ...");

		    var vFrameworksSrcSubPaths = framework_src_prefix.split(";");
		    for(var i=0; i<SOURCES.Frameworks.length; i++)
		    {
		    	var id = SOURCES.Frameworks[i];
		    	if(!id) continue;

		    	var framework = makefile.Components.Frameworks[id];

		    	if(!framework)
		    	{
		    		throw "ERROR: Invalid Framework " + id;
		    	}
		    	else
		    	{
		    		framework.id = id;

		    		// Check if this framework is compatible with this target
		    		if((";"+framework.Platforms+";").indexOf(";"+makefile.Vars.TARGET+";")==-1) continue;

		    		SOURCES.FRAMEWORKS.push(framework);

					// Process get/src framrwork folders
			    	for(j=0;j<vFrameworksSrcSubPaths.length;j++)
			    	{
			    		var root = _this.replaceVars(framework.Path);
			        	var path = _this.replaceVars(framework.Path + vFrameworksSrcSubPaths[j]);
			    		trace("  + " + id + " -> " + path);
			        	SOURCES.AddSources(root, path, true, framework, null);
			    	}
		    	}
		    }
	    }
	    else
	    {
	    	trace("+ frameworks: none");
	    }

	   	// ==========================================================================
	    // C. Collect sources from Target
	   	// ==========================================================================
	    if(src_paths)
	    {
		    trace("+ scanning target paths ...");

		    var vSourcePaths = src_paths.split(";");
		    for(var i=0; i<vSourcePaths.length; i++)
		    {
		    	var path = vSourcePaths[i];
		        trace("  + from source path: " + path);
	        	SOURCES.AddSources(path, path, true, null, null);
		    }
	    }

		// ==========================================================================
	    trace("+ found: " + SOURCES.FILES.length + " files");
	    return [].concat(SOURCES.FILES);
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
		if(!filePattern) filePattern = "*.jspp";
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
			var fileName = _this.fileName(files[i]);
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
  				var folderName = _this.fileName(folders[i]);
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
    // File name from path
    // =====================================================================
	_this.fileName = function(path)
	{
		return path.substr(path.lastIndexOf('/')+1);
	};

    // =====================================================================
    // Execute a shell command in the IDE
    // =====================================================================
	_this.shell = function(command, path, wait_process)
	{
		var json = JSON.stringify({command:command, path:path, wait_process:wait_process});
		trace(command);
		IDECallback("shell", command,0,0,json);
	};

    // =====================================================================
    // Sort dictionary by child attribute
    // =====================================================================
	_this.dicSort = function(dic, child_attr)
	{
		var out = [];

		if(child_attr)
		{
			var keys = [];
			for(var key in dic)
			{
				keys.push(dic[key][child_attr]);
			}

			keys = _this.sortFileNames(keys)

			for(var i=0; i<keys.length; i++)
			{
				for(var key in dic)
				{
					var item = dic[key];
					if(item[child_attr]==keys[i])
					{
						out.push(item);
						break;
					}
				}
			}
		}
		else
		{
			var keys = Object.keys(dic);
			keys = _this.sortFileNames(keys);

			for(var i=0; i<keys.length; i++)
			{
				out.push(dic[keys[i]]);
			}
		}

		return out;
	};

    // =====================================================================
    // Sort Files
    // =====================================================================
    _this.sortFileNames = function(files)
    {
		/*
		* Natural Sort algorithm for Javascript - Version 0.8.1 - Released under MIT license
		* Author: Jim Palmer (based on chunking idea from Dave Koelle)
		*/
		function naturalSort (a, b)
		{
			if(a.indexOf(".")!=-1 && b.indexOf(".")!=-1)
			{
				var p1 = a.lastIndexOf(".");
				var p2 = b.lastIndexOf(".");
				var L = Math.min(p1, p2);

				// File config.c and config-32bit.c
				// We compare against "config" and if both files are the same
				// then first comes the file with smaller length (config.c)

				if( a.substr(0, L)==b.substr(0, L) )
				{
					if(a.length < b.length)
						return -1;
					else
						return 1;
				}
				else
				{
					a = a.substr(0, L);
					b = b.substr(0, L);
				}
			}

		    var re = /(^([+\-]?\d+(?:\.\d*)?(?:[eE][+\-]?\d+)?(?=\D|\s|$))|^0x[\da-fA-F]+$|\d+)/g,
		        sre = /^\s+|\s+$/g,   // trim pre-post whitespace
		        snre = /\s+/g,        // normalize all whitespace to single ' ' character
		        dre = /(^([\w ]+,?[\w ]+)?[\w ]+,?[\w ]+\d+:\d+(:\d+)?[\w ]?|^\d{1,4}[\/\-]\d{1,4}[\/\-]\d{1,4}|^\w+, \w+ \d+, \d{4})/,
		        hre = /^0x[0-9a-f]+$/i,
		        ore = /^0/,
		        i = function(s)
		        {
		            return (naturalSort.insensitive && ('' + s).toLowerCase() || '' + s).replace(sre, '');
		        },
		        // convert all to strings strip whitespace
		        x = i(a),
		        y = i(b),
		        // chunk/tokenize
		        xN = x.replace(re, '\0$1\0').replace(/\0$/,'').replace(/^\0/,'').split('\0'),
		        yN = y.replace(re, '\0$1\0').replace(/\0$/,'').replace(/^\0/,'').split('\0'),
		        // numeric, hex or date detection
		        xD = parseInt(x.match(hre), 16) || (xN.length !== 1 && Date.parse(x)),
		        yD = parseInt(y.match(hre), 16) || xD && y.match(dre) && Date.parse(y) || null,
		        normChunk = function(s, l)
		        {
		            // normalize spaces; find floats not starting with '0', string or 0 if not defined (Clint Priest)
		            return (!s.match(ore) || l == 1) && parseFloat(s) || s.replace(snre, ' ').replace(sre, '') || 0;
		        },
		        oFxNcL, oFyNcL;

		    // first try and sort Hex codes or Dates
		    if (yD)
		    {
		        if (xD < yD) { return -1; }
		        else if (xD > yD) { return 1; }
		    }

		    // natural sorting through split numeric strings and default strings
		    for(var cLoc = 0, xNl = xN.length, yNl = yN.length, numS = Math.max(xNl, yNl); cLoc < numS; cLoc++)
		    {
		        oFxNcL = normChunk(xN[cLoc] || '', xNl);
		        oFyNcL = normChunk(yN[cLoc] || '', yNl);

		        // handle numeric vs string comparison - number < string - (Kyle Adams)
		        if (isNaN(oFxNcL) !== isNaN(oFyNcL))
		        {
		            return isNaN(oFxNcL) ? 1 : -1;
		        }

		        // if unicode use locale comparison
		        if (/[^\x00-\x80]/.test(oFxNcL + oFyNcL) && oFxNcL.localeCompare)
		        {
		            var comp = oFxNcL.localeCompare(oFyNcL);
		            return comp / Math.abs(comp);
		        }

		        if (oFxNcL < oFyNcL) { return -1; }
		        else if (oFxNcL > oFyNcL) { return 1; }
		    }
		}

		return [].concat(files).sort(naturalSort);
    };

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
		var compiler = new Compiler(ast);
		compiler.compile(false);
		var stateMachine = compiler.exportGameStateMachine();
		trace(stateMachine);
	};

	// ==================================================================================================================================
	//	    ____        _ __    __
	//	   / __ )__  __(_) /___/ /
	//	  / __  / / / / / / __  /
	//	 / /_/ / /_/ / / / /_/ /
	//	/_____/\__,_/_/_/\__,_/
	//
	// ==================================================================================================================================

    // =====================================================================
	// Pre build script
    // =====================================================================
	_this.prebuild = function(params)
	{
	};

    // =====================================================================
	// Post build script
    // =====================================================================
	_this.postbuild = function(params)
	{
		if(TARGET.TARGET_POST_BUILD)
		{
			var result = eval(TARGET.TARGET_POST_BUILD);
			trace(result);
		}
	};

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
		_this.set_framework_vars();

		var builder = null;
		if(command)
		{
			builder = this[command];
			if(!builder)
			{
				trace("Invalid make command: " + command);
				throw new Error("Invalid make command: " + command);
			}
		}
		else
		{
			var fn = "Build_" + makefile.Vars.TARGET.replace(/\./img, '_');
			builder = this[fn];
		}

		if(!builder)
		{
			trace("Build function not found for [" + makefile.Vars.TARGET + "] target");
			throw new Error("Build function not found for [" + makefile.Vars.TARGET + "] target");
		}

		// Build Target
		prebuild(params);
	    builder(params);
	    postbuild(params);

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
	var nodes = [];
	var edges = [];

	var _this = this;
	_this.errors = [];

	this.addV = function(n)
	{
		nodes.push(n);
	}

	this.addE = function(v1, v2)
	{
		edges.push([v1, v2]);
	}

	this.sort = function()
	{
	    var sorted = [];

	    function visit( node, predecessors, i )
	    {
	        var index, predsCopy;
	        predecessors = predecessors || [];

	        if(predecessors.indexOf(node) > -1)
	        {
	        	_this.errors.push( { file:node, cycle:predecessors.concat([node]), error: "Cyclic dependency found. '" + node + "' is dependent of itself.\nDependency Chain: " + predecessors.join( " -> " ) + " => " + node + "\n" } );
	        }

	        index = nodes.indexOf( node );
	        if ( index === -1 )
	        {
	            return i;
	        }

	        nodes.splice( index, 1 );
	        if ( predecessors.length === 0 )
	        {
	            i--;
	        }

	        predsCopy = predecessors.slice();
	        predsCopy.push( node );

	        edges.filter(function( e )
	        {
	            return e[ 0 ] === node;
	        }).forEach(function( e )
	        {
	            i = visit( e[ 1 ], predsCopy, i );
	        });

	        sorted.unshift( node );
	        return i;
	    }

	    for(var i=0; i<nodes.length; i++)
	    {
	        i = visit( nodes[ i ], null, i );
	    }

	    sorted = sorted.reverse();

	    return sorted;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function graphSort(nodes, edges)
{
	var cursor = nodes.length;
	var sorted = new Array(cursor);
	var visited = {};
	var i = cursor;

	while (i--)
	{
		if(!visited[i])
			visit(nodes[i], i, []);
	}
	return sorted

	function visit(node, i, predecessors)
	{
		if(predecessors.indexOf(node) >= 0)
		{
			trace("Cyclic dependency: "+JSON.stringify(node));
		}

		if(visited[i]) return;
		visited[i] = true;

		// outgoing edges
		var outgoing = edges.filter(function(edge)
		{
			return edge[0] === node;
		});

		if(i = outgoing.length)
		{
			var preds = predecessors.concat(node);
			do
			{
				var child = outgoing[--i][1];
				visit(child, nodes.indexOf(child), preds);

			} while(i)
		}

		sorted[--cursor] = node;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
					x= "<" + k + "><![CDATA[" + v + "]" + "]></" + k + ">";
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
	buff = RxReplace(buff, "\\s*//<<(.*)>>//", "mg", "$1");

	buff = RxReplace(buff, "\\bFloat\\b", "mg", "float");
	buff = RxReplace(buff, "\\bInteger\\b", "mg", "int32_t");
	buff = RxReplace(buff, "\\bBoolean\\b", "mg", "bool");
	buff = RxReplace(buff, "\\bTime\\b", "mg", "float");
	buff = RxReplace(buff, "\\bNumber\\b", "mg", "float");
	buff = RxReplace(buff, "\\bFunction\\b", "mg", "void");
	buff = RxReplace(buff, "\\bObject\\b", "mg", "void");

	buff = RxReplace(buff, "\\bMath::(\\w+)\\(", "mg", 		"math_$1(");

	//buff = RxReplace(buff, "\\btrace\\s*\\((.*)\\)\\s*;\\s*$", "mg", "trace(($1).c_str());");
	buff = RxReplace(buff, "([\\x22\\x27])\\x2e\\x2fassets\\x2f", "mg", "$1./");
	buff = RxReplace(buff, "_ENUM\\.(\\w+)", "mg", "_ENUM::$1");
	buff = RxReplace(buff, "__currentFrame\\->action\\.call\\(scene\\);", "mg", "(scene->*__currentFrame->action)();");
	return buff;
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

// =====================================================================
// Parent Folder
// =====================================================================
function parentFolder(path)
{
	if(path.indexOf('/')!=-1)
		return path.substr(0, path.lastIndexOf('/'));
	else
		return path.substr(0, path.lastIndexOf('\\'));
}

// =====================================================================
// File Name
// =====================================================================
function fileName(path)
{
	if(path.indexOf('/')!=-1)
		return path.substr(path.lastIndexOf('/')+1);
	else
		return path.substr(path.lastIndexOf('\\')+1);
}

// =====================================================================
// File NodeName
// =====================================================================
function fileNodeName(path)
{
	var name = _this.fileName(path);
	return name.substr(0, name.lastIndexOf('.'));
}

