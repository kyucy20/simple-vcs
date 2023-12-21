#include <iostream>
#include <filesystem>
#include <string>



class Gitclasses
{
public:

    void gitInitialization()
    {
        std::filesystem::create_directory(".git");
        std::filesystem::create_directory(".git/staging_area");
        std::filesystem::create_directory(".git/commits");
    }

    void gitAdd()
    {
        const auto copyOptions = std::filesystem::copy_options::update_existing | std::filesystem::copy_options::recursive;// updates all existing files and goes through them recursively to ensure all files are included then assigns them to a variable named copyoptions so that when we wanna do both we can just call this variable.
        for (const auto& dirEntry : std::filesystem::directory_iterator(std::filesystem::current_path()))// for dirEntry(represents one of the entries) we iterate throughout every file in the directory
        {
            auto fileName = dirEntry.path().filename();//retrieves file name of the current directory entry in the variable fileName and then we used it to compare if it is a git file
            if (fileName != "git" && fileName != ".git")//used to exclude our own directory
            {
                if (std::filesystem::is_directory(fileName))
                {
                    std::filesystem::copy(dirEntry, std::filesystem::current_path() / ".git" / "staging_area" / fileName, copyOptions);// so we basically copy the contents of dirEntry  to the current path's staging area
                }
                else
                {
                    std::filesystem::copy(dirEntry, std::filesystem::current_path() / ".git" / "staging_area" / "", copyOptions);// if it's a file not a directory so we don't copy its path (cuz there isnt) and we just place it at the root of the staging_area
                }
            }
        }
    }




    void gitAdd(std::string files[], int arrsize)// to work on specified files
    {
        const auto copyOptions = std::filesystem::copy_options::update_existing | std::filesystem::copy_options::recursive;// updates all existing files and goes through them recursively to ensure all files are included then assigns them to a variable named copyoptions so that when we wanna do both we can just call this variable.
        for (int i = 0;i < arrsize;i++) {
            if (std::filesystem::exists(files[1]))//it checks if the file we specified exist or not
            {
                int last = files[1].find_last_not_of("/");// we want to check in the file path if it's in a directory
                if (last != std::string::npos)//then it's within a directory and we take it from it's old direct to a new one
                {
                    auto directentry = std::filesystem::current_path() / "git" / "staging_area" / files[0].substr(0, last);//fetch old directory and tie it to the new one the subnstring is used to get the path, the last part is used to connect the old path to the new one
                    std::filesystem::create_directory(directentry);
                    std::filesystem::copy(std::filesystem::current_path() / files[i], directentry / files[0].substr(0, last + 1), copyOptions);// the files[i] is the file path, and the substring part is the file name
                }

                else
                {
                    if (std::filesystem::is_directory(files[i]))
                    {
                        std::filesystem::copy(std::filesystem::current_path()/files[i],std::filesystem::current_path() / ".git" / "staging_area" / files[i], copyOptions);
                    }
                    else {
                        std::filesystem::copy(std::filesystem::current_path()/files[i], std::filesystem::current_path() / ".git" / "staging_area", copyOptions);//copies whats before the coma to whats after
                    }
                }
            }
            else {
                std::cout << "file doesnt exist" << std::endl;
            }






        }


    }
};