
#include <fstream>
#include <filesystem>
#include <string>
#include <ctime>
#include <vector>
#include <iostream>
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS




class Commits
{
public:
    std::string commit_id;
    std::string commit_msg;
    std::string next_id;
    Commits* next;


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
    
    void create_commit()
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
    Commits()
    {
        this->next = NULL;
    }
    Commits(std::string commit_id, std::string commit_msg)
    {
        this->commit_id = commit_id;
        this->commit_msg;

    }
    Commits(std::string commit_id)
    {
        checknextcommit_id();
        this->commit_id = commit_id;
        this->next = NULL;
    }
    void revertcommit(std::string hash)// checks if it the head of the list or the tail.
    {
        Commits newCommit;
        std::filesystem::create_directories(std::filesystem::current_path() / ".git" / "commits" / get_id() / "data");// we are making a directory 
        auto next_path = std::filesystem::current_path() / ".git" / "commits" / get_id() / "commitinfo.txt";//sets the path for the "commitinfo.txt" file
        auto copy_from = std::filesystem::current_path() / ".git" / "commits" / hash / "data";
        std::ofstream output(next_path.string());
        if (output.is_open())
        {
            output << "1." + newCommit.commit_id + "\n" +
                "2." + newCommit.commit_msg + "\n" +
                "3." + get_time() + "\n";
            output.close();
        }
        else
        {
            std::cerr << "cant be open";
        }

        const auto copy_options = std::filesystem::copy_options::recursive;
        std::filesystem::copy(copy_from, std::filesystem::current_path() / ".git" / "commits" / get_id()/ "data", copy_options);


    }
    void read_git_info()
    {
        auto readfrom = std::filesystem::current_path() / ".git" / "commits" / get_id() / "commitinfo.txt";
        std::string info;
        std::ifstream output(readfrom.string());
        if (output.is_open())
        {
            while (getline(output, info))
            {
                if (info[0] == '1')
                {
                    this->set_id(info.substr(2));//gets the substring starting from the 2nd index to get the id

                }
                if (info[0] == '2')
                {
                    this->set_msg(info.substr(2));
                }

            }

        }

    }
    std::string get_id()
    {
        return this->commit_id;
    }
    void set_id(std::string commit_id)
    {
        this->commit_id = commit_id;
    }
    void set_msg(std::string commit_msg)
    {
        this->commit_msg = commit_msg;
    }
    std::string getcom_msg()
    {
        return this->commit_msg;
    }
    void set_next(Commits* next)
    {
        this->next = next;
    }
    Commits* get_next()
    {
        return next;
    }
    void set_next_id(std::string next_id)
    {
        this->next_id = next_id;
    }
    void writenextcommit_id(std::string nextcommit_id)
    {
        set_next_id(nextcommit_id);
        auto path = std::filesystem::current_path() / ".git" / "commits" / get_id() / "nextcommitinfo.txt";
        std::ofstream output(path.string());
        if (output.is_open())
        {
            output << nextcommit_id;
        }
    }

    std::string checknextcommit_id()
    {
        std::string info;
        auto path = std::filesystem::current_path() / ".git" / "commits" / get_id() / "nextcommitsinfo.txt";
        if (std::filesystem::exists(path))
        {
            std::ifstream output(path.string());
            if (output.is_open())
            {
                while (getline(output, info))
                {
                    this->next_id = info;
                    break;
                }

            }
            output.close();
            return info;
        }
        return "";



    }

    std::string getnextcommmit_id()
    {
        return this->next_id;
    }
};
class Node_Llist :public Commits
{
private:
    Commits* head;// makes a pointer named head
    Commits* tails;// makes a pointer named tails

    bool checkif_headexists()
    {
        auto path = std::filesystem::current_path() / ".git" / "commits" / "0x0000";
        return std::filesystem::exists(path);
    }

public:
    Node_Llist()
    {
        this->head = NULL;
        this->tails = NULL;
        if (checkif_headexists())
        {
            set_head(new Commits("0x0000"));
        }
    }

    void set_head(Commits* head)
    {
        this->head = head;
    }

    Commits* get_tail(Commits* tails)
    {
        return this->tails;
    }
    void set_tails(Commits* tails)
    {
        this->tails = tails;
    }
    Commits* gethead()
    {
        return this->head;

    }

    void add_on_tail(std::string msg)
    {
        if (!checkif_headexists())
        {
            Commits* newhead = new Commits("0x0000", msg);
            set_head(newhead);
        }
        else
        {
            std::string commit_id = gethash();
            Commits* current = gethead();
            while (current != NULL)
            {
                std::string nextid = checknextcommit_id();
            }
            if (next_id.length() < 10)
            {
                Commits* newnode = new Commits(commit_id, msg);//if the length is less than 10 next makes a new commit with commit_id and the msg
                current->writenextcommit_id(commit_id);
                current = NULL;// means its at the end of the list
            }
            else
            {
                Commits* newnode = new Commits();
                newnode->set_id(commit_id);
                current = newnode;


            }



        }

    }
    void revertcommit(std::string commithash)
    {
        Commits* node_revert;
        Commits* currentnode = gethead();
        node_revert = currentnode;
        bool error = true;
        if (!checkif_headexists())
        {
            std::cout << " this is the first iteration nothing to revert to" << std::endl;
        }
        else
        {
           
            std::string commitid = get_id();
            
            while (currentnode != NULL)
            {
                std::string nextCommitId = currentnode->checknextcommit_id();
                if (commithash == currentnode->get_id())//checks if the commit matches the current commit
                {
                    node_revert = currentnode;
                    error = false;

                }
                if (next_id.length() < 10)//checks if it's the end of the list
                {
                    if (!error)
                    {
                        node_revert->read_git_info();//reads info from the commit that will be reverted
                        Commits* newnode = new Commits();
                        newnode->set_id(commit_id);// sets the new node id to the  commit id generated
                        newnode->set_msg(node_revert->getcom_msg());//copies the message from the commit to be reverted
                        newnode->revertcommit(node_revert->get_id());//reverts the commit node, restoring it to the previous state
                        currentnode->writenextcommit_id(commit_id);//updates the next id to the new commit id

                    }
                    currentnode = NULL;//end of the linkedlist this handles where the next commit id means the end of the linkedlist
                }
                else
                {
                    Commits* newnode = new Commits();
                    newnode->set_id(commit_id);
                    currentnode = newnode;
                }
                if (error == true)
                {
                    std::cout << "the hash doesnt match any commits";
                }

            }

        }


    }
    void printcommitlist()
    {
        Commits* currnode = gethead();
        while (currnode != NULL)
        {
            std::string nextcom_id = currnode->checknextcommit_id();
            std::filesystem::path commitpath(std::filesystem::current_path() / ".git" / "commits" / currnode->get_id() / "commitinfo.txt");
            std::string info;
            std::ifstream output(commitpath.string());
            while (getline(output, info))
            {
                if (info[0] == '1')
                {
                    std::cout << "commit id     " << info.substr(2) << std::endl;
                }
                if (info[0] == '2')
                {
                    std::cout << "commit msg    " << info.substr(2) << std::endl;

                }
                if (info[0] == '3')
                {
                    std::cout << "date          " << info.substr(2) << std::endl;

                }


            }

            output.close();
            std::cout << "...........\n";
        }

        if (next_id.length() < 10)
        {
            currnode = NULL;
        }
        else
        {
            Commits* newnode = new Commits();
            newnode->set_id(next_id);
            currnode = newnode;
        }
    }

};