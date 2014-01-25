#ifndef __CANVASRENDERINGCONTEXT2D_HPP__
#define __CANVASRENDERINGCONTEXT2D_HPP__

#include "Coconut2D.hpp"
#include "HTMLImageElement.hpp"
#include "HTMLCanvasElement.hpp"
#include "HTMLCanvasContext.hpp"
#include "CocoFont.hpp"

class CanvasRenderingContext2D : public HTMLCanvasContext
{
public:
	ImageData* __imageData;
	float globalAlpha;
	String lineCap;
	float lineDashOffset;
	String lineJoin;
	float lineWidth;
	float miterLimit;
	float shadowBlur;
	String shadowColor;
	float shadowOffsetX;
	float shadowOffsetY;
	int strokeStyle;
	String textAlign;
	String textBaseline;
	String globalCompositeOperation;
	String __fillStyle;
	String __fontSetting;
	CocoFont* __font;
	CanvasRenderingContext2D(HTMLCanvasElement* canvas) : HTMLCanvasContext(canvas) {}
	~CanvasRenderingContext2D();
	void arc(float x, float y, float radius, float startAngle, float endAngle, bool anticlockwise = false);
	void arcTo(float x1, float y1, float x2, float y2, float radius);
	void beginPath();
	void bezierCurveTo(float cp1x, float cp1y, float cp2x, float cp2y, float x, float y);
	void clearRect(float x, float y, float width, float height);
	void clip();
	void closePath();
	ImageData* createImageData(float width, float height);
	HTMLCanvasGradient* createLinearGradient(float x0, float y0, float x1, float y1);
	HTMLCanvasPattern* createPattern(Image* image, String repetition);
	HTMLCanvasGradient* createRadialGradient(float x0, float y0, float r0, float x1, float y1, float r1);
	bool drawCustomFocusRing(HTMLElement* element);
	void drawSystemFocusRing(HTMLElement* element);
	void fill();
	void fillRect(float x, float y, float width, float height);
	ImageData* getImageData(float x, float y, float width, float height);
	void getLineDash();
	bool isPointInPath(float x, float y);
	bool isPointInStroke(float x, float y);
	void lineTo(float x, float y);
	void moveTo(float x, float y);
	void quadraticCurveTo(float cpx, float cpy, float x, float y);
	void rect(float x, float y, float width, float height);
	void restore();
	void rotate(float angle);
	void save();
	void scale(float x, float y);
	void scrollPathIntoView();
	void setLineDash(Array<float> segments);
	void setTransform(float m11, float m12, float m21, float m22, float dx, float dy);
	void stroke();
	void strokeRect(float x, float y, float w, float h);
	void strokeText(String text, float x, float y, float maxWidth = 0.0);
	void transform(float m11, float m12, float m21, float m22, float dx, float dy);
	void translate(float x, float y);
	void drawImage(Image* image, float a1, float a2, float a3 = 0.0, float a4 = 0.0, float a5 = 0.0, float a6 = 0.0, float a7 = 0.0, float a8 = 0.0);
	void putImageData(ImageData* imagedata, float dx, float dy, float dirtyX = 0.0, float dirtyY = 0.0, float dirtyWidth = 0.0, float dirtyHeight = 0.0);
	void fillText(String text, float x, float y, float maxWidth = 0.0);
	HTMLTextMetrics* measureText(String text);
};

#endif
