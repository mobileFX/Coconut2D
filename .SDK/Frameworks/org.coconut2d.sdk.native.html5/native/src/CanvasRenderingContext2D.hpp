/* ***** BEGIN LICENSE BLOCK *****
*
* Copyright (C) 2013-2016 www.mobilefx.com
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
//	   ______                            ____                 __          _             ______            __            __ ___   ____
//	  / ____/___ _____ _   ______ ______/ __ \___  ____  ____/ /__  _____(_)___  ____ _/ ____/___  ____  / /____  _  __/ /|__ \ / __ \
//	 / /   / __ `/ __ \ | / / __ `/ ___/ /_/ / _ \/ __ \/ __  / _ \/ ___/ / __ \/ __ `/ /   / __ \/ __ \/ __/ _ \| |/_/ __/_/ // / / /
//	/ /___/ /_/ / / / / |/ / /_/ (__  ) _, _/  __/ / / / /_/ /  __/ /  / / / / / /_/ / /___/ /_/ / / / / /_/  __/>  </ /_/ __// /_/ /
//	\____/\__,_/_/ /_/|___/\__,_/____/_/ |_|\___/_/ /_/\__,_/\___/_/  /_/_/ /_/\__, /\____/\____/_/ /_/\__/\___/_/|_|\__/____/_____/
//	                                                                          /____/
// ==================================================================================================================================

#ifndef __CanvasRenderingContext2D_H__
#define __CanvasRenderingContext2D_H__

#include "Coconut2D.hpp"

#include "HTMLElement.hpp"

#include "HTMLCanvasElement.hpp"
#include "HTMLImageElement.hpp"
#include "HTMLCanvasGradient.hpp"
#include "HTMLImageData.hpp"
#include "HTMLFontFace.hpp"

#define CANVAS_MAX_STATES 64

/////////////////////////////////////////////////////////////////////////////////////////////////////////
enum CANVAS_TEXT_DRAWING_MODE
{
	TEXT_DRAW_PATHS,
	TEXT_DRAW_GLYPHS
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
enum CANVAS_TEXT_BASELINE
{
	TEXT_BASELINE_ALPHABETIC,
	TEXT_BASELINE_TOP,
	TEXT_BASELINE_BOTTOM,
	TEXT_BASELINE_MIDDLE,
	TEXT_BASELINE_IDEOGRAPHIC,
	TEXT_BASELINE_HANGING
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
class HTMLTextMetrics
{
public:
	double width;
	double height;
	double actualBoundingBoxLeft;
	double actualBoundingBoxRight;
	double actualBoundingBoxAscent;
	double actualBoundingBoxDescent;
	double emHeightAscent;
	double emHeightDescent;
	double alphabeticBaseline;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
struct ContextArguments
{
	bool stencil;
	ContextArguments()
	{
		stencil = false;
	};
	ContextArguments(ContextArguments* T)
	{
		stencil = T->stencil;
	};
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
class Point
{
public:
	T x, y;
	Point(T x, T y) : x(x), y(y) {}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
struct native_context_state_t
{
	double globalAlpha;

	// Fill
	rgba_t fillColor;
	cairo_pattern_t* fillPattern;
	cairo_pattern_t* fillGradient;

	// Stroke
	rgba_t strokeColor;
	cairo_pattern_t* strokePattern;
	cairo_pattern_t* strokeGradient;

	// Patterns Fill / Stroke
	cairo_filter_t patternQuality;

	// Text
	short textAlignment;
	short textBaseline;
	CANVAS_TEXT_DRAWING_MODE textDrawingMode;

	// Shadow
	rgba_t shadow;
	int shadowBlur;
	double shadowOffsetX;
	double shadowOffsetY;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
class CanvasRenderingContext2D
{
public:

	HTMLCanvasElement* canvas;
	cairo_t* cairo_ctx;

	inline void setContext(cairo_t *ctx)
	{
		cairo_ctx = ctx;
	}

	bool imageSmoothingEnabled;
	bool mozImageSmoothingEnabled;
	bool oImageSmoothingEnabled;
	bool webkitImageSmoothingEnabled;

	CanvasRenderingContext2D(HTMLCanvasElement* canvas);
	~CanvasRenderingContext2D();

protected:

	cairo_path_t* path;
	short statePtr;
	native_context_state_t *states[CANVAS_MAX_STATES];

public:

	native_context_state_t *state;

	//==============================================================================
	// Internals

	void __savePath();
	void __restorePath();
	void __saveState();
	void __restoreState();
	String __getFilter();
	void __setFilter(const String& v);
	String __getAntiAlias();
	void __setAntiAlias(const String& aa);
	void __blur(cairo_surface_t *surface, double radius);
	void __setPatternQuality(String quality);
	String __getPatternQuality();
	void inline __setSourceRGBA(const rgba_t& color);
	void inline __setSourceRGBA(cairo_t *ctx, const rgba_t& color);
	inline bool __hasShadow();
	void __renderShadow(void (fn)(cairo_t *cr));
	void __fill(bool preserve = false);
	void __stroke(bool preserve = false);
	void __setTextAlignment(short v);
	void __setTextBaseline(short v);
	void __setTextDrawingMode(const String& mode);
	void __setTextPath(String *str, double x, double y);
	void __setTextPath(String str, double x, double y);
	void __setFontFace(HTMLFontFace *face, double size);
	void __drawImage(cairo_surface_t *surface, double sx, double sy, double sw, double sh, double dx, double dy, double dw, double dh);
	void __BitBltToHDC(int32_t ptr);

	//==============================================================================
	// CanvasRenderingContext2D API

public:

	// State (OK)
	void save();
	void restore();

	// Transformations (OK)
	void rotate(double angle);
	void scale(double sx, double sy);
	void translate(double tx, double ty);
	void transform(double  xx, double  yx, double  xy, double  yy, double  x0, double  y0);
	void setTransform(double  xx, double  yx, double  xy, double  yy, double  x0, double  y0);
	void resetTransform();

	// Compositing (OK)
	double __get_globalAlpha();
	void __set_globalAlpha(double n);
	String __get_globalCompositeOperation();
	void __set_globalCompositeOperation(String type);

	// Colors and Styles (OK)
	void __set_strokeStyle(const String& color);
	void __set_strokeStyle(CanvasGradient* grad);
	void __set_fillStyle(const String& color);
	void __set_fillStyle(CanvasGradient* grad);

	// Gradients (OK)
	CanvasGradient* createLinearGradient(double x0, double y0, double x1, double y1);
	CanvasGradient* createRadialGradient(double x0, double y0, double r0, double x1, double y1, double r1);
	CanvasGradient* createPattern(Image* src, String repetition);
	CanvasGradient* createPattern(HTMLCanvasElement* src, String repetition);
	CanvasGradient* createPattern(CanvasRenderingContext2D* src, String repetition);

	// Shadows (OK)
	void __set_shadowBlur(int v);
	double __get_shadowBlur();
	void __set_shadowColor(String color);
	String __get_shadowColor();
	double __get_shadowOffsetX();
	void __set_shadowOffsetX(double v);
	double __get_shadowOffsetY();
	void __set_shadowOffsetY(double v);

	// Rects (OK)
	void clearRect(double x, double y, double width, double height);
	void fillRect(double x, double y, double width, double height);
	void strokeRect(double x, double y, double width, double height);

	// Paths (OK)
	void beginPath();
	void closePath();
	void moveTo(double x, double y);
	void lineTo(double x, double y);
	void bezierCurveTo(double x1, double y1, double x2, double y2, double x3, double y3);
	void quadraticCurveTo(double x1, double y1, double x2, double y2);
	void arc(double xc, double yc, double radius, double angle1, double angle2, bool anticlockwise);
	void arcTo(double x0, double y0, double x1, double y1, double radius);
	void rect(double x, double y, double width, double height);

	// Drawing Paths (OK)
	void fill();
	void stroke();
	void clip();
	bool isPointInPath();
	bool isPointInPath(double x, double y);

	// Text (OK)
	void fillText(const String& text, const double& x, const double& y);
	void strokeText(const String& text, const double& x, const double& y);
	HTMLTextMetrics* measureText(const String& str);

	// Font	(OK)
	void __set_font(const String& css3font);
	void set_font(const String& family, const double& size, const String& style, const String& weight);
	void set_textAlign(const String& align);
	void set_textBaseLine(const String& value);

	// Drawing Images (OK)
	void drawImage(Image* img, double sx, double sy, double sw, double sh, double dx, double dy, double dw, double dh);
	void drawImage(HTMLCanvasElement* canvas, double sx, double sy, double sw, double sh, double dx, double dy, double dw, double dh);

	// Pixel Manipulation (OK)
	ImageData* createImageData(uint32_t w, uint32_t h);
	void putImageData(ImageData *imageData, int32_t dx, int32_t dy, int32_t sx, int32_t sy, int32_t sw, int32_t sh);
	ImageData* getImageData(int32_t sx, int32_t sy, int32_t sw, int32_t sh);

	// Line caps/joins (OK)
	double __get_lineWidth();
	void __set_lineWidth(double n);
	String __get_lineCap();
	void __set_lineCap(String type);
	String __get_lineJoin();
	void __set_lineJoin(String value);
	double __get_miterLimit();
	void __set_miterLimit(double n);

	// Dashed Lines	(OK)
	void setLineDash(Array<int32_t>* dash);
	std::vector<double>* getLineDash();
	double __get_lineDashOffset();
	void __set_lineDashOffset(double offset);
};

#endif /* __CAIRO_CANVAS_H__ */

