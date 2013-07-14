package com.siemens.test;

import processing.core.*;


public class Field extends PApplet {
	  private int _positionX;
	  private int _positionY;
	  private int _width;
	  private int _height;
	  
	  private int _red;
	  private int _green;
	  private int _blue;
	  
	  private boolean _state;
	  
	  private String _title;
	  private int _textPosition;
	  
	  private long _time;
	  private long _tempTime;
	  private PFont text;
	  
	  
	  public Field(String title, int positionX, int positionY, int width, int height, int red, int green, int blue, boolean state) {
	    _title = title;
	    _positionX = positionX;
	    _positionY = positionY;
	    _width = width;
	    _height = height;
	    _red = red;
	    _green = green;
	    _blue = blue;
	    _state = state;
	    _textPosition = _positionX + _width/2;
	    _tempTime = 0;
	    text = createFont("Arial",_width/5);
	  }
	  
	  public void setState(boolean state) {
	    _state = state;
	  }
	  
	  public boolean getState() {
	    return _state;
	  }
	  
	  public void setPositionX(int positionX) {
	    _positionX = positionX;
	  }
	  
	  public void setPositionY(int positionY) {
	    _positionY = positionY;
	  }
	  
	  public void setWidth(int width) {
	    _width = width;
	  }
	  
	  public void setHeight(int height) {
	    _height = height;
	  }
	  
	  public void setTextPosition(int textPosition) {
	    _textPosition = textPosition;
	  }
	  
	  public void show() {
	      fill(_red, _green, _blue);
	      rect(_positionX,_positionY, _width, _height);
	      stroke(255);
	      strokeWeight(10);
	      
	      textFont(text, _width/5);
	      textAlign(CENTER);
	      fill(255);
	      text(_title, _textPosition, _height-20);
	      
	      if(!_state) {
	      _time = millis();
	      if(_time - _tempTime >= 10) {
	        _tempTime = _time;
	        if(_height <= 550) {
	          _height += 1;
	        }
	      }
	    }  
	    
	    if(_state) {
	      _time = millis();
	      if(_time - _tempTime >= 10) {
	        _tempTime = _time;
	        if(_height >= 350) {
	          _height -= 1;
	        }
	      }
	    }  
	  }
	  
	  public void changeState() {
		    if(_state) {
		      _state = false;
		    }
		    else {
		      _state = true;
		    }
		  }
	  
	  boolean check() {
		    if (mouseX > _positionX && mouseX < (_positionX+_width) && mouseY > _positionY && mouseY < (_positionY+_height)) {
		      return true;
		    }
		    return false;
		  }
	};
