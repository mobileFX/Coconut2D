package com.mobilefx.cocoengine;

import com.mobilefx.cocoengine.VideoActivity;

import android.os.Bundle;
import android.os.ResultReceiver;
import android.app.NativeActivity;
import android.util.AttributeSet;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.view.ViewGroup;
import android.view.Window;
import android.view.inputmethod.InputMethodManager;
//import android.support.v4.app.NavUtils;
//import android.annotation.TargetApi;
import android.content.Context;
import android.content.Intent;
import android.content.res.Configuration;
//import android.os.Build;

public class MainActivity extends NativeActivity {
	public static final int fxScreenRotation_NONE = 0;
	public static final int fxScreenRotation_RCW = 1;
	public static final int fxScreenRotation_RCCW = 2;
	public static final int fxScreenRotation_FULL = 3;

	
	static class NativeSurfaceView extends SurfaceView {
		MainActivity mActivity;
		
		public NativeSurfaceView(Context context) {
			super(context);
		}
		public NativeSurfaceView(Context context, AttributeSet attrs) {
			super(context, attrs);
		}
		public NativeSurfaceView(Context context, AttributeSet attrs, int defStyle) {
			super(context, attrs, defStyle);
		}
		
		public void surfaceCreated(SurfaceHolder holder) {
			
		}
		public void surfaceChanged(SurfaceHolder holder, int foramt, int width, int height) {
			
		}
		public void surfaceRedrawNeeded(SurfaceHolder holder) {
			
		}
		public void surfaceDestroyed(SurfaceHolder holder) {
			
		}
	}
	
	//protected NativeSurfaceView sv;
	//protected VideoView vv;
	protected ResultReceiver kb_state;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		Log.i("info", "board: " + android.os.Build.BOARD);
		Log.i("info", "bootloader: " + android.os.Build.BOOTLOADER);
		Log.i("info", "brand: " + android.os.Build.BRAND);
		Log.i("info", "cpu_abi: " + android.os.Build.CPU_ABI);
		Log.i("info", "cpu_abi2: " + android.os.Build.CPU_ABI2);
		Log.i("info", "device: " + android.os.Build.DEVICE);
		Log.i("info", "display: " + android.os.Build.DISPLAY);
		Log.i("info", "fingerprint: " + android.os.Build.FINGERPRINT);
		Log.i("info", "hardware: " + android.os.Build.HARDWARE);
		Log.i("info", "host: " + android.os.Build.HOST);
		Log.i("info", "id: " + android.os.Build.ID);
		Log.i("info", "manufacturer: " + android.os.Build.MANUFACTURER);
		Log.i("info", "model: " + android.os.Build.MODEL);
		Log.i("info", "product: " + android.os.Build.PRODUCT);
		//Log.i("info", "radio: " + android.os.Build.RADIO);
		Log.i("info", "serial: " + android.os.Build.SERIAL);
		Log.i("info", "tags: " + android.os.Build.TAGS);
		Log.i("info", "type: " + android.os.Build.TYPE);
		Log.i("info", "uknown: " + android.os.Build.UNKNOWN);
		Log.i("info", "user: " + android.os.Build.USER);
		Log.i("info", "version.codename: " + android.os.Build.VERSION.CODENAME);
		Log.i("info", "version.incermental: " + android.os.Build.VERSION.INCREMENTAL);
		Log.i("info", "version.release: " + android.os.Build.VERSION.RELEASE);
		//Log.i("info", "version.sdk: " + android.os.Build.VERSION.SDK);
		Log.i("info", "version.sdk_int: " + android.os.Build.VERSION.SDK_INT);
		//Log.i("info", android.os.Build.TIME);
		//Log.i("info", android.os.Build.VERSION);
		//Log.i("info", android.os.Build.VERSION_CODES);
		//getWindow().takeSurface(null);
		//vv = new VideoView(this);
		//sv = new NativeSurfaceView(this);
		//sv.mActivity = this;
		//setContentView(sv);
		//sv.requestFocus();
		//((InputMethodManager)getSystemService(Context.INPUT_METHOD_SERVICE)).showSoftInput(getWindow().getDecorView(), InputMethodManager.SHOW_FORCED, kb_state);
		//setupActionBar();
	}

	@Override
	public void onDestroy() {
		System.exit(0);
		super.onDestroy();
	}
	
	@Override
	public void onStop() {
		super.onStop();
	}
	protected void logContentView(View parent, String indent) {
	    Log.i("test", indent + parent.getClass().getName());
	    if (parent instanceof ViewGroup) {
	        ViewGroup group = (ViewGroup)parent;
	        for (int i = 0; i < group.getChildCount(); i++)
	            logContentView(group.getChildAt(i), indent + " ");
	    }
	}
	protected void PlayVideo()
	{
		runOnUiThread(new Runnable() {
			public void run() {
				Intent videoIntent = new Intent(getApplicationContext(), VideoActivity.class);
				startActivity(videoIntent);
				/*Uri u = Uri.parse("android.resource://" + getPackageName() + "/" + R.raw.videosample);
				//VideoView v = (VideoView)((ViewGroup)((ViewGroup)getWindow().getDecorView()).getChildAt(0)).getChildAt(0);
				vv.setVideoURI(u);
				vv.setVisibility(View.VISIBLE);
				vv.bringToFront();
				vv.requestFocus();
				vv.start();*/
			}
		});
	}
	protected void KeyboardShow()
	{
		//vv.start();
		((InputMethodManager)getSystemService(Context.INPUT_METHOD_SERVICE)).showSoftInput(getWindow().getDecorView(), 0, kb_state);
	}
	protected void KeyboardHide()
	{
		((InputMethodManager)getSystemService(Context.INPUT_METHOD_SERVICE)).hideSoftInputFromWindow(getWindow().getDecorView().getWindowToken(), 0, kb_state);
	}
	protected void KeyboardToggle()
    {
		((InputMethodManager)getSystemService(Context.INPUT_METHOD_SERVICE)).toggleSoftInputFromWindow(getWindow().getDecorView().getWindowToken(), 0, 0);
    }
	protected int GetScreenRotation()
	{
		switch (getWindowManager().getDefaultDisplay().getRotation())
		{
			case Surface.ROTATION_0: return fxScreenRotation_NONE;
			case Surface.ROTATION_270: return fxScreenRotation_RCW;
			case Surface.ROTATION_90: return fxScreenRotation_RCCW;
			case Surface.ROTATION_180: return fxScreenRotation_FULL;
		}
		return -1;
	}
	protected boolean GetScreenIsPortrait()
	{
		return getResources().getConfiguration().orientation == Configuration.ORIENTATION_PORTRAIT;
	}
	protected int GetScreenTop()
	{
		return getWindow().findViewById(Window.ID_ANDROID_CONTENT).getTop();
	}
	
	/**
	 * Set up the {@link android.app.ActionBar}, if the API is available.
	 */
	/*@TargetApi(Build.VERSION_CODES.HONEYCOMB)
	private void setupActionBar() {
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB) {
			getActionBar().setDisplayHomeAsUpEnabled(true);
		}
	}*/

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		switch (item.getItemId()) {
		case android.R.id.home:
			// This ID represents the Home or Up button. In the case of this
			// activity, the Up button is shown. Use NavUtils to allow users
			// to navigate up one level in the application structure. For
			// more details, see the Navigation pattern on Android Design:
			//
			// http://developer.android.com/design/patterns/navigation.html#up-vs-back
			//
			//NavUtils.navigateUpFromSameTask(this);
			return true;
		}
		return super.onOptionsItemSelected(item);
	}

}
