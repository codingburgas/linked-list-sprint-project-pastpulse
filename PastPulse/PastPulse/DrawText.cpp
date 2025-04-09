#include "DrawText.h"
#include "Colors.h"
#include "Menu.h"

void pastPulse()
{
    setColor(YELLOW, BLACK);
    printCentered("  _____          _   _____       _           ", 1);
    printCentered(" |  __ \\        | | |  __ \\     | |          ", 2);
    printCentered(" | |__) __ _ ___| |_| |__) _   _| |___  ___  ", 3);
    printCentered(" |  ___/ _` / __| __|  ___| | | | / __|/ _ \\ ", 4);
    printCentered(" | |  | (_| \\__ \\ |_| |   | |_| | \\__ \\  __/ ", 5);
    printCentered(" |_|   \\__,_|___/\\__|_|    \\__,_|_|___/\\___| ", 6);
    resetColor();
}

void selectRole()
{
    setColor(YELLOW, BLACK);
    printCentered("   _____      _           _     _____       _      ", 1);
    printCentered("  / ____|    | |         | |   |  __ \\     | |     ", 2);
    printCentered(" | (___   ___| | ___  ___| |_  | |__) |___ | | ___ ", 3);
    printCentered("  \\___ \\ / _ \\ |/ _ \\/ __| __| |  _  // _ \\| |/ _ \\", 4);
    printCentered("  ____) |  __/ |  __/ (__| |_  | | \\ \\ (_) | |  __/", 5);
    printCentered(" |_____/ \\___|_|\\___|\\___|\\__| |_|  \\_\\___/|_|\\___|", 6);
    resetColor();
}

void userOptions()
{
    setColor(YELLOW, BLACK);
    printCentered("   _    _                  ____        _   _                 ", 1);
    printCentered("  | |  | |                / __ \\      | | (_)                ", 2);
    printCentered("  | |  | |___  ___ _ __  | |  | |_ __ | |_ _  ___  _ __  ___ ", 3);
    printCentered("  | |  | / __|/ _ \\ '__| | |  | | '_ \\| __| |/ _ \\| '_ \\/ __|", 4);
    printCentered("  | |__| \\__ \\  __/ |    | |__| | |_) | |_| | (_) | | | \\__ \\", 5);
    printCentered("   \\____/|___/\\___|_|     \\____/| .__/ \\__|_|\\___/|_| |_|___/", 6);
    printCentered("                                | |                          ", 7);
    printCentered("                                |_|                          ", 8);
    resetColor();
}

void loginText()
{
    setColor(YELLOW, BLACK);
    printCentered("   __       _____     ______ _______ __   __  ", 1);
    printCentered("  |  |    /  ___  \\ /  _____|__   __ |  \\ |  |  ", 2);
    printCentered("  |  |   |  |   |  |  | ____   |  |  |   \\|  |  ", 3);
    printCentered("  |  |   |  |   |  |  ||_   |  |  |  |  .    |  ", 4);
    printCentered("  |  |___|  |___|  |  |__|  |__|  |__|  |\\   |  ", 5);
    printCentered(" |______ \\_______/ \\_______|________|__| \\__|  ", 6);
    printCentered("                                              ", 8);
    resetColor();
}
void signupText()
{
    setColor(YELLOW, BLACK);
    printCentered("      ______ ______ _____ _   _ _    _ _____", 1);
    printCentered("      / _____|_  __/  ____| \\ | | |  | |  __ \\", 2);
    printCentered("     |  (__    | ||  |  __|  \\| | |  | | |__) |", 3);
    printCentered("     \\___  \\  | ||  | |_ | . ` | |  | |  ___/", 4);
    printCentered(" _____) |_| ||  |__| | |\\  | |__| | |", 5);
    printCentered("|______/|_____\\______|_| \\_|\\____/|_|", 6);
    printCentered("                                              ", 8);
    resetColor();
}

void riddleText()
{
    setColor(YELLOW, BLACK);
    printCentered("  _____  _____ _____  _____  _      ______ ", 1);
    printCentered(" |  __ \\|_   _|  __ \\|  __ \\| |    |  ____|", 2);
    printCentered(" | |__) | | | | |  | | |  | | |    | |__   ", 3);
    printCentered(" |  _  /  | | | |  | | |  | | |    |  __|  ", 4);
    printCentered(" | | \\ \\ _| |_| |__| | |__| | |____| |____ ", 5);
    printCentered(" |_|  \\_\\_____|_____/|_____/|______|______|", 6);
    printCentered("                                              ", 8);
    resetColor();
}

void adminText()
{
    setColor(YELLOW, BLACK);
    printCentered("           _____  __  __ _____ _   _ ", 1);
    printCentered("     /\\   |  __ \\|  \\/  |_   _| \\ | |", 2);
    printCentered("    /  \\  | |  | | \\  / | | | |  \\| |", 3);
    printCentered("   / /\\ \\ | |  | | |\\/| | | | | . ` |", 4);
    printCentered("  / ____ \\| |__| | |  | |_| |_| |\\  |", 5);
    printCentered(" /_/    \\_\\_____/|_|  |_|_____|_| \\_|", 6);
    printCentered("                                              ", 8);
    resetColor();
}

void selectText()
{
    setColor(YELLOW, BLACK);
    printCentered("    _____ ______ _      ______ _____ _______", 1);
    printCentered("  / ____|  ____| |    |  ____/ ____|__   __|", 2);
    printCentered("  | (___ | |__  | |    | |__ | |       | |  ", 3);
    printCentered("  \\___ \\|  __| | |    |  __|| |       | |   ", 4);
    printCentered("  ____) | |____| |____| |___| |____   | |   ", 5);
    printCentered(" |_____/|______|______|______\\_____|  |_|   ", 6);
    printCentered("                                              ", 8);
    resetColor();
}

void factText()
{
    setColor(YELLOW, BLACK);
    printCentered(" ______      _____ _______ _____ ", 1);
    printCentered("|  ____/\\   / ____|__   __/ ____|", 2);
    printCentered("| |__ /  \\ | |       | | | (___  ", 3);
    printCentered("|  __/ /\\ \\| |       | |  \\___ \\ ", 4);
    printCentered(" | | / ____ \\ |____   | |  ____) |", 5);
    printCentered(" |_|/_/    \\_\\_____|  |_| |_____/ ", 6);
    printCentered("                                              ", 8);
    resetColor();
}

void solveTheRiddleText()
{
    printCentered("   _____       _             _______ _            _____  _     _     _ _      ", 5);
    printCentered("  / ____|     | |           |__   __| |          |  __ \\(_)   | |   | | |     ", 6);
    printCentered(" | (___   ___ | |_   _____     | |  | |__   ___  | |__) |_  __| | __| | | ___ ", 7);
    printCentered(" \\___ \\ / _ \\| \\ \\ / / _ \\    | |  | '_ \\ / _ \\ |  _  /| |/ _ |/ _ | |/ _ \\", 8);
    printCentered("  ____) | (_) | |\ V /  __/    | |  | | | |  __/ | | \\ \\| | (_| | (_| | |  __/", 9);
    printCentered(" |_____/ \\___/|_| \\_/ \___|    |_|  |_| |_|\\___| |_|  \\_\\_|\\__,_|\\__,_|_|\\___|", 10);
}

void leadUsToWin()
{
    printCentered("  _                    _               _         __          ___       ", 1);
    printCentered(" | |                  | |             | |        \\ \\        / (_)      ", 2);
    printCentered(" | |     ___  __ _  __| |  _   _ ___  | |_ ___    \\ \\  /\\  / / _ _ __  ", 3);
    printCentered(" | |    / _ \\/ _` |/ _` | | | | / __| | __/ _ \\    \\ \\/  \\/ / | | '_ \\ ", 4);
    printCentered(" | |___|  __/ (_| | (_| | | |_| \\__ \\ | || (_) |    \\  /\\  /  | | | | |", 5);
    printCentered(" |______\\___|\\__,_|\\__,_|  \\__,_|___/  \\__\\___/      \\/  \\/   |_|_| |_|", 6);
}
void options(string option1,string option2,int selected,int y1,int y2)
{
    string contentSelectedFirst = ":  > " + option1 + " <  :";
    string contentSelectedSecond = ":  > " + option2 + " <  :";
    string contentFirst = ":    " + option1 + "    :";
    string contentSecond = ":    " + option2 + "    :";
    


    if (selected == 0) {
        setColor(LIGHT_PURPLE, BLACK);
        printCentered("...............", y1);
        printCentered(contentSelectedFirst, y1 + 1);
        printCentered("...............", y1 + 2);
        resetColor();
    }
    else {
        setColor(GRAY, BLACK);
        printCentered("...............", y1);
        printCentered(contentFirst, y1 + 1);
        printCentered("...............", y1 + 2);
        resetColor();
    }

    newLine(1);
    if (selected == 1) {
        setColor(LIGHT_PURPLE, BLACK);
        printCentered("...............", y2);
        printCentered(contentSelectedSecond, y2 + 1);
        printCentered("...............", y2 + 2);
        resetColor();
    }
    else {
        setColor(GRAY, BLACK);
        printCentered("...............", y2);
        printCentered(contentSecond, y2 + 1);
        printCentered("...............", y2 + 2);
        resetColor();
    }


 
}
