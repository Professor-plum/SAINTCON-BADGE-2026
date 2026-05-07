#include "unlocks.h"
#include "framebuffer.h"
#include "buttons.h"


const char* unlock_names[30] = {
"", // Obtained from having > 100 points total score - Game play easy
"", // Obtained from having > 2500 points total score -game play medium
"impossible score", // - Game play hard

"", // Obtained by having a crew with all different classes - social medium
"", // Obtained from "The Obsidian Monolith" event - Game play hard
"", // Obtained from "Relics of the First Builders" event - Game play hard

"", // Obtained by having a fully staffed crew- social easy
"", // Obtained from being a crew member on another player's mission - social medium
"", // Obtained from being a crew member on lots of players' missions - social hard

"", // Found via USB UART - easy
"", // Found via docker port UART - medium
"UART HARD", // Found via UART - hard

"", // Enter the Konima code (easy)
"Trivia ????", //(Medium)
"UNKNOWN", // (Hard)

"UNKNOWN", // (Easy)
"Xor or Caesar Cipher", //(Medium) 
"Crypto ??", // (Hard)	

"", // found on the Hardware Test screen - hardware easy
"", // Found on the EEPROM - hardware medium
"Hardware HARD", // - Hardware hard

"", // Found on the 5bit dot pattern - badge art easy	
"", // Constellations - badge art (Medium)	
"Art hidden", // badge art (Hard)	

"", // Found by reading flash image - RE easy
"", // Found via firmware RE (large if tree)- RE medium
"Crack Hash", // RE hard

"", //community
"", //community
"", //community

"", //community
"", //community
"", //community

};