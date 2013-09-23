package com.mobilefx.cocoengine;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.view.ViewGroup.LayoutParams;
import android.widget.VideoView;

public class VideoActivity extends Activity {
	@SuppressLint("NewApi")
	@Override
	protected void onCreate(Bundle state) {
		super.onCreate(state);
		
		VideoView vv = new VideoView(this);
		addContentView(vv, new LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT));
		
		Uri u = Uri.parse("android.resource://" + getPackageName() + "/" + R.raw.videosample);
		Log.i("VideoActivity", u.toString());
		vv.setVideoURI(u);
		vv.start();
	}
}
