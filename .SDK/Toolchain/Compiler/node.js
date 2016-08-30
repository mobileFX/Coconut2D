/* ***** BEGIN LICENSE BLOCK *****
 *
 * Copyright (C) 2013-2016 www.mobilefx.com
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
//	                    __         _         ______                           __           ____  __            _
//	   ____  ____  ____/ /__      (_)____   / ____/__  ____  ___  _________ _/ /_____     / __ \/ /_  ______ _(_)___
//	  / __ \/ __ \/ __  / _ \    / / ___/  / / __/ _ \/ __ \/ _ \/ ___/ __ `/ __/ __ \   / /_/ / / / / / __ `/ / __ \
//	 / / / / /_/ / /_/ /  __/   / (__  )  / /_/ /  __/ / / /  __/ /  / /_/ / /_/ /_/ /  / ____/ / /_/ / /_/ / / / / /
//	/_/ /_/\____/\__,_/\___(_)_/ /____/   \____/\___/_/ /_/\___/_/   \__,_/\__/\____/  /_/   /_/\__,_/\__, /_/_/ /_/
//	                        /___/                                                                    /____/
// ==================================================================================================================================
//
// This is work in progress (WIP):
//
// When compiling for node.js the process links seperate files that bare the same #module XXX directive into one wrapper
// file. The wrapper uses "require()" method to load all .jobj files and "module.exports" to export the entities from
// each .jobj file. Typicall the wrapper file (eg. module.js) is stored in ./node_modules/<module>/bin and the .jobj
// files are stored in ./node_modules/<module>/lib folders respectively. In your program you simply import "require(module)"
// and all entities are made available (classes, enums, functions).
//
// The compiler analyzes each .jobj file and detects vartypes to import, so no #include directive is required.
//
//	        +------------------------------------------------------+
//	        | Module1.jobj                                         |
//	        |                                                      |
//	 Exports|                                                      | Exports
//	 Class1 |                                                      | Class1 +----------------------------------+
//	<-------| module.exports.Class1 = require("file1.jobj").Class1 |<-------+ File1.jspp                       |
//	        |                                                      |        | #module Module1                  |
//	        |                                                      |        | #include "Class2.jspp"           |
//	        |                                                      |        | class Class1 { var x:Class2 }    |
//	        |                                                      |        |                                  |
//	        |                                                      |        | require("file2.jspp")            |
//	        |                                                      |        | module.exports.Class1 = Class1;  |
//	        |                                                      |        +----------------------------------+
//          |                                                      |
//	 Exports|                                                      | Exports
//	 Class2 |                                                      | Class2 +----------------------------------+
//	<-------| module.exports.Class2 = require("file2.jobj").Class2 |<-------+ File2.jspp                       |
//	        |                                                      |        | #module Module1                  |
//	        |                                                      |        | #include "ClassN.jspp"           |
//	        |                                                      |        | class Class2 { var x:ClassN }    |
//	        |                                                      |        |                                  |
//	        |                                                      |        | require("fileN.jspp")            |
//	 Exports|                                                      |        | module.exports.Class2 = Class2;  |
//	 ClassN |                                                      |        +----------------------------------+
//	<-------| module.exports.ClassN = require("fileN.jobj").ClassN |
//	        |                                                      |                      ...
//	        |                                                      |
//	        +------------------------------------------------------+
//
// Please send bugs/suggestions to elias.politakis@mobilefx.com

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function CompilerNodejsPlugin(compiler)
{
	//trace("+ Loaded CocoScript Compiler Node.js Plugin");

	var _this = this._this = compiler;

	_this.NODE_MODULES = {};
	_this.NODE_PACKAGES = {};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// For every module we need to create the following files:
	//
	// - Package File: 	package.json	(contains information about the package)
	// - Module File:	module_name.js	(contains export redirections from .jobj files)
	// - Library Files:	*.jobj			(compiled .jspp code, imports other .jobj files)
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	_this.createModules = function()
	{
		trace("\nGenerating Node.js Modules ...");

		//--------------------------------------------------------------------------------
		// Query each class of what imports it needs
		//--------------------------------------------------------------------------------

		for(item in _this.classes)
		{
			// Get class symbol
			var cls = _this.classes[item];

			// Check if class symbol exports to node.js
			if(!cls.ast.__VARIABLES.export_nodejs)
				continue;

			// Get class file
			var FILE = _this.FILES[cls.path];

			// Iterate through vartypes required by this class and produce imports.
			for(vartype in cls.vartypes)
			{
				var symbol = _this.classes[vartype];
				if(!symbol) continue;
				if(symbol.file=="externs.jspp") continue;
				FILE.imports[vartype] = symbol;
			}
		}

		//--------------------------------------------------------------------------------
		// Cache all package.json files
		//--------------------------------------------------------------------------------

		var search_path = [_this.TARGET.TARGET_ROOT];

		for(var file in _this.FILES)
		{
			if(file=="externs.jspp") continue;
			var FILE = _this.FILES[file];

			var file_root = makefile.Vars.SOURCES.SourceFiles[file].Path;

			if(search_path.indexOf(file_root)!=-1) continue;
			search_path.push(file_root);
		}

		for(var i=0; i<search_path.length; i++)
		{
			var files = findFiles(search_path[i], "package\.json$", true);
			for(var j=0; j<files.length; j++)
			{
				try
				{
					var PACKAGE = JSON.parse(read(files[j]));
					if(PACKAGE && PACKAGE.name)
					{
						_this.NODE_PACKAGES[PACKAGE.name] = PACKAGE;
					}
				}
				catch(e)
				{
					trace("ERROR: Invalid node.js package: " + files[j]);
				}
			}
		}

		//--------------------------------------------------------------------------------
		// Create a list of all node.js modules that derive from our source code
		// and keep a list of imports and exports for each module.
		//--------------------------------------------------------------------------------

		for(var file in _this.FILES)
		{
			if(file=="externs.jspp") continue;
			var FILE = _this.FILES[file];

			for(var i=0; i<FILE.symbols.length; i++)
			{
				var ast = FILE.symbols[i];
				var moduleName = ast.__MODULE;

				if(!moduleName) continue;
				if(ast.type==jsdef.INTERFACE) continue;

				// Get module of this ast node, of current file
				if(!_this.NODE_MODULES[moduleName])
				{
					var root =  _this.TARGET.TARGET_ROOT + "/node_modules/" + moduleName;
					var PACKAGE = _this.NODE_PACKAGES[moduleName];

					// If no package exists, create one
					if(!PACKAGE)
					{
						// Create a package
						PACKAGE = JSON.parse(read(makefile.Vars.PATH_SDK_TEMPLATE_FILES + "/package.json"));
						PACKAGE.name = moduleName;
						PACKAGE.description = moduleName + " module";
						PACKAGE.main = "./bin/" + moduleName + ".js";

						// Save package.json for this module
						_this.NODE_PACKAGES[PACKAGE.name] = PACKAGE;
					}

					// Create a module
					var module_file = root + PACKAGE.main.substr(1);
					_this.NODE_MODULES[moduleName] = { root:root, file:module_file, imports:{}, exports:[], files:[], package:PACKAGE };
				}

				var MODULE = _this.NODE_MODULES[moduleName];

				// Get module folders
				var lib = MODULE.root + MODULE.package.directories.lib.substr(1);
				var bin = MODULE.root + MODULE.package.directories.bin.substr(1);
				var rel = relativePath(bin, lib);

				// Check if file already imported in module
				if(MODULE.files.indexOf(file)==-1)
					MODULE.files.push(file);

				// Files are placed in lib folder
				var moduleName = "__MOD_" + file.substr(file.lastIndexOf("/")+1).replace(".jspp", "").toUpperCase() +  "__";
				var name = file.substr(file.lastIndexOf("/")+1).replace(".jspp", ".jobj");
				var path = lib + "/" + name;
				var imp = 'var ' + moduleName + ' = require("' + rel + '/' + name + '");';

				// Change output file path
				FILE.out = path;
				FILE.module = MODULE;

				// Module Imports
				MODULE.imports[moduleName] = imp;

				// Module Exports

				switch(ast.type)
				{
				case jsdef.INTERFACE:

					// Interfaces are compile-time entities really.
					break;

				case jsdef.CLASS:
				case jsdef.STRUCT:

					MODULE.exports.push( "module.exports." + ast.name + ' = ' + moduleName + '.' + ast.name + ";" );
					break;

				case jsdef.ENUM:

					MODULE.exports.push( "module.exports." + ast.name + ' = ' + moduleName + '.' + ast.name + ";" );
					for(var j=0; j<ast.length; j++)
					{
						MODULE.exports.push( "module.exports." + ast[j].name + ' = ' + moduleName + '.' + ast[j].name + ";" );
					}
					break;

				case jsdef.FUNCTION:

					if(!ast.inClass)
					{
						MODULE.exports.push( "module.exports." + ast.name + ' = ' + moduleName + '.' + ast.name + ";" );
					}
					break;

				case jsdef.VAR:
				case jsdef.CONST:

					if(!ast.inClass)
					{
						for(var j=0; j<ast.length; j++)
						{
							MODULE.exports.push( "module.exports." + ast[j].name + ' = ' + moduleName + '.' + ast[j].name + ";" );
						}
					}
					break;
				}
			}
		}

		//--------------------------------------------------------------------------------
		// Write every module bin file
		//--------------------------------------------------------------------------------

		for(var module_name in _this.NODE_MODULES)
		{
			var MODULE = _this.NODE_MODULES[module_name];

			trace("+ Module: " + module_name + " (" + MODULE.root + ")");
			trace("  + File: " + MODULE.files.join("\n  + File: "));

			var imps = [];
			for(var imp in MODULE.imports)
			{
				imps.push(MODULE.imports[imp]);
			}

			var buff = imps.join('\n') + '\n\n' + MODULE.exports.join("\n") + '\n';

			IDECallback("module", MODULE.file, 0, 0, buff);

			var PACKAGE = _this.NODE_PACKAGES[module_name];
			IDECallback("module", MODULE.root + "/package.json", 0, 0, JSON.stringify(PACKAGE));
		}

		//--------------------------------------------------------------------------------
		// Generate library files for every module
		//--------------------------------------------------------------------------------

		for(var file in _this.FILES)
		{
			if(file=="externs.jspp") continue;

			var FILE = _this.FILES[file];

			if(FILE.buff.length==0)
			{
				// We just write an empty file
				IDECallback("module", FILE.out, 0, 0, buff);
				IDECallback("module_link", file, 0, 0, FILE.out);
				continue;
			}

			// Check if this file can be exported
			if(_this.TARGET_EXPORT!="export_all" && !FILE.symbols[0].__VARIABLES[_this.TARGET_EXPORT])
				continue;

			// Create node.js require() heders for this file
			// The following code assumes that every CocoScript entity is associated with a #module.

			for(var item in FILE.imports)
			{
				var symbol = FILE.imports[item];
				var path = FILE.imports[item].path;
				if(file==path) continue;

				var _require = null;

				// Search modules for this symbol file
				for(var module_name in _this.NODE_MODULES)
				{
					var MODULE = _this.NODE_MODULES[module_name];

					// If the symbol module is the same with the
					// file module we require() the .jobj file.

					if(FILE.module==MODULE)
					{
						var path = relativePath(parentFolder(FILE.out), _this.FILES[symbol.path].out);
						FILE.requires.push( 'var ' + symbol.name + ' = require("' + path + '").' + symbol.name + ';' );
						break;
					}

					// Load the symbol from the external module.

					if(MODULE.files.indexOf(path)!=-1)
					{
						FILE.requires.push( 'var ' + symbol.name + ' = require("' + module_name + '").' + symbol.name + ';' );
						break;
					}
				}

			}

			// Generate and beutify code

			var buff = 	_this.SEPARATOR + "// Node.js Imports\n" +
						_this.SEPARATOR + FILE.requires.join("\n") + "\n\n" +
						_this.SEPARATOR + FILE.buff.join("\n") + "\n\n" +
						_this.SEPARATOR + "// Node.js Exports\n" +
						_this.SEPARATOR + FILE.exports.join("\n");

			buff = _this.beutify(buff);

			// Output library files
			IDECallback("module", FILE.out, 0, 0, buff);
			IDECallback("module_link", file, 0, 0, FILE.out);
		}

		//--------------------------------------------------------------------------------
		// Copy resources to node_module
		//--------------------------------------------------------------------------------

		// Get target frameworks
		var vFrameworks = TARGET_FRAMEWORKS();

		for(var i=0; i<vFrameworks.length; i++)
		{
			// Get a framework
			var framework = makefile.Components.Frameworks[vFrameworks[i]];

			// Find a module for this framework
			var MODULE = _this.NODE_MODULES[vFrameworks[i]];
			if(!MODULE) continue;

			// Get framework resources path
			var path = __coco_make.replaceVars(framework.Path + "/$(PATH_SDK_FRAMEWORKS_WEB)/$(PATH_SDK_FRAMEWORKS_RES)");

			// Copy framework resources to node_module/module_name/res folder
			if(folderExists(path))
			{
				// Create the resource folder in node_module/module_name
				var res = __coco_make.replaceVars(MODULE.root + "/$(PATH_SDK_FRAMEWORKS_RES)");
				buildPath(res);

				// Copy all resource files from framework to node_module/module_name resource folder
	        	var Files = __coco_make.FindFiles(path, "*.*", true);
		        for(var j=0;j<Files.length;j++)
		        {
		        	var file = Files[j];
		        	var fileName = file.substr(file.lastIndexOf("/")+1);
		     		copyFile(file, res + "/" + fileName);
		        }
			}
		}

	}
}
