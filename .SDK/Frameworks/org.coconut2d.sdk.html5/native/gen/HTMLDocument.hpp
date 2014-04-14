#ifndef __HTMLDOCUMENT_HPP__
#define __HTMLDOCUMENT_HPP__

#include "Coconut2D.hpp"

class HTMLDocument
{
public:
	HTMLElement* body;
	HTMLDocument();
	~HTMLDocument();
	HTMLCanvasElement* createElement(String tagName);
};

#endif
