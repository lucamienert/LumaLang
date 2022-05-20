#include <io.h>

std::string get_file_content(std::string filename)
{
    fstream inStream;
    in.open(filename, ios::in);

    if(!in.good())
        exit(1);

    std::string source;
    std::string temp;

    while(!in.eof())
    {
        getline(in, temp);
        source += temp;
    }

    source += "\0";

    return source;
}

std::string shell_command(std::string command)
{
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);

    if (!pipe)
        throw std::runtime_error("popen() failed!");
        
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
        result += buffer.data();

    return result;
}