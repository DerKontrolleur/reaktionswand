class Background {
  int m_x;
  int m_y;
  int m_w;
  int m_h;
  int m_red;
  int m_green;
  int m_blue;
  int m_alpha;
  float m_oscillate;

  final int sOffset = 50;
  final int fOffset = 20;
  final int val = 10;

  Background(int x, int y, int w, int h, int r, int g, int b, int a, float o) {
    m_x = x;
    m_y = y;
    m_w = w;
    m_h = h;
    m_red = r;
    m_green = g;
    m_blue = b;
    m_alpha = a;
    m_oscillate = o;
  }

  void oscillate() {
    m_oscillate += 0.08;
  }

  void display() {
    strokeWeight(1);
    stroke((m_red-sOffset)+val*sin(m_oscillate), (m_green-sOffset)+val*sin(m_oscillate), (m_blue-sOffset)+val*sin(m_oscillate));
    fill(m_red+fOffset*sin(m_oscillate), m_green+fOffset*sin(m_oscillate), m_blue+fOffset*sin(m_oscillate));
    rect(m_x, m_y, m_w, m_h);
  }
};


class Field {
  float m_x;
  float m_y;
  float m_w;
  float m_h;
  int m_red;
  int m_green;
  int m_blue;
  int m_alpha;
  boolean m_active;

  Field(float x, float y, float w, float h, int r, int g, int b, int a) {
    m_x = x;
    m_y = y;
    m_w = w;
    m_h = h;
    m_red = r;
    m_green = g;
    m_blue = b;
    m_alpha = a;
    m_active = false;
  }

  boolean check() {
    if (m_active) {
      if (mouseX > m_x && mouseX < (m_x+m_w) && mouseY > m_y && mouseY < (m_y+m_h)) {
        m_active = false;
        return true;
      }
    }
    return false;
  }

  void display(String name, float position_x, int position_y) {
    if (m_active) {
      fill(m_red, m_green, m_blue, m_alpha);
      rect(int(m_x), int(m_y), int(m_w), int(m_h));
      
      fill(255, 255, 255);    
      textFont(font, font_size);    
      textAlign(CENTER);
      text(name, int(position_x), int(position_y)); 
    }
  }

  boolean status() {
    if (m_active) {
      return true;
    }
    return false;
  }

  void set(boolean b) {
    m_active = b;
  }
};

















