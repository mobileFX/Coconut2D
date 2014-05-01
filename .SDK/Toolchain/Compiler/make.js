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

if(!this['window']) this.window = {};
if(!this['console']) console = {log:function(m){}}
if(!this['IDECallback']) this.IDECallback = function(){};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function __exists(collection, key)
{
	return Object.prototype.hasOwnProperty.call(collection, key);
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
function make(options)
{
	var _this = this;
	var TARGET = makefile.Config.TARGETS[makefile.Vars.TARGET];
	makefile.Vars["UCONFIGURATION"] = makefile.Vars.CONFIGURATION.toUpperCase();

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
  	this.Build_CocoPlayer = function()
  	{
  		_this.clean();
  		_this.apply_device_wrapper();
  		_this.generate_icons();
  		_this.copy_assets();
  		_this.generate_javascript();
  		_this.create_payload_js();
  		_this.closure();
  	};

    // =====================================================================
    // Build for HTML5 Browsers
    // =====================================================================
  	this.Build_HTML5 = function()
  	{
  		_this.clean();
  		_this.apply_device_wrapper();
  		_this.generate_icons();
  		_this.copy_assets();
  		_this.generate_javascript();
  		_this.create_payload_js();
  		_this.closure();
  		_this.create_index_html();
  	};

    // =====================================================================
    // Build for Android Devices
    // =====================================================================
  	this.Build_Android = function()
  	{
  		makefile.Vars["ANDROID_SDK_ESCAPED"] = makefile.Vars.PATH_3RD_PARTY_ANDROID_SDK.replace(/\x2f/mg, '\\\\');
  		makefile.Vars["PATH_SDK_LIBRARIES_ANDROID"] = relativePath(TARGET.TARGET_ROOT+"/jni", makefile.Vars.PATH_SDK_LIBRARIES+"/Android");

  		_this.clean();
  		_this.apply_device_wrapper();
  		_this.generate_icons();
  		_this.copy_assets();
  		_this.generate_cpp();
  		_this.compile_jni_static_lib();
  		_this.compile_apk();
  	};

    // =====================================================================
    // Build for iOS Devices
    // =====================================================================
  	this.Build_iOS = function()
  	{
  		_this.clean();
  		_this.apply_device_wrapper();
  		_this.generate_icons();
  		_this.copy_assets();
  		_this.generate_cpp();
  		_this.compile_ipa();
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
		var compiler = new Compiler(ast, true);
		compiler.compile();
		trace("+ Done.");
	};

    // =====================================================================
    // Compile JavaScript Classes to C++
    // =====================================================================
	_this.generate_cpp = function()
	{
		// Get all source code (including externs)
		var code = _this.getSourceCode();

		// Parse source code and generate AST
		trace("\nParsing JavaScript Class files ...");
		narcissus.__messages = true;
		narcissus.__cpp = true;
		var ast = narcissus.jsparse(code);
		trace("+ Abstract Syntax Tree (AST) generated.");

		// Compile AST to JavaScript to build symbol tables
		trace("\nBuilding Symbol Tables ...");
		var compiler = new Compiler(ast, false);
		compiler.compile();
		trace("+ Symbol tables generated.");

		// Compile AST to C++
		trace("\nCompiling JavaScript Classes to C++ ...");
		var compiler = new CPPCompiler(ast);
		compiler.compile();

		// Update Coconut2D.hpp
		//IDECallback("coconut2d.hpp", "", 0, 0, compiler.getClassList());

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
  		var CPP_SOURCES_PATH = [ makefile.Config.PROJECT_PATHS.NATIVE_COMMON, TARGET.TARGET_ADDITIONAL_NATIVE_SOURCES ].join(";");
  		var files = _this.collectSources(CPP_SOURCES_PATH,
  										 TARGET.TARGET_NATIVE_MASK,
  										 "/$(PATH_SDK_FRAMEWORKS_NATIVE)/$(PATH_SDK_FRAMEWORKS_GEN);" +
  										 "/$(PATH_SDK_FRAMEWORKS_NATIVE)/$(PATH_SDK_FRAMEWORKS_SRC)");

		// Make all paths relative to JNI folder
		files = _this.get_relative_cpp_hpp(files, TARGET.TARGET_ROOT + "/jni");
		makefile.Vars["NATIVE_CPP_SOURCES"] = files.CPP.join(" \\\n");
		makefile.Vars["NATIVE_CPP_INCLUDES"] = files.HPP.join(" \\\n");

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
  		var CPP_SOURCES_PATH = [ makefile.Config.PROJECT_PATHS.NATIVE_COMMON, TARGET.TARGET_ADDITIONAL_NATIVE_SOURCES ].join(";");
  		var files = _this.collectSources(CPP_SOURCES_PATH,
  										 TARGET.TARGET_NATIVE_MASK,
  										 "/$(PATH_SDK_FRAMEWORKS_NATIVE)/$(PATH_SDK_FRAMEWORKS_GEN);" +
  										 "/$(PATH_SDK_FRAMEWORKS_NATIVE)/$(PATH_SDK_FRAMEWORKS_SRC)");

		// Make all paths relative to target folder
		files = _this.get_relative_cpp_hpp(files, TARGET.TARGET_ROOT);
		makefile.Vars["NATIVE_CPP_SOURCES"] = _this.winPath(files.CPP.join(" \\\n"));
		makefile.Vars["NATIVE_CPP_INCLUDES"] = _this.winPath(" -I" + files.HPP.join(" \\\n -I"));

		// Collect resources
		trace("\n Collecting Resources ...");
		var files = _this.FindFiles(TARGET.TARGET_ROOT, TARGET.TARGET_RESOURCES_MASK, true);
		for(i=0;i<files.length;i++)
		{
			files[i] = relativePath(TARGET.TARGET_ROOT, files[i]);
		}
		files.push("./assets");
		makefile.Vars["NATIVE_RESOURCES"] = files.join(" \\\n");
		trace("+ Done.");

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

		// Create Info.plist		//$(APP_ICONS)
		trace("\n Creating Info.plist ...");
        trace("+ replacing variables ...");
		var file = TARGET.TARGET_ROOT+"/Info.plist";
		var buff = read(file);
		buff = _this.replaceVars(buff, true);
        _this.module(file, buff);

        // Create Makefile
		var file = TARGET.TARGET_ROOT+"/Makefile.mk";
		trace("\nCreating iOS Makefile makefile ...");
		trace("+ makefile: " + file);
        trace("+ replacing variables ...");
		var buff = read(file);
		buff = _this.replaceVars(buff, true, TARGET.DEVICE_WRAPPER.TEMPLATE_EXCLUDE_VARS.split(";"));
        _this.module(file, buff);

        // Create a custom make_ios.bat (offers better control than relying on environment variables)
        var buff = [];
        var make_cmd = TARGET.TARGET_ROOT + "/make_ios.bat";
        buff.push('@echo off');
        buff.push('SET IOSBUILDENV_PATH=' + makefile.Vars.PATH_3RD_PARTY_IOS_BUILD_ENV);
        buff.push('SET IOS_PROJECT_PATH=$(TARGET_ROOT)');
		buff.push('SET IOS_MAKEFILE=%IOS_PROJECT_PATH%/Makefile.mk');
		buff.push('"%IOSBUILDENV_PATH%/Toolchain/make.exe" --directory="%IOS_PROJECT_PATH%" --makefile="%IOS_MAKEFILE%" --warn-undefined-variables SHELL=%ComSpec% prepare resources');
        buff.push('"%IOSBUILDENV_PATH%/Toolchain/make.exe" --directory="%IOS_PROJECT_PATH%" --makefile="%IOS_MAKEFILE%" --jobs --warn-undefined-variables SHELL=%ComSpec% compile');
        buff.push('"%IOSBUILDENV_PATH%/Toolchain/make.exe" --directory="%IOS_PROJECT_PATH%" --makefile="%IOS_MAKEFILE%" --warn-undefined-variables SHELL=%ComSpec% link codesign ipa end');
        //buff.push('"%IOSBUILDENV_PATH%/Toolchain/make.exe" --directory="%IOS_PROJECT_PATH%" --makefile="%IOS_MAKEFILE%" --warn-undefined-variables SHELL=%ComSpec% all');
		buff = _this.replaceVars(_this.winPath(buff.join("\n")));
        _this.module(make_cmd, buff);

        // Build the static libraries for arm and x86
        trace("\nCalling iOS make ...");
        _this.shell(make_cmd, TARGET.TARGET_ROOT);
        _this.DeleteFile(make_cmd);
        _this.DeleteFolder(TARGET.TARGET_ROOT+"/obj");
        _this.DeleteFolder(TARGET.TARGET_ROOT+"/assets");

        // Sanity check
        if(!fileExists(TARGET.TARGET_OUTPUT))
       		throw new Error("ERROR: Failed to compile iOS Application");
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
			_this.cleanFolder(folders[i]);
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
	_this.copy_assets = function()
	{
		var src = makefile.Config.PROJECT_PATHS.ASSETS;
		var dst = TARGET.TARGET_ASSETS;
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
	_this.generate_icons = function()
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
  		var files = _this.collectSources(makefile.Config.PROJECT_PATHS.SOURCES,
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

		return buff.join("\n");
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
    // Read compiled CocoScript code and create JavaScript payload.js
    // =====================================================================
	_this.create_payload_js = function()
	{
	    trace("\nCreating payload.js ...");

	    var file = TARGET.TARGET_ROOT + "/payload.js";
	    var BUFFER = ["if(!this['include']) this.include=function(f){};\n"];

	    // Collect scripts
	    var scripts = _this.FindFiles(TARGET.TARGET_ROOT, "*.jobj", true);

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

	            case "oblique":
	                HTML.push("\t\tfont-style: italic, oblique;");
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
	    module(TARGET.TARGET_ROOT + "/index.html", HTML, false);

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
  	_this.collectSources = function(Sources, FileMasks, vFrameworksSrcSubPaths)
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

	    // Collect modules from each path
	    var files = [];
	    var ModuleFiles = {};
	    for(var path in SourcePaths)
	    {
	        var Files = _this.FindFiles(path, FileMasks, true);
	        for(var i=0;i<Files.length;i++)
	        {
	        	var file = Files[i];
	        	if(ModuleFiles[file]) continue;
        		files.push(file);
				ModuleFiles[file] = true;
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
		var includes = relativePath(root, makefile.Vars.PATH_SDK_INCLUDES);
		var CPP = [];
		var HPP = [includes];
		var HPPmap = {};
		HPPmap[includes] = true;
		for(i=0;i<files.length;i++)
		{
			files[i] = relativePath(root, files[i]);
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
		HPP =  HPP.sort().reverse();
		CPP = CPP.sort().reverse();
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
    // Make!
    // =====================================================================
    try
    {
		var builder = null;
		if(options)
		{
			builder = this[options];
		}
		else
		{
			builder = this["Build_" + makefile.Vars.TARGET];
		}
		if(!builder)
			throw new Error("Build function not found for [" + makefile.Vars.TARGET + "] target");
	    builder();
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
    	var e = v2i(v2)
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
        	var t = "Cyclic reference between " + first + " and " + last + "\n" +
	        	 	"Cyclic reference resolution path:\n" + path.join("\n") + "\n" + v[i];
        	throw new Error(t);
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
    	throw new Error("Cyclic reference detected processing " + v[i]);
	}

	this.sort = function()
	{
    	if(!v) return;
	    for(var i=0; i<v.length; i++)
	    {
	        var e = ni();
	        if(e == -1) cy(i);
	        o[i] = v[e];
	        for(var j=0; j<v.length; j++)
	        {
	            m[j][e] = 2;
	            m[e][j] = 2;
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
		var compiler = new Compiler(ast, true, className);
		compiler.compile();
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
	buff = RxReplace(buff, "\\bMath::random\\(\\)", "mg", "((float)rand()/(float)RAND_MAX)");
	buff = RxReplace(buff, "\\btrace\\s*\\((.*)\\)\\s*;\\s*$", "mg", "trace(($1).c_str());");
	buff = RxReplace(buff, "([\\x22\\x27])\\x2e\\x2fassets\\x2f", "mg", "$1./");
	buff = RxReplace(buff, "_ENUM\\.(\\w+)", "mg", "_ENUM::$1");
	buff = RxReplace(buff, "__currentFrame\\->action\\.call\\(scene\\);", "mg", "(scene->*__currentFrame->action)();");
	return buff;
}
