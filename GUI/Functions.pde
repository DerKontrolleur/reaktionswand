boolean CONNECTED = false;
final int text_x = 100;
final int text_y = 150;
void connectionStatus() {
  if (!CONNECTED) {
    if (bt_turningOn) {
      fill(0, 0, 0);
      textFont(font, 35);  
      text("Starting Bluetooth(TM) services...", text_x, 100);
    }
    if (bt_on) {
      fill(0, 0, 0);
      textFont(font, 35);      
      text("Bluetooth(TM) services started!", text_x, text_y);
    }
    if (bt_searching) {
      fill(0, 0, 0); 
      textFont(font, 35);  
      text("Searching for device...", text_x, text_y+50);
    }
    if (bt_deviceFound) {
      fill(0, 0, 0); 
      textFont(font, 35);  
      text("Device found!", text_x, text_y+100);
    }
    if (bt_creatingSocketConnection) {
      fill(0, 0, 0); 
      textFont(font, 35);  
      text("Creating socket connection...", text_x, text_y+150);
    }
    if (bt_socketConnected) {
      fill(0, 0, 0); 
      textFont(font, 35);  
      text("Socket connected!", text_x, text_y+200);
    }
    if (bt_connecting) {
      fill(0, 0, 0); 
      textFont(font, 35);  
      text("Connecting to device...", text_x, text_y+250);
    } 
    if (bt_connected) {
      fill(0, 0, 0); 
      textFont(font, 35);  
      text("Connected!", text_x, text_y+300);
      fill(0, 0, 0); 
      textFont(font, 35);  
      text("Sending start request...", text_x, text_y+350);
      bluetooth.write(START);
      fill(0, 0, 0); 
      textFont(font, 35);
      text("Waiting for answer...", text_x, text_y+400);
      if (bluetooth.read() != "") {
        fill(0, 0, 0); 
        textFont(font, 35);  
        text("Got it!", text_x, text_y+450);
        CONNECTED = true;
      }
    }
  }
}


void Display() {
  // All fields are displayed. Set true or false to make
  // them visible and responding
  // Games //
  games.display(Games, g_x+g_w/2, g_y+g_h/2);
  tictactoe.display(TicTacToe, ttt_x+ttt_w/2, ttt_y+ttt_h/2);
  fourwins.display(FourWins, vw_x+vw_w/2, vw_y+vw_h/2);
  reactionF.display(ReactionF, rf_x+rf_w/2, rf_y+rf_h/2);
  reactionT.display(ReactionT, rt_x+rt_w/2, rt_y+rt_h/2);  

  tictactoe_info.display(TicTacToe, ttti_x+ttti_w/2, ttti_y + ttti_h/2);

  // Programs //
  programs.display(Programs, p_x+p_w/2, p_y+p_h/2);

  // Options & Help //
  optionsHelp.display(OptionsHelp, oph_x+oph_w/2, oph_y+oph_h/2);
  options.display(Options, op_x+op_w/2, op_y+op_h/2);
  help.display(Help, he_x+he_w/2, he_y+he_h/2);

  // Start
  begin.display(Begin, st_x+st_w/2, st_y + st_h/2);
}

