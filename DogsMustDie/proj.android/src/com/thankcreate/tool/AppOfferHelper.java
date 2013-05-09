package com.thankcreate.tool;

import java.util.Hashtable;

import org.cocos2dx.lib.Cocos2dxActivity;

import com.tapjoy.TapjoyConnect;
import com.tapjoy.TapjoyConnectFlag;
import com.tapjoy.TapjoyEarnedPointsNotifier;
import com.tapjoy.TapjoyNotifier;



import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.View;

public class AppOfferHelper implements TapjoyEarnedPointsNotifier , TapjoyNotifier{
	protected static Handler mHandler;
	protected Cocos2dxActivity mActivity;
	
	public AppOfferHelper(Cocos2dxActivity activity)
    {
		mActivity = activity;
		
		// tapjoy
		Hashtable<String, String> flags = new Hashtable<String, String>();
		flags.put(TapjoyConnectFlag.ENABLE_LOGGING, "true");
		TapjoyConnect.requestTapjoyConnect(activity.getApplicationContext(),
				"5897ccc0-0f4d-4469-b49b-97694b47c958", "YqfWnmZkR7qO2EW5LaM4",
				flags);
		
		// 这个是测试的，上面的是真的
//		TapjoyConnect.requestTapjoyConnect(activity.getApplicationContext(), 
//				"bba49f11-b87f-4c0f-9632-21aa810dd6f1", "yiQIURFEeKm0zbOggubu", 
//				flags);
		TapjoyConnect.getTapjoyConnectInstance().setEarnedPointsNotifier(this);


		mHandler = new Handler()
        {
			@Override
			public void handleMessage(Message msg) {
				switch (msg.what) {
				case 1: {
					TapjoyConnect.getTapjoyConnectInstance().showOffers();					
					break;
				}
				case 2: {
			
					break;
				}
				default: 
					break;			
				}
			}
        };
    }	

	public static void nativeSendMsg(int i) {		
		mHandler.sendEmptyMessage(i);
	}
	
	private static native void nativeAppOfferCallback(int i);

	
	
	
	
	int lastEarn = 0;
	@Override
	public void earnedTapPoints(int arg0) {
		lastEarn = arg0;
		if(mHandler != null)			
			mHandler.post(mUpdateResults);
	}	

	
	public void refresh()
	{
		TapjoyConnect.getTapjoyConnectInstance().getTapPoints(this);
		// getTapPoints will invoke getUpdatePoints and earnedTapPoints
		// earnedTapPoints will be invoked only when point increased
		// but getUpdatePoints will be invoked every time
		// By now, I don't need getUpdatePoints
		// I'll hander the sum of points by my own in CCUserDefault
		// ^_^
	}
	
	public void getUpdatePoints(String currencyName, int pointTotal)
	{		
		// do nothing
	}
	
	// Notifier triggered when TapjoyConnect.getTapPoints fails.
	public void getUpdatePointsFailed(String error)
	{
		// do nothing
	}
	
	final Runnable mUpdateResults = new Runnable() 
	{
		public void run() 
		{
			nativeAppOfferCallback(lastEarn);
		}
	};
}
