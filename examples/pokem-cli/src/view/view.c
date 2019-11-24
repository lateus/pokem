#include "view.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define forever for(;;)
#define DISCLAIMER \
    "This program comes with ABSOLUTELY NO WARRANTY.\n" \
    "This is free software, and you are welcome to modify and/or redistribute it under\n" \
    "the terms of the GNU GENERAL PUBLIC LICENSE v2. Please visit http://www.gnu.org/licenses/\n\n"

int showSelectionScreen()
{
    fputs("Select one of the following options:\n"
          "1. Decode a Wonder Mail\n"
          "2. Encode a Wonder Mail\n"
          "3. Decode a SOS Mail\n"
          "4. Encode a SOS Mail\n"
          "5. Convert a SOS Mail -> A-OK Mail -> Thank-You Mail\n>>> ", stdout);

    fflush(stdin);
    return getchar() - '0';
}


int showGeneralHelp(const char *programName)
{
    fputs(DISCLAIMER, stdout);

    fprintf(stdout, "Usage: %s [ARGUMENTS]...\n"
                    "[ARGUMENTS]:\n"
                    "This program will try to autodetect what do you want to do based\n"
                    "on your input. If you enter a Wonder Mail, this program will try\n"
                    "to decode it. If you enter exactly 9 or 6 arguments, this program\n"
                    "will try to encode a Wonder Mail or a SOS Mail respectively.\n"
                    "If your input is incorrect, a menu will appear to bring you help\n"
                    "about a specific topic.\n\n"
                    "Developed by Carlos Enrique Perez Sanchez.\n", programName);
    fflush(stdout);
    return NoError;
}


int showHelpDecodingWM(const char* programName) /* argv[0] is the program path/name */
{
    fputs(DISCLAIMER, stdout);

    fprintf(stdout, "========= HELP DECODING WONDER MAIL =========\n"
                    "Usage: %s [PASSWORD_1] [PASSWORD_2]...\n"
                    "Enter the password in UPPERCASE.\n"
                    "Symbols conventions:\n"
                    "\t> 'FEMALE' are '*'\n"
                    "\t> 'MALE' are '/'\n"
                    "\t> '...' are '.'\n\n"
                    "Examples of valid entries:\n"
                    "\t%s 1?J9N/X?4P?34??764?0P??W 4?6F7M+?4JNRJ*??K??0+9?? 16J.8!0?1PS35-?06N?RP8?W\n"
                    "\t%s ??J9XJX?2P??8??F6H?0P??W\n"
                    "NOTE: On UNIX, you must quote (using simple quotes) the passwords.\n"
                    "      The first one will decode three Wonder Mails, and the second will decode just one.\n\n"
                    "Developed by Carlos Enrique Perez Sanchez.\n", programName, programName, programName);
    fflush(stdout);
    return NoError;
}


int showHelpEncodingWM(const char* programName)
{
    fputs(DISCLAIMER, stdout);

    fprintf(stdout, "========= HELP ENCODING WONDER MAIL =========\n"
                    "Usage: %s [Mission type] [Pkmn client] [Pkmn target] [Item to find/deliver] [Dungeon] [Floor] [Reward type] [Item reward] [Friend area reward]\n"
                    "Enter only the numerical values.\nYou must enter exactly 9 arguments.\n\n"
                    "Example of valid entry:\n%s 0 375 1 0 46 2 6 54 0\n"
                    "NOTE: It's a Help-type mission from Milotic, the target pkmn and the item\n"
                    "      to find/deliver are ignored. The rescue is in Fantasy Strait at 2nd floor.\n"
                    "      The reward is a lot of money and a Wish Stone, and the Friend Area Reward is ignored.\n\n"
                    "Developed by Carlos Enrique Perez Sanchez.\n\n", programName, programName);
    showDatabase();

    fflush(stdout);
    return NoError;
}


int showHelpDecodingSOS(const char* programName)
{
    fputs(DISCLAIMER, stdout);

    fprintf(stdout, "========== HELP DECODING SOS MAIL ==========\n"
                    "Usage: %s [PASSWORD_1] [PASSWORD_2]...\n"
                    "Enter the password in UPPERCASE.\n"
                    "Symbols conventions:\n"
                    "\t> 'FEMALE' are '*'\n"
                    "\t> 'MALE' are '/'\n"
                    "\t> '...' are '.'\n\n"
                    "Examples of valid entries:\n"
                    "\t%s ?M???.R066???2FC?!?R????3HCP?-??32H???Y?M4C??1J??NQ04? S6???.RF?6F??NWH*5KC???RH1!9?8?JK7P0??SNMJRPSKJ??7QJ4N\n"
                    "\t%s S2???.RYW6F\?\?!P5*5KW???RH3J-?3?JX7P0??SNM42PSKJ\?\?!QJ4N\n" /* Seek others passwords that not contains trigraphs */
            "NOTE: On UNIX, you must quote (using simple quotes) the passwords.\n"
            "      The first one will decode two SOS Mails, and the second will decode just one.\n\n"
            "Developed by Carlos Enrique Perez Sanchez.\n\n", programName, programName, programName);

    fflush(stdout);
    return NoError;
}


int showHelpEncodingSOS(const char *programName)
{
    fputs(DISCLAIMER, stdout);

    fprintf(stdout, "========== HELP ENCODING SOS MAIL ==========\n"
                    "Usage: %s [Pkmn client] [Pkmn nickname] [Dungeon] [Floor] [Mail ID (default: 0)] [Rescue chances (default: 10)]\n"
                    "Enter only the numerical values.\nYou must enter exactly 6 arguments.\n\n"
                    "Example of valid entry:\n%s 113 Nurcy 58 50 1234 10\n"
                    "NOTE: Rescue a Chansey named \'Nurcy\' at 'Joyous Tower' floor 50.\n"
                    "      The Mail ID is 1234 and you can try 10 times.\n\n"
                    "Developed by Carlos Enrique Perez Sanchez.\n\n", programName, programName);
    showDatabase();

    return NoError;
}


int showHelpConverting(const char *programName)
{
    fputs(DISCLAIMER, stdout);

    fprintf(stdout, "========= HELP CONVERTING SOS MAIL =========\n"
                    "Usage: %s [PASSWORD_1] [PASSWORD_2]...\n"
                    "Enter the password in UPPERCASE.\n"
                    "Symbols conventions:\n"
                    "\t> 'FEMALE' are '*'\n"
                    "\t> 'MALE' are '/'\n"
                    "\t> '...' are '.'\n\n"
                    "Examples of valid entries:\n"
                    "\t%s ?M???.R066???2FC?!?R????3HCP?-??32H???Y?M4C??1J??NQ04? S6???.RF?6F??NWH*5KC???RH1!9?8?JK7P0??SNMJRPSKJ??7QJ4N\n"
                    "\t%s S2???.RYW6F\?\?!P5*5KW???RH3J-?3?JX7P0??SNM42PSKJ\?\?!QJ4N\n" /* Seek others passwords that not contains trigraphs */
            "NOTE: On UNIX, you must quote (using simple quotes) the passwords.\n"
            "      The first one will convert two SOS Mails, and the second will convert just one.\n"
            "      You will get a A-OK Mail that allows you to be rescued.\n"
            "      You will get also a Thank-You Mail, use it if you want.\n\n"
            "Developed by Carlos Enrique Perez Sanchez.\n\n", programName, programName, programName);

    fflush(stdout);
    return NoError;
}


void showDatabase()
{
    int i;
    forever { /* infinite loop */
        fputs("Enter one of the following values to see the desired database:\n"
              "1) Pkmn database\n"
              "2) Dungeons database\n"
              "3) Mission type\n"
              "4) Reward type\n"
              "5) Friend area reward\n"
              "OTHER KEY: [Exit]\n"
              "Your choice?: ", stdout);
        fflush(stdout);
        fflush(stdin);
        int choice;
        if (scanf("%d", &choice) <= 0) {
            choice = 0; /* exit */
        }
        if (choice < 1 || choice > 5) {
            fputs("Exiting...\n", stdout);
            return;
        } else {
            switch (choice) {
            case 1:
                fprintf(stdout, " :: Pkmn database: ---\n");
                for (i = 0; i < 405; ++i) {
                    fprintf(stdout, "    %d - %s\n", i, pkmnSpeciesStr[i]);
                }
                break;
            case 2:
                fprintf(stdout, " :: Dungeons database: ---\n");
                for (i = 0; i < 63; ++i) {
                    fprintf(stdout, "    %d - %s\n", i, dungeonsStr[i]);
                }
                break;
            case 3:
                fprintf(stdout, " :: Mission type: ---\n");
                for (i = 0; i < 6; ++i) {
                    fprintf(stdout, "    %d - %s\n", i, missionTypeObjectiveStr[i]);
                }
                break;
            case 4:
                fprintf(stdout, " :: Reward type: ---\n");
                fputs("    0 - Money\n"
                      "    1 - Money + ?\n"
                      "    2 - Item\n"
                      "    3 - Item + ?\n"
                      "    4 - Money\n"
                      "    5 - Money + ?\n"
                      "    6 - Item\n"
                      "    7 - Item + ?\n"
                      "    8 - Friend area\n", stdout);
                break;
            case 5:
                fprintf(stdout, " :: Friend area reward: ---\n"); /* update the range if you uncomment the full database */
                for (i = 0; i < 4; ++i) {
                    fprintf(stdout, "    %d - %s\n", i, friendAreasStr[i]);
                }
                break;
            default:
                fprintf(stderr, " :: Invalid key\n");   /* this should never happen */
                break;
            }
            putchar('\n');
        }
    }
}


void printWMData(const struct WM_INFO *mailInfo)
{
    fprintf(stdout, "\n%s\n\n%s\n%s\n\n"
                    "Client: %s\n"
                    "Objective: %s\n"
                    "Place: %s  %s\n"
                    "Difficulty: %c\n"
                    "Reward: %s\n"
                    "Password: %s\n"
                    ". . . . . . . . . . . . . . . . . . . . . . .\n\n",
            mailInfo->head, mailInfo->body1, mailInfo->body2, mailInfo->client, mailInfo->objective, mailInfo->place, mailInfo->floor, mailInfo->difficulty, mailInfo->reward, mailInfo->WMail);
}


void printSOSData(const struct SOS_INFO *mailInfo)
{
    fprintf(stdout, "\n%s\n\n%s\n\n"
                    "Client: %s (%s)\n"
                    "Objective: %s\n"
                    "Place: %s  %s\n"
                    "Difficulty: %c\n"
                    "Reward: %s\n"
                    "ID: %s\n"
                    "Chances left: %s\n"
                    "Password: %s\n"
                    ". . . . . . . . . . . . . . . . . . . . . . .\n\n",
            mailInfo->head, mailInfo->body, mailInfo->nickname, mailInfo->client, mailInfo->objective, mailInfo->place, mailInfo->floor, mailInfo->difficulty, mailInfo->reward, mailInfo->id, mailInfo->chancesLeft, mailInfo->SOSMail);
}
