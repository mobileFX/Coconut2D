// ==================================================================================================================================
//	       _______    ____                   __  _ ____
//	      / / ___/   / __ )___  ____ ___  __/ /_(_) __/_  __
//	 __  / /\__ \   / __  / _ \/ __ `/ / / / __/ / /_/ / / /
//	/ /_/ /___/ /  / /_/ /  __/ /_/ / /_/ / /_/ / __/ /_/ /
//	\____//____/  /_____/\___/\__,_/\__,_/\__/_/_/  \__, /
//	                                               /____/
// ==================================================================================================================================
//
//  Written by Einar Lielmanis, <einar@jsbeautifier.org>
//  http://jsbeautifier.org/
//  Originally converted to javascript by Vital, <vital76@gmail.com>
//

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function do_js_beautify(js_source, indent_size, preserve_newlines, keep_array_indentation, braces_on_own_line)
{
	indent_char = ' ';
	if(indent_size == 1) indent_char = '\t';
	return js_beautify(js_source,
	{
		indent_size: indent_size,
		indent_char: indent_char,
		preserve_newlines: preserve_newlines,
		braces_on_own_line: braces_on_own_line,
		keep_array_indentation: keep_array_indentation,
		space_after_anon_function: true
	});
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function js_beautify(js_source_text, options)
{
	var input, output, token_text, last_type, last_text, last_last_text, last_word, flags, flag_store, indent_string;
	var whitespace, wordchar, punct, parser_pos, line_starters, digits;
	var prefix, token_type, do_block_just_closed;
	var wanted_newline, just_added_newline, n_newlines;

	options = options ? options : {};

	var opt_braces_on_own_line = options.braces_on_own_line ? options.braces_on_own_line : false;
	var opt_indent_size = options.indent_size ? options.indent_size : 1;
	var opt_indent_char = options.indent_char ? options.indent_char : '\t';
	var opt_preserve_newlines = typeof options.preserve_newlines === 'undefined' ? true : options.preserve_newlines;
	var opt_indent_level = options.indent_level ? options.indent_level : 0;
	var opt_space_after_anon_function = options.space_after_anon_function === 'undefined' ? false : options.space_after_anon_function;
	var opt_keep_array_indentation = typeof options.keep_array_indentation === 'undefined' ? false : options.keep_array_indentation;
	var input_length = js_source_text.length;

	just_added_newline = false;

	function trim_output()
	{
		while(output.length && (output[output.length - 1] === ' ' || output[output.length - 1] === indent_string))
		{
			output.pop();
		}
	}

	function is_array(mode)
	{
		return mode === '[EXPRESSION]' || mode === '[INDENTED-EXPRESSION]';
	}

	function print_newline(ignore_repeated)
	{
		flags.eat_next_space = false;
		if(opt_keep_array_indentation && is_array(flags.mode)) return;
		ignore_repeated = typeof ignore_repeated === 'undefined' ? true : ignore_repeated;
		flags.if_line = false;
		trim_output();
		if(!output.length) return;
		if(output[output.length - 1] !== "\n" || !ignore_repeated)
		{
			just_added_newline = true;
			output.push("\n");
		}
		for(var i = 0; i < flags.indentation_level; i += 1)
		{
			output.push(indent_string);
		}
		if(flags.var_line && flags.var_line_reindented)
		{
			if(opt_indent_char === ' ')
				output.push('    ');
			else
				output.push(indent_string);
		}
	}

	function print_single_space()
	{
		if(flags.eat_next_space)
		{
			flags.eat_next_space = false;
			return;
		}
		var last_output = ' ';
		if(output.length)
		{
			last_output = output[output.length - 1];
		}
		if(last_output !== ' ' && last_output !== '\n' && last_output !== indent_string)
		{
			output.push(' ');
		}
	}

	function print_token()
	{
		just_added_newline = false;
		flags.eat_next_space = false;
		output.push(token_text);
	}

	function indent()
	{
		flags.indentation_level += 1;
	}

	function remove_indent()
	{
		if(output.length && output[output.length - 1] === indent_string)
		{
			output.pop();
		}
	}

	function set_mode(mode)
	{
		if(flags)
		{
			flag_store.push(flags);
		}
		flags = {
			previous_mode: flags ? flags.mode : 'BLOCK',
			mode: mode,
			var_line: false,
			var_line_tainted: false,
			var_line_reindented: false,
			in_html_comment: false,
			if_line: false,
			in_case: false,
			eat_next_space: false,
			indentation_baseline: -1,
			indentation_level: (flags ? flags.indentation_level + ((flags.var_line && flags.var_line_reindented) ? 1 : 0) : opt_indent_level)
		};
	}

	function is_array(mode)
	{
		return mode === '[EXPRESSION]' || mode === '[INDENTED-EXPRESSION]';
	}

	function is_expression(mode)
	{
		return mode === '[EXPRESSION]' || mode === '[INDENTED-EXPRESSION]' || mode === '(EXPRESSION)';
	}

	function restore_mode()
	{
		do_block_just_closed = flags.mode === 'DO_BLOCK';
		if(flag_store.length > 0)
		{
			flags = flag_store.pop();
		}
	}

	function in_array(what, arr)
	{
		for(var i = 0; i < arr.length; i += 1)
		{
			if(arr[i] === what)
			{
				return true;
			}
		}
		return false;
	}

	function is_ternary_op()
	{
		var level = 0,
			colon_count = 0;
		for(var i = output.length - 1; i >= 0; i--)
		{
			switch(output[i])
			{
			case ':':
				if(level === 0)
				{
					colon_count++;
				}
				break;
			case '?':
				if(level === 0)
				{
					if(colon_count === 0)
					{
						return true;
					}
					else
					{
						colon_count--;
					}
				}
				break;
			case '{':
				if(level === 0)
				{
					return false;
				}
				level--;
				break;
			case '(':
			case '[':
				level--;
				break;
			case ')':
			case ']':
			case '}':
				level++;
				break;
			}
		}
	}

	function get_next_token()
	{
		n_newlines = 0;
		if(parser_pos >= input_length)
		{
			return ['', 'TK_EOF'];
		}
		wanted_newline = false;
		var c = input.charAt(parser_pos);
		parser_pos += 1;
		var keep_whitespace = opt_keep_array_indentation && is_array(flags.mode);
		if(keep_whitespace)
		{
			var whitespace_count = 0;
			while(in_array(c, whitespace))
			{
				if(c === "\n")
				{
					trim_output();
					output.push("\n");
					just_added_newline = true;
					whitespace_count = 0;
				}
				else
				{
					if(c === '\t')
					{
						whitespace_count += 4;
					}
					else
					{
						whitespace_count += 1;
					}
				}
				if(parser_pos >= input_length)
				{
					return ['', 'TK_EOF'];
				}
				c = input.charAt(parser_pos);
				parser_pos += 1;
			}
			if(flags.indentation_baseline === -1)
			{
				flags.indentation_baseline = whitespace_count;
			}
			if(just_added_newline)
			{
				var i;
				for(i = 0; i < flags.indentation_level + 1; i += 1)
				{
					output.push(indent_string);
				}
				if(flags.indentation_baseline !== -1)
				{
					for(i = 0; i < whitespace_count - flags.indentation_baseline; i++)
					{
						output.push(' ');
					}
				}
			}
		}
		else
		{
			while(in_array(c, whitespace))
			{
				if(c === "\n")
				{
					n_newlines += 1;
				}
				if(parser_pos >= input_length)
				{
					return ['', 'TK_EOF'];
				}
				c = input.charAt(parser_pos);
				parser_pos += 1;
			}
			if(opt_preserve_newlines)
			{
				if(n_newlines > 1)
				{
					for(i = 0; i < n_newlines; i += 1)
					{
						print_newline(i === 0);
						just_added_newline = true;
					}
				}
			}
			wanted_newline = n_newlines > 0;
		}
		if(in_array(c, wordchar))
		{
			if(parser_pos < input_length)
			{
				while(in_array(input.charAt(parser_pos), wordchar))
				{
					c += input.charAt(parser_pos);
					parser_pos += 1;
					if(parser_pos === input_length)
					{
						break;
					}
				}
			}
			if(parser_pos !== input_length && c.match(/^[0-9]+[Ee]$/) && (input.charAt(parser_pos) === '-' || input.charAt(parser_pos) === '+'))
			{
				var sign = input.charAt(parser_pos);
				parser_pos += 1;
				var t = get_next_token(parser_pos);
				c += sign + t[0];
				return [c, 'TK_WORD'];
			}
			if(c === 'in')
			{
				return [c, 'TK_OPERATOR'];
			}
			if(wanted_newline && last_type !== 'TK_OPERATOR' && !flags.if_line && (opt_preserve_newlines || last_text !== 'var'))
			{
				print_newline();
			}
			return [c, 'TK_WORD'];
		}
		if(c === '(' || c === '[')
		{
			return [c, 'TK_START_EXPR'];
		}
		if(c === ')' || c === ']')
		{
			return [c, 'TK_END_EXPR'];
		}
		if(c === '{')
		{
			return [c, 'TK_START_BLOCK'];
		}
		if(c === '}')
		{
			return [c, 'TK_END_BLOCK'];
		}
		if(c === ';')
		{
			return [c, 'TK_SEMICOLON'];
		}
		if(c === '/')
		{
			var comment = '';
			var inline_comment = true;
			if(input.charAt(parser_pos) === '*')
			{
				parser_pos += 1;
				if(parser_pos < input_length)
				{
					while(!(input.charAt(parser_pos) === '*' && input.charAt(parser_pos + 1) && input.charAt(parser_pos + 1) === '/') && parser_pos < input_length)
					{
						c = input.charAt(parser_pos);
						comment += c;
						if(c === '\x0d' || c === '\x0a')
						{
							inline_comment = false;
						}
						parser_pos += 1;
						if(parser_pos >= input_length)
						{
							break;
						}
					}
				}
				parser_pos += 2;
				if(inline_comment)
				{
					return ['/*' + comment + '*/', 'TK_INLINE_COMMENT'];
				}
				else
				{
					return ['/*' + comment + '*/', 'TK_BLOCK_COMMENT'];
				}
			}
			if(input.charAt(parser_pos) === '/')
			{
				comment = c;
				while(input.charAt(parser_pos) !== "\x0d" && input.charAt(parser_pos) !== "\x0a")
				{
					comment += input.charAt(parser_pos);
					parser_pos += 1;
					if(parser_pos >= input_length)
					{
						break;
					}
				}
				parser_pos += 1;
				if(wanted_newline)
				{
					print_newline();
				}
				return [comment, 'TK_COMMENT'];
			}
		}
		if(c === "'" ||
			c === '"' |
			(c === '/' && ((last_type === 'TK_WORD' && in_array(last_text, ['return', 'do'])) || (last_type === 'TK_START_EXPR' || last_type === 'TK_START_BLOCK' || last_type === 'TK_END_BLOCK' || last_type === 'TK_OPERATOR' || last_type === 'TK_EQUALS' || last_type === 'TK_EOF' || last_type === 'TK_SEMICOLON'))))
		{
			var sep = c;
			var esc = false;
			var resulting_string = c;
			if(parser_pos < input_length)
			{
				if(sep === '/')
				{
					var in_char_class = false;
					while(esc || in_char_class || input.charAt(parser_pos) !== sep)
					{
						resulting_string += input.charAt(parser_pos);
						if(!esc)
						{
							esc = input.charAt(parser_pos) === '\\';
							if(input.charAt(parser_pos) === '[')
							{
								in_char_class = true;
							}
							else if(input.charAt(parser_pos) === ']')
							{
								in_char_class = false;
							}
						}
						else
						{
							esc = false;
						}
						parser_pos += 1;
						if(parser_pos >= input_length)
						{
							return [resulting_string, 'TK_STRING'];
						}
					}
				}
				else
				{
					while(esc || input.charAt(parser_pos) !== sep)
					{
						resulting_string += input.charAt(parser_pos);
						if(!esc)
						{
							esc = input.charAt(parser_pos) === '\\';
						}
						else
						{
							esc = false;
						}
						parser_pos += 1;
						if(parser_pos >= input_length)
						{
							return [resulting_string, 'TK_STRING'];
						}
					}
				}
			}
			parser_pos += 1;
			resulting_string += sep;
			if(sep === '/')
			{
				while(parser_pos < input_length && in_array(input.charAt(parser_pos), wordchar))
				{
					resulting_string += input.charAt(parser_pos);
					parser_pos += 1;
				}
			}
			return [resulting_string, 'TK_STRING'];
		}
		if(c === '#')
		{
			var sharp = '#';
			if(parser_pos < input_length && in_array(input.charAt(parser_pos), digits))
			{
				do {
					c = input.charAt(parser_pos);
					sharp += c;
					parser_pos += 1;
				} while (parser_pos < input_length && c !== '#' && c !== '=');
				if(c === '#')
				{
				}
				else if(input.charAt(parser_pos) === '[' && input.charAt(parser_pos + 1) === ']')
				{
					sharp += '[]';
					parser_pos += 2;
				}
				else if(input.charAt(parser_pos) === '{' && input.charAt(parser_pos + 1) === '}')
				{
					sharp += '{}';
					parser_pos += 2;
				}
				return [sharp, 'TK_WORD'];
			}
		}
		if(c === '<' && input.substring(parser_pos - 1, parser_pos + 3) === '<!--')
		{
			parser_pos += 3;
			flags.in_html_comment = true;
			return ['<!--', 'TK_COMMENT'];
		}
		if(c === '-' && flags.in_html_comment && input.substring(parser_pos - 1, parser_pos + 2) === '-->')
		{
			flags.in_html_comment = false;
			parser_pos += 2;
			if(wanted_newline)
			{
				print_newline();
			}
			return ['-->', 'TK_COMMENT'];
		}
		if(in_array(c, punct))
		{
			while(parser_pos < input_length && in_array(c + input.charAt(parser_pos), punct))
			{
				c += input.charAt(parser_pos);
				parser_pos += 1;
				if(parser_pos >= input_length)
				{
					break;
				}
			}
			if(c === '=')
			{
				return [c, 'TK_EQUALS'];
			}
			else
			{
				return [c, 'TK_OPERATOR'];
			}
		}
		return [c, 'TK_UNKNOWN'];
	}

	indent_string = '';

	while(opt_indent_size > 0)
	{
		indent_string += opt_indent_char;
		opt_indent_size -= 1;
	}

	input = js_source_text;
	last_word = '';
	last_type = 'TK_START_EXPR';
	last_text = '';
	last_last_text = '';
	output = [];
	do_block_just_closed = false;
	whitespace = "\n\r\t ".split('');
	wordchar = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_$'.split('');
	digits = '0123456789'.split('');
	punct = '+ - * / % & ++ -- = += -= *= /= %= == === != !== > < >= <= >> << >>> >>>= >>= <<= && &= | || ! !! , : ? ^ ^= |= ::'.split(' ');
	line_starters = 'continue,try,throw,return,var,if,switch,case,default,for,while,break,function'.split(',');
	flag_store = [];
	set_mode('BLOCK');
	parser_pos = 0;
	while(true)
	{
		var t = get_next_token(parser_pos);
		token_text = t[0];
		token_type = t[1];
		if(token_type === 'TK_EOF')
		{
			break;
		}
		switch(token_type)
		{
		case 'TK_START_EXPR':
			if(token_text === '[')
			{
				if(last_type === 'TK_WORD' || last_text === ')')
				{
					if(in_array(last_text, line_starters))
					{
						print_single_space();
					}
					set_mode('(EXPRESSION)');
					print_token();
					break;
				}
				if(flags.mode === '[EXPRESSION]' || flags.mode === '[INDENTED-EXPRESSION]')
				{
					if(last_last_text === ']' && last_text === ',')
					{
						if(flags.mode === '[EXPRESSION]')
						{
							flags.mode = '[INDENTED-EXPRESSION]';
							if(!opt_keep_array_indentation)
							{
								indent();
							}
						}
						set_mode('[EXPRESSION]');
						if(!opt_keep_array_indentation)
						{
							print_newline();
						}
					}
					else if(last_text === '[')
					{
						if(flags.mode === '[EXPRESSION]')
						{
							flags.mode = '[INDENTED-EXPRESSION]';
							if(!opt_keep_array_indentation)
							{
								indent();
							}
						}
						set_mode('[EXPRESSION]');
						if(!opt_keep_array_indentation)
						{
							print_newline();
						}
					}
					else
					{
						set_mode('[EXPRESSION]');
					}
				}
				else
				{
					set_mode('[EXPRESSION]');
				}
			}
			else
			{
				set_mode('(EXPRESSION)');
			}
			if(last_text === ';' || last_type === 'TK_START_BLOCK')
			{
				print_newline();
			}
			else if(last_type === 'TK_END_EXPR' || last_type === 'TK_START_EXPR' || last_type === 'TK_END_BLOCK' || last_text === '.')
			{
			}
			else if(last_type !== 'TK_WORD' && last_type !== 'TK_OPERATOR')
			{
				print_single_space();
			}
			else if(last_word === 'function')
			{
				if(opt_space_after_anon_function)
				{
					print_single_space();
				}
			}
			else if(in_array(last_text, line_starters) || last_text === 'catch')
			{
				print_single_space();
			}
			print_token();
			break;
		case 'TK_END_EXPR':
			if(token_text === ']')
			{
				if(opt_keep_array_indentation)
				{
					if(last_text === '}')
					{
						remove_indent();
						print_token();
						restore_mode();
						break;
					}
				}
				else
				{
					if(flags.mode === '[INDENTED-EXPRESSION]')
					{
						if(last_text === ']')
						{
							restore_mode();
							print_newline();
							print_token();
							break;
						}
					}
				}
			}
			restore_mode();
			print_token();
			break;
		case 'TK_START_BLOCK':
			if(last_word === 'do')
			{
				set_mode('DO_BLOCK');
			}
			else
			{
				set_mode('BLOCK');
			}
			if(opt_braces_on_own_line)
			{
				if(last_type !== 'TK_OPERATOR')
				{
					if(last_text == 'return')
					{
						print_single_space();
					}
					else
					{
						print_newline(true);
					}
				}
				print_token();
				indent();
			}
			else
			{
				if(last_type !== 'TK_OPERATOR' && last_type !== 'TK_START_EXPR')
				{
					if(last_type === 'TK_START_BLOCK')
					{
						print_newline();
					}
					else
					{
						print_single_space();
					}
				}
				else
				{
					if(is_array(flags.previous_mode) && last_text === ',')
					{
						print_newline();
					}
				}
				indent();
				print_token();
			}
			break;
		case 'TK_END_BLOCK':
			restore_mode();
			if(opt_braces_on_own_line)
			{
				print_newline();
				print_token();
			}
			else
			{
				if(last_type === 'TK_START_BLOCK')
				{
					if(just_added_newline)
					{
						remove_indent();
					}
					else
					{
						trim_output();
					}
				}
				else
				{
					print_newline();
				}
				print_token();
			}
			break;
		case 'TK_WORD':
			if(do_block_just_closed)
			{
				print_single_space();
				print_token();
				print_single_space();
				do_block_just_closed = false;
				break;
			}
			if(token_text === 'function')
			{
				if((just_added_newline || last_text === ';') && last_text !== '{')
				{
					n_newlines = just_added_newline ? n_newlines : 0;
					for(var i = 0; i < 2 - n_newlines; i++)
					{
						print_newline(false);
					}
				}
			}
			if(token_text === 'case' || token_text === 'default')
			{
				if(last_text === ':')
				{
					remove_indent();
				}
				else
				{
					flags.indentation_level--;
					print_newline();
					flags.indentation_level++;
				}
				print_token();
				flags.in_case = true;
				break;
			}
			prefix = 'NONE';
			if(last_type === 'TK_END_BLOCK')
			{
				if(!in_array(token_text.toLowerCase(), ['else', 'catch', 'finally']))
				{
					prefix = 'NEWLINE';
				}
				else
				{
					if(opt_braces_on_own_line)
					{
						prefix = 'NEWLINE';
					}
					else
					{
						prefix = 'SPACE';
						print_single_space();
					}
				}
			}
			else if(last_type === 'TK_SEMICOLON' && (flags.mode === 'BLOCK' || flags.mode === 'DO_BLOCK'))
			{
				prefix = 'NEWLINE';
			}
			else if(last_type === 'TK_SEMICOLON' && is_expression(flags.mode))
			{
				prefix = 'SPACE';
			}
			else if(last_type === 'TK_STRING')
			{
				prefix = 'NEWLINE';
			}
			else if(last_type === 'TK_WORD')
			{
				prefix = 'SPACE';
			}
			else if(last_type === 'TK_START_BLOCK')
			{
				prefix = 'NEWLINE';
			}
			else if(last_type === 'TK_END_EXPR')
			{
				print_single_space();
				prefix = 'NEWLINE';
			}
			if(last_type !== 'TK_END_BLOCK' && in_array(token_text.toLowerCase(), ['else', 'catch', 'finally']))
			{
				print_newline();
			}
			else if(in_array(token_text, line_starters) || prefix === 'NEWLINE')
			{
				if(last_text === 'else')
				{
					print_single_space();
				}
				else if((last_type === 'TK_START_EXPR' || last_text === '=' || last_text === ',') && token_text === 'function')
				{
				}
				else if(last_text === 'return' || last_text === 'throw')
				{
					print_single_space();
				}
				else if(last_type !== 'TK_END_EXPR')
				{
					if((last_type !== 'TK_START_EXPR' || token_text !== 'var') && last_text !== ':')
					{
						if(token_text === 'if' && last_word === 'else' && last_text !== '{')
						{
							print_single_space();
						}
						else
						{
							print_newline();
						}
					}
				}
				else
				{
					if(in_array(token_text, line_starters) && last_text !== ')')
					{
						print_newline();
					}
				}
			}
			else if(is_array(flags.mode) && last_text === ',' && last_last_text === '}')
			{
				print_newline();
			}
			else if(prefix === 'SPACE')
			{
				print_single_space();
			}
			print_token();
			last_word = token_text;
			if(token_text === 'var')
			{
				flags.var_line = true;
				flags.var_line_reindented = false;
				flags.var_line_tainted = false;
			}
			if(token_text === 'if' || token_text === 'else')
			{
				flags.if_line = true;
			}
			break;
		case 'TK_SEMICOLON':
			print_token();
			flags.var_line = false;
			flags.var_line_reindented = false;
			break;
		case 'TK_STRING':
			if(last_type === 'TK_START_BLOCK' || last_type === 'TK_END_BLOCK' || last_type === 'TK_SEMICOLON')
			{
				print_newline();
			}
			else if(last_type === 'TK_WORD')
			{
				print_single_space();
			}
			print_token();
			break;
		case 'TK_EQUALS':
			if(flags.var_line)
			{
				flags.var_line_tainted = true;
			}
			print_single_space();
			print_token();
			print_single_space();
			break;
		case 'TK_OPERATOR':
			var space_before = true;
			var space_after = true;
			if(flags.var_line && token_text === ',' && (is_expression(flags.mode)))
			{
				flags.var_line_tainted = false;
			}
			if(flags.var_line)
			{
				if(token_text === ',')
				{
					if(flags.var_line_tainted)
					{
						print_token();
						flags.var_line_reindented = true;
						flags.var_line_tainted = false;
						print_newline();
						break;
					}
					else
					{
						flags.var_line_tainted = false;
					}
				}
			}
			if(last_text === 'return' || last_text === 'throw')
			{
				print_single_space();
				print_token();
				break;
			}
			if(token_text === ':' && flags.in_case)
			{
				print_token();
				print_newline();
				flags.in_case = false;
				break;
			}
			if(token_text === '::')
			{
				print_token();
				break;
			}
			if(token_text === ',')
			{
				if(flags.var_line)
				{
					if(flags.var_line_tainted)
					{
						print_token();
						print_newline();
						flags.var_line_tainted = false;
					}
					else
					{
						print_token();
						print_single_space();
					}
				}
				else if(last_type === 'TK_END_BLOCK' && flags.mode !== "(EXPRESSION)")
				{
					print_token();
					if(flags.mode === 'OBJECT' && last_text === '}')
					{
						print_newline();
					}
					else
					{
						print_single_space();
					}
				}
				else
				{
					if(flags.mode === 'OBJECT')
					{
						print_token();
						print_newline();
					}
					else
					{
						print_token();
						print_single_space();
					}
				}
				break;
			}
			else if(in_array(token_text, ['--', '++', '!']) || (in_array(token_text, ['-', '+']) && (in_array(last_type, ['TK_START_BLOCK', 'TK_START_EXPR', 'TK_EQUALS', 'TK_OPERATOR']) || in_array(last_text, line_starters))))
			{
				space_before = false;
				space_after = false;
				if(last_text === ';' && is_expression(flags.mode))
				{
					space_before = true;
				}
				if(last_type === 'TK_WORD' && in_array(last_text, line_starters))
				{
					space_before = true;
				}
				if(flags.mode === 'BLOCK' && (last_text === '{' || last_text === ';'))
				{
					print_newline();
				}
			}
			else if(token_text === '.')
			{
				space_before = false;
			}
			else if(token_text === ':')
			{
				if(!is_ternary_op())
				{
					flags.mode = 'OBJECT';
					space_before = false;
				}
			}
			if(space_before)
			{
				print_single_space();
			}
			print_token();
			if(space_after)
			{
				print_single_space();
			}
			if(token_text === '!')
			{
			}
			break;
		case 'TK_BLOCK_COMMENT':
			var lines = token_text.split(/\x0a|\x0d\x0a/);
			if(/^\/\*\*/.test(token_text))
			{
				print_newline();
				output.push(lines[0]);
				for(i = 1; i < lines.length; i++)
				{
					print_newline();
					output.push(' ');
					output.push(lines[i].replace(/^\s\s*|\s\s*$/, ''));
				}
			}
			else
			{
				if(lines.length > 1)
				{
					print_newline();
					trim_output();
				}
				else
				{
					print_single_space();
				}
				for(i = 0; i < lines.length; i++)
				{
					output.push(lines[i]);
					output.push('\n');
				}
			}
			print_newline();
			break;
		case 'TK_INLINE_COMMENT':
			print_single_space();
			print_token();
			if(is_expression(flags.mode))
			{
				print_single_space();
			}
			else
			{
				print_newline();
			}
			break;
		case 'TK_COMMENT':
			if(wanted_newline)
			{
				print_newline();
			}
			else
			{
				print_single_space();
			}
			print_token();
			print_newline();
			break;
		case 'TK_UNKNOWN':
			print_token();
			break;
		}
		last_last_text = last_text;
		last_type = token_type;
		last_text = token_text;
	}
	return output.join('').replace(/[\n ]+$/, '');
}
