package com.thankcreate.tool;

import org.cocos2dx.lib.Cocos2dxActivity;

import com.adsmogo.adapters.AdsMogoCustomEventPlatformEnum;
import com.adsmogo.adview.AdsMogoLayout;
import com.adsmogo.controller.listener.AdsMogoListener;



import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.view.ViewGroup;
import android.view.ViewGroup.LayoutParams;
import android.widget.RelativeLayout;


public class AdViewHelper implements AdsMogoListener{
	
	protected static Handler mHandler;
	protected Cocos2dxActivity mActivity;
	
	protected RelativeLayout mLayout;
	
	
	public AdViewHelper(Cocos2dxActivity activity)
    {	
		com.adsmogo.util.L.debug = true;
		mActivity = activity;
		
		mLayout = new RelativeLayout(mActivity);
		
        activity.addContentView(mLayout, new LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT));
        
        AdsMogoLayout adViewLayout = new AdsMogoLayout(mActivity, "487dbe92c586449a933f55d08c79c4e3", true);
        
        // µ×²¿¾ÓÖÐ
        RelativeLayout.LayoutParams layoutParams =
	            new RelativeLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT,
	                                            ViewGroup.LayoutParams.WRAP_CONTENT);
        layoutParams.addRule(RelativeLayout.CENTER_HORIZONTAL);
        layoutParams.addRule(RelativeLayout.ALIGN_PARENT_BOTTOM);        
        adViewLayout.setLayoutParams(layoutParams);
        
        mLayout.addView(adViewLayout); 
        mLayout.invalidate();        
        
		mHandler = new Handler()
        {
			@Override
			public void handleMessage(Message msg) {
				switch (msg.what) {
				case 1: {
					if(mLayout != null)
						mLayout.setVisibility( View.VISIBLE );					
					break;
				}
				case 2: {
					if(mLayout != null)
						mLayout.setVisibility( View.GONE );
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


	@Override
	public Class getCustomEvemtPlatformAdapterClass(
			AdsMogoCustomEventPlatformEnum arg0) {
		// TODO Auto-generated method stub
		return null;
	}


	@Override
	public void onClickAd(String arg0) {
		// TODO Auto-generated method stub
		
	}


	@Override
	public boolean onCloseAd() {
		// TODO Auto-generated method stub
		return false;
	}


	@Override
	public void onCloseMogoDialog() {
		// TODO Auto-generated method stub		
	}


	@Override
	public void onFailedReceiveAd() {
		// TODO Auto-generated method stub
		
	}


	@Override
	public void onRealClickAd() {
		// TODO Auto-generated method stub
		
	}


	@Override
	public void onReceiveAd(ViewGroup arg0, String arg1) {
		// TODO Auto-generated method stub
		
	}


	@Override
	public void onRequestAd(String arg0) {
		// TODO Auto-generated method stub
		
	}
}
