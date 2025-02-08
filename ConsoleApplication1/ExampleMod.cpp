#include "ExampleMod.h"
#include <fstream>
#include <sstream>
#include <string>
#include "Defaults.h"

bool beatReaper = false;
bool beatenRati = false;
bool reaperHasBeenBeaten = false;
bool inboss = false;
ExampleMod::ExampleMod() {
    cout << "[ReaperGameExampleMod] Mod Initialized!\n";
    CheckEnable(def.modSet1);
}

void ExampleMod::ModifyAttributes() {
    if (!modEnabled) {
        cout << "[Mod Disabled]\n";
        return;
    }
    else
    {
        if (inboss && beatReaper)
        {
            def.money += 10000;
            ofstream saveFile(def.saveFilePath, ios::out | ios::trunc);
            if (saveFile.is_open()) {
                saveFile << def.money << "\n" << def.points << "\n" << def.taxamount << "\n" << def.secretonefound << "\n" << def.secrettwofound << "\n" << def.csamount << "\n" << def.inprison << endl;
            }
            else {
                cout << "Error saving game.\n";
            }
        }
    }
}
void ExampleMod::CommandList() 
{
    if (modEnabled)
    {
        cout << "\033[A\33[2K\r"; //this will clear a line above (always include this)
        cout << "/exampleboss [ExampleMod]\n\n";
    }
}
string saveAchievements = "C:\\ReaperGame\\SaveData\\ExampleModAchievements.txt";

void ExampleMod::ModAchievementDisplay()
{
    if (modEnabled)
    {
        if (beatReaper)
        {
            cout << "Reaper Destroyed: You beat Reaper\n";
        }
    }
}

void ExampleMod::ModAchievementLoad()
{
    if (modEnabled)
    {
        ifstream achievementsFile(saveAchievements);
        if (achievementsFile.is_open()) {
            achievementsFile >> beatReaper;
            achievementsFile >> reaperHasBeenBeaten;
            achievementsFile.close();
        }
        else {
            cout << "No achievements file found... Starting fresh!\n";
        }
    }
}

void ExampleMod::ModifyAchievements()
{
    if (modEnabled)
    {
        if (beatReaper && !reaperHasBeenBeaten)
        {
            cout << "You got the Reaper Destroyed achievement! (You beat Reaper)\n";
            reaperHasBeenBeaten = true;
        }
        ModAchievementSave();
    }
}

void ExampleMod::ModAchievementSave()
{
    if (modEnabled)
    {
        ofstream achievementsFile(saveAchievements);
        if (achievementsFile.is_open()) {
            achievementsFile << beatReaper << "\n";
            achievementsFile << reaperHasBeenBeaten << "\n";
            achievementsFile.close();
        }
        else {
            cout << "Error: Unable to save achievements.\n";
        }
    }
}

void ExampleMod::Bosses()
{
    if (modEnabled) 
    {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        Type("REAPER: MAHAHAHA!!! YOU HAVE SUMMONED ME... THE REAPER!!!", 70);
        Sleep(1000);
        Type("REAPER: NOW I MUST END YOU...", 70);
        Sleep(2000);
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        Music("C:\\ReaperGame\\Assets\\gamble.mp3", true);
        inboss = true;
        int reaperHP = 120;
        int playerHP; //declare before checking if rati has been defeated
        //loads normal achievements 
        ifstream achievementsFile("C:\\ReaperGame\\SaveData\\achievements.txt");
        if (achievementsFile.is_open()) {
            string line;
            int lineNumber = 0;
            while (getline(achievementsFile, line)) {
                lineNumber++;
                //specifically checks if you have bean rati
                if (lineNumber == 19) {
                    istringstream(line) >> beatenRati;
                    break;
                }
            }
            achievementsFile.close();
        }
        if (beatenRati)
        {
            playerHP = 70;
        }
        else
        {
            playerHP = 60;
        }
        int playerPotions = 7;

        while (reaperHP > 0 && playerHP > 0) {
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif

            cout << "PLAYERS TURN!!!\n\n";
            cout << "Reaper Health: " + to_string(reaperHP) + "\n";
            cout << "Player Health: " + to_string(playerHP) + "\n\n";

            cout << "Attack Options:\n";
            cout << "Emotional Damage\n";
            cout << "Tax Forms\n";
            cout << "Child Support\n";
            if (playerPotions > 0) {
                cout << "Heal (" << playerPotions << " potions left)\n";
            }
            cout << "\n";

            string input;
            getline(cin, input);
            int damageToReaper = rand() % 16 + 3;
            int chance = rand() % 101 + 1;

            if (input == "Emotional Damage" || input == "emotional damage") {
                Type("Rolling Dice...\n", 60);
                Sleep(400);
                Type("Dice came out as... " + to_string(damageToReaper) + " damage!\n", 60);

                if (chance <= 10) {
                    Type("BUT WAIT... You have missed and caused no emotional damage...\n", 60);
                    Type("RATI'S TURN!!!\n\n", 30);
                }
                else {
                    reaperHP -= damageToReaper;
                    Type(to_string(damageToReaper) + " emotional damage done to rati... \n", 60);
                    Type("Reaper has: " + to_string(reaperHP) + " HP left. Cry... \n", 60);
                    Type("REAPER'S TURN!!!\n\n", 30);
                    Sleep(2000);
                }
            }
            else if (input == "Tax Forms" || input == "tax forms") {
                Type("Rolling Dice...\n", 60);
                Sleep(400);
                Type("Dice came out as... " + to_string(damageToReaper) + " damage!\n", 60);

                if (chance <= 10) {
                    Type("BUT WAIT... You have missed...\n", 60);
                    Type("REAPERS'S TURN!!!\n\n", 30);
                }
                else {
                    reaperHP -= damageToReaper;
                    Type(to_string(damageToReaper) + " Tax Forms given to Reaper... \n", 60);
                    Type("Reaper has: " + to_string(reaperHP) + " HP left. I HATE TAXES!!! \n", 60);
                    Type("REAPER'S TURN!!!\n\n", 30);
                    Sleep(2000);
                }
            }
            else if (input == "Child Support" || input == "child support") {
                Type("Rolling Dice...\n", 60);
                Sleep(400);
                Type("Dice came out as... " + to_string(damageToReaper) + " damage!\n", 60);

                if (chance <= 10) {
                    Type("BUT WAIT... Reaper doesnt have a child currently...\n", 60);
                    Type("REAPER'S TURN!!!\n\n", 30);
                }
                else {
                    reaperHP -= damageToReaper;
                    Type(to_string(damageToReaper) + " Child Support money taken from Reaper... \n", 60);
                    Type("Reaper has: " + to_string(reaperHP) + " HP left. I HATE PAYING CHILD SUPPORT!!! \n", 60);
                    Type("REAPER'S TURN!!!\n\n", 30);
                    Sleep(2000);
                }
            }
            if (input == "Attack Options" || input == "attack options")
            {
                const string rainbowColors[] = {
                    "\033[31m", //Red
                    "\033[32m", //Green
                    "\033[33m", //Yellow
                    "\033[34m", //Blue
                    "\033[35m"  //Magenta
                };

                int colorIndex = 0;
                auto CycleColor = [&]() {
                    cout << rainbowColors[colorIndex];
                    colorIndex = (colorIndex + 1) % 5;
                    };

                CycleColor();
                Type("Rolling Special Dice...\n", 60);
                this_thread::sleep_for(chrono::milliseconds(400));

                CycleColor();
                Type("Special Dice came out as... " + to_string(damageToReaper * 2) + " damage!\n", 60);

                if (chance <= 15)
                {
                    CycleColor();
                    Type("BUT WAIT... Reaper is skibidi toilet deluxe and you missed...\n", 60);

                    CycleColor();
                    Type("REAPER'S TURN!!!\n\n", 30);
                }
                else
                {
                    reaperHP -= damageToReaper *= 2;

                    CycleColor();
                    Type(to_string(damageToReaper) + " damage done to Reaper...\n", 60);

                    CycleColor();
                    Type("Reaper has: " + to_string(reaperHP) + " HP left.\n", 60);

                    CycleColor();
                    Type("REAPER'S TURN!!!\n\n", 30);
                    this_thread::sleep_for(chrono::milliseconds(2000));
                }

                cout << "\033[0m"; //reset
            }
            else if (input == "Heal" || input == "heal") {
                if (playerPotions > 0) {
                    playerHP += 50;
                    playerPotions--;
                    Type("You used a healing potion! +" + to_string(50) + " HP.\n", 60);
                    Type("You have " + to_string(playerPotions) + " healing potions left.\n", 60);
                    Type("REAPER'S TURN!!!\n\n", 30);
                    Sleep(2000);
                }
                else {
                    Type("No potions left! Try a different option...\n", 60);
                    continue;
                }
            }
            else {
                Type("Invalid option! Try again.\n", 60);
                continue;
            }

            //Reaper's turn
            if (reaperHP > 0) {
#ifdef _WIN32
                system("cls");
#else
                system("clear");
#endif
                cout << "REAPERS TURN!!!\n\n";
                cout << "Reaper Health: " + to_string(reaperHP) + "\n";
                cout << "Player Health: " + to_string(playerHP) + "\n\n";

                int reaperDamage = rand() % 31 + 11;
                playerHP -= reaperDamage;
                Type("Reaper dealt " + to_string(reaperDamage) + " damage to you.\n", 60);
                Type("You have: " + to_string(playerHP) + " HP left.\n", 60);
                Type("PLAYER'S TURN!!!\n\n", 30);
                Sleep(2000);
            }
        }

        if (reaperHP <= 0) {
            Type("Reaper has been defeated! You win!\n", 60);
            Type("You won 10,000 money\n", 60);
            beatReaper = true;
            ModifyAttributes();
            inboss = false;
            ModifyAchievements();
            Sleep(1000);
            cout << "type /help for commands\n";
        }
        else if (playerHP <= 0) {
            Type("You have been defeated by Reaper... Game Over!\n", 60);
            Sleep(1000);
            cout << "type /help for commands\n";
        }
    }
}

void ExampleMod::ModDescription()
{
    //you shouldnt put an enable check here preferably
    cout << "This is an Example Description!\n\n";
}

void ExampleMod::InitializeMod() {
    if (modEnabled) {
        cout << "[ReaperGameExampleMod] Mod Initialized!\n";
        EnsureSaveDirectory(false);
        HandleLoad();
        ModifyAttributes();
        HandleSave();
    }
}