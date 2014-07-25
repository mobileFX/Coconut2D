
function __make_plugin_emscripten(cocomaker)
{
	var _this = cocomaker;

	// ==================================================================================================================================
	//	    ______                         _       __                _____                              __
	//	   / ____/___ ___  _______________(_)___  / /____  ____     / ___/__  ______  ____  ____  _____/ /_
	//	  / __/ / __ `__ \/ ___/ ___/ ___/ / __ \/ __/ _ \/ __ \    \__ \/ / / / __ \/ __ \/ __ \/ ___/ __/
	//	 / /___/ / / / / (__  ) /__/ /  / / /_/ / /_/  __/ / / /   ___/ / /_/ / /_/ / /_/ / /_/ / /  / /_
	//	/_____/_/ /_/ /_/____/\___/_/  /_/ .___/\__/\___/_/ /_/   /____/\__,_/ .___/ .___/\____/_/   \__/
	//	                                /_/                                 /_/   /_/
	// ==================================================================================================================================

    // =====================================================================
    // Activate Emscripten version compatible with Coconut2D
    // =====================================================================
	_this.ACTIVATE_EMSCRIPTEN_VERSION = function()
	{
		var path = "c:/temp";
  		var make_lib_cmd = path + "/build.cmd";
  		var buff = [];
  		buff.push('@echo off');
		buff.push('cd /d "$(PATH_3RD_PARTY_EMSDK)"');
		buff.push('"$(PATH_3RD_PARTY_EMSDK)/emsdk" activate sdk-1.12.0-32bit');
		buff = _this.replaceVars(buff.join("\n"));
        _this.module(make_lib_cmd, buff);
        _this.shell(make_lib_cmd, path, null);
	};

    // =====================================================================
    // Compile Emscripten Library
    // =====================================================================
	_this.COMPILE_EMSCRIPTEN_LIBRARY = function(params)
	{
		for(var item in makefile.Components.Frameworks)
		{
			var framework = makefile.Components.Frameworks[item];
			if(framework.Type!="Emscripten Library") continue;
			if(_this.replaceVars(framework.Path + "/$(PATH_SDK_FRAMEWORKS_NATIVE)/$(PATH_SDK_FRAMEWORKS_EMS)") == params.path)
			{
				_this.compile_emscripten_framework(framework);
				break;
			}
		}
	};

    // =====================================================================
    // Compile Emscripten Framework
    // =====================================================================
  	_this.compile_emscripten_framework = function(framework)
  	{
  		trace("\nBuilding " + framework.Name + " with Emscripten ...");

  		// Get the path of the C++ Library
		var path = framework.Path + "/$(PATH_SDK_FRAMEWORKS_NATIVE)/$(PATH_SDK_FRAMEWORKS_EMS)";
		path = _this.replaceVars(path);

  		// Build C++ Library with Emscripten (*** ASSUMING YOU HAVE THE RIGHT MAKEFILE ***)
  		var make_lib_cmd = path + "/build.cmd";
  		var buff = [];
  		buff.push('@echo off');

  		// Make sure we have make.exe in the path and set all rest tools required by Emscripten
		buff.push('SET PATH=$(PATH_3RD_PARTY_MAKE);$(PATH_3RD_PARTY_EMSCRIPTEN);$(PATH_3RD_PARTY_PYTHON);$(PATH_3RD_PARTY_LLVM);$(PATH_3RD_PARTY_NODEJS);$(PATH_3RD_PARTY_JAVA)');

		buff.push('SET LLVM_ROOT=$(PATH_3RD_PARTY_LLVM)');
		buff.push('SET NODE_JS=$(PATH_3RD_PARTY_NODEJS)/node.exe');
		buff.push('SET PYTHON=$(PATH_3RD_PARTY_PYTHON)/python.exe');
		buff.push('SET JAVA=$(PATH_3RD_PARTY_JAVA)/bin/java.exe');
		buff.push('SET EMSCRIPTEN_ROOT=$(PATH_3RD_PARTY_EMSCRIPTEN)');

		// Call emmake!!
	    buff.push('emmake make');

	    // Save batch script and execute it
		buff = _this.replaceVars(buff.join("\n"));
        _this.module(make_lib_cmd, buff);
        _this.shell(make_lib_cmd, path, "clang++.exe");
        _this.DeleteFile(make_lib_cmd);

		// ================================
		// Export Bindings and Symbols
		// ================================

        trace("\nExporting " + framework.Name + " bindings ...");

		// Find xxx_bindings.cpp file
		var bindingsCppFile = _this.FindFiles(path, "*_bindings.cpp", true);
		if(bindingsCppFile.length==0)
			throw "Emscripten compilation failed, no C++ bindings found.";
		bindingsCppFile = bindingsCppFile[0];

		// Find xxx_bindings.js file
		var bindingsJsFile = _this.FindFiles(path, "*_bindings.js", true);
		if(bindingsJsFile.length==0)
			throw "Emscripten compilation failed, no JavaScript bindings found.";
		bindingsJsFile = bindingsJsFile[0];

		// Copy JavaScript files in lib
		var files = _this.FindFiles(path, "*.js", false);
		for(var i=0;i<files.length;i++)
		{
			var fileName = files[i].substr(files[i].lastIndexOf("/")+1);
			var dstFileName = framework.Path + "/$(PATH_SDK_FRAMEWORKS_WEB)/$(PATH_SDK_FRAMEWORKS_LIB)/" + fileName;
			dstFileName = _this.replaceVars(dstFileName);
			copyFile(files[i], dstFileName);
		}

		// Parse C++ headers
		files = _this.FindFiles(path, "*.h;*.hpp", false);
		var cppSymbols = CPPParser(files);

		// Parse C++ Bindings File
		var buffer = read(bindingsCppFile);
		var jspp_classes = {};
		var ems_binding_pattern = "^(.*?)__attribute__.*?emscripten_bind_([A-Za-z0-9]+?)__(.*?)_p\\d+\\((.*?)\\)";
		var rx = new RegExp(ems_binding_pattern, "img");
		var match=rx.exec(buffer);
		while(match)
		{
			var returnType	= match[1];
			var className 	= match[2];
			var fnSigName 	= match[3];
			var fnArgs 		= match[4];
			var setter 		= fnSigName.indexOf("set_")==0;
			var getter 		= fnSigName.indexOf("get_")==0;
			var fnName 		= fnSigName;

			// Parse Function Arguments
			var arguments = fnArgs.split(",");
			var jspp_arguments = [];
			for(var i=1; i<arguments.length; i++)
			{
				var arg = arguments[i].trim().split(" ");
				var argName = arg.splice(arg.length - 1, 1);
				var argType = arg.join(" ");
				jspp_arguments.push( argName + ":" + convertType(argType) );
			}
			jspp_arguments = jspp_arguments.join(", ");

			// Parse Function Return Type
			var jspp_retType = convertType(returnType.trim());

			// Generate Externs Code
			var classDef = jspp_classes[className]	|| { className:className, baseClass:"", methods:[], properties:{} };
			jspp_classes[className]=classDef;

			if(jspp_retType)
				jspp_retType = " : " + jspp_retType;

			if(fnName=="__destroy__")
			{
				fnName="Destructor";
				jspp_retType = "";
			}
			else if(fnName==className)
			{
				fnName="Constructor";
				jspp_retType = "";

				for(var i=classDef.methods.length;i--;)
				{
				}
			}

			var out = "\n\tpublic function " + fnName + "(" + jspp_arguments + ")" + jspp_retType + " {}";
			classDef.methods.push(out);
			match=rx.exec(buffer);
		}

		// Generate Externs CocoScript Code
		var jspp_externs = [];
		for(var item in jspp_classes)
		{
			trace("+ Class: " + item);
			var classDef = jspp_classes[item];
			var classCode = "emscripten class " + classDef.className + classDef.baseClass + "\n{" + classDef.methods.join("") + "\n}\n";
			jspp_externs.push(classCode);
		}

		// Append (or replace) externs to externs.jspp file
		var start_tag = "// BEGIN EMSCRIPTEN EXTERNS FOR " + framework.PrecompilerVarName + " //";
		var closing_tag = "// END EMSCRIPTEN EXTERNS FOR " + framework.PrecompilerVarName + " //";
		jspp_externs = ["\n", start_tag, "\n", figlet(framework.Name), jspp_externs.join("\n"), "\n", closing_tag].join("");
		var externs_file = makefile.Vars.PATH_SDK_COMPILER + "/externs.jspp";
		var buff = read(externs_file);
		var i1 = buff.indexOf(start_tag);
		var i2 = buff.indexOf(closing_tag);
		if(i1!=-1 && i2!=-1)
		{
			i2 += closing_tag.length;
			buff = buff.replace(buff.substring(i1, i2), jspp_externs);
		}
		else
		{
			buff += jspp_externs;
		}
		write(externs_file, buff);
		_this.module(externs_file, buff);

		trace("\nWARNING:Please note that symbol export is experimental, you will need to edit bindings.jspp file.");
	};

    // =====================================================================
    // C++ type to CocoScript type
    // =====================================================================
	_this.convertType = function(argType)
	{
		var pointer = argType.indexOf("*")!=-1;
		argType = argType.replace(/\bconst\b/mg, "");
		argType = argType.replace(/&/mg, "");
		argType = argType.replace(/\*/mg, "");
		argType = argType.trim();

		switch(argType)
		{
		case "void":
			return pointer ? "Object" : "";

		case "int":
		case "int32":
		case "signed int":
		case "unsigned int":
		case "signed short":
		case "unsigned short":
			return "Integer";

		case "float":
		case "float32":
			return "Float";

		case "bool":
			return "Boolean";
		}
		return argType;
	};
}