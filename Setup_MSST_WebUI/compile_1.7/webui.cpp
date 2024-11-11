#include <iostream>
#include <windows.h>

void disable_quick_edit_mode() {
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD prev_mode;
    GetConsoleMode(hInput, &prev_mode);

    prev_mode &= ~ENABLE_QUICK_EDIT_MODE;
    SetConsoleMode(hInput, prev_mode);
}

int main() {
    disable_quick_edit_mode();

    system("chcp 65001 > nul");
    std::cout << R"(    __  _________________  _      __    __   __  ______)" << std::endl;
    std::cout << R"(   /  |/  / __/ __/_  __/ | | /| / /__ / /  / / / /  _/)" << std::endl;
    std::cout << R"(  / /|_/ /\ \_\ \  / /    | |/ |/ / -_) _ \/ /_/ // /  )" << std::endl;
    std::cout << R"( /_/  /_/___/___/ /_/     |__/|__/\__/_.__/\____/___/  )" << std::endl;
    std::cout << std::endl;
    std::cout << "Launching WebUI..." << std::endl;

    std::string command = ".\\workenv\\python.exe webUI.py";
    system(command.c_str());
    system("pause");

    return 0;
}
