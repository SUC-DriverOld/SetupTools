//         ____    ____    ______      __      __          __       __  __  ______     
// /'\_/`\/\  _`\ /\  _`\ /\__  _\    /\ \  __/\ \        /\ \     /\ \/\ \/\__  _\    
///\      \ \,\L\_\ \,\L\_\/_/\ \/    \ \ \/\ \ \ \     __\ \ \____\ \ \ \ \/_/\ \/    
//\ \ \__\ \/_\__ \\/_\__ \  \ \ \     \ \ \ \ \ \ \  /'__`\ \ '__`\\ \ \ \ \ \ \ \    
// \ \ \_/\ \/\ \L\ \/\ \L\ \ \ \ \     \ \ \_/ \_\ \/\  __/\ \ \L\ \\ \ \_\ \ \_\ \__ 
//  \ \_\\ \_\ `\____\ `\____\ \ \_\     \ `\___x___/\ \____\\ \_,__/ \ \_____\/\_____\
//   \/_/ \/_/\/_____/\/_____/  \/_/      '\/__//__/  \/____/ \/___/   \/_____/\/_____/


#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <sstream>

// 禁用快速编辑模式
void disable_quick_edit_mode() {
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD prev_mode;
    GetConsoleMode(hInput, &prev_mode);

    prev_mode &= ~ENABLE_QUICK_EDIT_MODE;
    SetConsoleMode(hInput, prev_mode);
}

// 解析命令行参数
void parse_arguments(int argc, char* argv[], std::vector<std::string>& params) {
    for (int i = 1; i < argc; ++i) {
        params.push_back(argv[i]);
    }
}

// 构建 Python 命令
std::string build_python_command(const std::vector<std::string>& params) {
    std::string command = ".\\workenv\\python.exe webUI.py";

    for (const auto& param : params) {
        command += " " + param;
    }

    return command;
}

int main(int argc, char* argv[]) {
    disable_quick_edit_mode();

    system("chcp 65001 > nul");
    std::cout << R"(         ____    ____    ______      __      __          __       __  __  ______  )" << std::endl;
    std::cout << R"( /'\_/`\/\  _`\ /\  _`\ /\__  _\    /\ \  __/\ \        /\ \     /\ \/\ \/\__  _\  )" << std::endl;
    std::cout << R"(/\      \ \,\L\_\ \,\L\_\/_/\ \/    \ \ \/\ \ \ \     __\ \ \____\ \ \ \ \/_/\ \/  )" << std::endl;
    std::cout << R"(\ \ \__\ \/_\__ \\/_\__ \  \ \ \     \ \ \ \ \ \ \  /'__`\ \ '__`\\ \ \ \ \ \ \ \  )" << std::endl;
    std::cout << R"( \ \ \_/\ \/\ \L\ \/\ \L\ \ \ \ \     \ \ \_/ \_\ \/\  __/\ \ \L\ \\ \ \_\ \ \_\ \__)" << std::endl;
    std::cout << R"(  \ \_\\ \_\ `\____\ `\____\ \ \_\     \ `\___x___/\ \____\\ \_,__/ \ \_____\/\_____\)" << std::endl;
    std::cout << R"(   \/_/ \/_/\/_____/\/_____/  \/_/      '\/__//__/  \/____/ \/___/   \/_____/\/_____/)" << std::endl;

    std::cout << std::endl;
    std::cout << "[Launcher] Launching WebUI..." << std::endl;

    // 解析命令行参数
    std::vector<std::string> params;
    parse_arguments(argc, argv, params);

    // 根据解析的参数构建 Python 命令
    std::string command = build_python_command(params);

    // 执行命令
    system(command.c_str());
    system("pause");

    return 0;
}
