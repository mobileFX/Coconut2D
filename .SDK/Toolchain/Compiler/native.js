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
	trace("+ Loaded CocoScript Compiler C++ Generator Plugin");

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
		"Float"		: { "default": "0.0" },
		"Integer"	: { "default": "0" },
		"Object"	: { "default": "nullptr" },
		"String"	: { "default": '""' }
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
				items.push("\t" + _this.VTCPP(field.vartype) + field.name + ";");
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
							args.push((p.optional ? "const " : "") + _this.VTCPP(p.vartype) + p.name + (p.optional ? " = " + _this.getDefaultVartypeValue(p.vartype) : ""));
						}

						// Create the delegation HPP wrapper
						var wrapper = (delegatorFunctionSymbol.vartype ? delegatorFunctionSymbol.vartype : "void") + " " + fnName + "(" + args.join(", ") + ");";
						HPP.push(wrapper);
						args = [];
						for(var i=0; i<delegatorFunctionSymbol.paramsList.length; i++)
						{
							var p = delegatorFunctionSymbol.paramsList[i];
							args.push(_this.VTCPP(p.vartype) + p.name);
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
				for(var uid in classSymbol.__event_descriptors) { hasDispIds=true; break; };

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
										CPP.push(_this.VTCPP(event_parm.vartype) + event_parm.name + " = E->" + event_parm.name + ";");
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
		//	    ______                 __  _
		//	   / ____/_  ______  _____/ /_(_)___  ____
		//	  / /_  / / / / __ \/ ___/ __/ / __ \/ __ \
		//	 / __/ / /_/ / / / / /__/ /_/ / /_/ / / / /
		//	/_/    \__,_/_/ /_/\___/\__/_/\____/_/ /_/
		//
		// ==================================================================================================================================
		/*@@ FUNCTION @@*/

		case jsdef.FUNCTION:

			if(!ast.__VARIABLES.export_native) return _this.NULL_GEN;
			if(!_this.currClassName) return _this.NULL_GEN;

			var name = (ast.isConstructor ? _this.currClassName : (ast.isDestructor ? "~" + _this.currClassName : ast.name ));
			var param, cppParamsList = "(", hppParamList = "(";

			for(var i=0; i<ast.paramsList.length; i++)
			{
				param = ast.paramsList[i];
				var cpp_param = _this.VTCPP(param.vartype) + param.name;

				var def = "nullptr";
				if(param.optional)
				{
					if(_this.cpp_types.hasOwnProperty(param.vartype))
					{
						def = _this.cpp_types[param.vartype].default;
					}
					else if(_this.isEnum(param.vartype))
					{
						def = "(" + param.vartype + ")0";
					}
				}

				cppParamsList += cpp_param
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

			var fn = (ast.static ? "static " :"") + (ast.symbol.virtual ? "virtual " : "") + (ast.isConstructor || ast.isDestructor ? "" : _this.VTCPP(ast.returntype)) + name + hppParamList + (ast.symbol.abstract ? "=0":"") +";";
			HPP.push(fn);

			if(!ast.symbol.abstract && ast.inClass && !ast.inClass.symbol.interface)
			{
		        CPP.push("\n////////////////////////////////////////////////////////////////////////////////////////////////////\n");
				CPP.push( (ast.isConstructor || ast.isDestructor ? "" : _this.VTCPP(ast.returntype)) + _this.currClassName+"::" + (_this.in_state ? ast.symbol.scope.parentScope.ast.name + "::" : "") + name + cppParamsList);

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

		        CPP.push("\n{\n");

		        if(ast.isConstructor)
		        {
		        	CPP.push('__className = String("' + ast.inClass.symbol.name + '");');
		        	for(item in ast.inClass.symbol.events)
		        	{
		        		var ev = ast.inClass.symbol.events[item];
		        		CPP.push("this->"+ev.runtime+" = new " + ev.vartype + ";");
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
		        	var vt = _this.VTCPP(ast.symbol.restArgumentsVartype).trim();
		        	if(vt=="String") vt = "char*";
		   			CPP.push("std::vector<" + vt + "> __arguments;");
		   			CPP.push("std::vector<" + vt + ">* arguments = &__arguments;");
					CPP.push("va_list vl;");
					CPP.push("va_start(vl," + param.name + ");");
					CPP.push("for(UINT i=0;i<" + param.name + ";i++)");
					CPP.push("__arguments.push_back(va_arg(vl," + vt + "));");
					CPP.push("va_end(vl);");
		        }

		        if(ast.body)
					CPP.push(generate_cpp(ast.body).CPP);

				CPP.push("}\n");
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
						val = "const " + _this.VTCPP(ast[i].vartype) + ast[i].name + initializer(ast[i]) + ";";
						HPP.push(val);
					}
					else if(ast.static)
					{
						// static var needs to be defined in .cpp as well
						val = _this.VTCPP(ast[i].vartype) + _this.currClassName + "::" + ast[i].name + ";";
						CPP.push(val);

						val = "static " + (isConst ? "constexpr " : "") + _this.VTCPP(ast[i].vartype) + ast[i].name + (!isConst ? "" : initializer(ast[i])) + ";";
						HPP.push(val);
					}
					else
					{
						val = _this.VTCPP(ast[i].vartype) + ast[i].name + ";";
						HPP.push(val);
					}
				}
			}

			// Var in for(;;)
			else if(_this.__inFor)
			{
				CPP.push(_this.VTCPP(ast[0].vartype));
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
					val = _this.VTCPP(ast[i].vartype) + ast[i].name + initializer(ast[i]) + ";";
					HPP.push(val);
				}
			}

			// Var in function
			else if(ast.inFunction)
			{
				for(i=0;i<ast.length;i++)
				{
					val = _this.VTCPP(ast[i].vartype) + ast[i].name + initializer(ast[i]) + ";";
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
					return " = " + generate_cpp(vitem.initializer).CPP;
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
				HPP.push("\n\t"+ _this.VTCPP(field.vartype) + field.name +";");
			}

			// Event constructor and initialization of params
			HPP.push(ast.event_class_symbol.name + "() : CocoEvent(\"" + ast.symbol.name + "\", true, true)\n{");
			for(item in ast.event_class_symbol.vars)
			{
				var field = ast.event_class_symbol.vars[item].ast;
				HPP.push(field.name + " = " + (_this.cpp_types.hasOwnProperty(_this.getVarType(field.vartype)) ? _this.cpp_types[field.vartype].default : "nullptr") + ";");
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
			var native_file = _this.native_files[ast.symbol.file];
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
				HPP.push((ast.symbol.virtual ? "virtual " : "") + ret + name + "();");
		        CPP.push("\n////////////////////////////////////////////////////////////////////////////////////////////////////\n");
				CPP.push( ret + _this.currClassName + "::" + (_this.in_state ? ast.symbol.scope.parentScope.ast.name + "::" : "") + name + "()");
		        CPP.push("\n{\n");
				CPP.push(generate_cpp(ast.getter.body).CPP);
				CPP.push("}\n");
	    	}
	    	if(ast.setter)
	    	{
				var name = "__set_" + ast.name;
				var param = "(" + _this.VTCPP(ast.vartype) + ast.setter.paramsList[0].name + ")";
				HPP.push((ast.symbol.virtual ? "virtual " : "") + ("void ") + name + param + ";");
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

			if(ast.symbol.delegated)
				CPP.push(ast.symbol.scope.ast.name + "->");

			if(ast.symbol && ast.symbol.type==jsdef.FUNCTION && ast.parent.type==jsdef.LIST)
			{
				CPP.push("&" + ast.symbol.ast.scope.className + "::" + name);
				break;
			}
			else if(ast.symbol && ast.symbol.type == jsdef.PROPERTY)
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
		case jsdef.CALLBACK:

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

			var fn = "typedef " + _this.VTCPP(ast.returntype) + "(" + name + ")" + ParamList + ";";
			HPP.push(fn);

			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.CALL:

			var call0 = generate_cpp(ast[0]).CPP;

			// toJSON hack
			if(ast[0].__toJSON)
			{
				CPP.push(call0);
				break;
			}

			if(ast.typecasting)
			{
				var vartype = generate_cpp(ast[0]).CPP;
				if(ast.castToType=="String")
				{

					if(_this.isDerivativeOf(ast.castFromType, "Number"))
					{
						CPP.push("(String(toString(" + generate_cpp(ast[1]).CPP + ")))");
					}
					else if(_this.isDerivativeOf(ast.castFromType, "Boolean"))
					{
						CPP.push("(String(" + generate_cpp(ast[1]).CPP + " ? \"true\" : \"false\"))");
					}
					else if(_this.isDerivativeOf(ast.castFromType, "String"))
					{
						CPP.push("("+generate_cpp(ast[1]).CPP+")");
					}
					else
					{
						_this.NewError("Invalid type casting to string", ast);
					}
				}
				else
				{
					CPP.push("((");
					CPP.push(vartype + (_this.isPointer(vartype) ? "*":""));
					CPP.push(")");
					CPP.push(generate_cpp(ast[1]).CPP);
					CPP.push(")");
				}
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
					var list = _this.getCallList(_this.in_event_call);
					var event_symbol = _this.in_event_call.__event_descriptor.event_symbol;
					CPP.push((_this.in_state ? "self" : "this") + "->" + event_symbol.runtime + "->reset();");
					var i=1;
					for(item in event_symbol.vars)
					{
						CPP.push((_this.in_state ? "self" : "this") + "->" + event_symbol.runtime + "->" + item + " = " + generate_cpp(list[i]).CPP + ";\n");
						i++;
					}
				}

				CPP.push(generate_cpp(ast[0]).CPP);
				CPP.push("(");
				CPP.push(generate_cpp(ast[1]).CPP);
				CPP.push(")");

				_this.in_event_call = null;
			}
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/*@@ LIST @@*/

		case jsdef.LIST:
		case jsdef.COMMA:

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

			// Case1: new Float32Array([...])
			// Case2: new CocoSequence(params, [...]) or foo([...])
			// Case3: a = [...]
			// Case4: var x:Array<T> = [...]

			//(*(new Array<CocoClip*>()))(__root);

			var fnSymbol = null;
			var vartype = null;
			var subtype = null;
			var out=[];

	        if(ast.parent.parent.type==jsdef.VAR)
	        {
	        	//Case4
	        	vartype = ast.parent.parent[0].symbol.vartype;
	        	subtype = _this.getSubType(vartype);
	        }
			else if(ast.parent.type==jsdef.ASSIGN)
			{
				//Case3
				if(ast.parent.parent.expression[0].symbol)
				{
					vartype = ast.parent.parent.expression[0].symbol.vartype;
					subtype = _this.getSubType(vartype);
				}
				else
				{
					_this.NewWarning("Untyped array initialization, defaulting to Array<Float>", ast);
					vartype = "Array<Float>";
					subtype = _this.getSubType(vartype);
				}
			}
			else if(ast.parent.type==jsdef.LIST)
			{
				// Get ast index in function call list
				var index = -1;
				for(item in ast.parent)
				{
					if(!isFinite(item)) break;
					index++;
				}

				switch(ast.parent.parent.type)
				{
				case jsdef.CALL:
					//Case2
					switch(ast.inCall[0].type)
					{
					case jsdef.IDENTIFIER:
						fnSymbol = ast.inCall[0].symbol;
						break;
					case jsdef.DOT:
					  	fnSymbol = ast.inCall.inCall[0].identifier_last.symbol;
					  	break;
					}
					break;

				case jsdef.NEW_WITH_ARGS:
					//Case1
					for(item in ast.parent.parent[0].symbol.methods)
					{
						if(item=="Constructor")
						{
							fnSymbol = ast.parent.parent[0].symbol.methods[item];
							break;
						}
					}
					if(!fnSymbol)
					{
						// TypedArrays
						subtype = _this.getSubType(ast.parent.parent.vartype);
						vartype = "Array<" + subtype +">";
					}
					break;
				}

				// From function symbol arguments get ast datatype
				if(fnSymbol)
				{
					var arg = fnSymbol.paramsList[index];
					vartype = arg.vartype;
					subtype = _this.getSubType(vartype);
				}
			}

			// Special case when having Array<ENUM> because C++11 without experimental features fails.
			if(_this.isEnum(subtype) || ast.length<250)
			{
				out.push("((new " + _this.VTCPP(vartype, true) + ")");
				for(var i=0;i<ast.length;i++)
				{
					var v = generate_cpp(ast[i]).CPP;
					v = _this.VALUECPP(v, subtype);
					out.push("->push(" + v + ")");
				};
				out.push(")");
			}
			else
			{
				out.push("(new " + _this.VTCPP(vartype, true) + "(" + ast.length);
				for(var i=0;i<ast.length;i++)
				{
					var v = generate_cpp(ast[i]).CPP;
					v = _this.VALUECPP(v, subtype);
					out.push(", " + v);
				};
				out.push("))");
			}

			out = out.join("");
			CPP.push(out);
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

			if(ast[1].type==jsdef.ARRAY_INIT)
			{
				var isEmpty = true;
				for(var i in ast[1])
				{
					if(!isFinite(i)) break;
					isEmpty=false;
					break;
				}
				if(isEmpty) return _this.NULL_GEN;
			}

	     	if((ast[0].symbol && ast[0].symbol.type == jsdef.PROPERTY && ast[0].symbol.ast.setter) ||
	     	   (ast[0].type == jsdef.DOT && ast[0].identifier_last.symbol && ast[0].identifier_last.symbol.type == jsdef.PROPERTY && ast[0].identifier_last.symbol.ast.setter))
	     	{
					_this.in_setter = true;
					CPP.push(generate_cpp(ast[0]).CPP);
					_this.in_setter = false;
	     	}
	     	else
	     	{
				CPP.push(generate_cpp(ast[0]).CPP);
				CPP.push(ast.value);
				if(ast.value != "=") CPP.push("=");
	     	}

			var type1 = _this.getTypeName(ast[0]);
			var type2 = _this.getTypeName(ast[1]);

			if(type2!="CocoAction" && _this.isDerivativeOf(type2, "Function"))
			{
				if(ast[1].type==jsdef.FUNCTION)
				{
					// Lamda Function
				}

				CPP.push( "nullptr" );

				break;
			}

			if(type1=="CocoAction" && type2!="Null" && type2!="CocoAction")
			{
				var idf = ast[1].type==jsdef.DOT ? ast[1].identifier_last : ast[1];
				CPP.push("&" + idf.symbol.scope.className + "::" + idf.symbol.name);
				break;
			}

			if(_this.secondPass && type1 && type2 && type1!=type2 && type1!="Array<Object>" && type2!="Array<Object>" && type1.indexOf("<")!=-1 && type2.indexOf("<")!=-1)
			{
				var stype1 = _this.getSubType(type1);
				var stype2 = _this.getSubType(type2);
				if(_this.isDerivativeOf(stype1, stype2))
				{
					CPP.push("(reinterpret_cast<Array<" + stype1 + "*>*>(" + generate_cpp(ast[1]).CPP + "))");
					_this.NewWarning("Arbitrary array coversion from " + type2 + " to " + type1, ast);
					break;
				}
			}
	     	CPP.push( "("+generate_cpp(ast[1]).CPP+")" );
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

		case jsdef.STRING:
			CPP.push('String("' + ast.value + '")');
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.TRY:
			CPP.push("try");
			CPP.push(generate_cpp(ast.tryBlock).CPP);
			for(var catchClause in ast.catchClauses)
			{
				if(!isFinite(catchClause)) break;
				//CPP.push("catch(" + ast.catchClauses[catchClause].varName + ")");
				CPP.push("catch(...)");
				CPP.push(generate_cpp(ast.catchClauses[catchClause].block).CPP);
				ast.finallyBlock && CPP.push("finally" + generate_cpp(ast.finallyBlock).CPP);
			}
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

			if(_this.secondPass && ast[1].value=="toJSON" && _this.getClass(ast[0].symbol.vartype).struct)
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
			CPP.push("if(" + id + ") " + id + " = (delete " + id + ", nullptr)");
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.DEBUGGER:
			CPP.push("assert(false);");
			break;

		case jsdef.EXPONENT:			CPP.push("std::pow(" + generate_cpp(ast[0]).CPP + "," + generate_cpp(ast[1]).CPP + ")");break;
		case jsdef.MOD:					CPP.push("(int)" + generate_cpp(ast[0]).CPP); CPP.push("%"); CPP.push("(int)" + generate_cpp(ast[1]).CPP); break;
		case jsdef.THROW:				CPP.push("throw CocoException("); CPP.push(generate_cpp(ast.exception).CPP); CPP.push(");"); break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.NEW:
			if(!ast[0].vartype)	ast[0].vartype = ast[0].value;
			CPP.push("new " + _this.VTCPP(ast[0].vartype, true)+"()");
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.NEW_WITH_ARGS:

			if(!ast[0].vartype)
				ast[0].vartype = ast[0].value;

			CPP.push("(new " + _this.VTCPP(ast[0].vartype, true) + "(" + generate_cpp(ast[1]).CPP + "))");
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		case jsdef.AND:					CPP.push(generate_cpp(ast[0]).CPP); CPP.push("&&"); CPP.push(generate_cpp(ast[1]).CPP); break;
		case jsdef.BITWISE_AND:			CPP.push(generate_cpp(ast[0]).CPP); CPP.push("&"); CPP.push(generate_cpp(ast[1]).CPP); break;
		case jsdef.BITWISE_NOT:			CPP.push("~"); CPP.push(generate_cpp(ast[0]).CPP); break;
		case jsdef.BITWISE_OR:			CPP.push(generate_cpp(ast[0]).CPP); CPP.push("|"); CPP.push(generate_cpp(ast[1]).CPP); break;
		case jsdef.BITWISE_XOR:			CPP.push(generate_cpp(ast[0]).CPP); CPP.push("^"); CPP.push(generate_cpp(ast[1]).CPP); break;
		case jsdef.BREAK:				CPP.push("break;"); break;
		case jsdef.CONTINUE:			CPP.push("continue;"); break;
		case jsdef.DECREMENT:			if(ast.postfix) { CPP.push(generate_cpp(ast[0]).CPP); CPP.push("--"); } else { CPP.push("--"); CPP.push(generate_cpp(ast[0]).CPP); } break;
		case jsdef.DEFAULT:				CPP.push("default:"); CPP.push(generate_cpp(ast.statements).CPP); break;
		case jsdef.DIV:					CPP.push( "(float)(" + generate_cpp(ast[0]).CPP + ")"); CPP.push("/"); CPP.push( "(float)(" + generate_cpp(ast[1]).CPP + ")"); break;
		case jsdef.DO: 					ast.body.isLoop = true; CPP.push("do"); CPP.push(generate_cpp(ast.body).CPP); CPP.push("while(" + generate_cpp(ast.condition).CPP + ");"); break;
		case jsdef.EQ: 					CPP.push(generate_cpp(ast[0]).CPP); CPP.push("==");	 CPP.push(generate_cpp(ast[1]).CPP); break;
		case jsdef.FALSE:				CPP.push("false"); break;
		case jsdef.GE:					CPP.push(generate_cpp(ast[0]).CPP); CPP.push(">=");  CPP.push(generate_cpp(ast[1]).CPP); break;
		case jsdef.GT:					CPP.push(generate_cpp(ast[0]).CPP); CPP.push(">");   CPP.push(generate_cpp(ast[1]).CPP); break;
		case jsdef.HOOK:				CPP.push(generate_cpp(ast[0]).CPP); CPP.push("?"); CPP.push(generate_cpp(ast[1]).CPP); CPP.push(":"); CPP.push(generate_cpp(ast[2]).CPP); break;
		case jsdef.INCREMENT:			if(ast.postfix) { CPP.push(generate_cpp(ast[0]).CPP); CPP.push("++"); } else { CPP.push("++"); CPP.push(generate_cpp(ast[0]).CPP); } break;
		case jsdef.INSTANCEOF: 			CPP.push(generate_cpp(ast[0]).CPP); CPP.push(" instanceof "); CPP.push(generate_cpp(ast[1]).CPP); break;
		case jsdef.LABEL:				CPP.push(ast.label + ":"); CPP.push(generate_cpp(ast.statement).CPP); break;
		case jsdef.LE:					CPP.push(generate_cpp(ast[0]).CPP); CPP.push("<=");  CPP.push(generate_cpp(ast[1]).CPP); break;
		case jsdef.LSH:					CPP.push(generate_cpp(ast[0]).CPP); CPP.push("<<"); CPP.push(generate_cpp(ast[1]).CPP); break;
		case jsdef.LT:					CPP.push(generate_cpp(ast[0]).CPP); CPP.push("<");   CPP.push(generate_cpp(ast[1]).CPP); break;
		case jsdef.MINUS: 				CPP.push(generate_cpp(ast[0]).CPP); CPP.push("-"); CPP.push(generate_cpp(ast[1]).CPP); break;
		case jsdef.MUL: 				CPP.push(generate_cpp(ast[0]).CPP); CPP.push("*"); CPP.push(generate_cpp(ast[1]).CPP); break;
		case jsdef.NE:					CPP.push(generate_cpp(ast[0]).CPP); CPP.push("!=");	 CPP.push(generate_cpp(ast[1]).CPP); break;
		case jsdef.NOT:					CPP.push("!"); CPP.push(generate_cpp(ast[0]).CPP); break;
		case jsdef.NULL:				CPP.push("nullptr"); break;
		case jsdef.NUMBER:				CPP.push(ast.value); break;
		case jsdef.OR:					CPP.push(generate_cpp(ast[0]).CPP); CPP.push("||"); CPP.push(generate_cpp(ast[1]).CPP);	break;
		case jsdef.PLUS:				CPP.push(generate_cpp(ast[0]).CPP); CPP.push("+"); CPP.push(generate_cpp(ast[1]).CPP); break;
		case jsdef.RETURN:				CPP.push("return"); if(ast.value) CPP.push(" " + generate_cpp(ast.value).CPP); CPP.push(";\n"); break;
		case jsdef.RSH:					CPP.push(generate_cpp(ast[0]).CPP); CPP.push(">>"); CPP.push(generate_cpp(ast[1]).CPP); break;
		case jsdef.STRICT_EQ:			CPP.push(generate_cpp(ast[0]).CPP); CPP.push("=="); CPP.push(generate_cpp(ast[1]).CPP); break;
		case jsdef.STRICT_NE:			CPP.push(generate_cpp(ast[0]).CPP);	CPP.push("!="); CPP.push(generate_cpp(ast[1]).CPP); break;
		case jsdef.TRUE:				CPP.push("true"); break;
		case jsdef.TYPEOF:				CPP.push("typeof "); CPP.push(generate_cpp(ast[0]).CPP); break;
		case jsdef.UNARY_MINUS:			CPP.push(" -"); CPP.push(generate_cpp(ast[0]).CPP); break;
		case jsdef.UNARY_PLUS:			CPP.push(" +"); CPP.push(generate_cpp(ast[0]).CPP); break;
		case jsdef.URSH:				CPP.push(generate_cpp(ast[0]).CPP); CPP.push(">>"); CPP.push(generate_cpp(ast[1]).CPP); break;
		case jsdef.VOID:				CPP.push("void "); CPP.push(generate_cpp(ast[0]).CPP); break;
		case jsdef.WHILE:				ast.body.isLoop=true; CPP.push("while(" + generate_cpp(ast.condition).CPP + ")"); CPP.push(generate_cpp(ast.body).CPP); break;

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
			if(expr) CPP.push(expr + ";\n");
			break;

		}
		return {CPP:CPP.join(""), HPP:HPP.join("")};
	};
}
