#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>
#include <random>
#include <sstream>
#include <iomanip>

std::string base64_decode(const std::string &in)
{
    std::string out;
    std::vector<int> T(256, -1);
    for (int i = 0; i < 64; i++)
        T["ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[i]] = i;
    int val = 0, valb = -8;
    for (unsigned char c : in)
    {
        if (T[c] == -1)
            break;
        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0)
        {
            out.push_back(char((val >> valb) & 0xFF));
            valb -= 8;
        }
    }
    return out;
}

std::string generate_guid()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 15);

    std::stringstream ss;
    for (int i = 0; i < 32; ++i)
    {
        if (i == 8 || i == 12 || i == 16 || i == 20)
        {
            ss << "-";
        }
        ss << std::hex << dist(gen);
    }

    return ss.str();
}

std::string get_webui()
{
    std::string encoded = "STRING_TO_REPLACE";

    return encoded;
};

int main()
{
    system("chcp 65001 > nul");
    std::cout << R"(   __  _________________  _      __    __   __  ______)" << std::endl;
    std::cout << R"(  /  |/  / __/ __/_  __/ | | /| / /__ / /  / / / /  _/)" << std::endl;
    std::cout << R"( / /|_/ /\ \_\ \  / /    | |/ |/ / -_) _ \/ /_/ // /  )" << std::endl;
    std::cout << R"(/_/  /_/___/___/ /_/     |__/|__/\__/_.__/\____/___/  )" << std::endl;
    std::cout << std::endl;
    std::cout << "[INFO] 正在启动WebUI, 请稍等..." << std::endl;
    std::cout << "[INFO] Starting WebUI, please wait..." << std::endl;

    std::string encoded = get_webui();
    std::string decoded = base64_decode(encoded);

    char tempPath[MAX_PATH];
    if (!GetTempPath(MAX_PATH, tempPath))
    {
        std::cerr << "\033[91m" << "[ERROR] Error getting path!" << "\033[0m" << std::endl;
        system("pause");
        return 1;
    }

    std::string guid = generate_guid();
    std::string tempFilePath = std::string(tempPath) + guid + ".tmp";
    std::ofstream outfile(tempFilePath, std::ios::binary);
    outfile.write(decoded.c_str(), decoded.size());

    std::string command = ".\\workenv\\python.exe " + tempFilePath;
    std::cout << "[INFO] 若启动失败, 请尝试删除软件根目录下data文件夹或以管理员身份运行" << std::endl;
    std::cout << "[INFO] If launch failed, try to delete the data folder under the root directory or run as administrator" << std::endl;
    std::cout << "\033[91m" << "[NOTE] WebUI运行过程中请勿关闭此窗口!" << "\033[0m" << std::endl;
    std::cout << "\033[91m" << "[NOTE] Do not close this window while WebUI is running!" << "\033[0m" << std::endl;
    system(command.c_str());

    remove(tempFilePath.c_str());
    system("pause");
    return 0;
}