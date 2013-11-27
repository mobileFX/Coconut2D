
var jsdef = this.narcissus.jsdef;

function Compiler(ast, options) 
{
	var _this = this;

	this.ast = ast;
	this.lineno = -1;	
	this.errors = [];
	this.warnings = [];             
	this.scopes = [];
	this.currFile = "";
	this.currFileStartLine = 0;
	this.currFileOffset = 0;
	this.FILE_DELIM = "script_begin:///";		
	
	this.currClassName = null;
	this.currClassHPP = [];
	this.currClassCPP = [];
	
	// Defaults
	this.types = {  "Array": 	{ "default": "[]"},
					"Boolean": 	{ "default": "false" },
					"Date": 	{ "default": "new Date" },
					"Function": { "default": "function(){}" },
					"Null": 	{ "default": "null" },
					"Number": 	{ "default": "0" },
					"Object": 	{ "default": "{}" },
					"RegExp": 	{ "default": "/(?:)/" },
					"String": 	{	"default": '""' }
	};
		
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	this.NewWarning = function (e, node) 
	{
		trace("@@ WARNING: " + e);
		warnings.push(e);
	};
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	this.NewError = function (e, node)
	{
		trace("@@ ERROR: " + e);
		errors.push(e);
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	this.NewScope = function(id, node) 
	{
		var scope = { 
			scopeId:	id,
			type:	 	node.type,
			lineno:		node.lineno,
			nodeType:	node.nodeType,
			vars: 		{},
			methods:	{}			
		};
		
		_this.scopes.push(scope);
		return scope;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	this.ExitScope = function() 
	{
		return _this.scopes.pop();		
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	this.CurrentScope = function() 
	{
		return _this.scopes[_this.scopes.length-1];
	};
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	this.CurrentScopeId = function()
	{
		 return _this.scopes.length-1;
	};

	//Get the current scope based on regular JS scoping rules (nearest function or global only)
	this.ScopeJS = function(currentScopeId) 
	{
		return _this.CurrentFunction(currentScopeId) ||  _this.scopes[0];
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	this.LookupScopeChain = function (findIdentifier, scopeId, callback, deep) 
	{
		if(scopeId<0) return;
		
		var found = false;
		var data = null;
		var scope = _this.scopes[scopeId];
		
		for(var name in scope.vars)
		{
			if(name==findIdentifier)
			{
				found = true;  
				data = scope.vars[name];
				break;
			}			
		}
		
		if(found)
		{
			if(callback) callback(data);
			return data;
		}

		if(deep)		
			return _this.LookupScopeChain(findIdentifier, scopeId-1, callback, deep);		
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	this.NewClass = function(node, superClass) 
	{ 
		this.currClassName = node.name;
		this.currClassHPP = [];
		this.currClassCPP = [];		
		
		this.currClassHPP.push("#ifdef __" + node.name.toUpperCase() + "_HPP__");
		this.currClassHPP.push("#define __" + node.name.toUpperCase() + "_HPP__");
		
		this.currClassCPP.push('#include "coconut2d.h"');
		this.currClassCPP.push('#include "' + node.name + '.hpp"');
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	this.ExitClass = function() 
	{ 
		this.currClassHPP.push("\n#endif");
		buff = do_js_beautify(this.currClassCPP.join("\n"), 1, true, true, true);
		buff = RxReplace(buff, " - > ", "mg", "->");		
		write("C:/Users/admin/Desktop/Coco.CPP/" + this.currClassName + ".cpp", buff);
		write("C:/Users/admin/Desktop/Coco.CPP/" + this.currClassName + ".hpp", do_js_beautify(this.currClassHPP.join("\n"), 1, true, true, true));		
		this.currClassHPP = [];
		this.currClassCPP = [];		
		this.currClassName = null;
	};
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	this.isPointer = function(vartype)
	{
		return true;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Compiler.prototype.compile = function (ast) 
{
	var out = [], _this = this, ast = ast || this.ast, scope;
	
	var generate = function()
	{
		return _this.compile.apply(_this, Array.prototype.slice.call(arguments,0));
	};
    
    /*
	if(ast.lineno != this.lineno) 
	{
		this.lineno != -1 && out.push("\n");		
		out.push("\/\/@line " + (ast.lineno-this.currFileStartLine) + "\n");
		this.lineno = ast.lineno;
	}    
	*/
	
	switch(ast.type) 
	{

	// ==================================================================================================================================
	//	   ________               
	//	  / ____/ /___ ___________
	//	 / /   / / __ `/ ___/ ___/
	//	/ /___/ / /_/ (__  |__  ) 
	//	\____/_/\__,_/____/____/  
	//	                          
	// ==================================================================================================================================
	
	case jsdef.CLASS:

		var superClass = ast.extends ? generate(ast.extends) : null;									
		this.NewClass(ast, superClass);
		
		this.currClassHPP.push("class " + ast.name);
		if(superClass) this.currClassHPP.push(" : public " + superClass);
		this.currClassHPP.push("{");
		
		this.currClassHPP.push("public:");
		this.currClassHPP.push("void bind(fxJSObject& global, fxJSVM* VM);");
		this.currClassHPP.push("void unbind(){};");
		
		// Process Class Body
		for(var item in ast.body) 
		{
			if(!isFinite(item)) continue;
			currentItem = ast.body[item];			
			switch(currentItem.type)
			{
				case jsdef.FUNCTION:
					if(currentItem.name == "Constructor" || currentItem.name == ast.name)
					{
						currentItem.name = ast.name;
						currentItem.isConstructor = true;
					}					
					this.currClassCPP.push(generate(currentItem));
					break;
					
				case jsdef.VAR: 
					this.currClassCPP.push(generate(currentItem));
					break;
			}
		}
		
		this.currClassHPP.push("};");	
		this.ExitClass();
		break;  
				
	// ==================================================================================================================================
	//	    ______                 __  _                 
	//	   / ____/_  ______  _____/ /_(_)___  ____  _____
	//	  / /_  / / / / __ \/ ___/ __/ / __ \/ __ \/ ___/
	//	 / __/ / /_/ / / / / /__/ /_/ / /_/ / / / (__  ) 
	//	/_/    \__,_/_/ /_/\___/\__/_/\____/_/ /_/____/  
	//	                                                 
	// ==================================================================================================================================

	case jsdef.FUNCTION:
        		
		if(!this.currClassName) return;		
		if(!ast.returntype) ast.returntype = "void";
		
		var scope = this.NewScope(ast.name, ast);
		
		// Parameters
		var paramsList = "(";	
		for(var i=0; i<ast.paramsList.length; i++)
		{
			var param = ast.paramsList[i];
			param.isPointer = this.isPointer(param.vartype);
			paramsList += param.vartype + (param.isPointer?"*":"") + " " + param.name;
			if(i!=ast.paramsList.length-1) paramsList +=", ";			

			// push param to current scope.			
			scope.vars[param.name] = {name:param.name, vartype:param.vartype, pointer:param.isPointer}; 
		}
		paramsList += ")";
        
        // HPP          
		//this.currClassHPP.push("static fxJSBindFunction(" + ast.name + ");");	
		this.currClassHPP.push(ast.returntype + " __" + ast.name + paramsList + ";");
		
		// CPP - JavaScript function
		//out.push("////////////////////////////////////////////////////////////////////////////////////////////////////\n");
		//out.push("fxJSBindFunction("+this.currClassName+"::" + ast.name + ") {");
		//out.push("}\n");
		
		// CPP - Native function		
		out.push("////////////////////////////////////////////////////////////////////////////////////////////////////\n");
		out.push(ast.returntype + " " + this.currClassName+"::__" + ast.name + paramsList);
        out.push("{");
		out.push(generate(ast.body));
		out.push("\n}\n"); 
		
		_this.ExitScope();		
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
		var scope = this.NewScope(ast.scopeId, ast);			
		var body = [];
		for(var item in ast) 
		{
			if(!isFinite(item)) continue;
			body.push(generate(ast[item]));
		}
		out = out.concat(body);
		this.ExitScope();			
		break;            
		
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.BLOCK:
		this.NewScope(ast.scopeId, ast);
		out.push("{");
		for(var item in ast) 
		{
			if(!isFinite(item)) continue;
			out.push(generate(ast[item]));
		}
		out.push("}");
		this.ExitScope();
		break;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.CALL:
		out.push(generate(ast[0]));
		ast[0].type == jsdef.REGEXP && out.push(".exec");
		out.push("(");
		out.push(generate(ast[1]));
		out.push(")");
		break;
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.LIST:
	case jsdef.COMMA:
		var firstItem = true;
		for(var item in ast) 
		{
			if(!isFinite(item)) continue;
			if(!firstItem) out.push(",");
			out.push(generate(ast[item]));
			firstItem = false;
		}
		break;
		
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.GROUP:
		out.push("(");
		for(var item in ast) 
		{
			if(!isFinite(item)) continue;
			out.push(generate(ast[item]));
		}
		out.push(")");
		break;
		
	// ==================================================================================================================================
	//	 _    __           _       __    __         
	//	| |  / /___ ______(_)___ _/ /_  / /__  _____
	//	| | / / __ `/ ___/ / __ `/ __ \/ / _ \/ ___/
	//	| |/ / /_/ / /  / / /_/ / /_/ / /  __(__  ) 
	//	|___/\__,_/_/  /_/\__,_/_.___/_/\___/____/  
	//	                                            
	// ==================================================================================================================================   
	
	case jsdef.VAR:				
	case jsdef.CONST:
		if(!this.currClassName) return;				
		var scope = _this.CurrentScope();			
		var firstItem = true;
		for(var item in ast) 
		{
			if(!isFinite(item)) continue;
			
			if(firstItem) 
				out.push(ast[item].vartype);
			else
				out.push(",");			
				
			ast[item].isPointer = _this.isPointer(ast[item]);		
			if(ast[item].isPointer) out.push("*");
			
			var identifier = generate(ast[item]); 
			out.push(identifier);
			if(ast[item].initializer)
			{				
				out.push(" = ");
				out.push(generate(ast[item].initializer));
			} 
			
			scope.vars[identifier] = {name:identifier, vartype:ast[item].vartype, pointer: ast[item].isPointer}; 			
			firstItem = false;
		} 
		out.push(";");
		break;
		
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.ARRAY_INIT:
		out.push("{");
		var firstItem = true;
		for(var item in ast) 
		{
			if(!isFinite(item)) continue;
			if(!firstItem) out.push(",");
			out.push(generate(ast[item]));
			firstItem = false;
		}
		out.push("}");
		break; 
		
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.OBJECT_INIT:
		out.push("{");
		var firstItem = true;
		for(var item in ast) 
		{
			if(!isFinite(item)) continue;
			if(!firstItem) out.push(",");
			out.push(generate(ast[item]));			
			firstItem=false;
		}		
		out.push("}");
		break;
		
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.PROPERTY_INIT:
		out.push(generate(ast[0]) + ":");
		out.push(generate(ast[1]));
		break;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.ASSIGN:		
		
		if(ast[0].type==jsdef.THIS) 
		{
			this.NewError({type:ReferenceError, message:"Cannot assign to 'this'"},ast);
		}
		else if(ast[0].type != jsdef.IDENTIFIER && ast[0].type != jsdef.DOT && ast[0].type != jsdef.INDEX) 
		{
			this.NewError({type:ReferenceError, message:"Invalid left-hand assignment"},ast);
		}
		
		out.push(generate(ast[0])); 
		out.push(ast.value);		
		if(ast.value != "=") out.push("=");
		out.push(generate(ast[1]));		
		break; 
		
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.IDENTIFIER:
		out.push(ast.value);
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
		out.push("if(");
		out.push(generate(ast.condition));
		out.push("){");
		out.push(generate(ast.thenPart));
		out.push("}");
		if(ast.elsePart) 
		{
			out.push("else ");  
			if(ast.elsePart.type!=jsdef.IF) out.push("{");			
			out.push(generate(ast.elsePart));
			if(ast.elsePart.type!=jsdef.IF) out.push("}");
		}
		break;   
		
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.SWITCH:
		out.push("switch(" + generate(ast.discriminant) + "){");
		for(var _case in ast.cases) 
		{
			if(!isFinite(_case)) continue;
			out.push(generate(ast.cases[_case]));
		}
		out.push("}");
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
		var setupFor = ast.setup ? generate(ast.setup) : ";";
		out.push("for(" + setupFor + (setupFor.slice(-1) == ";" ? "": ";"));
		out.push((ast.condition ? generate(ast.condition) : "") + ";");
		out.push((ast.update ? generate(ast.update) : "") + ")");
		out.push(generate(ast.body));
		break;  
		
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.FOR_IN:
		out.push("for(" + (ast.iterator.type == jsdef.VAR ?	"auto " + ast.iterator[0].value : ast.iterator.value));
		out.push(" : " + (ast.object ? generate(ast.object) : "") + ")");
		out.push(generate(ast.body));
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

		out.push('String("' + ast.value + '")');

		//Detect file change in input stream and mark file line and offset
		var f = out.join("");			
		if(f.indexOf(this.FILE_DELIM)!=-1)
		{
			this.currFile = f.substr(this.FILE_DELIM.length+1, f.lastIndexOf('"')-this.FILE_DELIM.length-1 );
			this.currFileStartLine = ast.lineno;
			this.currFileOffset = ast.start + f.length +2;								
			trace("Compiling file: " + this.currFile + " (L:"+this.currFileStartLine+" P:"+this.currFileOffset + ")");
		}			
		break;	

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.TRY:
		out.push("try");
		out.push(generate(ast.tryBlock));
		for(var catchClause in ast.catchClauses) 
		{
			if(!isFinite(catchClause)) continue;
			out.push("catch(" + ast.catchClauses[catchClause].varName + ")");
			out.push(generate(ast.catchClauses[catchClause].block));
			ast.finallyBlock && out.push("finally" + generate(ast.finallyBlock));
		}
		break;		

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.DOT:					
		var isPointer = false;
		if(ast[0].type==jsdef.IDENTIFIER) _this.LookupScopeChain(ast[0].value, _this.CurrentScopeId(), function(data) { isPointer = data.pointer; }, true); 	
		out.push(generate(ast[0]));
		out.push(isPointer ? "->" : ".");
		out.push(generate(ast[1]));
		break;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.DELETE: 				out.push("delete "); out.push(generate(ast[0])); break;
	case jsdef.RETURN:				out.push("return"); if(ast.value.type) out.push(" " + generate(ast.value)); out.push(";"); break;
	case jsdef.INSTANCEOF: 			out.push(generate(ast[0])); out.push(" instanceof "); out.push(generate(ast[1])); break;
	case jsdef.SUPER:				out.push("super"); break; 
	case jsdef.THROW:				out.push("throw("); out.push(generate(ast.exception)); out.push(");"); break;
	case jsdef.TYPEOF:				out.push("typeof "); out.push(generate(ast[0])); break;			

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.AND:					out.push(generate(ast[0])); out.push("&&"); out.push(generate(ast[1])); break;
	case jsdef.BITWISE_AND:			out.push(generate(ast[0])); out.push("&"); out.push(generate(ast[1])); break;  		
	case jsdef.BITWISE_NOT:			out.push("~"); out.push(generate(ast[0])); break;  		
	case jsdef.BITWISE_OR:			out.push(generate(ast[0])); out.push("|"); out.push(generate(ast[1])); break; 		
	case jsdef.BITWISE_XOR:			out.push(generate(ast[0])); out.push("^"); out.push(generate(ast[1])); break;    		
	case jsdef.BREAK:				out.push("break"); break;
	case jsdef.CASE:				out.push("case " + generate(ast.caseLabel) + ":"); out.push(generate(ast.statements)); break;    
	case jsdef.CONTINUE:			out.push("continue"); break;
	case jsdef.DEBUGGER:			out.push("assert(false);"); break; 
	case jsdef.DECREMENT:			if(ast.postfix) { out.push(generate(ast[0])); out.push("--"); } else { out.push("--"); out.push(generate(ast[0])); } break;
	case jsdef.DEFAULT:				out.push("default:"); out.push(generate(ast.statements)); break; 
	case jsdef.DIV:					out.push(generate(ast[0])); out.push("/"); out.push(generate(ast[1])); break;  
	case jsdef.DO: 					ast.body.isLoop = true; out.push("do"); out.push(generate(ast.body)); out.push("while(" + generate(ast.condition) + ");"); break;
	case jsdef.EQ: 					out.push(generate(ast[0])); out.push("==");	 out.push(generate(ast[1])); break; 		
	case jsdef.EXPONENT:			out.push("std::pow(" + generate(ast[0]) + "," + generate(ast[1]) + ")");break;
	case jsdef.FALSE:				out.push("false"); break;    
	case jsdef.GE:					out.push(generate(ast[0])); out.push(">=");  out.push(generate(ast[1])); break;  		
	case jsdef.GT:					out.push(generate(ast[0])); out.push(">");   out.push(generate(ast[1])); break; 		
	case jsdef.HOOK:				out.push(generate(ast[0])); out.push("?"); out.push(generate(ast[1])); out.push(":"); out.push(generate(ast[2])); break;
	case jsdef.INCREMENT:			if(ast.postfix) { out.push(generate(ast[0])); out.push("++"); } else { out.push("++"); out.push(generate(ast[0])); } break;
	case jsdef.INDEX:				out.push(generate(ast[0])); out.push("["); out.push(generate(ast[1])); out.push("]"); break;
	case jsdef.LABEL:				out.push(ast.label + ":"); out.push(generate(ast.statement)); break;			
	case jsdef.LE:					out.push(generate(ast[0])); out.push("<=");  out.push(generate(ast[1])); break;
	case jsdef.LSH:					out.push(generate(ast[0])); out.push("<<"); out.push(generate(ast[1])); break; 		
	case jsdef.LT:					out.push(generate(ast[0])); out.push("<");   out.push(generate(ast[1])); break; 	
	case jsdef.MINUS: 				out.push(generate(ast[0])); out.push("-"); out.push(generate(ast[1])); break;  
	case jsdef.MOD:					out.push(generate(ast[0])); out.push("%"); out.push(generate(ast[1])); break;
	case jsdef.MUL: 				out.push(generate(ast[0])); out.push("*"); out.push(generate(ast[1])); break;   
	case jsdef.NE:					out.push(generate(ast[0])); out.push("!=");	 out.push(generate(ast[1])); break; 		
	case jsdef.NEW: 				out.push("new "); out.push(generate(ast[0]) +"()"); break;
	case jsdef.NEW_WITH_ARGS:		out.push("new "); out.push(generate(ast[0])); out.push("("); out.push(generate(ast[1])); out.push(")"); break;
	case jsdef.NOT:					out.push("!"); out.push(generate(ast[0])); break;
	case jsdef.NULL:				out.push("NULL"); break;	
	case jsdef.NUMBER:				out.push(ast.value); break; 
	case jsdef.OR:					out.push(generate(ast[0])); out.push("||"); out.push(generate(ast[1]));	break;
	case jsdef.PLUS: 				out.push(generate(ast[0])); out.push("+"); out.push(generate(ast[1])); break;	
	case jsdef.RSH:					out.push(generate(ast[0])); out.push(">>"); out.push(generate(ast[1])); break; 		
	case jsdef.SEMICOLON:			out.push((ast.expression ? generate(ast.expression) : "") + ";"); break;          		
	case jsdef.STRICT_EQ:			out.push(generate(ast[0])); out.push("=="); out.push(generate(ast[1])); break; 		
	case jsdef.STRICT_NE:			out.push(generate(ast[0]));	out.push("!="); out.push(generate(ast[1])); break;  		
	case jsdef.THIS:				out.push("this"); break;
	case jsdef.TRUE:				out.push("true"); break;
	case jsdef.UNARY_MINUS:			out.push(" -"); out.push(generate(ast[0])); break;
	case jsdef.UNARY_PLUS:			out.push(" +"); out.push(generate(ast[0])); break;		
	case jsdef.URSH:				out.push(generate(ast[0])); out.push(">>"); out.push(generate(ast[1])); break;
	case jsdef.VOID:				out.push("void "); out.push(generate(ast[0])); break;	
	case jsdef.WHILE:				ast.body.isLoop=true; out.push("while(" + generate(ast.condition) + ")"); out.push(generate(ast.body)); break;  

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	default:
		debugger;
	}
		
	return out.join("");
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Compiler.prototype.preprocess = function(ast, useTypeSys) 
{
	return ast;
};














