package com.mobilefx.cocoengine;

import android.app.NativeActivity;
import android.os.*;
import android.util.*;
import android.view.*;
import android.content.*;
import android.content.res.*;

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
		super.onCreate(savedInstanceState);
    	try
    	{	    		        	        
			//setRequestedOrientation (ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
			requestWindowFeature(Window.FEATURE_NO_TITLE);		
			DisplayMetrics metrics = new DisplayMetrics();
			getWindowManager().getDefaultDisplay().getMetrics(metrics);        
			mWidth = metrics.widthPixels;
			mHeight = metrics.heightPixels;	
			scale = getResources().getDisplayMetrics().density;
    	}
    	catch(Exception e)
    	{
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
	            logContentView(group.getChildAt(i), indent + " ");
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
}
