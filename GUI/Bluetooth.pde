import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;

import java.io.IOException;
import java.io.OutputStream;
import java.io.InputStream;

import android.util.Log;
import java.util.UUID;
import java.util.Set;

import android.os.Handler;
import android.os.Message;

private BluetoothAdapter bt_adapter = BluetoothAdapter.getDefaultAdapter();
private BluetoothDevice bt_device = null;
private BluetoothSocket bt_socket = null;
private Set<BluetoothDevice> bt_pairedDevices = null;
private OutputStream bt_outputStream = null;
private InputStream bt_inputStream = null;

private final UUID bt_uuid = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");

private String bt_message = "";
private final int BT_MESSAGE_READ = 1;

boolean bt_deviceFound = false;
boolean bt_on = false;
boolean bt_turningOn = false;
boolean bt_connecting = false;
boolean bt_connected = false;
boolean bt_creatingSocketConnection = false;
boolean bt_socketConnected = false;
boolean bt_searching = false;

private IntentFilter bt_filter_find = new IntentFilter(BluetoothDevice.ACTION_FOUND);
private BroadcastReceiver bt_receiver = new mBroadcastReceiver();



public class Bluetooth implements Runnable {
  public Bluetooth() {
  }

  private byte[] stringToBytes(String str) {
    char[] buffer = str.toCharArray();
    byte[] b = new byte[buffer.length << 1];
    for (int i = 0; i < buffer.length; i++) {
      int bpos = i << 1;
      b[bpos] = (byte)((buffer[i]&0xFF00)>>8);
      b[bpos + 1] = (byte)(buffer[i]&0x00FF);
    } 
    return b;
  }
  
  @Override
    public void run() {
    bt_turningOn = true;
    while (!bt_adapter.isEnabled ()) {
      bt_adapter.enable();
    }
    bt_on = true;

    //bt_device = bt_adapter.getRemoteDevice("00:06:66:06:BE:72");

    if (bt_device == null) {
      bt_pairedDevices = bt_adapter.getBondedDevices();
      if (bt_pairedDevices.size() > 0) {
        bt_searching = true;
        for (BluetoothDevice device : bt_pairedDevices) {
          if (device.getAddress().equals("00:06:66:06:BE:72")) {
            bt_device = bt_adapter.getRemoteDevice(device.getAddress());
            bt_deviceFound = true;
          }
        }
      }
    }

    if (bt_device == null) {
      bt_searching = true;
      registerReceiver(bt_receiver, bt_filter_find);
      if (!bt_adapter.isDiscovering ()) {
        bt_adapter.startDiscovery();
      }
    }

    while (bt_device == null) {
    }

    if (bt_device != null) {
      bt_creatingSocketConnection = true;
      Connect connection = new Connect();
      new Thread(connection).start();
    }

    while (bt_socket == null) {
    }
    bt_socketConnected = true;

    if (bt_socket != null) {
      bt_connecting = true;
      Communication communicate = new Communication();
      new Thread(communicate).start();
      bt_connected = true;
    }
  }


  public void write(String message) {
    if (bt_socket != null) {
      try {
        bt_outputStream = bt_socket.getOutputStream();
      } 
      catch(IOException getOutputStreamException) {
        Log.e("Write", "Error getting output stream");
      }

      try {
        bt_outputStream.write(stringToBytes(message));
      } 
      catch(IOException writeOutputStreamException) { 
        Log.e("Write", "Error writing to output stream");
      }
    }
  }

  public String read() {
    return bt_message;
  }

  public void cancel() {
    try {
      bt_socket.close();
    } 
    catch(IOException closeException) {
    }
  }
};


private final Handler handler = new Handler() {
  @Override
    public void handleMessage(Message msg) {
    switch(msg.what) {
    case BT_MESSAGE_READ:
      byte[] readBuf = (byte[])msg.obj;
      bt_message = new String(readBuf, 0, msg.arg1);
      break;
    }
  }
};


private class mBroadcastReceiver extends BroadcastReceiver {
  private String discoveredDeviceName;
  @Override
    public void onReceive(Context context, Intent intent) {
    String action = intent.getAction();

    if (BluetoothDevice.ACTION_FOUND.equals(action)) {
      discoveredDeviceName = intent.getStringExtra(BluetoothDevice.EXTRA_NAME);
    }

    if (discoveredDeviceName.equals("FireFly-BE72")) { 
      bt_device = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
      bt_deviceFound = true;
    }
  }
};


private class Connect implements Runnable {
  public Connect() {
    bt_adapter.cancelDiscovery();
    try {
      bt_socket = bt_device.createRfcommSocketToServiceRecord(bt_uuid);
    }
    catch(IOException createSocketException) {
      Log.e("ConnectToBluetooth", "Error with Socket");
    }
  }

  @Override
    public void run() {
    try {
      bt_socket.connect();
    }  
    catch (IOException connectException) {
      Log.e("ConnectToBluetooth", "Error with Socket Connection");
      try {
        bt_socket.close();
      }
      catch(IOException closeException) {
      }
      return;
    }
  }
};


private class Communication implements Runnable {
  @Override
    public void run() {
    try {
      bt_inputStream = bt_socket.getInputStream();
    }
    catch(IOException getInputStreamException) {
      Log.e("Read", "Error getting input stream");
    }

    byte[] buffer = new byte[1024];
    int bytes;
    while (true) {
      try {
        bytes = bt_inputStream.read(buffer);
        handler.obtainMessage(BT_MESSAGE_READ, bytes, -1, buffer).sendToTarget();
      } 
      catch (IOException e) {
        Log.e("Read", "Error reading from input stream");
        break;
      }
    }
  }
};

