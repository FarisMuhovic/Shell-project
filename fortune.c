#include "fortune.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "defines.h"

const char* fortunes[] = {
" _________________________________________\n"
"/ If you stand on your head, you will get \\\n"
"\\ footprints in your hair.                /\n"
" -----------------------------------------\n"
"  \\     .    _  .    \n"
"   \\    |\\_|/__/|    \n"
"       / / \\// \\  \\  \n"
"      /__|O||O|__ \\ \n"
"     |/_ \\_/\\_/ _\\ |  \n"
"     | | (____) | ||  \n"
"     \\//\\___/\\__/  // \n"
"     (_/         ||\n"
"      |          ||\n"
"      |          ||\\   \n"
"       \\        //_/  \n"
"       \\______//\n"
"       __ || __||\n"
"      (____(____)\n\n"
,
" _________________________________________\n"
"/ All generalizations are false,          \n"
"|                                         |\n"
"| including this one.                     |\n"
"|                                         |\n"
"| -- Mark Twain, Pudd'nhead Wilson's     |\n"
"\\ Calendar                               /\n"
" -----------------------------------------\n"
"   \\ \n"
"    \\ \n"
"        .--.\n"
"       |o_o |\n"
"       |:_/ |\n"
"      //   \\ \n"
"     (|     | )\n"
"    /'\\_   _/`\n"
"    \\___)=(___/\n\n"
,
"     ________________________________________\n"
"/ Just because the message may never be  \n"
"| received does not mean it is not worth |\n"
"\\ sending.                               /\n"
" ----------------------------------------\n"
"        \\    ,-^-.\n"
"         \\   !oYo!\n"
"          \\ /./=\\.\\______\n"
"               ##        )\\/\n"
"                ||-----w||\n"
"                ||      ||\n"
"\n"
"               Cowth Vader\n\n"
,
" ____________________________________ \n"
"/ You may be gone tomorrow, but that \\ \n"
"| doesn't mean that you weren't here | \n"
"\\ today.                             / \n"
" ------------------------------------ \n"
"    \\                                  ___-------___ \n"
"     \\                             _-~~             ~~-_ \n"
"      \\                         _-~                    /~-_ \n"
"             /^\\__/^\\         /~  \\                   /    \\ \n"
"           /|  O|| O|        /      \\_______________/        \\ \n"
"          | |___||__|      /       /                \\          \\ \n"
"          |          \\    /      /                    \\          \\ \n"
"          |   (_______) /______/                        \\_________ \\ \n"
"          |         / /         \\                      /            \\ \n"
"           \\         \\^\\       \\                  /               \\     / \n"
"             \\         ||          \\______________/      _-_       //\\__// \n"
"               \\       ||------_-~~-_ ------------- \\ --/~   ~\\    || __/ \n"
"                 ~-----||====/~     |==================|       |/~~~~~ \n"
"                  (_(__/  ./     /                    \\_\\      \\. \n"
"                         (_(___/                         \\_____)_) \n"
" \n"
,
"  ________________________________________  \n"
" / No violence, gentlemen -- no violence, \\  \n"
" | I beg of you! Consider the furniture!  |  \n"
" \\ -- Sherlock Holmes                     /  \n"
"  ----------------------------------------  \n"
"       \\                    / \\  //\\  \n"
"        \\    |\\___/|      /   \\//  \\  \n"
"             /0  0  \\__  /    //  | \\ \\      \n"
"            /     /  \\/_/    //   |  \\  \\    \n"
"            @_^_@'/   \\/_   //    |   \\   \\   \n"
"            //_^_/     \\/_ //     |    \\    \\  \n"
"         ( //) |        \\///      |     \\     \\  \n"
"       ( / /) _|_ /   )  //       |      \\     _\\  \n"
"     ( // /) '/,_ _ _/  ( ; -.    |    _ _\\.-~        .-~~~^-.  \n"
"   (( / / )) ,-{        _      `-.|.-~-.           .~         `.  \n"
"  (( // / ))  '/\\      /                 ~-. _ .-~      .-~^-.  \\  \n"
"  (( /// ))      `.   {            }                   /      \\  \\  \n"
"   (( / ))     .----~-.\\        \\-'                 .~         \\  `. \\^-.  \n"
"              ///.----..>        \\             _ -~             `.  ^-`  ^-_  \n"
"                ///-._ _ _ _ _ _ _}^ - - - - ~   `                  ~-- ,.-~  \n"
"                                                                   /.-~  \n"
"   \n"
};


int fortune(int argc, char** argv) {
    if (argc == 0) {
        srand(time(NULL));
        printf("%s", fortunes[rand() % 5]);
        return 0;
    } else if (strcmp(argv[1], "--cat") == 0) {
        if (strcmp(argv[2], "--black") == 0) {
            printf(BLACK"%s", fortunes[0]);
        }
        else if (strcmp(argv[2], "--red") == 0) {
            printf(RED"%s", fortunes[0]);
        }
        else if (strcmp(argv[2], "--yellow") == 0) {
            printf(YELLOW"%s", fortunes[0]);
        }
        else if (strcmp(argv[2], "--green") == 0) {
            printf(GREEN"%s", fortunes[0]);
        }
        else if (strcmp(argv[2], "--blue") == 0) {
            printf(BLUE"%s", fortunes[0]);
        }
        else if (strcmp(argv[2], "--purple") == 0) {
            printf(PURPLE"%s", fortunes[0]);
        }
        else if (strcmp(argv[2], "--cyan") == 0) {
            printf(CYAN"%s", fortunes[0]);
        }   
        else {
            printf(RESET"%s", fortunes[0]);
        }
    } else if (strcmp(argv[1], "--penguin") == 0) {
                if (strcmp(argv[2], "--black") == 0) {
            printf(BLACK"%s", fortunes[1]);
        }
        else if (strcmp(argv[2], "--red") == 0) {
            printf(RED"%s", fortunes[1]);
        }
        else if (strcmp(argv[2], "--yellow") == 0) {
            printf(YELLOW"%s", fortunes[1]);
        }
        else if (strcmp(argv[2], "--green") == 0) {
            printf(GREEN"%s", fortunes[1]);
        }
        else if (strcmp(argv[2], "--blue") == 0) {
            printf(BLUE"%s", fortunes[1]);
        }
        else if (strcmp(argv[2], "--purple") == 0) {
            printf(PURPLE"%s", fortunes[1]);
        }
        else if (strcmp(argv[2], "--cyan") == 0) {
            printf(CYAN"%s", fortunes[1]);
        }   
        else {
            printf(RESET"%s", fortunes[1]);
        }
    } else if (strcmp(argv[1], "--cow") == 0) {
        if (strcmp(argv[2], "--black") == 0) {
            printf(BLACK"%s", fortunes[2]);
        }
        else if (strcmp(argv[2], "--red") == 0) {
            printf(RED"%s", fortunes[2]);
        }
        else if (strcmp(argv[2], "--yellow") == 0) {
            printf(YELLOW"%s", fortunes[2]);
        }
        else if (strcmp(argv[2], "--green") == 0) {
            printf(GREEN"%s", fortunes[2]);
        }
        else if (strcmp(argv[2], "--blue") == 0) {
            printf(BLUE"%s", fortunes[2]);
        }
        else if (strcmp(argv[2], "--purple") == 0) {
            printf(PURPLE"%s", fortunes[2]);
        }
        else if (strcmp(argv[2], "--cyan") == 0) {
            printf(CYAN"%s", fortunes[2]);
        }   
        else {
            printf(RESET"%s", fortunes[2]);
        }
    } else if (strcmp(argv[1], "--turtle") == 0) {
        if (strcmp(argv[2], "--black") == 0) {
            printf(BLACK"%s", fortunes[3]);
        }
        else if (strcmp(argv[2], "--red") == 0) {
            printf(RED"%s", fortunes[3]);
        }
        else if (strcmp(argv[2], "--yellow") == 0) {
            printf(YELLOW"%s", fortunes[3]);
        }
        else if (strcmp(argv[2], "--green") == 0) {
            printf(GREEN"%s", fortunes[3]);
        }
        else if (strcmp(argv[2], "--blue") == 0) {
            printf(BLUE"%s", fortunes[3]);
        }
        else if (strcmp(argv[2], "--purple") == 0) {
            printf(PURPLE"%s", fortunes[3]);
        }
        else if (strcmp(argv[2], "--cyan") == 0) {
            printf(CYAN"%s", fortunes[3]);
        }   
        else {
            printf(RESET"%s", fortunes[3]);
        }
    } else if (strcmp(argv[1], "--dragon") == 0) {
        if (strcmp(argv[2], "--black") == 0) {
            printf(BLACK"%s", fortunes[4]);
        }
        else if (strcmp(argv[2], "--red") == 0) {
            printf(RED"%s", fortunes[4]);
        }
        else if (strcmp(argv[2], "--yellow") == 0) {
            printf(YELLOW"%s", fortunes[4]);
        }
        else if (strcmp(argv[2], "--green") == 0) {
            printf(GREEN"%s", fortunes[4]);
        }
        else if (strcmp(argv[2], "--blue") == 0) {
            printf(BLUE"%s", fortunes[4]);
        }
        else if (strcmp(argv[2], "--purple") == 0) {
            printf(PURPLE"%s", fortunes[4]);
        }
        else if (strcmp(argv[2], "--cyan") == 0) {
            printf(CYAN"%s", fortunes[4]);
        }   
        else {
            printf(RESET"%s", fortunes[4]);
        }
    }
    return 0;
}
