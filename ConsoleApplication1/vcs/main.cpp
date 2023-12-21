
#include <iostream>
#include <string>
#include "gitclasses.cpp"

int main(int argc, char argv[]) {
    Gitclasses gitclassobj;
    if (argc >= 2) {

        std::string arguement;
        arguement = argv[1];
        if (arguement == "initialization")
        {
            gitclassobj.gitInitialization();
            std::cout << "git has been initialized";

        }
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
                std::string** files = new std::string * [argc - 2];
                for (int i = 0; i < argc - 2; i++) {
                    files[i] = new std::string(argv[i]);
                }
  
                gitclassobj.gitAdd(files, argc-2);


            }

        }


    }

};