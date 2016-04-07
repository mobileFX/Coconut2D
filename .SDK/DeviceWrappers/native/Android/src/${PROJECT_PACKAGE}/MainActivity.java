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

////////////////////////////////////////////////////////////////////////////////////////////////////

package $(PROJECT_PACKAGE);

import android.app.NativeActivity;
import android.os.*;
import android.util.*;
import android.view.*;
import android.content.*;
import android.content.res.*;
import android.content.pm.*;

public class MainActivity extends NativeActivity
{
	private int mWidth;
	private int mHeight;
	private float scale = 1f;

    /////////////////////////////////////////////////////////////////////////////////////////////
	static class NativeSurfaceView extends SurfaceView
	{
		MainActivity mActivity;
		public NativeSurfaceView(Context context) { super(context); }
		public NativeSurfaceView(Context context, AttributeSet attrs) { super(context, attrs); }
		public NativeSurfaceView(Context context, AttributeSet attrs, int defStyle) { super(context, attrs, defStyle); }
		public void surfaceCreated(SurfaceHolder holder) {}
		public void surfaceChanged(SurfaceHolder holder, int foramt, int width, int height) {}
		public void surfaceRedrawNeeded(SurfaceHolder holder) {}
		public void surfaceDestroyed(SurfaceHolder holder) {}
	}

    /////////////////////////////////////////////////////////////////////////////////////////////
	protected void onCreate(Bundle savedInstanceState)
	{
		// Enable Java Debug Mode
		// ----------------------------------------------------------
		if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.KITKAT)
		{
			if (0 != (getApplicationInfo().flags &= ApplicationInfo.FLAG_DEBUGGABLE))
			{
				android.os.Debug.waitForDebugger();
			}
		}

		super.onCreate(savedInstanceState);

    	try
    	{
			requestWindowFeature(Window.FEATURE_NO_TITLE);
    		getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
			DisplayMetrics metrics = new DisplayMetrics();
			getWindowManager().getDefaultDisplay().getMetrics(metrics);
			mWidth = metrics.widthPixels;
			mHeight = metrics.heightPixels;
			scale = getResources().getDisplayMetrics().density;
    	}
    	catch(Exception e)
    	{
    		scale = 1f;
    	}
	}

    /////////////////////////////////////////////////////////////////////////////////////////////
	public void onDestroy()
	{
		System.exit(0);
		super.onDestroy();
	}

    /////////////////////////////////////////////////////////////////////////////////////////////
	public void onStop()
	{
		super.onStop();
	}

    /////////////////////////////////////////////////////////////////////////////////////////////
	protected void logContentView(View parent, String indent)
	{
	    Log.i("test", indent + parent.getClass().getName());
	    if(parent instanceof ViewGroup)
	    {
	        ViewGroup group = (ViewGroup)parent;
	        for(int i = 0; i < group.getChildCount(); i++)
	        {
	            logContentView(group.getChildAt(i), indent + " ");
	        }
	    }
	}

    /////////////////////////////////////////////////////////////////////////////////////////////
	protected void PlayVideo()
	{
	}

    /////////////////////////////////////////////////////////////////////////////////////////////
	protected void KeyboardShow()
	{
	}

    /////////////////////////////////////////////////////////////////////////////////////////////
	protected void KeyboardHide()
	{
	}

    /////////////////////////////////////////////////////////////////////////////////////////////
	protected void KeyboardToggle()
    {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
	protected int GetScreenRotation()
	{
		return -1;
	}

    /////////////////////////////////////////////////////////////////////////////////////////////
	protected boolean GetScreenIsPortrait()
	{
		return true;
	}

    /////////////////////////////////////////////////////////////////////////////////////////////
	protected int GetScreenTop()
	{
		return 0;
	}

    /////////////////////////////////////////////////////////////////////////////////////////////
	protected float GetScreenPixelRatio()
	{
		return scale;
	}
}
