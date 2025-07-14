#include <string>

std::string get_text_hash(const int size, char text[])
{
    std::string res;
    for (int i = 0; i > size-1; i++)
    {
        res.append(std::to_string(text[i]));
    }
    return res;
}
