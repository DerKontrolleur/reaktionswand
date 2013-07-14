

Field Spiele = new Field("Spiele",20,20,370,370,247,148,29,false);
Field Programme = new Field("Programme",410,20,370,370,247,148,29,false);
Field Optionen = new Field("Optionen",20,890,370,370,247,148,29,true);
Field Hilfe = new Field("Hilfe",410,890,370,370,247,148,29,true);

void setup() {
  size(800,1280);
}

void draw() {
  background(199,178,153);
  Spiele.show();
  Programme.show();
  Optionen.show();
}

void mousePressed() {
  if(Spiele.check()) {
    Spiele.changeState();
    Optionen.changeState();
  }
  if(Programme.check()) {
    Programme.changeState();
    Hilfe.changeState();
  }
  if(Optionen.check()) {
    Optionen.changeState();
    Spiele.changeState();
  }
  if(Hilfe.check()) {
    Hilfe.changeState();
    Programme.changeState();
  }
}
