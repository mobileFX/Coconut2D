﻿/* ***** BEGIN LICENSE BLOCK *****
 *
 * Copyright (C) 2013-2017 www.mobilefx.com
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
//	   ______              ______                           __                ____  __            _
//	  / ____/__    __     / ____/__  ____  ___  _________ _/ /_____  _____   / __ \/ /_  ______ _(_)___
//	 / /  __/ /___/ /_   / / __/ _ \/ __ \/ _ \/ ___/ __ `/ __/ __ \/ ___/  / /_/ / / / / / __ `/ / __ \
//	/ /__/_  __/_  __/  / /_/ /  __/ / / /  __/ /  / /_/ / /_/ /_/ / /     / ____/ / /_/ / /_/ / / / / /
//	\____//_/   /_/     \____/\___/_/ /_/\___/_/   \__,_/\__/\____/_/     /_/   /_/\__,_/\__, /_/_/ /_/
//	                                                                                    /____/
// ==================================================================================================================================
// This code transforms an AST to C++ .hpp and .cpp files.
// Since CocoScript is strongly typed and very similar to C++, the generation is straight forward.
// The generated code is used by Coconut2D IDE in conjunction with the Coconut2D Device Wrappers.
// Please send bugs/suggestions to elias.politakis@mobilefx.com

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function CompilerCppPlugin(compiler)
{
	//trace("+ Loaded CocoScript Compiler C++ Generator Plugin");

	var _this = this._this = compiler;

	_this.classList 	= {};
	_this.in_setter 	= false;
	_this.in_event_call = false;
	_this.NULL_GEN 		= { CPP:"", HPP:"" };
	_this.currClass 	= null;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.cpp_types =
	{
		"Boolean"	: { "default": "false" },
		"Function"	: {	"default": "nullptr" },
		"Null"		: { "default": "nullptr" },
		"Number"	: {	"default": "0" },
		"Float"		: { "default": "0.0f" },
		"Integer"	: { "default": "0" },
		"Object"	: { "default": "nullptr" },
		"String"	: { "default": '""' }
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.generate_shaders_cpp = function(CPP, ast, classSymbol)
	{
		var file,shader;

		// Vertex Shader
		file = _this.SHADERS_PATH + "/" + classSymbol.name + ".vert";
		shader = read(file);
		if(shader)
		{
			shader = shader.replace(/[\n\r]+/g,"\\n");
			CPP.push('vertex_shader = "' + shader + '";');
		}

		// Fragment Shader
		file = _this.SHADERS_PATH + "/" + classSymbol.name + ".frag";
		shader = read(file);
		if(shader)
		{
			shader = shader.replace(/[\n\r]+/g,"\\n");
			CPP.push('fragment_shader = "' + shader + '";');
		}
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.generate_cpp = function(ast)
	{
		var _this = this, CPP = [], HPP = [], ast = ast || _this.ast;

		if(ast.__CONDITIONS)
		{
			if(!_this.evalCondition(ast.__CONDITIONS))
				return _this.NULL_GEN;
		}

		var generate_cpp = function()
		{
			return _this.generate_cpp.apply(_this, Array.prototype.slice.call(arguments,0));
		};

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		switch(ast.type)
		{
		// ==================================================================================================================================
		//	    _   _____    __  ______________ ____  ___   ____________
		//	   / | / /   |  /  |/  / ____/ ___// __ \/   | / ____/ ____/
		//	  /  |/ / /| | / /|_/ / __/  \__ \/ /_/ / /| |/ /   / __/
		//	 / /|  / ___ |/ /  / / /___ ___/ / ____/ ___ / /___/ /___
		//	/_/ |_/_/  |_/_/  /_/_____//____/_/   /_/  |_\____/_____/
		//
		// ==================================================================================================================================
		/*@@ NAMESPACE @@*/

		case jsdef.NAMESPACE:
			if(!ast.__VARIABLES.export_native) return _this.NULL_GEN;
			break;

		// ==================================================================================================================================
		//	   _____ __                  __
		//	  / ___// /________  _______/ /_
		//	  \__ \/ __/ ___/ / / / ___/ __/
		//	 ___/ / /_/ /  / /_/ / /__/ /_
		//	/____/\__/_/   \__,_/\___/\__/
		//
		// ==================================================================================================================================
		/*@@ STRUCT @@*/

		case jsdef.STRUCT:

			if(!ast.__VARIABLES.export_native) return _this.NULL_GEN;

			var items = [];
			var clone = [];
			var init = [];
			for(item in ast)
			{
				if(!isFinite(item)) break;
				var field =  ast[item];
				items.push("\t" + _this.VTCPP(field.vartype) + " " + field.name + ";");
				var value = field.symbol.value;
				if(value==null) value = "nullptr";
				if(value=='""') value = 'String("")';
				clone.push( "\t\t" + field.name + " = T->" + field.name + ";");
				init.push( "\t\t" + field.name + " = " + _this.getDefaultVartypeValueCPP(field.vartype) + ";");
			}
			items.push("\t" + ast.name + "()\n\t{" + init.join("\n") + "\n\t};");
			items.push("\t" + ast.name + "(" + ast.name + "* T)\n\t{\n" + clone.join("\n") + "\n\t};");
			HPP.push("struct " + ast.name + "\n{\n" + items.join("\n") + "\n\t};");

			// Push code into native file node
			var native_file = _this.native_files[ast.symbol.file];
			native_file.hpp.body.push(formatCPP(HPP.join("")));
			native_file.cpp.body.push(formatCPP(CPP.join("")));
			break;

		// ==================================================================================================================================
		//	   ________
		//	  / ____/ /___ ___________
		//	 / /   / / __ `/ ___/ ___/
		//	/ /___/ / /_/ (__  |__  )
		//	\____/_/\__,_/____/____/
		//
		// ==================================================================================================================================
		/*@@ CLASS @@*/

		case jsdef.INTERFACE:
		case jsdef.CLASS:

			if(!ast.scope) return _this.NULL_GEN;
			if(!ast.__VARIABLES.export_native) return _this.NULL_GEN;

		 	_this.currClassName = ast.name;

			// Add class to class list
		 	if(ast.file!="externs.jspp")
		 		_this.classList[ast.name] = ast;

			var ext = [];
			if(ast.symbol.base) ext.push("public " + ast.symbol.base + (ast.symbol.subtype ? ("<" + ast.symbol.subtype + (_this.isPointer(ast.symbol.subtype) ? "*" : "") + ">") : ""));
			for(var i = 0; i < ast.symbol.interfaces.length; i++)
				ext.push("public " + ast.symbol.interfaces[i]);

			HPP.push("class " + ast.name + (ext.length ? " : " + ext.join(",") : "") + "\n{\npublic:\n");

			var result;

			for(var item in ast.body)
			{
				if(!isFinite(item)) break;
				if(ast.body[item].type==jsdef.FUNCTION && ast.body[item].name=="Constructor")
				{
					ast.isConstructor = ast.body[item];
					break;
				}
			}

			for(var item in ast.body)
			{
				if(!isFinite(item)) break;
				switch(ast.body[item].type)
				{
				case jsdef.CONST:
					result = generate_cpp(ast.body[item]);
					HPP.push(result.HPP);
					break;
				case jsdef.ENUM:
					result = generate_cpp(ast.body[item]);
					HPP.push(result.HPP);
					break;
				case jsdef.VAR:
				case jsdef.EVENT:
					result = generate_cpp(ast.body[item]);
					CPP.push(result.CPP);
					HPP.push(result.HPP);
					break;
				}
			}

			// Delegates
			for(var item in ast.symbol.vars)
			{
				var delegator = ast.symbol.vars[item];
				if(delegator.delegate)
				{
					var cls = _this.getClass(delegator.vartype);

					for(member in cls.vars)
					{
						if(member=="__className") continue;
						var delegatorVarSymbol = cls.vars[member];
						if(!delegatorVarSymbol.public) continue;
						if(delegatorVarSymbol.static) continue;
						if(delegatorVarSymbol.type==jsdef.STATE) continue;
						if(delegatorVarSymbol.type==jsdef.CONST) continue;

						var fnName = delegatorVarSymbol.name;
						var hasSetter = (delegatorVarSymbol.type!=jsdef.CONST && (delegatorVarSymbol.type==jsdef.VAR || (delegatorVarSymbol.type==jsdef.PROPERTY && delegatorVarSymbol.ast.setter)));
						var vt = _this.VTCPP(delegatorVarSymbol.vartype);

						// Create the delegation HPP wrapper
						HPP.push( vt + " __get_" + fnName + "();" );
						if(hasSetter) HPP.push( "void __set_" + fnName + "(" + vt + " v);" );

						// Create the delegation CPP wrapper
						CPP.push(_this.SEPARATOR);
						CPP.push(vt + " " + _this.currClassName+"::__get_" + fnName + "() { return " + delegator.name + "->__get_" + fnName + "()" + "; }");
						if(hasSetter) CPP.push("void " + _this.currClassName+"::__set_" + fnName + "(" + vt + " v) { " + delegator.name + "->__set_" + fnName + "(v)" + ";}");
					}

					for(member in cls.methods)
					{
						// Get delegate function
						var delegatorFunctionSymbol = cls.methods[member];

						// If delegate function is not public or if it is static or abstract, continue
						if(!delegatorFunctionSymbol.public) continue;
						if(delegatorFunctionSymbol.static) continue;
						if(delegatorFunctionSymbol.abstract) continue;

						// Get delegate function name
						var fnName = delegatorFunctionSymbol.overloads && delegatorFunctionSymbol.overloads.length ? delegatorFunctionSymbol.overloads[0].name : delegatorFunctionSymbol.name;

						// No delegation for constructor or destructor
						if(fnName=="Constructor") continue;
						if(fnName=="Destructor") continue;

						// Get params list and build argumetns
						var paramsList = delegatorFunctionSymbol.__untypedParamsList;
						var args = [];
						for(var i=0; i<delegatorFunctionSymbol.paramsList.length; i++)
						{
							var p = delegatorFunctionSymbol.paramsList[i];
							args.push((p.optional ? "const " : "") + _this.VTCPP(p.vartype) + " " + p.name + (p.optional ? " = " + _this.getDefaultVartypeValue(p.vartype) : ""));
						}

						// Create the delegation HPP wrapper
						var wrapper = (delegatorFunctionSymbol.vartype ? delegatorFunctionSymbol.vartype : "void") + " " + fnName + "(" + args.join(", ") + ");";
						HPP.push(wrapper);
						args = [];
						for(var i=0; i<delegatorFunctionSymbol.paramsList.length; i++)
						{
							var p = delegatorFunctionSymbol.paramsList[i];
							args.push(_this.VTCPP(p.vartype) + " " + p.name);
						}

						// Create the delegation CPP wrapper
						wrapper = (delegatorFunctionSymbol.vartype ? delegatorFunctionSymbol.vartype : "void") + " " + ast.name + "::" + fnName + "(" + args.join(", ") + ")";
						wrapper += "{ if(" + delegator.name + ") { ";
						if(delegatorFunctionSymbol.vartype) wrapper += "return ";
						wrapper += delegator.name + "->" + fnName + delegatorFunctionSymbol.__untypedParamsList + ";";
						wrapper += (delegatorFunctionSymbol.vartype ? "" : "return;") + " } else { return";
						wrapper += (delegatorFunctionSymbol.vartype ? " " +_this.getDefaultVartypeValue(delegatorFunctionSymbol.vartype) : "") + "; }}";
						CPP.push(_this.SEPARATOR+wrapper);
					}
				}
			}

			for(var item in ast.body)
			{
				if(!isFinite(item)) break;
				switch(ast.body[item].type)
				{
				case jsdef.PROPERTY:
				case jsdef.STATE:
				case jsdef.FUNCTION:
					result = generate_cpp(ast.body[item]);
					if(result.CPP) CPP.push(result.CPP);
					if(result.HPP) HPP.push(result.HPP);
					break;
				}
			}

			// Add Public Virtual Destructon in Interfaces
			if(ast.symbol.interface)
			{
				HPP.push("virtual ~" + ast.symbol.name + "(){}");
			}

			//TODO: Derivative Casting Helper for STL container tranformations
			//if(ast.symbol.base && !ast.symbol.subtype)
			//{
			//	var cast = "D* __convert_B_to_D(B* in) { return dynamic_cast<D*>(in); }\n" +
			//			   "transform(VB->begin(), VB->end(), back_insert_iterator<vector<D*> >(*VD), __convert_B_to_D);";
			//}

			/*@@ CLASS:EVENTS @@*/

			// Create events dispatch static function with dispatch switch.
			if(!ast.interface && _this.implementsInterface(ast.symbol, "IEventListener"))
			{
				var hasDispIds = false;
				var classSymbol = ast.symbol;
				for(var uid in classSymbol.__event_descriptors) { hasDispIds=true; break; }

				// ==================================================================
				// Create event handler Dispatch ID constants
				// ==================================================================
				var list = [].concat(classSymbol.__event_bindings).concat(classSymbol.__event_unbindings);
				for(i=0;i<list.length;i++)
				{
					var event_ast = list[i];
					var ebd = event_ast.__event_descriptor;
					_this.native_files['Constants.jspp'].hpp.dispIds[ebd.uid] = "#ifndef " + ebd.uid + "\n#define " + ebd.uid + " " + ebd.id + "\n#endif\n";
				}

				// ========================================================================
				// Create dispatchEvent function:
				// ------------------------------------------------------------------------
				// It is the "bridge" function called from event source to pass the
				// event to event listener and it is implemented in the event listener.
				// ========================================================================

				var local_handler = "dispatchEvent(CocoEvent* Event)";

				if(!hasDispIds)
				{
					if(ast.name=="CocoClip")
					{
						HPP.push("virtual void " + local_handler + ";");

						CPP.push("\n////////////////////////////////////////////////////////////////////////////////////////////////////\n");
						CPP.push("void " + ast.name + "::" + local_handler + "\n{");
						CPP.push("}");
					}
				}
				else
				{
					HPP.push("virtual void " + local_handler + ";");

					CPP.push("\n////////////////////////////////////////////////////////////////////////////////////////////////////\n");
					CPP.push("void " + ast.name + "::" + local_handler + "\n{");

					if(hasDispIds)
					{

						CPP.push("\tfor(int i = __eventListeners->size() - 1; i>=0; i--)\n\t{\n\t\tCocoEventConnectionPoint* cp = (*__eventListeners)[i];\n");
						CPP.push("\t\tif(cp->Event->is(Event))\n\t\t{\n\t\tbool cancel = false;");

						// Create dispatch switch:

						CPP.push("switch(cp->DispID)\n{");
						{
							for(var uid in classSymbol.__event_descriptors)
							{
								var ebd = classSymbol.__event_descriptors[uid];
								CPP.push("case " + ebd.uid+ ":\n{\n");
								{
									CPP.push(ebd.event_listener.name + "* L = reinterpret_cast<"+ebd.event_listener.name+"*>(cp->Listener);");
									CPP.push("//Event Listener\n");

									CPP.push(ebd.event_handler.paramsList[0].vartype + "* S = reinterpret_cast<"+ebd.event_handler.paramsList[0].vartype+"*>(this);");
									CPP.push("//Event Source type-casted to what event handler argument needs\n");

									CPP.push(ebd.event_symbol.name + "* E = reinterpret_cast<"+ebd.event_symbol.name+"*>(Event);");
									CPP.push("//Event object type-casted to what event handler argument needs\n");

									// Collect event handler flat arguments
									var flat_arguments = [];
									for(j=2;j<ebd.event_handler.paramsList.length;j++)
									{
										var event_parm = ebd.event_handler.paramsList[j];
										flat_arguments.push("E->"+event_parm.name);
										//CPP.push(_this.VTCPP(event_parm.vartype) + event_parm.name + " = E->" + event_parm.name + ";");
									}
									flat_arguments = (flat_arguments.length>0 ? ", " + flat_arguments.join(", ") : "");

									// Make the call to the event handler
									CPP.push("cancel = L->" + ebd.event_handler.name + "(S,E"+flat_arguments+");");

								}
								CPP.push("}\n");
								CPP.push("break;\n");
							}
							CPP.push("}\n");
						}

						CPP.push("\tif(cancel)\n\t{\n\t\tcp->Event->cancelBubble();\n\t}\n\tif(cp->Event->stopPropagation)\n\t{\n\t\treturn;\n\t}\n}\n}");
					}

					// Call base class dispatchEvent
					if(classSymbol.baseSymbol.name!="CocoEventSource")
						CPP.push(classSymbol.baseSymbol.name + "::dispatchEvent(Event);\n");

					CPP.push("}\n");
				}
			}

			HPP.push("};\n");
			_this.currClassName = null;

			// Push code into native file node
			var native_file = _this.native_files[ast.symbol.file];
			native_file.hpp.body.push(formatCPP(HPP.join("")));
			native_file.cpp.body.push(formatCPP(CPP.join("")));
			break;

		// ==================================================================================================================================
		//	   ______      ______               __      ____       _____       _ __  _
		//	  / ____/___ _/ / / /_  ____ ______/ /__   / __ \___  / __(_)___  (_) /_(_)___  ____
		//	 / /   / __ `/ / / __ \/ __ `/ ___/ //_/  / / / / _ \/ /_/ / __ \/ / __/ / __ \/ __ \
		//	/ /___/ /_/ / / / /_/ / /_/ / /__/ ,<    / /_/ /  __/ __/ / / / / / /_/ / /_/ / / / /
		//	\____/\__,_/_/_/_.___/\__,_/\___/_/|_|  /_____/\___/_/ /_/_/ /_/_/\__/_/\____/_/ /_/
		//
		// ==================================================================================================================================
		/*@@ CALLBACK @@*/

		case jsdef.CALLBACK:

			if(!ast.__VARIABLES.export_native) return _this.NULL_GEN;

			var name = ast.name;
			var param, ParamList = "(";

			for(var i=0; i < ast.paramsList.length; i++)
			{
				param = ast.paramsList[i];
				ParamList += _this.VTCPP(param.vartype);
				if(i!=ast.paramsList.length-1)
					ParamList +=", ";
			}
			ParamList += ")";

			//var fn = "typedef " + _this.VTCPP(ast.returntype) + " (" + name + ")" + ParamList + ";";
			var fn = "#define " + name + " std::function<" + _this.VTCPP(ast.returntype) + ParamList + ">";

			var native_file = _this.native_files['Constants.jspp'];
			native_file.hpp.body.push(fn);
			return _this.NULL_GEN;

		// ==================================================================================================================================
		//	    ______                 __  _
		//	   / ____/_  ______  _____/ /_(_)___  ____
		//	  / /_  / / / / __ \/ ___/ __/ / __ \/ __ \
		//	 / __/ / /_/ / / / / /__/ /_/ / /_/ / / / /
		//	/_/    \__,_/_/ /_/\___/\__/_/\____/_/ /_/
		//
		// ==================================================================================================================================
		/*@@ FUNCTION @@*/

		case jsdef.FUNCTION:

			if(ast.type!=jsdef.CALLBACK)
			{
				if(!ast.__VARIABLES.export_native) return _this.NULL_GEN;
				if(!_this.currClassName) return _this.NULL_GEN;
			}

			_this.currFunction = ast;

			var name = (ast.isConstructor ? _this.currClassName : (ast.isDestructor ? "~" + _this.currClassName : ast.name ));
			var param, cppParamsList = "(", hppParamList = "(";

			for(var i=0; i<ast.paramsList.length; i++)
			{
				param = ast.paramsList[i];

				var vt = _this.VTCPP(param.vartype);
				var cpp_param = vt + " " + param.name;

				var def = "nullptr";
				if(param.optional)
				{
					if(param.initializer)
					{
						def = generate_cpp(param.initializer).CPP;
					}
					else if(_this.cpp_types.hasOwnProperty(param.vartype))
					{
						def = _this.cpp_types[param.vartype].default;
					}
					else if(_this.isEnum(param.vartype))
					{
						def = "(" + param.vartype + ")0";
					}
				}

				cppParamsList += cpp_param;
				hppParamList += cpp_param + (param.optional ? "=" + def : "");
				if(i!=ast.paramsList.length-1)
				{
					cppParamsList +=", ";
					hppParamList +=", ";
				}
			}

			if(!ast.symbol)
				ast.symbol = _this.LookupScopeChain(ast.name, ast.inClass.scope, true);

			// Rest arguments
			if(ast.symbol.restArguments)
			{
				hppParamList+=", ...";
				cppParamsList+=", ...";
			}

			cppParamsList += ")";
			hppParamList += ")";

			var fn = "";
			var return_type = null;

			if(ast.lambda)
			{
				return_type = _this.VTCPP(ast.returntype);

				fn = "[=]" + hppParamList + " mutable " + (return_type ?  "->" + return_type : "");
			}
			else if(ast.type==jsdef.CALLBACK)
			{
				return_type = _this.VTCPP(ast.returntype);

				fn = (return_type ? return_type + " " : "") +
				     name +
				     hppParamList +
				     ";";
			}
			else
			{
				return_type = _this.VTCPP(ast.returntype);
				if(ast.isConstructor || ast.isDestructor) return_type = null;

				fn = (ast.static ? "static " :"") +
				     (ast.symbol.virtual ? "virtual " : "") +
				     (return_type ? return_type + " " : "") +
				     name +
				     hppParamList +
				     (ast.symbol.abstract ? "=0":"") +";";

				HPP.push(fn);
			}

			if(!ast.symbol.abstract && ast.inClass && !ast.inClass.symbol.interface)
			{
		        if(!ast.lambda)
		        {
		        	CPP.push("\n////////////////////////////////////////////////////////////////////////////////////////////////////\n");

					CPP.push(  (return_type ? return_type + " " : "") +
							   _this.currClassName+"::" +
							   (_this.in_state ? ast.symbol.scope.parentScope.ast.name + "::" : "") +
							   name +
							   cppParamsList);

					if(ast.isConstructor && ast.inClass.base_init)
					{
						var baseConstructorArguments = [];
						for(var item in ast.inClass.base_init[1])
						{
							if(!isFinite(item)) break;
							var arg = ast.inClass.base_init[1][item];
							if(arg.type==jsdef.IDENTIFIER)
							{
								baseConstructorArguments.push(arg.value);
							}
							else
							{
								var gen = _this.generate_cpp(arg);
								baseConstructorArguments.push(gen.CPP);
							}
						}
						CPP.push(" : " + ast.inClass.extends + "(" + formatCPP(baseConstructorArguments.join(",")) + ")");
					}
		        }
		        else
		        {
		        	CPP.push(fn);
		        }

		        CPP.push("\n{\n");

		        if(ast.isConstructor)
		        {
		        	CPP.push('__className = String("' + ast.inClass.symbol.name + '");');

		        	for(item in ast.inClass.symbol.events)
		        	{
		        		var ev = ast.inClass.symbol.events[item];
		        		CPP.push("this->"+ev.runtime+" = new " + ev.vartype + ";");
		        	}

		        	// Compiler Hack: inject GLSL
		        	if(makefile.Vars.COCONUT2D_ANIMATION && ast.inClass.symbol && (ast.inClass.symbol.name.indexOf("Shader")!=-1))
		        	{
		        		_this.generate_shaders_cpp(CPP, ast, ast.inClass.symbol);
		        	}

		        }

		        if(ast.isDestructor)
		        {
		        	for(item in ast.inClass.symbol.events)
		        	{
		        		var ev = ast.inClass.symbol.events[item];
		        		var id = "this->"+ev.runtime;
		        		CPP.push("if(" + id + ") " + id + " = (delete " + id + ", nullptr);");
		        	}
		        }

		        // Rest Arguments to std::vector<> arguments
		        if(ast.symbol.restArguments)
		        {
		        	var param = ast.paramsList[0];
		        	var vt = _this.VTCPP(ast.symbol.restArgumentsVartype);
		        	if(vt=="String") vt = "char*";
		   			CPP.push("Array<" + vt + "> __arguments;");
		   			CPP.push("Array<" + vt + ">* arguments = &__arguments;");
					CPP.push("va_list vl;");
					CPP.push("va_start(vl," + param.name + ");");
					CPP.push("for(int32_t i=0;i<" + param.name + ";i++)");
					CPP.push("__arguments.push_back(va_arg(vl," + vt + "));");
					CPP.push("va_end(vl);");
		        }

		        if(ast.body)
					CPP.push(generate_cpp(ast.body).CPP);

				CPP.push("}\n");
			}

			_this.currFunction = null;

			if(ast.type==jsdef.CALLBACK)
			{
				var native_file = _this.native_files['Constants.jspp'];
				native_file.hpp.body.push(fn);
				return _this.NULL_GEN;
			}

			break;

		// ==================================================================================================================================
		//	 _    __           _       __    __
		//	| |  / /___ ______(_)___ _/ /_  / /__  _____
		//	| | / / __ `/ ___/ / __ `/ __ \/ / _ \/ ___/
		//	| |/ / /_/ / /  / / /_/ / /_/ / /  __(__  )
		//	|___/\__,_/_/  /_/\__,_/_.___/_/\___/____/
		//
		// ==================================================================================================================================
		/*@@ VAR @@*/

		case jsdef.VAR:
		case jsdef.CONST:

			if(!ast.__VARIABLES.export_native) return _this.NULL_GEN;
	        var isConst = (ast.type == jsdef.CONST) && !(ast.__rtti && ast[0].name == "__className");

			// Var as class member
			if(ast.inClass && !ast.inFunction && !ast.scope.isState)
			{
				for(i=0;i<ast.length;i++)
				{
					if(ast[i].name == "__className" && ast.inClass.symbol.base)	continue;

					if(isConst && !ast.static)
					{
						val = "const " + _this.VTCPP(ast[i].vartype) + " " + ast[i].name + initializer(ast[i]) + ";";
						HPP.push(val);
					}
					else if(ast.static)
					{
						// static var needs to be defined in .cpp as well
						val = _this.VTCPP(ast[i].vartype) + " " + _this.currClassName + "::" + ast[i].name + initializer(ast[i]) + ";";
						CPP.push(val);

						val = "static " + (isConst ? "constexpr " : "") + _this.VTCPP(ast[i].vartype) + " " + ast[i].name + (!isConst ? "" : initializer(ast[i])) + ";";
						HPP.push(val);
					}
					else
					{
						val = _this.VTCPP(ast[i].vartype) + " " + ast[i].name + ";";
						HPP.push(val);
					}
				}
			}

			// Var in for(;;)
			else if(_this.__inFor)
			{
				CPP.push(_this.VTCPP(ast[0].vartype) + " ");
				for(i=0;i<ast.length;i++)
				{
					val = ast[i].name + initializer(ast[i]) + (i<ast.length-1 ? ", " : "");
					CPP.push(val);
				}
			}

			// Var in state
			else if(ast.scope.isState)
			{
				for(i=0;i<ast.length;i++)
				{
					val = _this.VTCPP(ast[i].vartype) + " " + ast[i].name + initializer(ast[i]) + ";";
					HPP.push(val);
				}
			}

			// Var in function
			else if(ast.inFunction)
			{
				for(i=0;i<ast.length;i++)
				{
					val = _this.VTCPP(ast[i].vartype) + " " + ast[i].name + initializer(ast[i]) + ";";
					CPP.push(val);
				}
			}

			// Var in global
			else
			{
				for(i=0;i<ast.length;i++)
				{
					val = "#ifndef " + ast[i].name + "\n#define " + ast[i].name+ " " + initializer(ast[i]).replace("=", "") + "\n#endif\n";
					_this.native_files['Constants.jspp'].hpp.constants[ast[i].name] = val;
				}
			}

			//==================================================================
			// Get value initializer or default value
			function initializer(vitem)
			{
				var init;

				if(vitem.initializer)
				{
					//#TYPECAST
					var rhs = _this.typeCastCPP(vitem.initializer, generate_cpp(vitem.initializer).CPP);
					return " = " + rhs;
				}
				else
				{
					var vartype = _this.getVarType(vitem.vartype);

					if(_this.cpp_types.hasOwnProperty(vartype))
						return " = " + _this.cpp_types[vartype].default;

					else if(vitem.symbol.pointer)
						return " = nullptr";

					else if(ast.scope.isClass)
						return "";

					else
						return "";
				}
			}

			break;

		// ==================================================================================================================================
		//	    ______                 __
		//	   / ____/   _____  ____  / /______
		//	  / __/ | | / / _ \/ __ \/ __/ ___/
		//	 / /___ | |/ /  __/ / / / /_(__  )
		//	/_____/ |___/\___/_/ /_/\__/____/
		//
		// ==================================================================================================================================
		/*@@ EVENT @@*/

		case jsdef.EVENT:

			if(!ast.__VARIABLES.export_native) return _this.NULL_GEN;
			if(!_this.currClassName) return _this.NULL_GEN;

			// Define event class
			HPP.push("// Event " + _this.currClassName + "::" + ast.event_class_symbol.runtime + "\nclass " + ast.event_class_symbol.name + " : public CocoEvent\n{\npublic:\n");

			// Event params
			for(item in ast.event_class_symbol.vars)
			{
				var field = ast.event_class_symbol.vars[item].ast;
				HPP.push("\n\t"+ _this.VTCPP(field.vartype) + " " + field.name +";");
			}

			// Event constructor and initialization of params
			HPP.push(ast.event_class_symbol.name + "() : CocoEvent(\"" + ast.symbol.name + "\", true, true)\n{");
			for(item in ast.event_class_symbol.vars)
			{
				var field = ast.event_class_symbol.vars[item].ast;
				var def = "nullptr";
				var vt = _this.getVarType(field.vartype);

				if(_this.cpp_types.hasOwnProperty(vt))
					def = _this.cpp_types[vt].default;

				else if(_this.isEnum(vt))
					def = _this.enumDefault(vt, true);

				HPP.push(field.name + " = " + def + ";");
			}
			HPP.push("\n}");

			HPP.push("\n};\n");

			// Add event class to hpp file
			_this.native_files[ast.file].hpp.body.insert(0, formatCPP(HPP.join("")));
			_this.native_files[ast.file].classes[ast.event_class_symbol.name]=ast.event_class_symbol;

			// Declare an event object in the class
			HPP=[];
			HPP.push(ast.event_class_symbol.name + "* " + ast.symbol.name +"; // Event\n");
			break;

		// ==================================================================================================================================
		//	    ______
		//	   / ____/___  __  ______ ___  _____
		//	  / __/ / __ \/ / / / __ `__ \/ ___/
		//	 / /___/ / / / /_/ / / / / / (__  )
		//	/_____/_/ /_/\__,_/_/ /_/ /_/____/
		//
		// ==================================================================================================================================
		/*@@ ENUM @@*/

		case jsdef.ENUM:

			if(!ast.__VARIABLES.export_native) return _this.NULL_GEN;

			HPP.push("\nenum " + ast.name + " {\n");
			var firstItem = true;
			for(item in ast)
			{
				if(!isFinite(item)) break;
				if(!firstItem) HPP.push("," + "\n");
				HPP.push(ast[item].name + " = " + ast[item].value);
				firstItem = false;
			}
			HPP.push("\n};\n");

			// Push code into native file node
			var native_file = _this.native_files['Constants.jspp'];//_this.native_files[ast.symbol.file];
			native_file.hpp.body.push(formatCPP(HPP.join("")));
			native_file.cpp.body.push(formatCPP(CPP.join("")));
			break;

		// ==================================================================================================================================
		//	    ____                             __
		//	   / __ \_________  ____  ___  _____/ /___  __
		//	  / /_/ / ___/ __ \/ __ \/ _ \/ ___/ __/ / / /
		//	 / ____/ /  / /_/ / /_/ /  __/ /  / /_/ /_/ /
		//	/_/   /_/   \____/ .___/\___/_/   \__/\__, /
		//	                /_/                  /____/
		// ==================================================================================================================================
		/*@@ PROPERTY @@*/

	    case jsdef.PROPERTY:

	    	if(!ast.__VARIABLES.export_native) return _this.NULL_GEN;
	    	if(!_this.currClassName) return _this.NULL_GEN;

	    	if(ast.getter)
	    	{
				var name = "__get_" + ast.name;
				var ret = _this.VTCPP(ast.getter.returntype);
				HPP.push((ast.static ? "static " :"") + (ast.symbol.virtual ? "virtual " : "") + ret + " " + name + "();");
		        CPP.push("\n////////////////////////////////////////////////////////////////////////////////////////////////////\n");
				CPP.push( ret + " " + _this.currClassName + "::" + (_this.in_state ? ast.symbol.scope.parentScope.ast.name + "::" : "") + name + "()");
		        CPP.push("\n{\n");
				CPP.push(generate_cpp(ast.getter.body).CPP);
				CPP.push("}\n");
	    	}
	    	if(ast.setter)
	    	{
				var name = "__set_" + ast.name;
				var param = "(" + _this.VTCPP(ast.vartype) + " " + ast.setter.paramsList[0].name + ")";
				HPP.push((ast.static ? "static " :"") + (ast.symbol.virtual ? "virtual " : "") + ("void ") + name + param + ";");
		        CPP.push("\n////////////////////////////////////////////////////////////////////////////////////////////////////\n");
				CPP.push( "void " + _this.currClassName + "::" + (_this.in_state ? ast.symbol.scope.parentScope.ast.name + "::" : "") + name + param);
		        CPP.push("\n{\n");
				CPP.push(generate_cpp(ast.setter.body).CPP);
				CPP.push("}\n");
	    	}
	    	break;

		// ==================================================================================================================================
		//	    ___________ __  ___   _____ __        __
		//	   / ____/ ___//  |/  /  / ___// /_____ _/ /____
		//	  / /_   \__ \/ /|_/ /   \__ \/ __/ __ `/ __/ _ \
		//	 / __/  ___/ / /  / /   ___/ / /_/ /_/ / /_/  __/
		//	/_/    /____/_/  /_/   /____/\__/\__,_/\__/\___/
		//
		// ==================================================================================================================================
		/*@@ STATE @@*/

		case jsdef.STATE:

		    if(!ast.__VARIABLES.export_native) return _this.NULL_GEN;
		    if(!_this.currClassName || !ast.scope) return _this.NULL_GEN;

		    _this.in_state = true;

			HPP.push("struct " + ast.name + " : State {");
			HPP.push(_this.currClassName + "* self;");
			CPP.push("\n\n//=======================================================\n");
			CPP.push("// State: " + ast.name + "\n");
			CPP.push("//=======================================================\n");
			var result;
			for(var item in ast.body)
			{
				if(!isFinite(item)) break;
				switch(ast.body[item].type)
				{
				case jsdef.CONST:
				case jsdef.VAR:
					result = generate_cpp(ast.body[item]);
					HPP.push(result.HPP);
					break;
				}
			}
			HPP.push(ast.name + "(" + _this.currClassName + "* self) : self(self) {}\n");
			for(var item in ast.body)
			{
				if(!isFinite(item)) break;
				switch(ast.body[item].type)
				{
				case jsdef.FUNCTION:
					result = generate_cpp(ast.body[item]);
					HPP.push(result.HPP);
					CPP.push(result.CPP);
					break;
				}
			}
			HPP.push("} *" + ast.name + " = new struct " + ast.name + "(this);");

	        _this.in_state = false;
			break;

		// ==================================================================================================================================
		//	    ____    __           __  _ _____
		//	   /  _/___/ /__  ____  / /_(_) __(_)__  _____
		//	   / // __  / _ \/ __ \/ __/ / /_/ / _ \/ ___/
		//	 _/ // /_/ /  __/ / / / /_/ / __/ /  __/ /
		//	/___/\__,_/\___/_/ /_/\__/_/_/ /_/\___/_/
		//
		// ==================================================================================================================================
		/*@@ IDENTIFIER @@*/

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.SUPER:
			if(_this.currClassName && _this.classList[_this.currClassName] && _this.classList[_this.currClassName].extends)
			{
				CPP.push(_this.classList[_this.currClassName].extends);
			}
			else
			{
				CPP.push("super");
			}
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.THIS:
			if(_this.currClassName && ast.inDot && ast.inDot.identifier_first == ast && ast.inDot.identifier_last.symbol.type == jsdef.FUNCTION && ast.inDot.identifier_last.symbol.virtual)
			{
				CPP.push(_this.currClassName);
			}
			else
			{
				CPP.push(_this.in_state ? "self" : "this");
			}
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.IDENTIFIER:

			var isProp = false;
			var name = ast.value.replace(/\$\d+/,'');

			if(!ast.symbol)
			{
				CPP.push(ast.value);
				break;
			}

			if(ast.symbol.delegated)
				CPP.push(ast.symbol.scope.ast.name + "->");

			if(ast.symbol.type==jsdef.FUNCTION && ast.parent.type==jsdef.LIST)
			{
				var paramList = [];
				var callList = [];
				for(var i in ast.symbol.arguments)
				{
					var arg = ast.symbol.arguments[i];
					var vt = _this.VTCPP(arg.vartype);
					paramList.push(vt + " " + arg.name);
					callList.push(arg.name);
				}
				paramList = "(" + paramList.join(",") + ")";
				callList = "(" + callList.join(",") + ")";

				var lambda = "[=]" + paramList + " mutable { " + ast.symbol.ast.scope.className + "::" + name + callList + "; }";

				CPP.push(lambda);

				break;
			}
			else if(ast.symbol.type == jsdef.PROPERTY)
			{
				CPP.push(_this.in_setter ? "__set_" : "__get_");
				isProp = true;
			}
			else if(_this.in_state)
			{
				if(ast.symbol.ast.parent.scope && ast.symbol.ast.parent.scope.isClass && (ast.parent.type != jsdef.DOT || (ast.parent[0] == ast)))
					CPP.push("self->");
				else if(ast.symbol.ast.parent.parent && ast.symbol.ast.parent.parent.scope && ast.symbol.ast.parent.parent.scope.isClass && (ast.parent.type != jsdef.DOT || (ast.parent[0] == ast)))
					CPP.push("self->");
			}

			if(ast.symbol.static && !ast.symbol.extern && !ast.symbol.enum && !ast.symbol.state && !ast.inDot)
				CPP.push(ast.symbol.scope.className+"::");

			CPP.push(name + (isProp && !_this.in_setter ? "()" : ""));
			break;

		// ==================================================================================================================================
		//	   ______      ____
		//	  / ____/___ _/ / /____
		//	 / /   / __ `/ / / ___/
		//	/ /___/ /_/ / / (__  )
		//	\____/\__,_/_/_/____/
		//
		// ==================================================================================================================================

		case jsdef.SCRIPT:
			var result;
			for(var item in ast)
			{
				if(!isFinite(item)) break;
			    result = generate_cpp(ast[item]);
				HPP.push(result.HPP);
				CPP.push(result.CPP);
			}
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.BLOCK:
			CPP.push("{\n");
			for(var item in ast)
			{
				if(!isFinite(item)) break;
				CPP.push(generate_cpp(ast[item]).CPP);
			}
			CPP.push("}\n");
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.CALL:

			if(ast[0].value=="__copy__")
			{
				if(!_this.secondPass) break;

				// Get calling method ast
				var callIdentifier = _this.getCallIdentifier(ast);
				var src_idf = _this.generate_cpp(ast[1][0]).CPP;
				var dst_idf = _this.generate_cpp(ast[1][1]).CPP;
				var props = _this.generate_cpp(ast[1][2]).CPP;
				var members = _this.getClass('COCO_OBJECT_COPY_MEMBERS_ENUM').vars[ast[1][2].value].value;

				var src_type = _this.getTypeName(ast[1][0]);
				var dst_type = _this.getTypeName(ast[1][1]);

				if(src_type!=dst_type)
					_this.NewError("Cannot copy between different types, from " + src_type + " to " + dst_type, ast);

				var cls = _this.getClass(src_type);

				var dot = "->";

				for(var item in cls.vars)
				{
					switch(item)
					{
						case "__className":
							continue;
					}

					var mbr = cls.vars[item];

					// Do not copy objects
					if(_this.isPointer(mbr.vartype)) continue;

					var clone = ((mbr.public && (members & _this.COPY_MEMBERS_PUBLIC)==_this.COPY_MEMBERS_PUBLIC) ||	(mbr.published && (members & _this.COPY_MEMBERS_PUBLISHED)==_this.COPY_MEMBERS_PUBLISHED) || (mbr.protected && (members & _this.COPY_MEMBERS_PROTECTED)==_this.COPY_MEMBERS_PROTECTED));
					if(!clone) continue;

					if(mbr.type == jsdef.PROPERTY)
					{
						if(mbr.ast.setter && mbr.ast.getter)
							CPP.push(dst_idf + dot + "__set_" + mbr.name + "(" + src_idf + dot + "__get_" + mbr.name + "());");
					}
					else
					{
						CPP.push(dst_idf + dot + mbr.name + " = " + src_idf + dot + mbr.name + ";");
					}
				}

				break;
			}

			var is_event = false;
			var call0 = generate_cpp(ast[0]).CPP;
			var scope_this = false;

			// Hack to support JSON()
			if(ast[0].__toJSON)
			{
				CPP.push(call0);
				break;
			}

			// Hack to support setInterval() and setTimeout() with classes
			if(_this.currClassName)
			{
				switch(call0)
				{
					case "setInterval":
					case "setTimeout":
						call0 += "<" + _this.currClassName + ">";
						scope_this = true;
						break;
				}
			}

			// Explicit type casting
			if(ast[1][0] && ast[1][0].__typecast_explicit)
			{
				//#TYPECAST
				CPP.push(_this.typeCastCPP(ast[1][0], generate_cpp(ast[1][0]).CPP));
			}
			else
			{
				/*@@ CALL:EVENTS @@*/

				// Dectect if we are registering/unregistering/dispatching an event
				var call_fn = _this.getCallIdentifier(ast);
				_this.in_event_call = (call_fn.__event && (call_fn.value==_this.DISPATCH_EVENT || call_fn.value==_this.ADD_EVENT || call_fn.value==_this.REMOVE_EVENT)) ? call_fn : null;

				// If we are dispatching an event we need to set event parameters
				if(_this.in_event_call && _this.in_event_call.value==_this.DISPATCH_EVENT)
				{
					is_event = true;

					CPP.push("{");

					var list = _this.getCallList(_this.in_event_call);
					var event_symbol = _this.in_event_call.__event_descriptor.event_symbol;
					var evObj = generate_cpp(list[0]).CPP; //(_this.in_state ? "self" : "this")

					CPP.push(evObj + "->reset();");
					var i=1;
					for(item in event_symbol.vars)
					{
						CPP.push(evObj + "->" + item + " = " + generate_cpp(list[i]).CPP + ";\n");
						i++;
					}
				}

				CPP.push(call0);
				CPP.push("(");

				if(scope_this)
					CPP.push((_this.in_state ? "self" : "this") + ",");

				CPP.push(generate_cpp(ast[1]).CPP);
				CPP.push(")");

				if(is_event)
				{
					CPP.push(";");
					CPP.push("}");
				}

				_this.in_event_call = null;
			}
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/*@@ LIST @@*/

		case jsdef.LIST:

			// Handle addEventListener, removeEventListener,
			// dispatchEvent for Coconut2D native events.
			if(_this.in_event_call)
			{
				/*@@ LIST:EVENTS @@*/

				switch(_this.in_event_call.value)
				{
				case _this.DISPATCH_EVENT:
					CPP.push(generate_cpp(ast[0]).CPP);
					break;

				case _this.ADD_EVENT:
					var event_descr = _this.in_event_call.__event_descriptor;
					CPP.push(generate_cpp(ast[0]).CPP + ",");
					CPP.push((_this.in_state ? "self" : "this")+",");
					CPP.push(event_descr.uid);
					break;

				case _this.REMOVE_EVENT:
					var event_descr = _this.in_event_call.__event_descriptor;
					CPP.push(generate_cpp(ast[0]).CPP + ",");
					CPP.push((_this.in_state ? "self" : "this")+",");
					CPP.push(event_descr.uid);
					break;
				}
				break;
			}

			var firstItem = true;

			//#TYPECAST
			for(var item in ast)
			{
				if(!isFinite(item)) break;
				if(!firstItem) CPP.push(", ");

				var gen = generate_cpp(ast[item]).CPP;
				gen = _this.typeCastCPP(ast[item], gen);
				CPP.push(gen);

				firstItem = false;
			}

			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.COMMA:
			for(i=0;i<ast.length;i++)
			{
				if(i>0) CPP.push(", ");
				CPP.push( generate_cpp(ast[i]).CPP);
			}
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.GROUP:
			CPP.push("(");
			for(var item in ast)
			{
				if(!isFinite(item)) break;
				CPP.push(generate_cpp(ast[item]).CPP);
			}
			CPP.push(")");
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.ARRAY_INIT:

			// We need to detect array subtype and type cast items to it

			// Cases of implicit inline array initialization:
			// 1: new Float32Array([...])
			// 2: new CocoSequence(params, [...]) or foo([...]) // handled by jsdef.CALL !!
			// 3: a = [...]
			// 4: var x:Array<T> = [...]

			var vartype, subtype;

			//===================================================================================
	        if(ast.parent.parent.type==jsdef.VAR)
	        {
	        	// var x:Array<T> = [...]
	        	vartype = ast.parent.parent[0].symbol.vartype;
	        	subtype = _this.getSubType(vartype);
	        }

			//===================================================================================
			else if(ast.parent.type==jsdef.ASSIGN)
			{
				// a = [...]
				if(ast.__typecast)
				{
					vartype = ast.__typecast;
					subtype = _this.getSubType(vartype);
				}
				else
				{
					// Should never get in here because jsdef.ASSIGN sets ast.__typecast
					debugger;
				}
			}

			//===================================================================================
			else if(ast.parent.type==jsdef.LIST)
			{
				switch(ast.parent.parent.type)
				{
				case jsdef.NEW_WITH_ARGS:

					vartype = ast.parent.parent.vartype;

					if(_this.isTypedArray(vartype))
					{
						// new Float32Array([...])
						subtype = _this.getSubType(vartype);
						break;
					}
					else
					{
						// Constructor parameter as array eg. new CocoSequence([...])
						// Fall down to jsdef.CALL ...
					}

				case jsdef.CALL:

					_this.NewWarning("Possible memory leak from array initialization within function call: " + ast.parent.parent.source, ast);

					// foo([...])
					var fn = _this.getCallIdentifier(ast.parent);
					var paramIndex = _this.getCallListParamIndex(ast);
					var paramsList = fn.symbol.paramsList ? fn.symbol.paramsList : fn.symbol.methods.Constructor.paramsList;
					vartype = paramsList[paramIndex].vartype;
					subtype = _this.getSubType(vartype);
					break;
				}
			}

			if(!subtype)
				_this.NewError("Unknown array initialization subtype: " + ast.parent.source, ast);

			// Create an std::initializerlist for array initializer
			var values = [];
			for(var i=0;i<ast.length;i++)
			{
				ast[i].__typecast = subtype;
				values.push(_this.typeCastCPP(ast[i], generate_cpp(ast[i]).CPP));
			}

			CPP.push("{");
			CPP.push(values.join(", "));
			CPP.push("}");

			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.OBJECT_INIT:
			CPP.push("{ ");
			var firstItem = true;
			for(var item in ast)
			{
				if(!isFinite(item)) break;
				if(!firstItem) CPP.push(", ");
				ast[item].parent = ast;
				CPP.push(generate_cpp(ast[item]).CPP);
				firstItem=false;
			}
			CPP.push("}");
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.PROPERTY_INIT:
			CPP.push(generate_cpp(ast[0]).CPP + ":");
			CPP.push(generate_cpp(ast[1]).CPP);
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.ASSIGN:

			var setter = false;

			//-----------------------------------------------------------
			// ARRAY_INIT
			if(ast[1].type==jsdef.ARRAY_INIT)
			{
				var isEmpty = true;
				for(var i in ast[1])
				{
					if(!isFinite(i)) break;
					isEmpty=false;
					break;
				}
				if(isEmpty)
					return _this.NULL_GEN;
			}

			//-----------------------------------------------------------
			// PROPERTY
	     	if((ast[0].symbol && ast[0].symbol.type == jsdef.PROPERTY && ast[0].symbol.ast.setter) ||
	     	   (ast[0].type == jsdef.DOT && ast[0].identifier_last.symbol && ast[0].identifier_last.symbol.type == jsdef.PROPERTY && ast[0].identifier_last.symbol.ast.setter))
	     	{
					setter = _this.in_setter = true;
					CPP.push( generate_cpp(ast[0]).CPP );
					_this.in_setter = false;
	     	}
	     	else
	     	{
				CPP.push(generate_cpp(ast[0]).CPP);
				CPP.push(ast.value);
				if(ast.value != "=") CPP.push("=");
	     	}

			//-----------------------------------------------------------
			// Function Pointer

			var type1 = _this.getTypeName(ast[0]);
			var cls = _this.getClass(type1);
			if(cls.callback)
			{
				// LHS is callback, therefore we must decide if RHS will be wrapped inside a Lambda

				var type2 = _this.getTypeName(ast[1]);
				if(type2=="Null")
				{
					CPP.push("nullptr");
					break;
				}

				var cls2 = _this.getClass(type2);

				//trace(ast.source + " -> " + (cls2 && cls2.callback ? "CALLBACK" : "" ));

				if(cls2 && cls2.callback)
				{
				}
				else
				{
					var gen = generate_cpp(ast[1]).CPP;
					var lambda = gen.indexOf("[=]")==-1 ? "[this](){" + gen + "();" + "}" : gen;
					CPP.push(lambda);
					break;
				}
			}

			//-----------------------------------------------------------
			//#TYPECAST
			var rhs = _this.typeCastCPP(ast[1], generate_cpp(ast[1]).CPP);
			CPP.push( setter ? "( " + rhs + " )" : rhs );
			setter = false;

			break;

		// ==================================================================================================================================
		//	   ______                ___ __  _                   __
		//	  / ____/___  ____  ____/ (_) /_(_)___  ____  ____ _/ /____
		//	 / /   / __ \/ __ \/ __  / / __/ / __ \/ __ \/ __ `/ / ___/
		//	/ /___/ /_/ / / / / /_/ / / /_/ / /_/ / / / / /_/ / (__  )
		//	\____/\____/_/ /_/\__,_/_/\__/_/\____/_/ /_/\__,_/_/____/
		//
		// ==================================================================================================================================

		case jsdef.IF:
			CPP.push("if(");
			CPP.push(generate_cpp(ast.condition).CPP);
			CPP.push(")\n");
			CPP.push(generate_cpp(ast.thenPart).CPP);
			if(ast.elsePart)
			{
				CPP.push("else ");
				CPP.push(generate_cpp(ast.elsePart).CPP);
			}
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.SWITCH:

			// Detect if the switch should be converted to if
			var type = _this.getTypeName(ast.discriminant);

			ast.__switch_to_if = false;
			switch(type)
			{
				case "Number":
				case "Integer":
				case "Float":
				case "Time":
					break;

				default:
					ast.__switch_to_if = !_this.getClass(type).enum;
					break;
			}

			if(!ast.__switch_to_if)
			{
				CPP.push("switch(" + generate_cpp(ast.discriminant).CPP + "){");
				for(var _case in ast.cases)
				{
					if(!isFinite(_case)) break;
					CPP.push(generate_cpp(ast.cases[_case]).CPP);
					CPP.push("break;");
				}
				CPP.push("}");
			}
			else
			{
				var cond =  generate_cpp(ast.discriminant).CPP;
				for(var i=0; i<ast.cases.length; i++)
				{
					var label = generate_cpp(ast.cases[i].caseLabel).CPP;
					CPP.push("if(" + cond + "==" + label + ") { while(true)");
					CPP.push(generate_cpp(ast.cases[i].statements).CPP);
					CPP.push("}");
					if(i<ast.cases.length-1) CPP.push("else ");
				}
			}
			break;

		case jsdef.CASE:
			CPP.push("case " + generate_cpp(ast.caseLabel).CPP + ":");
			CPP.push(generate_cpp(ast.statements).CPP);
			break;


		// ==================================================================================================================================
		//	    ____              __
		//	   / __/___  _____   / /   ____  ____  ____
		//	  / /_/ __ \/ ___/  / /   / __ \/ __ \/ __ \
		//	 / __/ /_/ / /     / /___/ /_/ / /_/ / /_/ /
		//	/_/  \____/_/     /_____/\____/\____/ .___/
		//	                                   /_/
		// ==================================================================================================================================

		case jsdef.FOR:
			_this.__inFor = true;
			var setupFor = ast.setup ? generate_cpp(ast.setup).CPP : ";";
			_this.__inFor = false;
			setupFor=setupFor.trim();
			CPP.push("for(" + setupFor + (setupFor.slice(-1) == ";" ? "": ";"));
			CPP.push((ast.condition ? generate_cpp(ast.condition).CPP : "") + ";");
			CPP.push((ast.update ? generate_cpp(ast.update).CPP : "") + ")\n");
			CPP.push(generate_cpp(ast.body).CPP);
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.FOR_IN:
			CPP.push("for(" + (ast.iterator.type == jsdef.VAR ?	"auto " + ast.iterator[0].value : ast.iterator.value));
			CPP.push(" : " + (ast.object ? generate_cpp(ast.object).CPP : "") + ")\n");
			CPP.push(generate_cpp(ast.body).CPP);
			break;

		// ==================================================================================================================================
		//	    __  ____                ____
		//	   /  |/  (_)____________  / / /___ _____  ___  ____  __  _______
		//	  / /|_/ / / ___/ ___/ _ \/ / / __ `/ __ \/ _ \/ __ \/ / / / ___/
		//	 / /  / / (__  ) /__/  __/ / / /_/ / / / /  __/ /_/ / /_/ (__  )
		//	/_/  /_/_/____/\___/\___/_/_/\__,_/_/ /_/\___/\____/\__,_/____/
		//
		// ==================================================================================================================================

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.TRY:
			CPP.push("try");
			CPP.push(generate_cpp(ast.tryBlock).CPP);
			for(var catchClause in ast.catchClauses)
			{
				if(!isFinite(catchClause)) break;
				CPP.push("catch(...)");
				CPP.push(generate_cpp(ast.catchClauses[catchClause].block).CPP);
				ast.finallyBlock && CPP.push("finally" + generate_cpp(ast.finallyBlock).CPP);
			}
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.THROW:
			CPP.push("throw CocoException(");
			CPP.push(generate_cpp(ast.exception).CPP);
			CPP.push(");");
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.INDEX:
			var out = [];
			var type = ast[0].vartype;
			var pointerAccess = true;
			if(pointerAccess) out.push("(*");
			out.push(generate_cpp(ast[0]).CPP);
			if(pointerAccess) out.push(")");
			out.push("[");
			out.push(generate_cpp(ast[1]).CPP);
			out.push("]");
			CPP.push(out.join(""));
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.DOT:

			var gen0 = generate_cpp(ast[0]).CPP;

			if(ast[1].value=="toJSON" && ast[0].symbol && _this.getClass(ast[0].symbol.vartype).struct)
			{
			 	var cls = _this.getClass(ast[0].symbol.vartype);
			 	var jsonExpr = ['"{"'];
			 	var i=0;
			 	for(var item in cls.vars)
			 	{
					var v = "";
					var mbr = "";

					switch(cls.vars[item].vartype)
					{
					case "String":
						v = " + " + gen0 + "->" + item;
						mbr = '"' + (i>0?",":"") + '\\\"' + item + '\\\":\\\""' + v + ' + "\\\""';
						jsonExpr.push(mbr);
						break;

					case "Integer":
					case "Float":
					case "Boolean":
					case "Number":
					case "Time":
						v = " + String(toString(" + gen0 + "->" + item + "))";
						mbr = '"' + (i>0?",":"") + '\\\"' + item + '\\\":"' + v;
						jsonExpr.push(mbr);
						break;

					default:
					}

					i++;
			 	}
			 	jsonExpr.push('"}"');
			 	jsonExpr = jsonExpr.join("+");

				CPP.push(jsonExpr);

				ast[0].vartype = "String";
				ast.__toJSON = true;
			}
			else
			{
				CPP.push(gen0);

				if(ast[1].symbol.static && ast[1].symbol.enum)
				{
					CPP.push("::");
				}
				else if(ast[1].symbol.static && ast[1].symbol.state)
				{
					CPP.push("->");
				}
				else if(ast[1].symbol.static)
				{
					CPP.push("::");
				}
				else if(ast[1].symbol.type==jsdef.FUNCTION && ast[1].symbol.virtual && (ast[0].type==jsdef.SUPER || ast[0].type==jsdef.THIS))
				{
					CPP.push("::");
				}
				else
				{
					CPP.push(_this.isPointer(ast[0].vartype) ? "->" : ".");
				}

				CPP.push(generate_cpp(ast[1]).CPP);
			}
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.DELETE:

			var id = generate_cpp(ast[0]).CPP;
			if(_this.currClassName)
			{
				var items = (ast.delete_array && ast[0].symbol && ast[0].symbol.subtype && _this.isPointer(ast[0].symbol.subtype));
				if(items)
					CPP.push("COCO_DELETE_ARRAY(" + id + ")");
				else
					CPP.push("COCO_DELETE_OBJECT(" + id + ")");
			}
			else
			{
				CPP.push("COCO_DELETE_OBJECT(" + id + ")");
			}
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.DEBUGGER:
			CPP.push("assert(false);");
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.NEW:
			if(!ast[0].vartype)	ast[0].vartype = ast[0].value;
			CPP.push("new " + _this.VTCPP(ast[0].vartype, true));
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.NEW_WITH_ARGS:

			if(!ast[0].vartype)
				ast[0].vartype = ast[0].value;

			CPP.push("new " + _this.VTCPP(ast[0].vartype, true) + "(" + generate_cpp(ast[1]).CPP + ")");
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.RETURN:

			CPP.push("return");
			if(ast.value)
			{
				//#TYPECAST
				CPP.push(" " + _this.typeCastCPP(ast.value, generate_cpp(ast.value).CPP));
			}
			CPP.push(";\n");
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.PLUS:

			var type1 = _this.getTypeName(ast[0]);
			var type2 = _this.getTypeName(ast[1]);

			if(type1=="String")
			{
				var ogen = gen = generate_cpp(ast[0]).CPP;

				ast[0].__typecast = "String";
				gen = _this.typeCastCPP(ast[0], gen);

				//#TYPECAST
				if(ogen==gen && gen.indexOf("String(")!=0)
					gen = "String(" + gen + ")";

				CPP.push(gen);
				CPP.push(" + ");
				CPP.push(generate_cpp(ast[1]).CPP);
			}
			else if(type2=="String")
			{
				CPP.push(generate_cpp(ast[0]).CPP);
				CPP.push(" + ");
				CPP.push(generate_cpp(ast[1]).CPP);
			}
			else
			{
				_this.arithmeticOp_cpp(ast, "+", CPP);
			}
			break;

		case jsdef.MINUS:
			_this.arithmeticOp_cpp(ast, "-", CPP);
			break;

		case jsdef.MUL:
			_this.arithmeticOp_cpp(ast, "*", CPP);
			break;

		case jsdef.DIV:
			_this.arithmeticOp_cpp(ast, "/", CPP);
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.EXPONENT:
			var base = generate_cpp(ast[0]).CPP;
			var exp = generate_cpp(ast[1]).CPP;
			CPP.push("std::pow(" + base  + "," + exp + ")");
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.MOD:
			var oper1 = generate_cpp(ast[0]).CPP;
			var oper2 = generate_cpp(ast[1]).CPP;
			CPP.push("(int32_t)(" + oper1 + ")");
			CPP.push("%");
			CPP.push("(int32_t)(" + oper2 + ")");
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.STRING:

			if(!ast.value)
			{
				CPP.push('""');
			}
			else if(/^[\x00-\x7F]+$/.test(ast.value))
			{
				CPP.push('"' + ast.value + '"');
			}
			else
			{
				CPP.push('String(L"' + ast.value + '")');
			}
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.NUMBER:
			CPP.push(ast.value && String(ast.value).indexOf(".")!=-1 ? ast.value + "f" : ast.value);
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.INCREMENT:			if(ast.postfix) { CPP.push(generate_cpp(ast[0]).CPP); CPP.push("++"); } else { CPP.push("++"); CPP.push(generate_cpp(ast[0]).CPP); } break;
		case jsdef.DECREMENT:			if(ast.postfix) { CPP.push(generate_cpp(ast[0]).CPP); CPP.push("--"); } else { CPP.push("--"); CPP.push(generate_cpp(ast[0]).CPP); } break;

		case jsdef.UNARY_MINUS:			CPP.push(" -"); CPP.push(generate_cpp(ast[0]).CPP); break;
		case jsdef.UNARY_PLUS:			CPP.push(" +"); CPP.push(generate_cpp(ast[0]).CPP); break;

		case jsdef.NOT:					CPP.push("!"); CPP.push(generate_cpp(ast[0]).CPP); break;
		case jsdef.AND:					CPP.push(generate_cpp(ast[0]).CPP); CPP.push("&&"); CPP.push(generate_cpp(ast[1]).CPP); break;
		case jsdef.OR:					CPP.push(generate_cpp(ast[0]).CPP); CPP.push("||"); CPP.push(generate_cpp(ast[1]).CPP);	break;

		case jsdef.BITWISE_AND:			CPP.push(generate_cpp(ast[0]).CPP); CPP.push("&"); CPP.push(generate_cpp(ast[1]).CPP); break;
		case jsdef.BITWISE_NOT:			CPP.push("~"); CPP.push(generate_cpp(ast[0]).CPP); break;
		case jsdef.BITWISE_OR:			CPP.push(generate_cpp(ast[0]).CPP); CPP.push("|"); CPP.push(generate_cpp(ast[1]).CPP); break;
		case jsdef.BITWISE_XOR:			CPP.push(generate_cpp(ast[0]).CPP); CPP.push("^"); CPP.push(generate_cpp(ast[1]).CPP); break;

		case jsdef.EQ: 					_this.generate_op(ast, CPP, "=="); break;
		case jsdef.GE:					_this.generate_op(ast, CPP, ">="); break;
		case jsdef.GT:					_this.generate_op(ast, CPP, ">");  break;
		case jsdef.LE:					_this.generate_op(ast, CPP, "<="); break;
		case jsdef.LT:					_this.generate_op(ast, CPP, "<");  break;
		case jsdef.NE:					_this.generate_op(ast, CPP, "!="); break;
		case jsdef.STRICT_EQ:			_this.generate_op(ast, CPP, "=="); break;
		case jsdef.STRICT_NE:			_this.generate_op(ast, CPP, "!="); break;

		case jsdef.TRUE:				CPP.push("true"); break;
		case jsdef.FALSE:				CPP.push("false"); break;

		case jsdef.LSH:					CPP.push(generate_cpp(ast[0]).CPP); CPP.push("<<"); CPP.push(generate_cpp(ast[1]).CPP); break;
		case jsdef.RSH:					CPP.push(generate_cpp(ast[0]).CPP); CPP.push(">>"); CPP.push(generate_cpp(ast[1]).CPP); break;
		case jsdef.URSH:				CPP.push(generate_cpp(ast[0]).CPP); CPP.push(">>"); CPP.push(generate_cpp(ast[1]).CPP); break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		case jsdef.BREAK:				CPP.push("break;"); break;
		case jsdef.CONTINUE:			CPP.push("continue;"); break;
		case jsdef.DEFAULT:				CPP.push("default:"); CPP.push(generate_cpp(ast.statements).CPP); break;
		case jsdef.DO: 					ast.body.isLoop = true; CPP.push("do"); CPP.push(generate_cpp(ast.body).CPP); CPP.push("while(" + generate_cpp(ast.condition).CPP + ");"); break;
		case jsdef.HOOK:				CPP.push(generate_cpp(ast[0]).CPP); CPP.push("?"); CPP.push(generate_cpp(ast[1]).CPP); CPP.push(":"); CPP.push(generate_cpp(ast[2]).CPP); break;
		case jsdef.INSTANCEOF: 			CPP.push(generate_cpp(ast[0]).CPP); CPP.push(" instanceof "); CPP.push(generate_cpp(ast[1]).CPP); break;
		case jsdef.LABEL:				CPP.push(ast.label + ":"); CPP.push(generate_cpp(ast.statement).CPP); break;
		case jsdef.TYPEOF:				CPP.push("typeof "); CPP.push(generate_cpp(ast[0]).CPP); break;
		case jsdef.VOID:				CPP.push("void "); CPP.push(generate_cpp(ast[0]).CPP); break;
		case jsdef.WHILE:				ast.body.isLoop=true; CPP.push("while(" + generate_cpp(ast.condition).CPP + ")"); CPP.push(generate_cpp(ast.body).CPP); break;
		case jsdef.NULL:				CPP.push("nullptr"); break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.SEMICOLON:

			var expr = (ast.expression ? generate_cpp(ast.expression).CPP : "");

			if(ast.expression && ast.expression[0] && ast.expression[0].type==jsdef.SUPER && ast.expression[1].symbol.type==jsdef.FUNCTION)
			{
				var params = [];
				for(item in ast.inFunction.symbol.paramsList)
				{
					if(!isFinite(item)) break;
					var param = ast.inFunction.symbol.paramsList[item];
					params.push(param.name);
				}
				expr += "(" + params.join(",") + ")";
			}

			if(expr)
				CPP.push(expr + ";\n");

			break;

		}

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		_this.generate_op = function(ast, CPP, operator)
		{
			var type1 = _this.getTypeName(ast[0]);
			var type2 = _this.getTypeName(ast[1]);

			if(type1!=type2)
			{
				var typecast = _this.typeCheck(ast, type1, type2, null, true, true, "DIV");

				//#TYPECAST
				ast[0].__typecast = typecast;
				ast[1].__typecast = typecast;
				var lhs = _this.typeCastCPP(ast[0], generate_cpp(ast[0]).CPP);
				var rhs = _this.typeCastCPP(ast[1], generate_cpp(ast[1]).CPP);

				CPP.push(lhs);
				CPP.push(operator);
				CPP.push(rhs);
			}
			else
			{
				CPP.push(generate_cpp(ast[0]).CPP);
				CPP.push(operator);
				CPP.push(generate_cpp(ast[1]).CPP);
			}
		};

		// Done!
		return { CPP:CPP.join(""), HPP:HPP.join("") };
	};
}
