#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <ctime>
#include <vector>

std::string  gethash()
{
    std::string s;
    srand(time(NULL));
    char array[] = "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0;i < 10;i++) {
        s += array[rand() % (sizeof(array) - 1)];// this ensures that the value is inside the array and isnt out of bounds 
    }
    return s;


}
std::string get_time()
{
    time_t t = std::time(0); // get time now
    tm* now = std::localtime(&t);
    std::string dateTime = std::to_string(now->tm_year + 1900) + "/" +
        std::to_string(now->tm_mon + 1) + "/" +
        std::to_string(now->tm_mday) + " " +
        std::to_string(now->tm_hour) + ":" +
        std::to_string(now->tm_min) + "\n";

    return dateTime;
}


class Commits
{
public:
    std::string commit_id;
    std::string commit_msg;
    std::string next_id;
    Commits* next;


    ; void create_commit()
    {
        Commits newCommit;
        newCommit.commit_id;
        std::filesystem::create_directory(std::filesystem::current_path() / ".git" / "commits" / newCommit.commit_id);
        auto path = std::filesystem::current_path() / ".git" / "commits" / newCommit.commit_id / "commits_info.txt";
        if (!std::filesystem::exists(path.parent_path())) {
            std::filesystem::create_directories(path.parent_path());//checks if directory exists and if it doesnt we create a new one
        }

        std::ofstream outputfile(path.string());//path.string converts the path to a string,outputfile is an object that represents the file stream.
        if (outputfile.is_open())
        {
            std::string t = get_time();
            outputfile << "1." + newCommit.commit_id + "\n" +
                "2." + newCommit.commit_msg + "\n" +
                "3." + get_time() + "\n";
            outputfile.close();
        }
        else
        {
            std::cerr << "Error opening file: " << path << std::endl;
        }

        auto staging_area = std::filesystem::path(std::filesystem::current_path() / ".git" / "staging_area");
        const auto copyOptions = std::filesystem::copy_options::update_existing | std::filesystem::copy_options::recursive;
        std::filesystem::path destination = (std::filesystem::current_path() / ".git" / "commits" / newCommit.commit_id / "data");
        if (std::filesystem::exists(staging_area) && std::filesystem::is_directory(staging_area))
        {
            std::filesystem::copy(staging_area, destination, copyOptions);
        }
        else {
            std::cout << "isnt a directory";
        }

    }
public:
     auto commit()
    {
         this->next = NULL;
    }
};