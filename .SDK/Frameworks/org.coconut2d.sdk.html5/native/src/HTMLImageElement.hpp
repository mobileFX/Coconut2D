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
//	    __  __________  _____    ____                           ________                          __
//	   / / / /_  __/  |/  / /   /  _/___ ___  ____ _____ ____  / ____/ /__  ____ ___  ___  ____  / /_
//	  / /_/ / / / / /|_/ / /    / // __ `__ \/ __ `/ __ `/ _ \/ __/ / / _ \/ __ `__ \/ _ \/ __ \/ __/
//	 / __  / / / / /  / / /____/ // / / / / / /_/ / /_/ /  __/ /___/ /  __/ / / / / /  __/ / / / /_
//	/_/ /_/ /_/ /_/  /_/_____/___/_/ /_/ /_/\__,_/\__, /\___/_____/_/\___/_/ /_/ /_/\___/_/ /_/\__/
//	                                             /____/
// ==================================================================================================================================

#ifndef __HTMLIMAGEELEMENT_HPP__
#define __HTMLIMAGEELEMENT_HPP__

#include <string>
#include "ImageData.hpp"

class Image
{
public:
	Image() {}
	~Image();
	void load(std::string str);
	ImageData* data;
	std::string src;
	int width;
	int height;
	int naturalWidth;
	int naturalHeight;
};

#endif /* __HTMLIMAGEELEMENT_HPP__ */
