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

#include "Coconut2D.hpp"
#include "CanvasRenderingContext2D.hpp"
#include "WebGLRenderingContext.hpp"

/////////////////////////////////////////////////////////////////////////////
CanvasRenderingContext2D::CanvasRenderingContext2D(HTMLCanvasElement *canvas)
{
	this->canvas = canvas;
	cairo_ctx = cairo_create(canvas->_surface);
	cairo_set_line_width(cairo_ctx, 1);
	state = states[statePtr = 0] = (native_context_state_t *) malloc(sizeof(native_context_state_t));
	state->shadowBlur = 0;
	state->shadowOffsetX = state->shadowOffsetY = 0;
	state->globalAlpha = 1;
	state->textAlignment = -1;
	state->fillPattern = state->strokePattern = NULL;
	state->fillGradient = state->strokeGradient = NULL;
	state->textBaseline = TEXT_BASELINE_ALPHABETIC;
	rgba_t transparent = { 0, 0, 0, 1 };
	rgba_t transparent_black = { 0, 0, 0, 0 };
	state->fillColor = transparent;
	state->strokeColor = transparent;
	state->shadow = transparent_black;
	state->patternQuality = CAIRO_FILTER_GOOD;
	state->textDrawingMode = TEXT_DRAW_PATHS;
	imageSmoothingEnabled = false;
	mozImageSmoothingEnabled = false;
	oImageSmoothingEnabled = false;
	webkitImageSmoothingEnabled = false;
}

/////////////////////////////////////////////////////////////////////////////
CanvasRenderingContext2D::~CanvasRenderingContext2D()
{
	while (statePtr >= 0)
	{
		free(states[statePtr--]);
	}
	cairo_destroy(cairo_ctx);
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::save()
{
	cairo_save(cairo_ctx);
	__saveState();
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::restore()
{
	cairo_restore(cairo_ctx);
	__restoreState();
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::__saveState()
{
	if (statePtr == CANVAS_MAX_STATES) return;
	states[++statePtr] = (native_context_state_t *) malloc(sizeof(native_context_state_t));
	memcpy(states[statePtr], state, sizeof(native_context_state_t));
	state = states[statePtr];
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::__restoreState()
{
	if (0 == statePtr) return;
	free(states[statePtr]);
	states[statePtr] = NULL;
	state = states[--statePtr];
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::__savePath()
{
	path = cairo_copy_path_flat(cairo_ctx);
	cairo_new_path(cairo_ctx);
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::__restorePath()
{
	cairo_new_path(cairo_ctx);
	cairo_append_path(cairo_ctx, path);
	cairo_path_destroy(path);
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::__fill(bool preserve)
{
	if (state->fillPattern)
	{
		cairo_set_source(cairo_ctx, state->fillPattern);
		cairo_pattern_set_extend(cairo_get_source(cairo_ctx), CAIRO_EXTEND_REPEAT);
		// TODO repeat/repeat-x/repeat-y
	}
	else if (state->fillGradient)
	{
		cairo_pattern_set_filter(state->fillGradient, state->patternQuality);
		cairo_set_source(cairo_ctx, state->fillGradient);
	}
	else
	{
		__setSourceRGBA(state->fillColor);
	}

	if (preserve)
	{
		__hasShadow() ? __renderShadow(cairo_fill_preserve) : cairo_fill_preserve(cairo_ctx);
	}
	else
	{
		__hasShadow() ? __renderShadow(cairo_fill) : cairo_fill(cairo_ctx);
	}
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::__stroke(bool preserve)
{
	if (state->strokePattern)
	{
		cairo_set_source(cairo_ctx, state->strokePattern);
		cairo_pattern_set_extend(cairo_get_source(cairo_ctx), CAIRO_EXTEND_REPEAT);
	}
	else if (state->strokeGradient)
	{
		cairo_pattern_set_filter(state->strokeGradient, state->patternQuality);
		cairo_set_source(cairo_ctx, state->strokeGradient);
	}
	else
	{
		__setSourceRGBA(state->strokeColor);
	}

	if (preserve)
	{
		__hasShadow() ? __renderShadow(cairo_stroke_preserve) : cairo_stroke_preserve(cairo_ctx);
	}
	else
	{
		__hasShadow() ? __renderShadow(cairo_stroke) : cairo_stroke(cairo_ctx);
	}
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::__renderShadow(void (fn)(cairo_t *cr))
{
	cairo_path_t *path = cairo_copy_path_flat(cairo_ctx);
	cairo_save(cairo_ctx);

	// shadowOffset is unaffected by current transform
	cairo_matrix_t path_matrix;
	cairo_get_matrix(cairo_ctx, &path_matrix);
	cairo_identity_matrix(cairo_ctx);

	// Apply shadow
	cairo_push_group(cairo_ctx);

	// No need to invoke blur if shadowBlur is 0
	if (state->shadowBlur)
	{
		// find out extent of path
		double x1, y1, x2, y2;
		if (fn == cairo_fill || fn == cairo_fill_preserve)
		{
			cairo_fill_extents(cairo_ctx, &x1, &y1, &x2, &y2);
		}
		else
		{
			cairo_stroke_extents(cairo_ctx, &x1, &y1, &x2, &y2);
		}

		// create new image surface that size + padding for blurring
		double dx = x2 - x1, dy = y2 - y1;
		cairo_user_to_device_distance(cairo_ctx, &dx, &dy);
		int pad = state->shadowBlur * 2;
		cairo_surface_t *shadow_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, (int) (dx + 2 * pad), (int) (dy + 2 * pad));
		cairo_t *shadow_context = cairo_create(shadow_surface);

		// transform path to the right place
		cairo_translate(shadow_context, pad - x1, pad - y1);
		cairo_transform(shadow_context, &path_matrix);

		// draw the path and blur
		cairo_set_line_width(shadow_context, cairo_get_line_width(cairo_ctx));
		cairo_new_path(shadow_context);
		cairo_append_path(shadow_context, path);
		__setSourceRGBA(shadow_context, state->shadow);
		fn(shadow_context);
		__blur(shadow_surface, state->shadowBlur);

		// paint to original context
		cairo_set_source_surface(cairo_ctx, shadow_surface, x1 - pad + state->shadowOffsetX + 1, y1 - pad + state->shadowOffsetY + 1);
		cairo_paint(cairo_ctx);
		cairo_destroy(shadow_context);
		cairo_surface_destroy(shadow_surface);
	}
	else
	{
		// Offset first, then apply path's transform
		cairo_translate(cairo_ctx, state->shadowOffsetX, state->shadowOffsetY);
		cairo_transform(cairo_ctx, &path_matrix);

		// Apply shadow
		cairo_new_path(cairo_ctx);
		cairo_append_path(cairo_ctx, path);
		__setSourceRGBA(state->shadow);

		fn(cairo_ctx);
	}

	// Paint the shadow
	cairo_pop_group_to_source(cairo_ctx);
	cairo_paint(cairo_ctx);

	// Restore state
	cairo_restore(cairo_ctx);
	cairo_new_path(cairo_ctx);
	cairo_append_path(cairo_ctx, path);
	fn(cairo_ctx);

	cairo_path_destroy(path);
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::__setSourceRGBA(const rgba_t& color)
{
	__setSourceRGBA(cairo_ctx, color);
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::__setSourceRGBA(cairo_t *ctx, const rgba_t& color)
{
	cairo_set_source_rgba(ctx, color.r, color.g, color.b, color.a * state->globalAlpha);
}

/////////////////////////////////////////////////////////////////////////////
bool CanvasRenderingContext2D::__hasShadow()
{
	return state->shadow.a && (state->shadowBlur || state->shadowOffsetX || state->shadowOffsetY);
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::__blur(cairo_surface_t *surface, double radius)
{
	radius = radius * 0.57735f + 0.5f;

	int width = cairo_image_surface_get_width(surface);
	int height = cairo_image_surface_get_height(surface);

	unsigned* precalc = (unsigned*) malloc(width*height*sizeof(unsigned));

	cairo_surface_flush(surface);
	unsigned char* src = cairo_image_surface_get_data(surface);

	double mul = 1.f / ((radius * 2)*(radius * 2));
	int channel;

	// The number of times to perform the averaging. According to Wikipedia,
	// three iterations is good enough to pass for a Gaussian.
	const int MAX_ITERATIONS = 3;
	int iteration;

	for (iteration = 0; iteration < MAX_ITERATIONS; iteration++)
	{
		for (channel = 0; channel < 4; channel++)
		{
			int x, y;

			// precomputation step
			unsigned char* pix = src;
			unsigned* pre = precalc;

			pix += channel;
			for (y = 0; y<height; y++)
			{
				for (x = 0; x<width; x++)
				{
					int tot = pix[0];
					if (x>0) tot += pre[-1];
					if (y>0) tot += pre[-width];
					if (x>0 && y>0) tot -= pre[-width - 1];
					*pre++ = tot;
					pix += 4;
				}
			}

			// blur step.
			pix = src + (int) radius * width * 4 + (int) radius * 4 + channel;
			for (y = (int) radius; y<(int) (height - radius); y++)
			{
				for (x = (int) radius; x<(int) (width - radius); x++)
				{
					int l = (int) (x < radius ? 0 : x - radius);
					int t = (int) (y < radius ? 0 : y - radius);
					int r = (int) (x + radius >= width ? width - 1 : x + radius);
					int b = (int) (y + radius >= height ? height - 1 : y + radius);
					int tot = precalc[r + b*width] + precalc[l + t*width] - precalc[l + b*width] - precalc[r + t*width];
					*pix = (unsigned char) (tot*mul);
					pix += 4;
				}
				pix += (int) radius * 2 * 4;
			}
		}
	}

	cairo_surface_mark_dirty(surface);
	free(precalc);
}

/////////////////////////////////////////////////////////////////////////////
ImageData* CanvasRenderingContext2D::createImageData(uint32_t w, uint32_t h)
{
	return new ImageData(nullptr, w, h);
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::putImageData(ImageData *imageData, int32_t dx, int32_t dy, int32_t sx, int32_t sy, int32_t sw, int32_t sh)
{
	ImageData* cim = canvas->toImageData();
	uint8_t* dst = cim->data;
	delete cim;

	uint8_t* src = imageData->data;

	int srcStride = imageData->stride;
	int	dstStride = canvas->stride();

	// fix up negative height, width
	if (sw < 0) sx += sw, sw = -sw;
	if (sh < 0) sy += sh, sh = -sh;

	// clamp the left edge
	if (sx < 0) sw += sx, sx = 0;
	if (sy < 0) sh += sy, sy = 0;

	// clamp the right edge
	if (sx + sw > imageData->width) sw = imageData->width - sx;
	if (sy + sh > imageData->height) sh = imageData->height - sy;

	// start destination at source offset
	dx += sx;
	dy += sy;

	// chop off outlying source data
	if (dx < 0) sw += dx, sx -= dx, dx = 0;
	if (dy < 0) sh += dy, sy -= dy, dy = 0;

	// clamp width at canvas size
	int cols = math_min(sw, canvas->width - dx);
	int rows = math_min(sh, canvas->height - dy);

	if (cols <= 0 || rows <= 0) return;

	src += sy * srcStride + sx * 4;
	dst += dstStride * dy + 4 * dx;
	for (int y = 0; y < rows; ++y)
	{
		uint8_t *dstRow = dst;
		uint8_t *srcRow = src;
		for (int x = 0; x < cols; ++x)
		{
			uint8_t r = *srcRow++;
			uint8_t g = *srcRow++;
			uint8_t b = *srcRow++;
			uint8_t a = *srcRow++;

			if (a == 0)
			{
				*dstRow++ = 0;
				*dstRow++ = 0;
				*dstRow++ = 0;
				*dstRow++ = 0;
			}
			else if (a == 255)
			{
				*dstRow++ = b;
				*dstRow++ = g;
				*dstRow++ = r;
				*dstRow++ = a;
			}
			else
			{
				double alpha = (double) a / 255;
				*dstRow++ = CLAMPTOBYTE((int)(b * alpha));
				*dstRow++ = CLAMPTOBYTE((int)(g * alpha));
				*dstRow++ = CLAMPTOBYTE((int)(r * alpha));
				*dstRow++ = a;
			}
		}
		dst += dstStride;
		src += srcStride;
	}

	cairo_surface_mark_dirty_rectangle(canvas->_surface, dx, dy, cols, rows);
}

/////////////////////////////////////////////////////////////////////////////
ImageData* CanvasRenderingContext2D::getImageData(int32_t sx, int32_t sy, int32_t sw, int32_t sh)
{
	if (sw < 0)
	{
		sx += sw;
		sw = -sw;
	}
	if (sh < 0)
	{
		sy += sh;
		sh = -sh;
	}

	if (sx + sw > canvas->width) sw = (canvas->width - sx);
	if (sy + sh > canvas->height) sh = (canvas->height - sy);

	if (sw <= 0) sw = 1;
	if (sh <= 0) sh = 1;

	// Pixels outside the canvas must be returned as transparent black
	if (sx < 0)
	{
		sw += sx;
		sx = 0;
	}
	if (sy < 0)
	{
		sh += sy;
		sy = 0;
	}

	int size = sw * sh * 4;

	int srcStride = canvas->stride();
	int dstStride = sw * 4;

	ImageData* im = canvas->toImageData();
	uint8_t *src = im->data;
	delete im;

	ImageData* out_im = new ImageData(nullptr, sw, sh, true);
	uint8_t* dst = out_im->data;

	// Normalize data (ARGB -> RGBA)
	for (int y = 0; y < sh; ++y)
	{
		uint32_t *row = (uint32_t *) (src + srcStride * (y + sy));
		for (int x = 0; x < sw; ++x)
		{
			int bx = x * 4;
			uint32_t *pixel = row + x + sx;
			uint8_t a = *pixel >> 24;
			uint8_t r = *pixel >> 16;
			uint8_t g = *pixel >> 8;
			uint8_t b = *pixel;
			dst[bx + 3] = a;

			if (a == 0 || a == 255)
			{
				dst[bx + 0] = r;
				dst[bx + 1] = g;
				dst[bx + 2] = b;
			}
			else
			{
				double alpha = (double) a / 255;
				dst[bx + 0] = (int) ((double) r / alpha);
				dst[bx + 1] = (int) ((double) g / alpha);
				dst[bx + 2] = (int) ((double) b / alpha);
			}
		}
		dst += dstStride;
	}

	return out_im;
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::drawImage(Image* img, double sx, double sy, double sw, double sh, double dx, double dy, double dw, double dh)
{
	__drawImage(img->_surface, sx, sy, sw, sh, dx, dy, dw, dh);
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::drawImage(HTMLCanvasElement* canvas, double sx, double sy, double sw, double sh, double dx, double dy, double dw, double dh)
{
	__drawImage(canvas->_surface, sx, sy, sw, sh, dx, dy, dw, dh);
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::__drawImage(cairo_surface_t *surface, double sx, double sy, double sw, double sh, double dx, double dy, double dw, double dh)
{
	canvas->__resurface();

	// Start draw
	cairo_save(cairo_ctx);

	// Scale src
	double fx = (double) dw / sw;
	double fy = (double) dh / sh;

	if (dw != sw || dh != sh)
	{
		cairo_scale(cairo_ctx, fx, fy);
		dx /= fx;
		dy /= fy;
		dw /= fx;
		dh /= fy;
	}

	// apply shadow if there is one
	if (__hasShadow())
	{
		if (state->shadowBlur)
		{
			// we need to create a new surface in order to blur
			int pad = state->shadowBlur * 2;
			cairo_surface_t *shadow_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, (int) (dw + 2 * pad), (int) (dh + 2 * pad));
			cairo_t *shadow_context = cairo_create(shadow_surface);

			// mask and blur
			__setSourceRGBA(shadow_context, state->shadow);
			cairo_mask_surface(shadow_context, surface, pad, pad);
			__blur(shadow_surface, state->shadowBlur);

			// paint
			// @note: ShadowBlur looks different in each browser. This implementation matches chrome as close as possible.
			//        The 1.4 offset comes from visual tests with Chrome. I have read the spec and part of the shadowBlur
			//        implementation, and its not immediately clear why an offset is necessary, but without it, the result
			//        in chrome is different.
			cairo_set_source_surface(cairo_ctx, shadow_surface, dx - sx + (state->shadowOffsetX / fx) - pad + 1.4, dy - sy + (state->shadowOffsetY / fy) - pad + 1.4);
			cairo_paint(cairo_ctx);

			// cleanup
			cairo_destroy(shadow_context);
			cairo_surface_destroy(shadow_surface);
		}
		else
		{
			__setSourceRGBA(state->shadow);
			cairo_mask_surface(cairo_ctx, surface, dx - sx + (state->shadowOffsetX / fx), dy - sy + (state->shadowOffsetY / fy));
		}
	}

	__savePath();
	cairo_rectangle(cairo_ctx, dx, dy, dw, dh);
	cairo_clip(cairo_ctx);
	__restorePath();

	// Paint
	cairo_set_source_surface(cairo_ctx, surface, dx - sx, dy - sy);
	cairo_pattern_set_filter(cairo_get_source(cairo_ctx), state->patternQuality);
	cairo_paint_with_alpha(cairo_ctx, state->globalAlpha);
	cairo_restore(cairo_ctx);
}

/////////////////////////////////////////////////////////////////////////////
double CanvasRenderingContext2D::__get_globalAlpha()
{
	return state->globalAlpha;
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::__set_globalAlpha(double n)
{
	if (n >= 0 && n <= 1)
	{
		state->globalAlpha = n;
	}
}

/////////////////////////////////////////////////////////////////////////////
String CanvasRenderingContext2D::__get_globalCompositeOperation()
{
	const char *op = "source-over";

	switch (cairo_get_operator(cairo_ctx))
	{
	case CAIRO_OPERATOR_ATOP: op = "source-atop"; break;
	case CAIRO_OPERATOR_IN: op = "source-in"; break;
	case CAIRO_OPERATOR_OUT: op = "source-out"; break;
	case CAIRO_OPERATOR_XOR: op = "xor"; break;
	case CAIRO_OPERATOR_DEST_ATOP: op = "destination-atop"; break;
	case CAIRO_OPERATOR_DEST_IN: op = "destination-in"; break;
	case CAIRO_OPERATOR_DEST_OUT: op = "destination-out"; break;
	case CAIRO_OPERATOR_DEST_OVER: op = "destination-over"; break;
	case CAIRO_OPERATOR_CLEAR: op = "clear"; break;
	case CAIRO_OPERATOR_SOURCE: op = "source"; break;
	case CAIRO_OPERATOR_DEST: op = "dest"; break;
	case CAIRO_OPERATOR_OVER: op = "over"; break;
	case CAIRO_OPERATOR_SATURATE: op = "saturate"; break;

	case CAIRO_OPERATOR_LIGHTEN: op = "lighten"; break;
	case CAIRO_OPERATOR_ADD: op = "add"; break;
	case CAIRO_OPERATOR_DARKEN: op = "darker"; break;
	case CAIRO_OPERATOR_MULTIPLY: op = "multiply"; break;
	case CAIRO_OPERATOR_SCREEN: op = "screen"; break;
	case CAIRO_OPERATOR_OVERLAY: op = "overlay"; break;
	case CAIRO_OPERATOR_HARD_LIGHT: op = "hard-light"; break;
	case CAIRO_OPERATOR_SOFT_LIGHT: op = "soft-light"; break;
	case CAIRO_OPERATOR_HSL_HUE: op = "hsl-hue"; break;
	case CAIRO_OPERATOR_HSL_SATURATION: op = "hsl-saturation"; break;
	case CAIRO_OPERATOR_HSL_COLOR: op = "hsl-color"; break;
	case CAIRO_OPERATOR_HSL_LUMINOSITY: op = "hsl-luminosity"; break;
	case CAIRO_OPERATOR_COLOR_DODGE: op = "color-dodge"; break;
	case CAIRO_OPERATOR_COLOR_BURN: op = "color-burn"; break;
	case CAIRO_OPERATOR_DIFFERENCE: op = "difference"; break;
	case CAIRO_OPERATOR_EXCLUSION: op = "exclusion"; break;
	}

	return String(op);
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::__setPatternQuality(String quality)
{
	if (quality == "fast")
	{
		state->patternQuality = CAIRO_FILTER_FAST;
	}
	else if (quality == "good")
	{
		state->patternQuality = CAIRO_FILTER_GOOD;
	}
	else if (quality == "best")
	{
		state->patternQuality = CAIRO_FILTER_BEST;
	}
	else if (quality == "nearest")
	{
		state->patternQuality = CAIRO_FILTER_NEAREST;
	}
	else if (quality == "bilinear")
	{
		state->patternQuality = CAIRO_FILTER_BILINEAR;
	}
}

/////////////////////////////////////////////////////////////////////////////
String CanvasRenderingContext2D::__getPatternQuality()
{
	String quality;

	switch (state->patternQuality)
	{
	case CAIRO_FILTER_FAST: quality = "fast"; break;
	case CAIRO_FILTER_BEST: quality = "best"; break;
	case CAIRO_FILTER_NEAREST: quality = "nearest"; break;
	case CAIRO_FILTER_BILINEAR: quality = "bilinear"; break;
	default: quality = "good";
	}

	return quality;
}

/////////////////////////////////////////////////////////////////////////////
CanvasGradient* CanvasRenderingContext2D::createLinearGradient(double x0, double y0, double x1, double y1)
{
	return new CanvasGradient(x0, y0, x1, y1);
}

/////////////////////////////////////////////////////////////////////////////
CanvasGradient* CanvasRenderingContext2D::createRadialGradient(double x0, double y0, double r0, double x1, double y1, double r1)
{
	return new CanvasGradient(x0, y0, r0, x1, y1, r1);
}

/////////////////////////////////////////////////////////////////////////////
CanvasGradient* CanvasRenderingContext2D::createPattern(Image* src, String repetition)
{
	return new CanvasGradient(src->_surface, src->width, src->height, repetition);
}

/////////////////////////////////////////////////////////////////////////////
CanvasGradient* CanvasRenderingContext2D::createPattern(HTMLCanvasElement* src, String repetition)
{
	return new CanvasGradient(src->_surface, src->width, src->height, repetition);
}

/////////////////////////////////////////////////////////////////////////////
CanvasGradient* CanvasRenderingContext2D::createPattern(CanvasRenderingContext2D* src, String repetition)
{
	return new CanvasGradient(src->canvas->_surface, src->canvas->width, src->canvas->height, repetition);
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::__set_globalCompositeOperation(String type)
{
	if (type == "xor")
	{
		cairo_set_operator(cairo_ctx, CAIRO_OPERATOR_XOR);
	}
	else if (type == "source-atop")
	{
		cairo_set_operator(cairo_ctx, CAIRO_OPERATOR_ATOP);
	}
	else if (type == "source-in")
	{
		cairo_set_operator(cairo_ctx, CAIRO_OPERATOR_IN);
	}
	else if (type == "source-out")
	{
		cairo_set_operator(cairo_ctx, CAIRO_OPERATOR_OUT);
	}
	else if (type == "destination-atop")
	{
		cairo_set_operator(cairo_ctx, CAIRO_OPERATOR_DEST_ATOP);
	}
	else if (type == "destination-in")
	{
		cairo_set_operator(cairo_ctx, CAIRO_OPERATOR_DEST_IN);
	}
	else if (type == "destination-out")
	{
		cairo_set_operator(cairo_ctx, CAIRO_OPERATOR_DEST_OUT);
	}
	else if (type == "destination-over")
	{
		cairo_set_operator(cairo_ctx, CAIRO_OPERATOR_DEST_OVER);
	}
	else if (type == "clear")
	{
		cairo_set_operator(cairo_ctx, CAIRO_OPERATOR_CLEAR);
	}
	else if (type == "source")
	{
		cairo_set_operator(cairo_ctx, CAIRO_OPERATOR_SOURCE);
	}
	else if (type == "dest")
	{
		cairo_set_operator(cairo_ctx, CAIRO_OPERATOR_DEST);
	}
	else if (type == "saturate")
	{
		cairo_set_operator(cairo_ctx, CAIRO_OPERATOR_SATURATE);
	}
	else if (type == "over")
	{
		cairo_set_operator(cairo_ctx, CAIRO_OPERATOR_OVER);
	}
	else if (type == "add")
	{
		cairo_set_operator(cairo_ctx, CAIRO_OPERATOR_ADD);
	}
	else if (type == "lighten")
	{
		cairo_set_operator(cairo_ctx, CAIRO_OPERATOR_LIGHTEN);
	}
	else if (type == "darker")
	{
		cairo_set_operator(cairo_ctx, CAIRO_OPERATOR_DARKEN);
	}
	else if (type == "multiply")
	{
		cairo_set_operator(cairo_ctx, CAIRO_OPERATOR_MULTIPLY);
	}
	else if (type == "screen")
	{
		cairo_set_operator(cairo_ctx, CAIRO_OPERATOR_SCREEN);
	}
	else if (type == "overlay")
	{
		cairo_set_operator(cairo_ctx, CAIRO_OPERATOR_OVERLAY);
	}
	else if (type == "hard-light")
	{
		cairo_set_operator(cairo_ctx, CAIRO_OPERATOR_HARD_LIGHT);
	}
	else if (type == "soft-light")
	{
		cairo_set_operator(cairo_ctx, CAIRO_OPERATOR_SOFT_LIGHT);
	}
	else if (type == "hsl-hue")
	{
		cairo_set_operator(cairo_ctx, CAIRO_OPERATOR_HSL_HUE);
	}
	else if (type == "hsl-saturation")
	{
		cairo_set_operator(cairo_ctx, CAIRO_OPERATOR_HSL_SATURATION);
	}
	else if (type == "hsl-color")
	{
		cairo_set_operator(cairo_ctx, CAIRO_OPERATOR_HSL_COLOR);
	}
	else if (type == "hsl-luminosity")
	{
		cairo_set_operator(cairo_ctx, CAIRO_OPERATOR_HSL_LUMINOSITY);
	}
	else if (type == "color-dodge")
	{
		cairo_set_operator(cairo_ctx, CAIRO_OPERATOR_COLOR_DODGE);
	}
	else if (type == "color-burn")
	{
		cairo_set_operator(cairo_ctx, CAIRO_OPERATOR_COLOR_BURN);
	}
	else if (type == "difference")
	{
		cairo_set_operator(cairo_ctx, CAIRO_OPERATOR_DIFFERENCE);
	}
	else if (type == "exclusion")
	{
		cairo_set_operator(cairo_ctx, CAIRO_OPERATOR_EXCLUSION);
	}
	else if (type == "lighter")
	{
		cairo_set_operator(cairo_ctx, CAIRO_OPERATOR_ADD);
	}
	else
	{
		cairo_set_operator(cairo_ctx, CAIRO_OPERATOR_OVER);
	}
}

/////////////////////////////////////////////////////////////////////////////
double CanvasRenderingContext2D::__get_shadowOffsetX()
{
	return state->shadowOffsetX;
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::__set_shadowOffsetX(double v)
{
	state->shadowOffsetX = v;
}

/////////////////////////////////////////////////////////////////////////////
double CanvasRenderingContext2D::__get_shadowOffsetY()
{
	return state->shadowOffsetY;
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::__set_shadowOffsetY(double v)
{
	state->shadowOffsetY = v;
}

/////////////////////////////////////////////////////////////////////////////
double CanvasRenderingContext2D::__get_shadowBlur()
{
	return state->shadowBlur;
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::__set_shadowBlur(int n)
{
	if (n >= 0)
		state->shadowBlur = n;
}

/////////////////////////////////////////////////////////////////////////////
String CanvasRenderingContext2D::__getAntiAlias()
{
	String aa;
	switch (cairo_get_antialias(cairo_ctx))
	{
	case CAIRO_ANTIALIAS_NONE: aa = "none"; break;
	case CAIRO_ANTIALIAS_GRAY: aa = "gray"; break;
	case CAIRO_ANTIALIAS_SUBPIXEL: aa = "subpixel"; break;
	default: aa = "default";
	}
	return aa;
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::__setAntiAlias(const String& aa)
{
	cairo_antialias_t a;

	if (aa == "none")
	{
		a = CAIRO_ANTIALIAS_NONE;
	}
	else if (aa == "default")
	{
		a = CAIRO_ANTIALIAS_DEFAULT;
	}
	else if (aa == "gray")
	{
		a = CAIRO_ANTIALIAS_GRAY;
	}
	else if (aa == "subpixel")
	{
		a = CAIRO_ANTIALIAS_SUBPIXEL;
	}
	else
	{
		a = cairo_get_antialias(cairo_ctx);
	}

	cairo_set_antialias(cairo_ctx, a);
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::__setTextDrawingMode(const String& mode)
{
	if (mode == "path")
	{
		state->textDrawingMode = TEXT_DRAW_PATHS;
	}
	else if (mode == "glyph")
	{
		state->textDrawingMode = TEXT_DRAW_GLYPHS;
	}
}

/////////////////////////////////////////////////////////////////////////////
String CanvasRenderingContext2D::__getFilter()
{
	String filter;
	switch (cairo_pattern_get_filter(cairo_get_source(cairo_ctx)))
	{
	case CAIRO_FILTER_FAST: filter = "fast"; break;
	case CAIRO_FILTER_BEST: filter = "best"; break;
	case CAIRO_FILTER_NEAREST: filter = "nearest"; break;
	case CAIRO_FILTER_BILINEAR: filter = "bilinear"; break;
	default: filter = "good";
	}
	return filter;
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::__setFilter(const String& filter)
{
	cairo_filter_t f;

	if (filter == "fast")
	{
		f = CAIRO_FILTER_FAST;
	}
	else if (filter == "best")
	{
		f = CAIRO_FILTER_BEST;
	}
	else if (filter == "nearest")
	{
		f = CAIRO_FILTER_NEAREST;
	}
	else if (filter == "bilinear")
	{
		f = CAIRO_FILTER_BILINEAR;
	}
	else
	{
		f = CAIRO_FILTER_GOOD;
	}

	cairo_pattern_set_filter(cairo_get_source(cairo_ctx), f);
}

/////////////////////////////////////////////////////////////////////////////
double CanvasRenderingContext2D::__get_miterLimit()
{
	return (double) cairo_get_miter_limit(cairo_ctx);
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::__set_miterLimit(double n)
{
	if (n > 0)
	{
		cairo_set_miter_limit(cairo_ctx, n);
	}
}

/////////////////////////////////////////////////////////////////////////////
double CanvasRenderingContext2D::__get_lineWidth()
{
	return cairo_get_line_width(cairo_ctx);
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::__set_lineWidth(double n)
{
	if (n > 0 && n != std::numeric_limits<double>::infinity())
	{
		cairo_set_line_width(cairo_ctx, n);
	}
}

/////////////////////////////////////////////////////////////////////////////
String CanvasRenderingContext2D::__get_lineJoin()
{
	String join;
	switch (cairo_get_line_join(cairo_ctx))
	{
	case CAIRO_LINE_JOIN_BEVEL: join = "bevel"; break;
	case CAIRO_LINE_JOIN_ROUND: join = "round"; break;
	default: join = "miter";
	}
	return join;
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::__set_lineJoin(String value)
{
	if (value == "round")
	{
		cairo_set_line_join(cairo_ctx, CAIRO_LINE_JOIN_ROUND);
	}
	else if (value == "bevel")
	{
		cairo_set_line_join(cairo_ctx, CAIRO_LINE_JOIN_BEVEL);
	}
	else
	{
		cairo_set_line_join(cairo_ctx, CAIRO_LINE_JOIN_MITER);
	}
}

/////////////////////////////////////////////////////////////////////////////
String CanvasRenderingContext2D::__get_lineCap()
{
	String cap;
	switch (cairo_get_line_cap(cairo_ctx))
	{
	case CAIRO_LINE_CAP_ROUND: cap = "round"; break;
	case CAIRO_LINE_CAP_SQUARE: cap = "square"; break;
	default: cap = "butt";
	}
	return cap;
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::__set_lineCap(String type)
{
	if (type == "round")
	{
		cairo_set_line_cap(cairo_ctx, CAIRO_LINE_CAP_ROUND);
	}
	else if (type == "square")
	{
		cairo_set_line_cap(cairo_ctx, CAIRO_LINE_CAP_SQUARE);
	}
	else
	{
		cairo_set_line_cap(cairo_ctx, CAIRO_LINE_CAP_BUTT);
	}
}

/////////////////////////////////////////////////////////////////////////////
bool CanvasRenderingContext2D::isPointInPath(double x, double y)
{
	return (cairo_in_fill(cairo_ctx, x, y) || cairo_in_stroke(cairo_ctx, x, y));
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::__set_shadowColor(String color)
{
	short ok;
	uint32_t rgba = rgba_from_string(color.c_str(), &ok);
	if (ok)
	{
		state->shadow = rgba_create(rgba);
	}
}

/////////////////////////////////////////////////////////////////////////////
String CanvasRenderingContext2D::__get_shadowColor()
{
	char buf[64];
	rgba_to_string(state->shadow, buf, sizeof(buf));
	return String(buf);
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::__set_fillStyle(const String& color)
{
	short ok;
	uint32_t rgba = rgba_from_string(color.c_str(), &ok);
	if (!ok) return;
	state->fillPattern = state->fillGradient = NULL;
	state->fillColor = rgba_create(rgba);
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::__set_fillStyle(CanvasGradient* style)
{
	state->fillPattern = state->fillGradient = NULL;

	if (style->isPattern)
		state->fillPattern = style->_pattern;
	else
		state->fillGradient = style->_pattern;
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::__set_strokeStyle(const String& color)
{
	short ok;
	uint32_t rgba = rgba_from_string(color.c_str(), &ok);
	if (!ok) return;
	state->strokePattern = state->strokeGradient = NULL;
	state->strokeColor = rgba_create(rgba);
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::__set_strokeStyle(CanvasGradient* style)
{
	state->strokePattern = state->strokeGradient = NULL;

	if (style->isPattern)
		state->strokePattern = style->_pattern;
	else
		state->strokeGradient = style->_pattern;
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::bezierCurveTo(double x1, double y1, double x2, double y2, double x3, double y3)
{
	cairo_curve_to(cairo_ctx, x1, y1, x2, y2, x3, y3);
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::quadraticCurveTo(double x1, double y1, double x2, double y2)
{
	double x, y;
	cairo_get_current_point(cairo_ctx, &x, &y);

	if (0 == x && 0 == y)
	{
		x = x1;
		y = y1;
	}

	cairo_curve_to(cairo_ctx, x + 2.0 / 3.0 * (x1 - x), y + 2.0 / 3.0 * (y1 - y), x2 + 2.0 / 3.0 * (x1 - x2), y2 + 2.0 / 3.0 * (y1 - y2), x2, y2);
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::beginPath()
{
	cairo_new_path(cairo_ctx);
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::closePath()
{
	cairo_close_path(cairo_ctx);
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::rotate(double angle)
{
	cairo_rotate(cairo_ctx, angle);
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::transform(double  xx, double  yx, double  xy, double  yy, double  x0, double  y0)
{
	cairo_matrix_t matrix;
	cairo_matrix_init(&matrix, xx, yx, xy, yy, x0, y0);
	cairo_transform(cairo_ctx, &matrix);
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::resetTransform()
{
	cairo_identity_matrix(cairo_ctx);
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::setTransform(double  xx, double  yx, double  xy, double  yy, double  x0, double  y0)
{
	cairo_identity_matrix(cairo_ctx);
	cairo_matrix_t matrix;
	cairo_matrix_init(&matrix, xx, yx, xy, yy, x0, y0);
	cairo_transform(cairo_ctx, &matrix);
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::translate(double tx, double ty)
{
	cairo_translate(cairo_ctx, tx, ty);
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::scale(double sx, double sy)
{
	cairo_scale(cairo_ctx, sx, sy);
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::clip()
{
	cairo_clip_preserve(cairo_ctx);
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::fill()
{
	__fill(true);
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::stroke()
{
	__stroke(true);
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::fillText(const String& text, const double& x, const double& y)
{
	__savePath();

	if (state->textDrawingMode == TEXT_DRAW_GLYPHS)
	{
		__fill();
		__setTextPath(text.c_str(), x, y);
	}
	else if (state->textDrawingMode == TEXT_DRAW_PATHS)
	{
		__setTextPath(text.c_str(), x, y);
		__fill();
	}

	__restorePath();
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::strokeText(const String& text, const double& x, const double& y)
{
	__savePath();

	if (state->textDrawingMode == TEXT_DRAW_GLYPHS)
	{
		__stroke();
		__setTextPath(text.c_str(), x, y);
	}
	else if (state->textDrawingMode == TEXT_DRAW_PATHS)
	{
		__setTextPath(text.c_str(), x, y);
		__stroke();
	}

	__restorePath();
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::__setTextPath(String str, double x, double y)
{
	cairo_text_extents_t te;
	cairo_font_extents_t fe;

	// Alignment
	switch (state->textAlignment)
	{
		// center
	case 0:
		cairo_text_extents(cairo_ctx, str.c_str(), &te);
		x -= te.width / 2;
		break;

		// right
	case 1:
		cairo_text_extents(cairo_ctx, str.c_str(), &te);
		x -= te.width;
		break;
	}

	// Baseline approx
	switch (state->textBaseline)
	{
	case TEXT_BASELINE_TOP:
	case TEXT_BASELINE_HANGING:
		cairo_font_extents(cairo_ctx, &fe);
		y += fe.ascent;
		break;

	case TEXT_BASELINE_MIDDLE:
		cairo_font_extents(cairo_ctx, &fe);
		y += (fe.ascent - fe.descent) / 2;
		break;

	case TEXT_BASELINE_BOTTOM:
		cairo_font_extents(cairo_ctx, &fe);
		y -= fe.descent;
		break;
	}

	cairo_move_to(cairo_ctx, x, y);

	if (state->textDrawingMode == TEXT_DRAW_PATHS)
	{
		cairo_text_path(cairo_ctx, str.c_str());
	}
	else if (state->textDrawingMode == TEXT_DRAW_GLYPHS)
	{
		cairo_show_text(cairo_ctx, str.c_str());
	}
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::lineTo(double x, double y)
{
	cairo_line_to(cairo_ctx, x, y);
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::moveTo(double x, double y)
{
	cairo_move_to(cairo_ctx, x, y);
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::__setFontFace(HTMLFontFace *face, double size)
{
	canvas->__resurface();

	cairo_set_font_face(cairo_ctx, face->_crFace);
	cairo_set_font_size(cairo_ctx, size);
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::set_font(const String& family, const double& size, const String& style, const String& weight)
{
	canvas->__resurface();

	cairo_font_slant_t s = CAIRO_FONT_SLANT_NORMAL;
	if (style == "italic")
	{
		s = CAIRO_FONT_SLANT_ITALIC;
	}
	else if (style == "oblique")
	{
		s = CAIRO_FONT_SLANT_OBLIQUE;
	}

	cairo_font_weight_t w = CAIRO_FONT_WEIGHT_NORMAL;
	if (weight == "bold")
	{
		w = CAIRO_FONT_WEIGHT_BOLD;
	}

	cairo_select_font_face(cairo_ctx, family.c_str(), s, w);
	cairo_set_font_size(cairo_ctx, size);
}

/////////////////////////////////////////////////////////////////////////////
HTMLTextMetrics* CanvasRenderingContext2D::measureText(const String& str)
{
	canvas->__resurface();

	cairo_text_extents_t te;
	cairo_font_extents_t fe;

	cairo_text_extents(cairo_ctx, str.c_str(), &te);
	cairo_font_extents(cairo_ctx, &fe);

	double x_offset;
	switch (state->textAlignment)
	{
	case 0: // center
		x_offset = te.width / 2;
		break;

	case 1: // right
		x_offset = te.width;
		break;

	default: // left
		x_offset = 0.0;
	}

	double y_offset;

	switch (state->textBaseline)
	{
	case TEXT_BASELINE_TOP:
	case TEXT_BASELINE_HANGING:
		y_offset = fe.ascent;
		break;

	case TEXT_BASELINE_MIDDLE:
		y_offset = (fe.ascent - fe.descent) / 2;
		break;

	case TEXT_BASELINE_BOTTOM:
		y_offset = -fe.descent;
		break;

	default:
		y_offset = 0.0;
	}

	HTMLTextMetrics* t = new HTMLTextMetrics;
	t->width = te.x_advance;
	t->height = fe.ascent - y_offset;
	t->actualBoundingBoxLeft = x_offset - te.x_bearing;
	t->actualBoundingBoxRight = (te.x_bearing + te.width) - x_offset;
	t->actualBoundingBoxAscent = -(te.y_bearing + y_offset);
	t->actualBoundingBoxDescent = te.height + te.y_bearing + y_offset;
	t->emHeightAscent = fe.ascent - y_offset;
	t->emHeightDescent = fe.descent + y_offset;
	t->alphabeticBaseline = y_offset;

	return t;
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::__set_font(const String& css_font)
{
	canvas->__resurface();

	// Parse CSS3 Font
	String fontFamily;
	int32_t fontSize;
	String  fontStyle;
	String  fontWeight;

	// Parse CSS3 Font
	if (!HTMLFontFace::parseCSSFont(css_font, fontFamily, fontSize, fontStyle, fontWeight))
		return;

	#ifdef FONT_CACHE

		// Get Font Name
		String fontName = HTMLFontFace::getFontName(fontFamily, fontStyle, fontWeight);

		// Get Font from Cache
		HTMLFontFace* font = HTMLFontFace::getFont(fontName);
		if (!font) return;

		// Load font to Native context
		__setFontFace(font, (double) fontSize);

	#else

		// Load font to Native context (toy version)
		set_font(fontFamily, fontSize, fontStyle, fontWeight);

	#endif
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::__setTextBaseline(short v)
{
	state->textBaseline = v;
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::__setTextAlignment(short v)
{
	state->textAlignment = v;
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::setLineDash(Array<int32_t>* dash)
{
	uint32_t dashes = dash->size() & 1 ? dash->size() * 2 : dash->size();

	std::vector<double> a(dashes);
	for (uint32_t i=0; i<dashes; i++)
	{
	a[i] = (*dash)[(i % dash->size())];
	if (a[i] < 0 || isnan(a[i]) || isinf(a[i])) return;
	}

	double offset;
	cairo_get_dash(cairo_ctx, NULL, &offset);
	cairo_set_dash(cairo_ctx, a.data(), dashes, offset);
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::set_textBaseLine(const String& align)
{
	if (align == "top")
	{
		__setTextBaseline(TEXT_BASELINE_TOP);

	}
	else if (align == "hanging")
	{
		__setTextBaseline(TEXT_BASELINE_HANGING);
	}
	else if (align == "middle")
	{
		__setTextBaseline(TEXT_BASELINE_MIDDLE);
	}
	else if (align == "alphabetic")
	{
		__setTextBaseline(TEXT_BASELINE_ALPHABETIC);
	}
	else if (align == "ideographic")
	{
		__setTextBaseline(TEXT_BASELINE_IDEOGRAPHIC);
	}
	else if (align == "bottom")
	{
		__setTextBaseline(TEXT_BASELINE_BOTTOM);
	}
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::set_textAlign(const String& align)
{
	if (align == "start")
	{
		__setTextAlignment(2);
	}
	else if (align == "end")
	{
		__setTextAlignment(1);
	}
	else if (align == "left")
	{
		__setTextAlignment(2);
	}
	else if (align == "right")
	{
		__setTextAlignment(1);
	}
	else if (align == "center")
	{
		__setTextAlignment(0);
	}
}

/////////////////////////////////////////////////////////////////////////////
std::vector<double>* CanvasRenderingContext2D::getLineDash()
{
	int dashes = cairo_get_dash_count(cairo_ctx);
	std::vector<double>* a = new std::vector<double>;
	cairo_get_dash(cairo_ctx, a->data(), NULL);
	return a;
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::__set_lineDashOffset(double offset)
{
	int dashes = cairo_get_dash_count(cairo_ctx);
	std::vector<double> a(dashes);
	cairo_get_dash(cairo_ctx, a.data(), NULL);
	cairo_set_dash(cairo_ctx, a.data(), dashes, offset);
}

/////////////////////////////////////////////////////////////////////////////
double CanvasRenderingContext2D::__get_lineDashOffset()
{
	double offset;
	cairo_get_dash(cairo_ctx, NULL, &offset);
	return offset;
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::fillRect(double x, double y, double width, double height)
{
	if (0 == width || 0 == height) return;
	__savePath();
	cairo_rectangle(cairo_ctx, x, y, width, height);
	__fill();
	__restorePath();
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::strokeRect(double x, double y, double width, double height)
{
	if (0 == width && 0 == height) return;
	__savePath();
	cairo_rectangle(cairo_ctx, x, y, width, height);
	__stroke();
	__restorePath();
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::clearRect(double x, double y, double width, double height)
{
	if (width == 0 || height == 0) return;
	cairo_save(cairo_ctx);
	__savePath();
	cairo_rectangle(cairo_ctx, x, y, width, height);
	cairo_set_operator(cairo_ctx, CAIRO_OPERATOR_CLEAR);
	cairo_fill(cairo_ctx);
	__restorePath();
	cairo_restore(cairo_ctx);
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::rect(double x, double y, double width, double height)
{
	if (width == 0)
	{
		cairo_move_to(cairo_ctx, x, y);
		cairo_line_to(cairo_ctx, x, y + height);
	}
	else if (height == 0)
	{
		cairo_move_to(cairo_ctx, x, y);
		cairo_line_to(cairo_ctx, x + width, y);
	}
	else
	{
		cairo_rectangle(cairo_ctx, x, y, width, height);
	}
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::arc(double xc, double yc, double radius, double angle1, double angle2, bool anticlockwise)
{
	if (anticlockwise && M_PI * 2 != angle2)
	{
		cairo_arc_negative(cairo_ctx, xc, yc, radius, angle1, angle2);
	}
	else
	{
		cairo_arc(cairo_ctx, xc, yc, radius, angle1, angle2);
	}
}

/////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::arcTo(double x0, double y0, double x1, double y1, double radius)
{
	canvas->__resurface();

	// Current path point
	double x, y;
	cairo_get_current_point(cairo_ctx, &x, &y);

	Point<double> p0(x, y);
	Point<double> p1(x0, y0);
	Point<double> p2(x1, y1);

	if ((p1.x == p0.x && p1.y == p0.y)
		|| (p1.x == p2.x && p1.y == p2.y)
		|| radius == 0.f)
	{
		cairo_line_to(cairo_ctx, p1.x, p1.y);
		return;
	}

	Point<double> p1p0((p0.x - p1.x), (p0.y - p1.y));
	Point<double> p1p2((p2.x - p1.x), (p2.y - p1.y));
	double p1p0_length = sqrtd(p1p0.x * p1p0.x + p1p0.y * p1p0.y);
	double p1p2_length = sqrtd(p1p2.x * p1p2.x + p1p2.y * p1p2.y);

	double cos_phi = (p1p0.x * p1p2.x + p1p0.y * p1p2.y) / (p1p0_length * p1p2_length);

	// all points on a line logic
	if (cos_phi == -1)
	{
		cairo_line_to(cairo_ctx, p1.x, p1.y);
		return;
	}

	if (cos_phi == 1)
	{
		// add infinite far away point
		unsigned int max_length = 65535;
		double factor_max = max_length / p1p0_length;
		Point<double> ep((p0.x + factor_max * p1p0.x), (p0.y + factor_max * p1p0.y));
		cairo_line_to(cairo_ctx, ep.x, ep.y);
		return;
	}

	double tangent = radius / tan(acos(cos_phi) / 2);
	double factor_p1p0 = tangent / p1p0_length;
	Point<double> t_p1p0((p1.x + factor_p1p0 * p1p0.x), (p1.y + factor_p1p0 * p1p0.y));

	Point<double> orth_p1p0(p1p0.y, -p1p0.x);
	double orth_p1p0_length = sqrt(orth_p1p0.x * orth_p1p0.x + orth_p1p0.y * orth_p1p0.y);
	double factor_ra = radius / orth_p1p0_length;

	double cos_alpha = (orth_p1p0.x * p1p2.x + orth_p1p0.y * p1p2.y) / (orth_p1p0_length * p1p2_length);
	if (cos_alpha < 0.f)
		orth_p1p0 = Point<double>(-orth_p1p0.x, -orth_p1p0.y);

	Point<double> p((t_p1p0.x + factor_ra * orth_p1p0.x), (t_p1p0.y + factor_ra * orth_p1p0.y));

	orth_p1p0 = Point<double>(-orth_p1p0.x, -orth_p1p0.y);
	double sa = acos(orth_p1p0.x / orth_p1p0_length);

	if (orth_p1p0.y < 0.f)
		sa = 2 * M_PI - sa;

	bool anticlockwise = false;

	double factor_p1p2 = tangent / p1p2_length;
	Point<double> t_p1p2((p1.x + factor_p1p2 * p1p2.x), (p1.y + factor_p1p2 * p1p2.y));
	Point<double> orth_p1p2((t_p1p2.x - p.x), (t_p1p2.y - p.y));
	double orth_p1p2_length = sqrtd(orth_p1p2.x * orth_p1p2.x + orth_p1p2.y * orth_p1p2.y);
	double ea = acos(orth_p1p2.x / orth_p1p2_length);

	if (orth_p1p2.y < 0) ea = 2 * M_PI - ea;
	if ((sa > ea) && ((sa - ea) < M_PI)) anticlockwise = true;
	if ((sa < ea) && ((ea - sa) > M_PI)) anticlockwise = true;

	cairo_line_to(cairo_ctx, t_p1p0.x, t_p1p0.y);

	if (anticlockwise && M_PI * 2 != radius)
	{
		cairo_arc_negative(cairo_ctx, p.x, p.y, radius, sa, ea);
	}
	else
	{
		cairo_arc(cairo_ctx, p.x, p.y, radius, sa, ea);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::__BitBltToHDC(int32_t ptr)
{
	/*
	#ifdef _WINDOWS_

	if (!ptr) return;

	// Cast ptr to HDC
	HDC dst_dc = (HDC) (ptr);

	// Wrap DC in Cairo surface
	cairo_surface_t* tmp_surface = cairo_win32_surface_create(dst_dc);
	bool result = (cairo_surface_status(tmp_surface) == CAIRO_STATUS_SUCCESS);

	if (result)
	{
		// Create a Cairo context for the wrapped surface
		cairo_t* cr = cairo_create(tmp_surface);

		// Paint Canvas surface to wrapped DC surface
		cairo_surface_flush(canvas->_surface);
		cairo_set_source_surface(cr, canvas->_surface, 0, 0);
		cairo_paint(cr);

		// Flush and destroy
		cairo_surface_flush(tmp_surface);
		cairo_destroy(cr);
	}

	cairo_surface_destroy(tmp_surface);

	#endif
	*/
}
