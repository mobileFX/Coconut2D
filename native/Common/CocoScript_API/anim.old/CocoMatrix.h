/* ***** BEGIN LICENSE BLOCK *****
 *
 * Copyright (C) 2013 www.coconut2D.org
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

#ifndef __CocoMatrix__
#define __CocoMatrix__

#include "Coconut2D.h"
#include "CocoVector.h"

// ==================================================================================================================================
//	   ______                 __  ___      __       _     
//	  / ____/___  _________  /  |/  /___ _/ /______(_)  __
//	 / /   / __ \/ ___/ __ \/ /|_/ / __ `/ __/ ___/ / |/_/
//	/ /___/ /_/ / /__/ /_/ / /  / / /_/ / /_/ /  / />  <  
//	\____/\____/\___/\____/_/  /_/\__,_/\__/_/  /_/_/|_|  
//	                                                      
// ==================================================================================================================================
   
class CocoMatrix
{ 
public:	   

    Number rc11;
    Number rc12;
    Number rc13;
    Number rc14;
    Number rc21;
    Number rc22;
    Number rc23;
    Number rc24;
    Number rc31;
    Number rc32;
    Number rc33;  
    Number rc34;
    Number rc41;
    Number rc42;
    Number rc43;
    Number rc44;
		 
    Stack<Float32Array> __stack;
    Float32Array* __data;
	
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    CocoMatrix()
    {
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    CocoMatrix(CocoMatrix* M)
	{           		
		if(M)   
		{
			rc11 = M->rc11;
			rc12 = M->rc12;
			rc13 = M->rc13;
			rc14 = M->rc14;
			rc21 = M->rc21;
			rc22 = M->rc22;
			rc23 = M->rc23;
			rc24 = M->rc24;
			rc31 = M->rc31;
			rc32 = M->rc32;
			rc33 = M->rc33;
			rc34 = M->rc34;
			rc41 = M->rc41;
			rc42 = M->rc42;
			rc43 = M->rc43;
			rc44 = M->rc44;		
		}
		else
			identity();

        __data = new Float32Array( {rc11, rc12, rc13, rc14, rc21, rc22, rc23, rc24, rc31, rc32, rc33, rc34, rc41, rc42, rc43, rc44 });
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ~CocoMatrix()
    {
		while(!__stack.empty())
		{
			delete __stack.top();
			__stack.pop();
		}
		delete data;
    }

	// ==================================================================================================================================
	//	    __  ___      __       _         ____                        __  _                 
	//	   /  |/  /___ _/ /______(_)  __   / __ \____  ___  _________ _/ /_(_)___  ____  _____
	//	  / /|_/ / __ `/ __/ ___/ / |/_/  / / / / __ \/ _ \/ ___/ __ `/ __/ / __ \/ __ \/ ___/
	//	 / /  / / /_/ / /_/ /  / />  <   / /_/ / /_/ /  __/ /  / /_/ / /_/ / /_/ / / / (__  ) 
	//	/_/  /_/\__,_/\__/_/  /_/_/|_|   \____/ .___/\___/_/   \__,_/\__/_/\____/_/ /_/____/  
	//	                                     /_/                                              
	// ==================================================================================================================================	
			
    void identity()
	{
	    rc11 = 1; rc12 = 0; rc13 = 0; rc14 = 0;
	    rc21 = 0; rc22 = 1; rc23 = 0; rc24 = 0;
	    rc31 = 0; rc32 = 0; rc33 = 1; rc34 = 0;
	    rc41 = 0; rc42 = 0; rc43 = 0; rc44 = 1;		
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
    void ortho(Number left, Number right, Number bottom, Number top, Number near, Number far)
    {
		rc11 = 2 / (right - left);
		rc12 = 0.0;
		rc13 = 0.0;
		rc14 = 0.0;
		rc21 = 0.0;
		rc22 = 2 / (top - bottom);
		rc23 = 0.0;
		rc24 = 0.0;
		rc31 = 0.0;
		rc32 = 0.0;
		rc33 = -2 / (far - near);
		rc34 = 0.0;
		rc41 = -(right + left) / (right - left);
		rc42 = -(top + bottom) / (top - bottom);
		rc43 = -(far + near) / (far - near);
		rc44 = 1.0;		
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
    void transpose()
	{
        Number t;
	    t = rc12; rc12 = rc21; rc21 = t;
	    t = rc13; rc13 = rc31; rc31 = t;
	    t = rc14; rc14 = rc41; rc41 = t;
	    t = rc21; rc21 = rc12; rc12 = t;
	    t = rc23; rc23 = rc32; rc32 = t;
	    t = rc24; rc24 = rc42; rc42 = t;
	    t = rc31; rc31 = rc13; rc13 = t;
	    t = rc32; rc32 = rc23; rc23 = t;
	    t = rc34; rc34 = rc43; rc43 = t;
	    t = rc41; rc41 = rc14; rc14 = t;
	    t = rc42; rc42 = rc24; rc24 = t;
	    t = rc43; rc43 = rc34; rc34 = t;	    
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
    Number determinant()
	{
	    var D = (rc14 * rc23 * rc32 * rc41) - (rc13 * rc24 * rc32 * rc41) - (rc14 * rc22 * rc33 * rc41) + (rc12 * rc24 * rc33 * rc41) + 
		        (rc13 * rc22 * rc34 * rc41) - (rc12 * rc23 * rc34 * rc41) - (rc14 * rc23 * rc31 * rc42) + (rc13 * rc24 * rc31 * rc42) + 
		        (rc14 * rc21 * rc33 * rc42) - (rc11 * rc24 * rc33 * rc42) - (rc13 * rc21 * rc34 * rc42) + (rc11 * rc23 * rc34 * rc42) + 
		        (rc14 * rc22 * rc31 * rc43) - (rc12 * rc24 * rc31 * rc43) - (rc14 * rc21 * rc32 * rc43) + (rc11 * rc24 * rc32 * rc43) + 
		        (rc12 * rc21 * rc34 * rc43) - (rc11 * rc22 * rc34 * rc43) - (rc13 * rc22 * rc31 * rc44) + (rc12 * rc23 * rc31 * rc44) + 
		        (rc13 * rc21 * rc32 * rc44) - (rc11 * rc23 * rc32 * rc44) - (rc12 * rc21 * rc33 * rc44) + (rc11 * rc22 * rc33 * rc44);
		        
		return D;
	}		

	////////////////////////////////////////////////////////////////////////////////////////////////////
    void invert()
	{    
        Number D = determinant();
	    if(D == 0) return;	    
	        
	    var invRC11 = (rc23 * rc34 * rc42) - (rc24 * rc33 * rc42) + (rc24 * rc32 * rc43) - (rc22 * rc34 * rc43) - (rc23 * rc32 * rc44) + (rc22 * rc33 * rc44);
	    var invRC12 = (rc14 * rc33 * rc42) - (rc13 * rc34 * rc42) - (rc14 * rc32 * rc43) + (rc12 * rc34 * rc43) + (rc13 * rc32 * rc44) - (rc12 * rc33 * rc44);
	    var invRC13 = (rc13 * rc24 * rc42) - (rc14 * rc23 * rc42) + (rc14 * rc22 * rc43) - (rc12 * rc24 * rc43) - (rc13 * rc22 * rc44) + (rc12 * rc23 * rc44);
	    var invRC14 = (rc14 * rc23 * rc32) - (rc13 * rc24 * rc32) - (rc14 * rc22 * rc33) + (rc12 * rc24 * rc33) + (rc13 * rc22 * rc34) - (rc12 * rc23 * rc34);
               
	    var invRC21 = (rc24 * rc33 * rc41) - (rc23 * rc34 * rc41) - (rc24 * rc31 * rc43) + (rc21 * rc34 * rc43) + (rc23 * rc31 * rc44) - (rc21 * rc33 * rc44);
	    var invRC22 = (rc13 * rc34 * rc41) - (rc14 * rc33 * rc41) + (rc14 * rc31 * rc43) - (rc11 * rc34 * rc43) - (rc13 * rc31 * rc44) + (rc11 * rc33 * rc44);
	    var invRC23 = (rc14 * rc23 * rc41) - (rc13 * rc24 * rc41) - (rc14 * rc21 * rc43) + (rc11 * rc24 * rc43) + (rc13 * rc21 * rc44) - (rc11 * rc23 * rc44);
	    var invRC24 = (rc13 * rc24 * rc31) - (rc14 * rc23 * rc31) + (rc14 * rc21 * rc33) - (rc11 * rc24 * rc33) - (rc13 * rc21 * rc34) + (rc11 * rc23 * rc34);
               
	    var invRC31 = (rc22 * rc34 * rc41) - (rc24 * rc32 * rc41) + (rc24 * rc31 * rc42) - (rc21 * rc34 * rc42) - (rc22 * rc31 * rc44) + (rc21 * rc32 * rc44);
	    var invRC32 = (rc14 * rc32 * rc41) - (rc12 * rc34 * rc41) - (rc14 * rc31 * rc42) + (rc11 * rc34 * rc42) + (rc12 * rc31 * rc44) - (rc11 * rc32 * rc44);
	    var invRC33 = (rc12 * rc24 * rc41) - (rc14 * rc22 * rc41) + (rc14 * rc21 * rc42) - (rc11 * rc24 * rc42) - (rc12 * rc21 * rc44) + (rc11 * rc22 * rc44);
	    var invRC34 = (rc14 * rc22 * rc31) - (rc12 * rc24 * rc31) - (rc14 * rc21 * rc32) + (rc11 * rc24 * rc32) + (rc12 * rc21 * rc34) - (rc11 * rc22 * rc34);
               
	    var invRC41 = (rc23 * rc32 * rc41) - (rc22 * rc33 * rc41) - (rc23 * rc31 * rc42) + (rc21 * rc33 * rc42) + (rc22 * rc31 * rc43) - (rc21 * rc32 * rc43);
	    var invRC42 = (rc12 * rc33 * rc41) - (rc13 * rc32 * rc41) + (rc13 * rc31 * rc42) - (rc11 * rc33 * rc42) - (rc12 * rc31 * rc43) + (rc11 * rc32 * rc43);
	    var invRC43 = (rc13 * rc22 * rc41) - (rc12 * rc23 * rc41) - (rc13 * rc21 * rc42) + (rc11 * rc23 * rc42) + (rc12 * rc21 * rc43) - (rc11 * rc22 * rc43);
	    var invRC44 = (rc12 * rc23 * rc31) - (rc13 * rc22 * rc31) + (rc13 * rc21 * rc32) - (rc11 * rc23 * rc32) - (rc12 * rc21 * rc33) + (rc11 * rc22 * rc33);
	    	    
	    rc11 = invRC11 / D;
	    rc12 = invRC12 / D;
	    rc13 = invRC13 / D;
	    rc14 = invRC14 / D;
	                     
	    rc21 = invRC21 / D;
	    rc22 = invRC22 / D;
	    rc23 = invRC23 / D;
	    rc24 = invRC24 / D;
	                    
	    rc31 = invRC31 / D;
	    rc32 = invRC32 / D;
	    rc33 = invRC33 / D;
	    rc34 = invRC34 / D;
	                    
	    rc41 = invRC41 / D;
	    rc42 = invRC42 / D;
	    rc43 = invRC43 / D;
	    rc44 = invRC44 / D;
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
    CocoVector* multiplyByVector(CocoVector* v)
	{  
        CocoVector* out = new CocoVector();
        out->X = (v->X * rc11) + (v->Y * rc21) + (v->Z * rc31) + (v->W * rc41);
        out->Y = (v->X * rc12) + (v->Y * rc22) + (v->Z * rc32) + (v->W * rc42);
        out->Z = (v->X * rc13) + (v->Y * rc23) + (v->Z * rc33) + (v->W * rc43);
        out->W = (v->X * rc14) + (v->Y * rc24) + (v->Z * rc34) + (v->W * rc44);
        return out;
	}
				
	// ==================================================================================================================================
	//	  ______                      ____                           __  _                 
	//	 /_  __/________ _____  _____/ __/___  _________ ___  ____ _/ /_(_)___  ____  _____
	//	  / / / ___/ __ `/ __ \/ ___/ /_/ __ \/ ___/ __ `__ \/ __ `/ __/ / __ \/ __ \/ ___/
	//	 / / / /  / /_/ / / / (__  ) __/ /_/ / /  / / / / / / /_/ / /_/ / /_/ / / / (__  ) 
	//	/_/ /_/   \__,_/_/ /_/____/_/  \____/_/  /_/ /_/ /_/\__,_/\__/_/\____/_/ /_/____/  
	//	                                                                                   
	// ==================================================================================================================================	
		
    void translate(Number tx, Number ty)
	{
		rc41 += rc11 * tx + rc21 * ty;
		rc42 += rc12 * tx + rc22 * ty;
		rc43 += rc13 * tx + rc23 * ty;
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
    void scale(Number sx, Number sy)
	{
		rc11 *= sx;
		rc21 *= sy;		
		rc12 *= sx;
		rc22 *= sy;		
		rc13 *= sx;
		rc23 *= sy;		
		rc14 *= sx;
		rc24 *= sy;		
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
    void rotateZ(Number rz)
	{
		// counter-clockwise rotation around Z-axis (perpendicular to the screen)
        Number c = cosf(rz);
        Number s = sinf(rz);
        Number t0, t1;
	
		t0 = rc11;
		t1 = rc21;
		rc11 =  t0 * c + t1 * s;
		rc21 = -t0 * s + t1 * c;
		
		t0 = rc12;
		t1 = rc22;
		rc12 =  t0 * c + t1 * s;
		rc22 = -t0 * s + t1 * c;
		
		t0 = rc13;
		t1 = rc23;
		rc13 =  t0 * c + t1 * s;
		rc23 = -t0 * s + t1 * c;
		
		t0 = rc14;
		t1 = rc24;
		rc14 =  t0 * c + t1 * s;
		rc24 = -t0 * s + t1 * c;
	}

	// ==================================================================================================================================
	//	   ____                   ________ 
	//	  / __ \____  ___  ____  / ____/ / 
	//	 / / / / __ \/ _ \/ __ \/ / __/ /  
	//	/ /_/ / /_/ /  __/ / / / /_/ / /___
	//	\____/ .___/\___/_/ /_/\____/_____/
	//	    /_/                            
	// ==================================================================================================================================
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
    void update(WebGLRenderingContext* gl, WebGLUniformLocation* ul)
	{
		__data[0]  = rc11;
		__data[1]  = rc12;
		__data[2]  = rc13;
		__data[3]  = rc14;
		__data[4]  = rc21;
		__data[5]  = rc22;
		__data[6]  = rc23;
		__data[7]  = rc24;
		__data[8]  = rc31;
		__data[9]  = rc32;
		__data[10] = rc33;
		__data[11] = rc34;
		__data[12] = rc41;
		__data[13] = rc42;
		__data[14] = rc43;
		__data[15] = rc44;
		
		if(gl && ul)
            gl->uniformMatrix4fv(ul, false, __data);
	}	

	// ==================================================================================================================================
	//	   _____ __             __  
	//	  / ___// /_____ ______/ /__
	//	  \__ \/ __/ __ `/ ___/ //_/
	//	 ___/ / /_/ /_/ / /__/ ,<   
	//	/____/\__/\__,_/\___/_/|_|  
	//	                            
	// ==================================================================================================================================

	////////////////////////////////////////////////////////////////////////////////////////////////////
    void push()
	{		
        __stack.push( data );
		__data = new Float32Array( {rc11, rc12, rc13, rc14, rc21, rc22, rc23, rc24, rc31, rc32, rc33, rc34, rc41, rc42, rc43, rc44 });
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
    void pop()
	{
		if(__stack.size()) 
		{
			delete data;
			data = __stack.top();
			__stack.pop();
			rc11 = data[0];
			rc12 = data[1];
			rc13 = data[2];
			rc14 = data[3];
			rc21 = data[4];
			rc22 = data[5];
			rc23 = data[6];
			rc24 = data[7];
			rc31 = data[8];
			rc32 = data[9];
			rc33 = data[10];
			rc34 = data[11];
			rc41 = data[12];
			rc42 = data[13];
			rc43 = data[14];
			rc44 = data[15];	
		}
	}
}

#endif
