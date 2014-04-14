#include "CocoText.hpp"
#include "HTMLCanvasElement.hpp"
#include "CanvasRenderingContext2D.hpp"
#include "HTMLDocument.hpp"
#include "HTMLCanvasContext.hpp"
#include "HTMLTextMetrics.hpp"

CanvasRenderingContext2D* CocoText::c2d;

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoTextStyle::CocoTextStyle(String ff, int fsp, String fs, String fw, bool u, int r, int g, int b, int a, int br, int bg, int bb, int ba)
{
	fontFamily = ff;
	fontSizePixels = fsp;
	fontStyle = fs;
	fontWeight = fw;
	underline = u;
	color = new Array<int> ();
	color->push(r);
	color->push(g);
	color->push(b);
	color->push(a);
	bgcolor = new Array<int> ();
	bgcolor->push(br);
	bgcolor->push(bg);
	bgcolor->push(bb);
	bgcolor->push(ba);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoTextStyle::~CocoTextStyle()
{
	if(color)
	{
		color = (delete color, nullptr);
	}
	if(bgcolor)
	{
		bgcolor = (delete bgcolor, nullptr);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int CocoText::npo2(int i)
{
	--i;
	i |= i >> 1;
	i |= i >> 2;
	i |= i >> 4;
	i |= i >> 8;
	i |= i >> 16;
	return ++i;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoText::init(int width, int height)
{
	HTMLCanvasElement* canvas = document->createElement(String("canvas"));
	canvas->width = ((float)npo2(width));
	canvas->height = ((float)npo2(height));
	c2d = ((CanvasRenderingContext2D*)canvas->getContext(String("2d")));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoText::CocoText()
{
	styles = new Array<CocoTextStyle*> ();
	indices = new Array<int> ();
	mappings = new Array<int> ();
	lineBreaks = new Array<int> ();
	lineWidths = new Array<int> ();
	lineHeights = new Array<int> ();
	totalHeight = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoText::~CocoText()
{
	if(styles)
	{
		styles = (delete styles, nullptr);
	}
	if(indices)
	{
		indices = (delete indices, nullptr);
	}
	if(mappings)
	{
		mappings = (delete mappings, nullptr);
	}
	if(lineBreaks)
	{
		lineBreaks = (delete lineBreaks, nullptr);
	}
	if(lineWidths)
	{
		lineWidths = (delete lineWidths, nullptr);
	}
	if(lineHeights)
	{
		lineHeights = (delete lineHeights, nullptr);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoText::wrap(int width)
{
	lineBreaks->clear();
	lineWidths->clear();
	lineHeights->clear();
	totalHeight = 0;
	int lineWidth = 0;
	int lineHeight = 0;
	for(int i = 0; i < indices->size(); i++)
	{
		CocoTextStyle* style = (*styles)[(*mappings)[i]];
		lineHeight = std::max(lineHeight, style->fontSizePixels);
		c2d->__set_font(style->fontStyle + String(" normal ") + style->fontWeight + String(" ") + (String(toString(style->fontSizePixels))) + String("px ") + style->fontFamily);
		int to = i + 1 < indices->size() ? (*indices)[i + 1] : str.size();
		for(int r = (*indices)[i]; r < to; r++)
		{
			int charWidth = c2d->measureText((str.substr(r, 1)))->width;
			if(lineWidth + charWidth > width)
			{
				if(lineWidth == 0)
				{
					throw CocoException(String("Too small width!"));
				}
				lineBreaks->push(r);
				lineWidths->push(lineWidth);
				lineHeights->push(lineHeight);
				totalHeight += lineHeight;
				lineWidth = charWidth;
				lineHeight = style->fontSizePixels;
			}
			else
			{
				lineWidth += charWidth;
			}
		}
	}
	lineWidths->push(lineWidth);
	lineHeights->push(lineHeight);
	totalHeight += lineHeight;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
String CocoText::draw(float width, float height, float halign, float valign, int bgR, int bgG, int bgB, int bgA)
{
	trace((String("CocoText::draw")).c_str());
	if(width > c2d->canvas->width || height > c2d->canvas->height)
	{
		return String("");
	}
	c2d->clearRect(0.0, 0.0, width, height);
	c2d->__set_fillStyle(String("rgba(") + (String(toString(bgR))) + String(", ") + (String(toString(bgG))) + String(", ") + (String(toString(bgB))) + String(", ") + (String(toString(bgA))) + String(")"));
	float cx = 0;
	float cy = 0;
	int currentLine = 0;
	int prevStop = 0;
	bool firstChar = true;
	for(int i = 0; i < indices->size(); i++)
	{
		CocoTextStyle* style = (*styles)[(*mappings)[i]];
		c2d->__set_font(style->fontStyle + String(" normal ") + style->fontWeight + String(" ") + (String(toString(style->fontSizePixels))) + String("px ") + style->fontFamily);
		trace((String("CocoText::draw 1")).c_str());
		int stop = 0;
		int nextStop = ((i + 1 < indices->size()) ? (*indices)[i + 1] : str.size());
		trace((String("CocoText::draw 2")).c_str());
		do
		{
			trace((String("CocoText::draw 3")).c_str());
			int nextBreak = currentLine < lineBreaks->size() ? (*lineBreaks)[currentLine] : str.size();
			trace((String("CocoText::draw 4")).c_str());
			stop = std::min(nextStop, nextBreak);
			String s = str.substring(prevStop, stop);
			trace((String("CocoText::draw 5")).c_str());
			if(firstChar)
			{
				firstChar = false;
			}
			prevStop = stop;
			float sWidth = c2d->measureText(s)->width;
			trace((String("CocoText::draw 5 1")).c_str());
			float left = (width - (*lineWidths)[currentLine]) * halign;
			trace((String("CocoText::draw 5 2")).c_str());
			float top = (float)((*lineHeights)[currentLine]) / (float)(1.125) + (height - totalHeight * 1.25) * valign;
			trace((String("CocoText::draw 5 3")).c_str());
			c2d->__set_fillStyle(String("rgba(") + (String(toString((*style->bgcolor)[0]))) + String(", ") + (String(toString((*style->bgcolor)[1]))) + String(", ") + (String(toString((*style->bgcolor)[2]))) + String(", ") + (String(toString((*style->bgcolor)[3]))) + String(")"));
			trace((String("CocoText::draw 5 4")).c_str());
			c2d->fillRect(cx + left, cy + top - (float)(((float)style->fontSizePixels)) / (float)(1.25), sWidth, ((float)style->fontSizePixels) * 1.125);
			trace((String("CocoText::draw 5 5")).c_str());
			String StyleString = String("rgba(") + (String(toString((*style->color)[0]))) + String(", ") + (String(toString((*style->color)[1]))) + String(", ") + (String(toString((*style->color)[2]))) + String(", ") + (String(toString((*style->color)[3]))) + String(")");
			trace((String("CocoText::draw 5 6")).c_str());
			c2d->__set_fillStyle(StyleString);
			trace((String("CocoText::draw 5 7")).c_str());
			c2d->__set_strokeStyle(StyleString);
			trace((String("CocoText::draw 5 8")).c_str());
			trace((String("CocoText::draw 6")).c_str());
			c2d->fillText(s, cx + left, cy + top);
			trace((String("CocoText::draw 7")).c_str());
			if(style->underline)
			{
				c2d->__set_lineWidth((float)(((float)style->fontSizePixels)) / (float)(12.0));
				c2d->beginPath();
				c2d->moveTo(cx + left, cy + top + c2d->__get_lineWidth() * 1.5);
				c2d->lineTo(cx + left + sWidth, cy + top + c2d->__get_lineWidth() * 1.5);
				c2d->stroke();
			}
			trace((String("CocoText::draw 8")).c_str());
			cx += sWidth;
			if(stop == nextBreak)
			{
				cx = 0;
				cy += ((float)(*lineHeights)[currentLine]) * 1.25;
				++currentLine;
				firstChar = true;
			}
			trace((String("CocoText::draw 9")).c_str());
		}
		while(stop != nextStop);
	}
	return c2d->canvas->toDataURL();
}
