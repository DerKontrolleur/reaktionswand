package com.siemens.test;

import android.bluetooth.*;

import java.io.IOException;
import java.util.UUID;

import com.siemens.test.ConnectedThread;


public class ConnectThread implements Runnable {
	private static final UUID mUUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
	private final BluetoothSocket mmSocket;
	private ConnectedThread Connected = null;
	 
	    public ConnectThread(BluetoothDevice device) {
	        BluetoothSocket tmp = null;
	 
	        try {
	            tmp = device.createRfcommSocketToServiceRecord(mUUID);
	        } catch (IOException e) { }
	        mmSocket = tmp;
	    }
	 
	    public void run() {
	        try {
	            mmSocket.connect();
	        } catch (IOException connectException) {
	            try {
	                mmSocket.close();
	            } catch (IOException closeException) { }
	            return;
	        }

	        if(mmSocket != null) {
	        	Connected = new ConnectedThread(mmSocket);
	        	new Thread(Connected).start();
	        }
	    }
	 
	    public void cancel() {
	        try {
	            mmSocket.close();
	        } catch (IOException e) { }
	    }
	    
	    public ConnectedThread getConnectedThread() {
	    	return Connected;
	    }
	}
