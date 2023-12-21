
#include <iostream>
#include <string>
#include "gitclasses.cpp"
#include <vector>
int main(int argc, char *argv[]) {
    Gitclasses gitclassobj;
    std::cout << "this is a simple vcs system" << std::endl;
    std::cout << "choose what you want to do in this format" << std::endl;
    std::cout << "(what you want to do), your arguement" << std::endl;
   

    if (argc >= 2) {

        std::string arguement;
        arguement = argv[1];
        if (arguement == "initialization")
        {
            gitclassobj.gitInitialization();
            std::cout << "git has been initialized";

        }
        else if (arguement == "add") {
            if (argc >= 3)
            {
                if (argc == 3)
                {
                    std::string checker;
                    checker = argv[2];

                    if (checker == ".")
                    {
                        gitclassobj.gitAdd();

                    }

                    else {
                        std::string v;//a string v
                        v = argv[2];//v is equal to the 2nd arguemtn in argv
                        std::string files[1] = { v };//array of string called files sized 1 and the only "variable" inside this array is the v
                        gitclassobj.gitAdd(files, 1);// calling of the gitadd
                    }


                }
                else
                {
                    std::vector<std::string> files(argc - 2);
                    for (int i = 2;i < argc;i++)
                    {
                        std::string v;
                        v = argv[i];
                        files[i] = v;
                    }
                    gitclassobj.gitAdd(files, argc - 2);


                }

            }

        }

        else if (arguement == "commit")
        {
            if (argc == 4)//git,commit,3rd argument should indicate where a mssg follows or not.
            {
                std::string s2, s3;
                s2 = argv[2];
                s3 = argv[3];
                if (s2 == "m")
                {
                    gitclassobj.gitcommit(s3);
                    std::cout << "files commited" << std::endl;;
                }
                else
                {
                    std::cout << "missing arguements" << std::endl;;
                }


            }
        }
        else if (arguement == "revert")
        {
            if (argc == 3) {
                std::string s2;
                std::string argv2= argv[2];
                s2 = argv2;
                if (s2 == "head")
                {
                    gitclassobj.gitrevert(s2);
                    std::cout << "now we are at head" << std::endl;
                }
                else
                {
                    gitclassobj.gitrevert(s2);
                    std::cout << "reverted " << std::endl;

                }
            }
            else
            {
                std::cout << "invalid arguements" << std::endl;
            }
        }


    }
    else {
        std::cout << "invalid arguments" << std::endl;
    }

}