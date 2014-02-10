//
//  HTMLCanvasContext.hpp
//  CocoEngine
//
//  Created by Administrator on 1/24/14.
//
//

#ifndef __CocoEngine__HTMLCanvasContext__
#define __CocoEngine__HTMLCanvasContext__

class HTMLCanvasElement;

class HTMLCanvasContext {
public:
	HTMLCanvasElement* canvas;
	HTMLCanvasContext(HTMLCanvasElement* i_canvas);
};

#endif /* defined(__CocoEngine__HTMLCanvasContext__) */
