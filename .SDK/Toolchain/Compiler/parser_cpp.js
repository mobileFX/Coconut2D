// parser_cpp.js

function CPPParser(files)
{
	// ==========================================================================================
	// Parse native non-generated C++ headers and record external classes (Externs)
	// ==========================================================================================

	// The vartype was not found in CocoScript code.
	// It is possible that it is an Emscripten class.

	trace("\nParsing C++ Headers ...");

	var cpp_class_pattern = "(class|struct)\s+(\w+)(\s*\:\s*(?:,?\s*(?:public|private|protected)?\s*(?:\w+))*)?\s*\{([\w\W]*?)\};";
	var cpp_method_pattern = "^(.*?)\s([a-zA-Z_]\w*)\s*\(([^)]+)\)[\s\n\r]*[;{]";
	var cpp_member_var_pattern = "^(.+?)\s+([a-zA-Z_]\w*)(\[[^\]]*\])*[\n\r\s]*[=;]";
	var cpp_enum_pattern = "enum\s([A-Za-z_]\w*)\s*\{([^}]*)\}([^;]*);";

	for(var item in makefile.Components.Frameworks)
	{
		var framework = makefile.Components.Frameworks[item];
		if(framework.Type!="Emscripten Library") continue;

		var path = __coco_make.replaceVars(framework.Path + "/$(PATH_SDK_FRAMEWORKS_NATIVE)/$(PATH_SDK_FRAMEWORKS_EMS)");
		var header_files = __coco_make.FindFiles(path, "*.h;*.hpp", true);
		for(i=0;i<header_files.length;i++)
		{
			var file = header_files[i];
			var fileName = file.substr(file.lastIndexOf("/")+1);
			trace("+ Parsing: " + file);
		}
	}

	function parse_class(m)
	{
	}

	function parse_function(m)
	{
	}

	function parse_member_var(m)
	{
	}

	function parse_enum(m)
	{
	}
}