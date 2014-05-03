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
//	   ______                _____           _       __     ______                      _ __
//	  / ____/___  _________ / ___/__________(_)___  / /_   / ____/___  ____ ___  ____  (_) /__  _____
//	 / /   / __ \/ ___/ __ \\__ \/ ___/ ___/ / __ \/ __/  / /   / __ \/ __ `__ \/ __ \/ / / _ \/ ___/
//	/ /___/ /_/ / /__/ /_/ /__/ / /__/ /  / / /_/ / /_   / /___/ /_/ / / / / / / /_/ / / /  __/ /
//	\____/\____/\___/\____/____/\___/_/  /_/ .___/\__/   \____/\____/_/ /_/ /_/ .___/_/_/\___/_/
//	                                      /_/                                /_/
// ==================================================================================================================================

function CompilerAnalyzerPlugin(compiler)
{
	var _this = this._this = compiler;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Create a non-enumerable metata entry on an object
	_this.SET_METADATA = function(node, metaname, metadata)
	{
		Object.defineProperty(node, metaname, {enumerable:false, value:metadata});
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Generic AST descend.
	// Usage: _this.descend("string id of this descend", node_to_start_descending, checker_function);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.descend = function(visitedId, node, checkFn)
	{
		if(!node || !checkFn || !visitedId) return;
		if(node["__visited__"+visitedId]) return;
		_this.SET_METADATA(node, "__visited__"+visitedId, true);
		if(checkFn && checkFn(node)) return;
		for(var item in node)
		{
			if(/^(base_init_params|constructorNode|destructorNode|identifier_first|identifier_last|identifiers_list|inClass|inDot|inFunction|overloadOf|overloads|params|returnPaths|tokenizer|__end|__fileLineOffset|__filePosOffset|__start|__visited|abstract|blockId|contextId|defaultIndex|end|extends|file|isConstructor|isDestructor|isLoop|length|line_end|line_start|name|nodeType|optional|path|postfix|private|protected|public|push|readOnly|returntype|scopeId|source|start|state|static|subtype|top|type|vartype|virtual|xmlvartype|symbol|parent|ast|scope|states)$/.test(item)) continue;
			if(typeof node[item] == 'object'  && node[item])
			{
				var stop = _this.descend(visitedId,node[item],checkFn);
				//if(stop) return true;
			}
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Analyze CocoScript code for potential memory leaks.
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.detectMemoryLeaks = function()
	{
		// Memory leaks from jsdef.NEW inside a function that is node returned and not deleted
		/*
		_this.descend("memory_leaks_check", _this.ast, function(node)
		{
			if(node.type==jsdef.FUNCTION)
			{

			}
		});
		*/

	};
}

