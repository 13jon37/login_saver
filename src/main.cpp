#include <iostream>
#include <cstring>
#include <fstream>
#include <filesystem>

int main(int argc, char *argv[])
{
    std::string title    = " "; // Website title for example
    std::string username = " ";
    std::string password = " ";
    
    /* This cmd argument is an option for finding the login title */
    std::string cmd_find = "find";
    
    /* This cmd argument is optional for the show
 password when inputing new data. */
    std::string post_cmd_argument = " ";
    
    for (int i = 0; i < argc; ++i)
    {
        if (argc < 2)
        {
            std::cerr << "Please enter at least one argument!" << std::endl;
            break;
        }
        else
        {
            const char *arg_one = argv[1];
            
            if (arg_one == cmd_find)
            {
                // char *second_arg = argv[2];
                std::cout << "find\n";
                // cout the found shit
                
                break;
            }
            
            std::ofstream file;
            namespace fs = std::filesystem;
            fs::path f{ ".logins" };
            
            if (fs::exists(f))
            {
                std::cout << "\nFile exists.\n";
                file.open(".logins", std::ios::in | std::ios::app);
            }
            else
            {
                // Create file
                std::cout << "\nFile created.\n";
                file.open(".logins", std::ios::in | std::ios::out | std::ios::app);
            }
            
            // Store input arguments
            title    = argv[1];
            username = argv[2];
            password = argv[3];
            
            // If there is a 4th arugmuent store it
            if (argv[4])  asdfasdf// 4th arg is optional
                post_cmd_argument = argv[4];
            
            file << "-----------------------" << std::endl;
            file << "Website: " << title << std::endl;
            file << "Username/Email: " << username << std::endl;
            file << "Password: " << password << std::endl;
            
            file.close();
            
            if (username != "" && password != "")
            {
                /* Count password letters and display amount of said letters in stars */
                
                // Declare string that we're gonna only enter * in
                std::string password_in_stars = "";
                
                // Append stars to password_in_stars length times
                for (size_t j = 0; j < strlen(password.c_str()); ++j) 
                    password_in_stars.append("*");
                
                if (post_cmd_argument == "-show")
                {
                    std::cout << "\n" << title << ": "  << "\n";
                    std::cout << "Username/Email: " << username << " | Password: " << password << std::endl;
                }
                else
                {
                    std::cout << "\n" << title << ": "  << "\n";
                    std::cout << "Username/Email: " << username << " | Password: " << password_in_stars << std::endl;
                }
                
                break;
            }
        }
    }
    return 0;
}