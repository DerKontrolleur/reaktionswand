package com.siemens.test;

import android.bluetooth.*;

import com.siemens.test.ConnectThread;


public class Bluetooth {
	private final BluetoothAdapter mAdapter;
	private final BluetoothDevice mDevice;
	private ConnectThread Connect = null;

	private static final String MAC = "00:06:66:06:BE:72";
	
	
	public Bluetooth() {
		mAdapter = BluetoothAdapter.getDefaultAdapter();
		
		mAdapter.cancelDiscovery();
	  
		mDevice = mAdapter.getRemoteDevice(MAC);
	  
	  if(mDevice != null) {
		  Connect = new ConnectThread(mDevice);
		  new Thread(Connect).start();
	  }
	}
	
	
	public static byte[] stringToBytes(String str) {
		 char[] buffer = str.toCharArray();
		 byte[] b = new byte[buffer.length << 1];
		 for (int i = 0; i < buffer.length; i++) {
		 int bpos = i << 1;
		 b[bpos] = (byte) ((buffer[i]&0xFF00)>>8);
		 b[bpos + 1] = (byte) (buffer[i]&0x00FF);
		 }
		 return b;
		}
	
	
	public void write(String message) {
		if(Connect != null) {
			if(Connect.getConnectedThread() != null) {
				Connect.getConnectedThread().write(stringToBytes(message));
			}
		}
	}
	
	public String read() {
		if(Connect != null) {
			if(Connect.getConnectedThread() != null) {
				return Connect.getConnectedThread().read();
			}
		}
		return "";
	}
	
	public boolean check() {
		if(Connect != null) {
			if(Connect.getConnectedThread() != null) { 
				return true;
			}
		}
		return false;
	}
  };




