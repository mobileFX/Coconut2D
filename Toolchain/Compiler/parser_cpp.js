// parser_cpp.js

function CPPParser()
{
	// ==========================================================================================
	// Parse native non-generated C++ headers and record external classes (Externs)
	// ==========================================================================================

	// The vartype was not found in CocoScript code.
	// It is possible that it is an Emscripten class.

	trace("\nParsing C++ Headers ...");

	var cpp_class_pattern = "(class|struct|enum)\\s+(\\w+)(\\s*\:\\s*(?:,?\\s*(?:public|private|protected)?\\s*(?:\\w+))*)?\\s*\\{";
	var cpp_constructor_pattern = "^\\s*(virtual)?()\\s*($CLASSNAME)\\s*\\(([^\\)]*)\\)[\\w\\W]*?[\\{;]";
	var cpp_method_pattern = "^\\s*(virtual)?(.*?)\\s+([a-zA-Z_]\\w*)\\s*\\(([^\\)]*)\\)[\\w\\W]*?[\\{;]";
	var cpp_member_pattern = "^\\s*([a-zA-Z0-9_\\&\\*\\<\\>\\{\\}]*?)\\s+([a-zA-Z_]\\w*)(\\[[^\\]]*\\])*\\s*(?:=.*?)?;";
	var cpp_enum_member_pattern = "([a-zA-Z_]\\w*)\\s*(?:=\\s*(\\w+))?,?";

	var classes = {};

	// Get project framworks
	var frameworks = __global.TARGET_FRAMEWORKS();
	for(item in makefile.Components.Frameworks)
	{
		if(frameworks.indexOf(item)==-1) continue;

		var framework = makefile.Components.Frameworks[item];
		if(framework.Type!="Emscripten Library") continue;

		var path = __coco_make.replaceVars(framework.Path + "/$(PATH_SDK_FRAMEWORKS_NATIVE)/$(PATH_SDK_FRAMEWORKS_SRC)");
		var header_files = __coco_make.FindFiles(path, "*.h;*.hpp", true);
		for(i=0;i<header_files.length;i++)
		{
			var file = header_files[i];
			var fileName = file.substr(file.lastIndexOf("/")+1);
			trace("+ Parsing: " + file);

			var reg = new RegExp(cpp_class_pattern, "gm");
			var data = read(file);
			data = data.replace(new RegExp("//.*", "gm"), "");
			data = data.replace(new RegExp("/\\*[\\w\\W]*?\\*/", "gm"), "");
			for(var cls = parse_class(reg, data); cls; cls = parse_class(reg, data))
			{
				data = data.substring(0, cls.idx) + data.substring(reg.lastIndex);
				reg.lastIndex = cls.idx;

				//trace("\t\t" + (cls.struct ? "Struct" : (cls.enum ? "Enum" : "Class")) + ": " + cls.name);
				cls.file = framework.Include ? framework.Include : file;
				classes[cls.name] = cls;
			}
		}
	}

	return classes;

	function get_block(data, idx)
	{
		var idx_semicolon = data.indexOf(";", idx);
		var idx_leftcurly = data.indexOf("{", idx);
		var idx_rightcurly = idx;
		if(idx_leftcurly != -1 && idx_leftcurly < idx_semicolon)
		{
			var count = 0;
			do
			{
				idx_rightcurly = data.indexOf("}", idx_rightcurly + 1);
				while(idx_leftcurly != -1 && idx_leftcurly < idx_rightcurly)
				{
					idx_leftcurly = data.indexOf("{", idx_leftcurly + 1);
					count++;
				}
			} while(--count);
			return data.substring(idx, idx_rightcurly + 1);
		}
		return data.substring(idx);
	}

	function skip_block(data, idx0, idx1)
	{
		var idx_semicolon = data.indexOf(";", idx1);
		var idx_leftcurly = data.indexOf("{", idx1);
		var idx_rightcurly = idx1;
		if(idx_leftcurly != -1 && idx_leftcurly < idx_semicolon)
		{
			var count = 0;
			do
			{
				idx_rightcurly = data.indexOf("}", idx_rightcurly + 1);
				while(idx_leftcurly != -1 && idx_leftcurly < idx_rightcurly)
				{
					idx_leftcurly = data.indexOf("{", idx_leftcurly + 1);
					count++;
				}
			} while(--count);
			return data.substring(0, idx0) + data.substring(idx_rightcurly);
		}
		return data.substring(0, idx0) + data.substring(idx1);
	}

	function parse_type(s)
	{
		var smb = {};
		if(!s) s = "undefined";
		smb.isPointer = (s.indexOf("*") != -1);
		s = s.replace(/&/mg, "");
		s = s.replace(/\*/mg, "");
		s = s.replace(/\bconst\b/mg, "");
		s = s.trim();
		switch(s)
		{
		case "void":
			if(smb.isPointer) s = "Object";
			else s = "undefined";
			break;
		case "int":
		case "int8":
		case "int16":
		case "int32":
		case "uint":
		case "uint8":
		case "uint16":
		case "uint32":
		case "signed int":
		case "unsigned int":
		case "signed short":
		case "unsigned short":
			s = "Integer";
			break;
		case "float":
		case "float32":
		case "float64":
			s = "Float";
			break;
		case "bool":
			s = "Boolean";
			break;
		}
		smb.vartype = s;
		smb.subtype = "";
		return smb;
	}

	function parse_class(m, d)
	{
		var match = m.exec(d);
		if(!match) return null;
		var smb = { idx: match.index };
		smb.name = match[2];
		smb.struct = match[1] == "struct";
		smb.enum = match[1] == "enum";
		smb.methods = [];
		smb.members = [];
		smb.bases = [];
		smb.base = null;
		if(match[3])
		{
			var basesStrs = match[3].split(",");
			for(var i = basesStrs.length; i--;)
			{
				var spl = basesStrs[i].trim().split(" ");
				smb.base = spl[spl.length - 1];
				smb.bases.push(smb.base);
			}
		}
		var data = get_block(d, m.lastIndex - 1);

		if(smb.enum)
		{
			var reg = new RegExp(cpp_enum_member_pattern, "gm");
			for(var enu = parse_enum_member(reg, data); enu; enu = parse_enum_member(reg, data))
			{
				data = skip_block(data, enu.idx, reg.lastIndex - 1);
				reg.lastIndex = enu.idx;

				//trace("\t\t\tEnum Value: " + enu.name);
				smb.members.push(enu);
			}
		}
		else
		{
			var reg = new RegExp(cpp_constructor_pattern.replace("$CLASSNAME", smb.name), "gm");
			for(var con = parse_method(reg, data); con; con = parse_method(reg, data))
			{
				data = skip_block(data, con.idx, reg.lastIndex - 1);
				reg.lastIndex = con.idx;

				//trace("\t\t\tConstructor: " + con.name);
				smb.methods.push(con);
			}

			reg = new RegExp(cpp_constructor_pattern.replace("$CLASSNAME", "~" + smb.name), "gm");
			for(var des = parse_method(reg, data); des; des = parse_method(reg, data))
			{
				data = skip_block(data, des.idx, reg.lastIndex - 1);
				reg.lastIndex = des.idx;

				//trace("\t\t\tDestructor: " + des.name);
				smb.methods.push(des);
			}

			reg = new RegExp(cpp_method_pattern, "gm");
			for(var mth = parse_method(reg, data); mth; mth = parse_method(reg, data))
			{
				data = skip_block(data, mth.idx, reg.lastIndex - 1);
				reg.lastIndex = mth.idx;

				//trace("\t\t\tMethod: " + mth.name);
				smb.methods.push(mth);
			}

			reg = new RegExp(cpp_member_pattern, "gm");
			for(var mbr = parse_member(reg, data); mbr; mbr = parse_member(reg, data))
			{
				data = data.substring(0, mbr.idx) + data.substring(reg.lastIndex);
				reg.lastIndex = mbr.idx;

				//trace("\t\t\tMember: " + mbr.name);
				smb.members.push(mbr);
			}
		}
		return smb;
	}

	function parse_method(m, d)
	{
		var match = m.exec(d);
		if(!match) return null;
		var returntype = parse_type(match[2]);
		var smb = { idx: match.index };
		smb.virtual = (match[1] == "virtual");
		smb.name = match[3];
		smb.vartype = returntype.vartype;
		smb.subtype = returntype.subtype;
		smb.arguments = [];
		var args = match[4].split(",");
		for(var i = 0; i < args.length; i++)
		{
			if(!args[i]) continue;
			var idx = args[i].lastIndexOf(" ");
			if(idx == -1)
				return null;
			var argName = args[i].substr(idx + 1);
			var argType = parse_type(args[i].substr(0, idx));
			smb.arguments.push({
				name: argName,
				vartype: argType.vartype,
				subtype: argType.subtype
			});
		}
		return smb;
	}

	function parse_member(m, d)
	{
		var match = m.exec(d);
		if(!match) return null;
		var type = parse_type(match[1]);
		var smb = { idx: match.index };
		smb.name = match[2];
		smb.vartype = type.vartype;
		smb.subtype = type.subtype;
		return smb;
	}

	function parse_enum_member(m, d)
	{
		var match = m.exec(d);
		if(!match) return null;
		var smb = { idx: match.index };
		smb.name = match[1];
		smb.value = match[2];
		return smb;
	}
}