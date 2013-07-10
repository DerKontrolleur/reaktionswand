package com.siemens.test;

import android.bluetooth.*;
import android.os.Looper;

import java.io.IOException;
import java.io.OutputStream;
import java.io.InputStream;

import android.os.Handler;
import android.os.Message;

public class ConnectedThread implements Runnable {
	private final BluetoothSocket mmSocket;
    private final InputStream mmInStream;
    private final OutputStream mmOutStream;
    private static final int MESSAGE_READ = 1;
    
    private String mMessage = "";
    
    final Handler mHandler = new Handler(Looper.getMainLooper()) {
    	@Override
    	public void handleMessage(Message msg) {
    	    switch(msg.what) {
    	    case MESSAGE_READ:
    	      byte[] readBuf = (byte[])msg.obj;
    	      mMessage = new String(readBuf, 0, msg.arg1);
    	      break;
    	    }
    	}
    };
 
    public ConnectedThread(BluetoothSocket socket) {
        mmSocket = socket;
        InputStream tmpIn = null;
        OutputStream tmpOut = null;
 
        try {
            tmpIn = socket.getInputStream();
            tmpOut = socket.getOutputStream();
        } catch (IOException e) { }
 
        mmInStream = tmpIn;
        mmOutStream = tmpOut;
    }
    
 
    public void run() {
        byte[] buffer = new byte[1024];
        int bytes;
 
        while (true) {
            try {
                bytes = mmInStream.read(buffer);
                mHandler.obtainMessage(MESSAGE_READ, bytes, -1, buffer)
                        .sendToTarget();
            } catch (IOException e) {
                break;
            }
        }
    }
 
    public void write(byte[] bytes) {
        try {
            mmOutStream.write(bytes);
        } catch (IOException e) { }
    }
    
    public String read() {
    	return mMessage;
    }
 
    public void cancel() {
        try {
            mmSocket.close();
        } catch (IOException e) { }
    }
};
