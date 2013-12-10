// ==================================================================================================================================
//	  ______                _____            __               
//	 /_  __/_  ______  ___ / ___/__  _______/ /____  ____ ___ 
//	  / / / / / / __ \/ _ \\__ \/ / / / ___/ __/ _ \/ __ `__ \
//	 / / / /_/ / /_/ /  __/__/ / /_/ (__  ) /_/  __/ / / / / /
//	/_/  \__, / .___/\___/____/\__, /____/\__/\___/_/ /_/ /_/ 
//	    /____/_/              /____/                          
// ==================================================================================================================================

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function __isPointer(vartype)
{
	if(!vartype) 
		return false;		
		
	switch(vartype)
	{
	case "Boolean": 
	case "Date": 	
	case "Number": 	
	case "String": 
	case "Integer":
	case "Float":
	case "void":	
		return false;
	default:
		if(vartype.indexOf("_ENUM")!=-1) return false;
		if(vartype.indexOf("<")!=-1) return false;
		return true; 
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Compiler.prototype.TYPESYS = function() 
{ 
	this.UNTYPED = "untyped";
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	this.typerules = 
	{
		explicit: 
		{
			"__UNARY__"		: ["Boolean", "Number", "String"],
			"Array"			: [],
			"Boolean"		: ["Number", "String"],
			"Date"			: ["Number", "String"],
			"Function"		: ["String"],
			"null"			: [],
			"Number"		: ["Boolean", "String"],
			"Object"		: [],
			"RegExp"		: ["Boolean", "Date", "Number", "String"],
			"String"		: ["Boolean", "Date", "Function", "Number", "RegExp"]
		},
		
		implicit: 
		{
			PLUS:	{ "Boolean": { "Boolean": "Number", "Number": "Number" }, "Number": { "Boolean": "Number", "Number": "Number" }, "String": { "String": "String" } },
			MINUS:	{ "Boolean": { "Boolean": "Number", "Number": "Number" }, "Number": { "Boolean": "Number", "Number": "Number" } },
			MUL: 	{ "Boolean": { "Boolean": "Number", "Number": "Number" }, "Number": { "Boolean": "Number", "Number": "Number" } },
			DIV: 	{ "Boolean": { "Boolean": "Number", "Number": "Number" }, "Number": { "Boolean": "Number", "Number": "Number" } },
			MOD:	{ "Boolean": { "Boolean": "Number", "Number": "Number" }, "Number": { "Boolean": "Number", "Number": "Number" } },
			BIT: 	{ "Boolean": { "Boolean": "Number", "Number": "Number" }, "Number": { "Boolean": "Number", "Number": "Number" } },
			ASSIGN: { "Number":	 { "Boolean": "Number",	"Number": "Number" }, "Boolean": { "Boolean": "Number", "Number": "Number" }
			}
		}
	}; 
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	this.typesys = function(Node, Compiler) 
	{
		if(!Compiler.currentClass) return;
		
		var _this = this;
		
		//=============================================================================================================================
		function reduceProps(node) 
		{
			var out = [];
			
			switch (node[0].type) {
				case jsdef.IDENTIFIER:
				case jsdef.TRUE:
				case jsdef.FALSE:
				case jsdef.NULL:
					out.push(node[0].value);
					break; 
					
				case jsdef.INDEX:
				case jsdef.GROUP:
				case jsdef.DOT:
				case jsdef.CALL:
					out = out.concat(reduceProps(node[0]));
					break;					
					
				case jsdef.THIS:
					out.push(Compiler.currentClass);
					break;
					
				case jsdef.SUPER:
					var cls = Compiler.SymbolTable.getClassSymbol(Compiler.currentClass);
					return cls && cls.bases.length ? cls.bases[0] : "Object";					
					
				default:    
					Compiler.NewError({type: SyntaxError, message: "Illegal operation on dot accessor"}, Node);
					break;
			}
						
			if (node.type == jsdef.DOT) 
				out.push(node[1].value);
			else if (node.type == jsdef.INDEX)    
				out.push([false, "@@INDEX@@"]);				
			
			return out;
		} 
		
		//=============================================================================================================================
		function getIdentifierDataType(identifier, NodeType)
		{			
			var type = _this.UNTYPED;  
			
			//Is it a class?
			var cls = Compiler.SymbolTable.getClassSymbol(identifier);
			if(cls) return cls.name;
			
			//Lookup
			Compiler.LookupScopeChain(identifier, Compiler.scopeChain.length-1, function(find) 
			{
				if(!find)
				{  
					//Handled by compiler as warning
					//Compiler.NewError({type:ReferenceError, message:"Variable "+identifier+" has not been declared"}, Node);
				}
				else
				{
					if(find.data.type == jsdef.FUNCTION || find.data.type=="FUNCTION") 
					{
						if(NodeType ==jsdef.CALL)
							type = find.data.returntype
						else
							type = "Function";
					}
					else
					{
						type = find.data.datatype || find.data["[[Type]]"];
					}
				}
			},null, true);	
			
			return type || _this.UNTYPED;
		}
			
		//=============================================================================================================================
		function TYPE_CHECK(Node, left, right, ErrorMessage)
		{
			if(!left) left = _this.UNTYPED;
			if(!right) right = _this.UNTYPED;
			  
			// Numbers
			if(left && left=="Float") left = "Number";
			if(left && left=="Integer") left = "Number";
			if(right && right=="Float") right = "Number";
			if(right && right=="Integer") right = "Number";
			
			// Nasty-hacks
			if(left=="HTMLImageElement" && right=="Image") return "HTMLImageElement";			
			if(left=="Image" && right=="HTMLImageElement") return "HTMLImageElement";			
			if(left=="Float32Array") left = "Array";
			if(right=="Float32Array") right = "Array";
			if(left && left.indexOf("_ENUM")!=-1) return left;
			if(right && right.indexOf("_ENUM")!=-1) return right;
						                            
			// Type check (including UNTYPED)			
			if(left==right) return left;
			
			// No type checking for void and object
			if(left==_this.UNTYPED || right==_this.UNTYPED) return _this.UNTYPED;		                       			
			if(left=="Object" || right=="Object") return "Object";
			
			// Arrays			
			if(left.indexOf("<")!=-1) left = left.substr(0, left.indexOf("<"));
			if(right.indexOf("<")!=-1) right = right.substr(0, right.indexOf("<"));			
			if(left==right=="Array") return left;				
			
			// Conversions
			if(left!=right && _this.typerules.implicit.ASSIGN[left] && _this.typerules.implicit.ASSIGN[left].hasOwnProperty(right)) 
				return left; 
				
			// Inheritance
			var cls = Compiler.SymbolTable.getClassSymbol(right);
			while(cls)
			{
				if(cls.name==left) return left; 
				if(!cls.bases || cls.bases.length==0) break;
				if(cls.bases[0]==left) return left;
				cls = Compiler.SymbolTable.getClassSymbol(cls.bases[0]); 
			}
			
			if(!ErrorMessage) ErrorMessage = "Cannot convert "+right+" to "+left;
			Compiler.NewError({type:TypeError, message:ErrorMessage}, Node);			
			return left;
		}

		//=============================================================================================================================
		//=============================================================================================================================
		switch(Node.type) 
		{
		case jsdef.ARRAY_INIT:		return "Array"			
		case jsdef.BITWISE_NOT:		return "Number";
		case jsdef.COMMA: 			return _this.typesys(Node[+Node.length-1], Compiler);
		case jsdef.DELETE:          return "Boolean";
		case jsdef.EQ:              return "Boolean";
		case jsdef.FALSE:           return "Boolean";
		case jsdef.GE:              return "Boolean";
		case jsdef.GROUP: 			return _this.typesys(Node[0], Compiler);
		case jsdef.GT:              return "Boolean";
		case jsdef.IDENTIFIER:		return getIdentifierDataType(Node.value, Node.type);
		case jsdef.IN:              return "Boolean";
		case jsdef.INSIDE:          return "Boolean";
		case jsdef.INSTANCEOF:      return "Boolean";
		case jsdef.LE:              return "Boolean";
		case jsdef.LT:              return "Boolean";
		case jsdef.NE:              return "Boolean";
		case jsdef.NEW:				return Node[0].value || "Object";			
		case jsdef.NEW_WITH_ARGS:	return Node[0].value || "Object";			         			
		case jsdef.NOT:             return "Boolean";
		case jsdef.NULL:			return "Object"; //TODO: null
		case jsdef.NUMBER:			return "Number";
		case jsdef.OBJECT_INIT:		return "Object";
		case jsdef.REGEXP:			return "RegExp";
		case jsdef.STRICT_EQ:       return "Boolean";
		case jsdef.STRICT_NE:       return "Boolean";
		case jsdef.STRING:			return "String";
		case jsdef.TRUE:			return "Boolean";
		case jsdef.TYPEOF:			return "String";								
		case jsdef.VOID:			return _this.UNTYPED;	
		case jsdef.THIS:			return Compiler.currentClass || "Function";
		
		//=============================================================================================================================
		case jsdef.ASSIGN:		    
		    var type1 = _this.typesys(Node[0],Compiler); 
		    var type2 = _this.typesys(Node[1],Compiler);		    
		    return TYPE_CHECK(Node, type1, type2);		    

		//=============================================================================================================================
		case jsdef.AND:
		case jsdef.OR:
			var type1 = _this.typesys(Node[0], Compiler);
			var type2 = _this.typesys(Node[1], Compiler);
			return TYPE_CHECK(Node, type1, type2);
		
		//=============================================================================================================================
		case jsdef.HOOK:
			var type1 = _this.typesys(Node[1], Compiler);
			var	type2 = _this.typesys(Node[2], Compiler);
			return TYPE_CHECK(Node, type1, type2, "Type mismatch: "+type1+" and "+type2);
			
		//=============================================================================================================================
		case jsdef.PLUS:
		case jsdef.MINUS:
		case jsdef.MUL:
		case jsdef.DIV:
		case jsdef.MOD:
			var operation = "", op = "";				
			if (Node.type == jsdef.PLUS) op = "PLUS";
			else if (Node.type == jsdef.MINUS) op = "MINUS";
			else if (Node.type == jsdef.MUL) op = "MUL";
			else if (Node.type == jsdef.DIV) op = "DIV";
			else if (Node.type == jsdef.MOD) op = "MOD";				
			operation = this.typerules.implicit[op];				
			var type1 = _this.typesys(Node[0], Compiler);
			var type2 = _this.typesys(Node[1], Compiler);				
			if(operation[type1]) 
			{
				if(operation[type1].hasOwnProperty(type2)) 
					return operation[type1][type2];
				else  
					return TYPE_CHECK(Node, type1, type2);
			}
			return TYPE_CHECK(Node, type1, type2, "Illegal operation "+op+" on: "+type1+" and "+type2);				
		
		//=============================================================================================================================
		case jsdef.INCREMENT:
		case jsdef.DECREMENT:
		case jsdef.UNARY_PLUS:
		case jsdef.UNARY_MINUS:
			var type = _this.typesys(Node[0], Compiler);			
			if (~this.typerules.explicit.__UNARY__.indexOf(type)) {
				return "Number";
			} 
			else 
			{
				var op = "";
				if (Node.type == jsdef.INCREMENT) {
					Compiler.NewError({type:TypeError, message:"Illegal operation INCREMENT on: "+type}, Node);
				} else if (Node.type == jsdef.DECREMENT) {
					Compiler.NewError({type:TypeError, message:"Illegal operation DECREMENT on: "+type}, Node);
				} else TYPE_CHECK(Node, type, "Number");
			}		
			return type;

		//=============================================================================================================================
		case jsdef.BITWISE_AND:
		case jsdef.BITWISE_OR:
		case jsdef.BITWISE_XOR:
		case jsdef.LSH:
		case jsdef.RSH:
		case jsdef.URSH:
			var operation = "", op = "";				
			if (Node.type == jsdef.BITWISE_AND) op = "&";
			else if (Node.type == jsdef.BITWISE_OR) op = "|";
			else if (Node.type == jsdef.BITWISE_XOR) op = "^";
			else if (Node.type == jsdef.LSH) op = "<<";
			else if (Node.type == jsdef.RSH) op = ">>";
			else if (Node.type == jsdef.URSH) op = ">>>";				
			operation = this.typerules.implicit.BIT;				
			var type1 = _this.typesys(Node[0], Compiler);
			var type2 = _this.typesys(Node[1], Compiler);				
			return operation[type1] ? 
				   (operation[type1].hasOwnProperty(type2) ? operation[type1][type2] : TYPE_CHECK(Node, type1, type2)) 
				   : TYPE_CHECK(Node, type1, type2, "Illegal operation "+op+" on: "+type1+" and "+type2);
		
		//=============================================================================================================================
		case jsdef.VAR:			
			for (var item in Node) 
			{
				if(!isFinite(item))continue;
				
				if (typeof Node[item].vartype == _this.UNTYPED) 
					Compiler.NewWarning({type:TypeError, message:"Missing type declaration for var " + Node[item].value}, Node);
					
				if (Node[item].initializer) 
				{
					//If we're inside an object, tag it
					if (Node[item].initializer.type == jsdef.OBJECT_INIT) 
					{
						Node[item].initializer.assignedTo = Node[item].value;
					}
					
					//Is this is a function expression?
					if (Node[item].initializer.type == jsdef.FUNCTION) 
					{
						Node[item].value.returntype = Node[item].initializer.returntype;
					} 
					
					var type = _this.typesys(Node[item].initializer, Compiler);
					TYPE_CHECK(Node, Node[item].vartype, type);
				}						
			}
			break;
			
		//=============================================================================================================================
		case jsdef.FUNCTION:
			break; 
			
		case jsdef.RETURN:			
			var type1 = Compiler.functionReturnTypes[Compiler.functionReturnTypes.length-1];
			var type2 = _this.typesys(Node.value, Compiler);				
			TYPE_CHECK(Node, type1, type2, "Illegal return type");			
			break;
		
		case jsdef.INDEX:	
		case jsdef.CALL:				
		case jsdef.DOT:   		
		
			var type = _this.UNTYPED;
			var reduced = reduceProps(Node);
		    if(reduced && reduced.length)
		    {
			    type = getIdentifierDataType(reduced[0], Node.type);
			                     			    
			    if(type!=_this.UNTYPED)
			    {
				    var cls = Compiler.SymbolTable.getClassSymbol(type);
				    var isProto = cls!=null && cls.proto; // Relax strict if prototype
			    	var out=[]; out.push(reduced[0]);
					for(var i=1;i<reduced.length;i++)
					{          
						if(!isNaN(reduced[i])) return "Object";
						if(reduced[i] instanceof Object) return "Object";
						
						out.push(reduced[i]);			
						cls = Compiler.SymbolTable.getClassSymbol(type);
						if(!cls) 
						{
							Compiler.NewError({type:ReferenceError, message:"Class not found "+type}, Node);
							return _this.UNTYPED;
						}
						isProto |= cls.proto;										
						var member = Compiler.SymbolTable.getMemberSymbol(cls, reduced[i]); 
						if(!member) 
						{
							if(!isProto)
								Compiler.NewError({type:ReferenceError, message:"Illegal dynamic member access "+out.join(".")}, Node);
							return _this.UNTYPED;
						}  
						 
						// Check arguments too
						if(Node.type==jsdef.CALL && i==reduced.length-1 && member.parameters.length)
						{							
							var list = JSPath.apply(".*{.type === " + jsdef.LIST + "}", Node);													
							
							var count = 0;
							for(var j in list[0])
							{
								if(!isFinite(j)) break;
								count++;
							}
							
							for(var j=0; j<member.parameters.length; j++)
							{														
								var type1 = member.parameters[j].datatype;
								if(type1)
								{
									var param = list[0][j];
									if(param)
									{
										var type2 = _this.typesys(param, Compiler);
										TYPE_CHECK(Node, type1, type2);									
									}
								} 
							}
							
							if(count>member.parameters.length)
								Compiler.NewError({type:ReferenceError, message:"Function " + member.name + " does not take "+count+" arguments"}, Node);							
							//else if(count<member.parameters.length)
							//	Compiler.NewWarning({type:ReferenceError, message:"Function " + member.name + " does not take only "+count+" arguments"}, Node);							
						}
						
						type = member.datatype || _this.UNTYPED;
						if(type==_this.UNTYPED) break;
					}					
					if(Node.type!=jsdef.CALL && type==_this.UNTYPED && !isProto) 
					{						
						Compiler.NewWarning({type:ReferenceError, message:"Illegal dynamic member access "+out.join(".")}, Node);
					}
			    }
		    }
			return type;			
		
		//=============================================================================================================================
		case jsdef.PROPERTY_INIT:
			break;
			
		}  //switch							
	};
};


