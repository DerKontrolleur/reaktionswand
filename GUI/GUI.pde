// Bluetooth //
Bluetooth bluetooth = new Bluetooth();

// Messages //
final String STOP = "stop\n";
final String START = "start\n";
final String BACK = "back\n";
final String HOME = "home\n";
final String TICTACTOE = "tictactoe\n";
final String FOURWINS = "fourwins\n";
final String REACTION_F = "reactionf\n";
final String REACTION_T = "reactiont\n";
final String OPTIONS = "options\n";
final String HELP = "help\n";

// Swichtes //
boolean MAIN_SCREEN = false;
boolean SELECT_SCREEN = false;
boolean INFO_SCREEN = false;
boolean START_SCREEN = false;

// Setup //
PFont font;
final int font_size = 20;

final float factor = 1;
final int framerate = 40;

// Screen //
final int screen_x = 600;
final int screen_y = 1024;

// Background //
final int cells_x = 12;
final int cells_y = 20;
final int cell_size = 48;
final int cell_gap = 4;
final int cell_red = 235;
final int cell_green = 235;
final int cell_blue = 235;
final int cell_alpha = 255;

Background[][] cell = new Background[cells_x][cells_y];

// Fields //
final int field_gap = 10;

/////////////////////////////////////////////////////////////////////
//////////////  BUTTONS  ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////

// Start
final int st_x = 500;
final int st_y = 0;
final int st_w = 100;
final int st_h = 50;
final String Begin = "START";

Field begin = new Field(st_x, st_y, st_w, st_h, 0, 0, 0, 0);

/////////////////////////////////////////////////////////////////////
//////////////  GAMES  /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

// Games //
final int g_x = 10;
final int g_y = 10;
final int g_w = 580;
final int g_h = 300;
final String Games = "Spiele";

// TicTacToe //
final int ttt_x = g_x;
final int ttt_y = g_y;
final int ttt_w = 285;
final int ttt_h = 285;
final String TicTacToe = "TicTacToe";

final int ttti_x = g_x;
final int ttti_y = g_y;
final int ttti_w = 580;
final int ttti_h = 900;

// FourWins //
final int vw_x = g_x + field_gap + ttt_w;
final int vw_y = g_y;
final int vw_w = 285;
final int vw_h = 285;
final String FourWins = "Vier Gewinnt";

// ReactionF //
final int rf_x = g_x;
final int rf_y = g_y + field_gap + ttt_h;
final int rf_w = 285;
final int rf_h = 285;
final String ReactionF = "Reaktionsspiel Felder";

// ReactionT //
final int rt_x = g_x + field_gap + rf_w;
final int rt_y = vw_y + field_gap + vw_h;
final int rt_w = 285;
final int rt_h = 285;
final String ReactionT = "Reaktionsspiel Zeit";

Field games = new Field(g_x, g_y, g_w, g_h, 0, 0, 0, 255);

Field tictactoe = new Field(ttt_x, ttt_y, ttt_w, ttt_h, 0, 0, 0, 255);
Field tictactoe_info = new Field(ttti_x, ttti_y, ttti_w, ttti_h, 0, 0, 0, 255);
Field fourwins = new Field(vw_x, vw_y, vw_w, vw_h, 0, 0, 0, 255);
Field reactionF = new Field(rf_x, rf_y, rf_w, rf_h, 0, 0, 0, 255);
Field reactionT = new Field(rt_x, rt_y, rt_w, rt_h, 0, 0, 0, 255);

/////////////////////////////////////////////////////////////////////
//////////////  Programs  //////////////////////////////////////////
///////////////////////////////////////////////////////////////////

final int p_x = g_x;
final int p_y = g_y + g_h + field_gap;
final int p_w = g_w;
final int p_h = g_h;
final String Programs = "Programme";

Field programs = new Field(p_x, p_y, p_w, p_h, 0, 0, 0, 255);

/////////////////////////////////////////////////////////////////////
//////////////  OPTIONS & HELP  ////////////////////////////////////
///////////////////////////////////////////////////////////////////

// Options & Help//
final int oph_x = g_x;
final int oph_y = p_y + p_h + field_gap;
final int oph_w = g_w;
final int oph_h = g_h;
final String OptionsHelp = "Optionen & Hilfe";

// Options //
final int op_x = g_x;
final int op_y = g_y;
final int op_w = g_w;
final int op_h = 450;
final String Options = "Optionen";

// Help //
final int he_x = g_x;
final int he_y = op_y + op_h + field_gap;
final int he_w = g_w;
final int he_h = op_h;
final String Help = "Hilfe";

Field optionsHelp = new Field(oph_x, oph_y, oph_w, oph_h, 0, 0, 0, 255);
Field options = new Field(op_x, op_y, op_w, op_h, 0, 0, 0, 255);
Field help = new Field(he_x, he_y, he_w, he_h, 0, 0, 0, 255);

////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

// Time //
long time = 0;
long connectTime = 0;


void setup() {
  // Setup //
  orientation(PORTRAIT);
  frameRate(framerate);
  colorMode(RGB);
  background(255, 255, 255);
  size(int(screen_x*factor), int(screen_y*factor));
  smooth();
  font = createFont("UbuntuCondensed-Regular-35", 35, true);

  // Set background
  for (int i = 0; i < cells_x; i++) {
    for (int j = 0; j < cells_y; j++) {
      cell[i][j] = new Background(int(i*(cell_size+cell_gap)+cell_gap), int(j*(cell_size+cell_gap)+cell_gap), 
      int(cell_size), int(cell_size), cell_red, cell_green, cell_blue, cell_alpha, random(i+j));
    }
  }

  // Activate main screen
  MAIN_SCREEN = true;
  games.set(true);
  programs.set(true);
  optionsHelp.set(true);

  // Bluetooth
  new Thread(bluetooth).start();
}


void draw() {
  // Update time
  time = millis();

  // Display connection status to bluetooth device
  connectionStatus();

  // Render menu if connected
  if (CONNECTED) {
    /////////////////////////////////////////////////////////////////////
    //////////////  FIRST  /////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////

    background(255, 255, 255);

    /////////////////////////////////////////////////////////////////////
    //////////////  SECOND  ////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////

    // Render background
    for (int i = 0; i < cells_x; i++) {
      for (int j = 0; j < cells_y; j++) {
        cell[i][j].oscillate();
        cell[i][j].display();
      }
    }

    /////////////////////////////////////////////////////////////////////
    //////////////  THIRD  /////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////

    // Display ALL fields here
    Display();
  }
}

void mousePressed() {
  bluetooth.write(START);
  // Check ALL fields here //
  // Menu
  games.check();
  programs.check();
  optionsHelp.check();

  // Games
  tictactoe.check();
  fourwins.check();
  reactionF.check();
  reactionT.check();

  // Start
  begin.check();
}

void mouseReleased() {
  // Check if parent field is disabled and 
  // enable child field

    // ALL reactions here

  // Main menu
  if (!games.status() && MAIN_SCREEN) {
    MAIN_SCREEN = false;
    SELECT_SCREEN = true;

    tictactoe.set(true);
    fourwins.set(true);
    reactionF.set(true);
    reactionT.set(true);

    programs.set(false);
    optionsHelp.set(false);
  }

  if (!programs.status() && MAIN_SCREEN) {
    MAIN_SCREEN = false;
    SELECT_SCREEN = true;

    games.set(false);
    optionsHelp.set(false);
  }

  if (!optionsHelp.status() && MAIN_SCREEN) {
    MAIN_SCREEN = false;
    SELECT_SCREEN = true;

    options.set(true);
    help.set(true);

    games.set(false);
    programs.set(false);
  }

  // Info screens
  if (!tictactoe.status() && SELECT_SCREEN) {
    SELECT_SCREEN = false;
    INFO_SCREEN = true;

    tictactoe_info.set(true);
    begin.set(true);

    fourwins.set(false);
    reactionF.set(false);
    reactionT.set(false);
  }
  if (!fourwins.status() && SELECT_SCREEN) {
    SELECT_SCREEN = false;
    INFO_SCREEN = true;
  }
  if (!reactionF.status() && SELECT_SCREEN) {
    SELECT_SCREEN = false;
    INFO_SCREEN = true;
  }
  if (!reactionT.status() && SELECT_SCREEN) {
    SELECT_SCREEN = false;
    INFO_SCREEN = true;
  }

  // Start
  if (tictactoe_info.status() && INFO_SCREEN && !begin.status()) {
    INFO_SCREEN = false;
    START_SCREEN = true;

    tictactoe_info.set(false);
    bluetooth.write(TICTACTOE);
  }
}

