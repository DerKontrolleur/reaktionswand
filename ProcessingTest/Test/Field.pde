public class Field {
  private int _positionX;
  private int _positionY;
  private int _width;
  private int _height;
  
  private int _red;
  private int _green;
  private int _blue;
  
  private boolean _state;
  
  private String _title;
  private int _textPositionX;
  private int _textPositionY;
  
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
    _textPositionX = _positionX + _width/2;
    _textPositionY = _positionY + _height-20;
    _tempTime = 0;
    text = createFont("Arial",_width/8);
  }
  
  
  public void changeState() {
    if(_state) {
      _state = false;
    }
    else {
      _state = true;
    }
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
  
  public void show() {
      fill(_red, _green, _blue);
      rect(_positionX,_positionY, _width, _height);
      stroke(255);
      strokeWeight(10);
      
      textFont(text, _width/8);
      textAlign(CENTER);
      fill(255);
      text(_title, _textPositionX, _textPositionY);
      
      if(_title.equals("Spiele") || _title.equals("Programme")) {
        if(!_state) {
          _time = millis();
          if(_time - _tempTime >= 10) {
            _tempTime = _time;
            if(_height <= 870) {
              _height += 1;
            }
             if(_textPositionY >= 70) {
              _textPositionY -= 1;
             }
          }
        }  
      
      if(_state) {
        _time = millis();
        if(_time - _tempTime >= 10) {
          _tempTime = _time;
          if(_height >= 370) {
            _height -= 1;
          }
           if(_textPositionY <=  _positionY + _height-30) {
            _textPositionY += 1;
           }
        }
      }  
    }
    else {
      if(!_state) {
        _time = millis();
        if(_time - _tempTime >= 10) {
          _tempTime = _time;
          if(_positionY >= 410) {
            _positionY -= 1;
            _height += 1;
          }
           if(_textPositionY >= 460) {
            _textPositionY -= 1;
           }
        }
      }  
      
      if(_state) {
        _time = millis();
        if(_time - _tempTime >= 10) {
          _tempTime = _time;
          if(_positionY <= 600) {
            _positionY += 1;
            _height -= 1;
          }
           if(_textPositionY <=  _positionY + _height-20) {
            _textPositionY += 1;
           }
        }
      }
    }
  }
  
  boolean check() {
    if (mouseX > _positionX && mouseX < (_positionX+_width) && mouseY > _positionY && mouseY < (_positionY+_height)) {
      return true;
    }
    return false;
  }
};

