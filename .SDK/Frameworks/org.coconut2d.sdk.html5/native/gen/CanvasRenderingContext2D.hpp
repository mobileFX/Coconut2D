#ifndef __CANVASRENDERINGCONTEXT2D_HPP__
#define __CANVASRENDERINGCONTEXT2D_HPP__

#include "Coconut2D.hpp"
#include "HTMLCanvasContext.hpp"

class PathLine
{
public:
	float x0;
	float y0;
	float x1;
	float y1;
	PathLine(float _x0, float _y0, float _x1, float _y1);
};

class CanvasRenderingContext2D : public HTMLCanvasContext
{
public:
	const Number DRAWWINDOW_DRAW_CARET = 1;
	const Number DRAWWINDOW_DO_NOT_FLUSH = 2;
	const Number DRAWWINDOW_DRAW_VIEW = 4;
	const Number DRAWWINDOW_USE_WIDGET_LAYERS = 8;
	const Number DRAWWINDOW_ASYNC_DECODE_IMAGES = 16;
	float globalAlpha;
	String lineCap;
	float lineDashOffset;
	String lineJoin;
	float miterLimit;
	float shadowBlur;
	String shadowColor;
	float shadowOffsetX;
	float shadowOffsetY;
	String textAlign;
	String textBaseline;
	String globalCompositeOperation;
	float __lineWidth;
	String __fillStyle;
	Array<float>* __fillColor;
	String __strokeStyle;
	Array<float>* __strokeColor;
	String __fontSetting;
	CocoFont* __font;
	float __curX;
	float __curY;
	Array<PathLine*>* __pathLines;
	CanvasRenderingContext2D(HTMLCanvasElement* canvas);
	~CanvasRenderingContext2D();
	void arc(float x, float y, float radius, float startAngle, float endAngle, bool anticlockwise = false);
	void arcTo(float x1, float y1, float x2, float y2, float radius);
	void bezierCurveTo(float cp1x, float cp1y, float cp2x, float cp2y, float x, float y);
	void clip();
	void closePath();
	ImageData* createImageData(float width, float height);
	HTMLCanvasGradient* createLinearGradient(float x0, float y0, float x1, float y1);
	HTMLCanvasPattern* createPattern(Image* image, String repetition);
	HTMLCanvasGradient* createRadialGradient(float x0, float y0, float r0, float x1, float y1, float r1);
	bool drawCustomFocusRing(HTMLElement* element);
	void drawSystemFocusRing(HTMLElement* element);
	void fill();
	ImageData* getImageData(float x, float y, float width, float height);
	void getLineDash();
	bool isPointInPath(float x, float y);
	bool isPointInStroke(float x, float y);
	void quadraticCurveTo(float cpx, float cpy, float x, float y);
	void rect(float x, float y, float width, float height);
	void restore();
	void rotate(float angle);
	void save();
	void scale(float x, float y);
	void scrollPathIntoView();
	void setLineDash(Array<float>* segments);
	void setTransform(float m11, float m12, float m21, float m22, float dx, float dy);
	void strokeRect(float x, float y, float w, float h);
	void strokeText(String text, float x, float y, float maxWidth = 0.0);
	void transform(float m11, float m12, float m21, float m22, float dx, float dy);
	void translate(float x, float y);
	void drawImage(Image* image, float a1, float a2, float a3 = 0.0, float a4 = 0.0, float a5 = 0.0, float a6 = 0.0, float a7 = 0.0, float a8 = 0.0);
	void putImageData(ImageData* imagedata, float dx, float dy, float dirtyX = 0.0, float dirtyY = 0.0, float dirtyWidth = 0.0, float dirtyHeight = 0.0);
	void beginPath();
	void moveTo(float x, float y);
	void lineTo(float x, float y);
	void stroke();
	String __get_fillStyle();
	void __set_fillStyle(String v);
	String __get_strokeStyle();
	void __set_strokeStyle(String v);
	float __get_lineWidth();
	void __set_lineWidth(float v);
	String __get_font();
	void __set_font(String v);
	void fillText(String text, float x, float y, float maxWidth = 0.0);
	void fillRect(float x, float y, float width, float height);
	void clearRect(float x, float y, float width, float height);
	HTMLTextMetrics* measureText(String text);
};

#endif
