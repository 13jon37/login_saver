#include <iostream>
#include <cstring>
#include <fstream>
#include <filesystem>

#define LOGIN_FILE_NAME ".logins"
#define DATA_SEPERATOR  "------------------"

/* "Encryption & decryption" it really just moves the character up two ascii letters. */
static std::string_view
encrypt_string(const std::string &input_string)
{
    char *converted_input_string = (char *)input_string.c_str();
    for (size_t i = 0; i < strlen(converted_input_string); ++i)
        converted_input_string[i] = converted_input_string[i] + 2;
    
    return converted_input_string;
}

static std::string_view 
decrypt_string(const std::string &input_string)
{
    char *converted_input_string = (char *)input_string.c_str();
    for (size_t i = 0; i < strlen(converted_input_string); ++i)
        converted_input_string[i] = converted_input_string[i] - 2;
    
    return converted_input_string;
}

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
            const char *arg_two = argv[2];
            
            if (arg_one == cmd_find)
            {
                std::cout << "Running find command...\n\n";
                // cout the found shit
                
                if (!arg_two)
                {
                    std::cerr << "Find cmd needs a second argument!" << std::endl;
                    break;
                }
                
                std::string arg_two_string = arg_two;
                std::string to_find = "Website: " + arg_two_string;
                
                std::ifstream file(LOGIN_FILE_NAME);
                
                namespace fs = std::filesystem;
                fs::path f{ LOGIN_FILE_NAME };
                
                if (!fs::exists(f))
                {
                    std::cerr << "There is no database! Please enter login information to create a database!" << std::endl;
                    break;
                }
                
                std::string line;
                
                int count = 0;
                
                if (file.is_open())
                {
                    while(!file.eof())
                    {
                        // Count the number of lines
                        std::getline(file, line);
                        ++count;
                        
                        if (line == to_find)
                        {
                            std::cout << line << "\n";
                            
                            // Output the rest of the lines after found line
                            std::string line_2;
                            for (int x = 0; x < count - 1; ++x)
                            {
                                std::getline(file, line_2);
                                
                                if (line_2 == DATA_SEPERATOR) // this is the mark before the next data so break there
                                    break;
                                if (line_2 == "") // check if there is nothing on the line, if so stop iterating
                                    break;
                                
                                std::cout << line_2 << std::endl;
                                
                                // Find and decrypt password
                                for (int h = 0; h < 1; ++h)
                                {
                                    std::getline(file, line_2);
                                    
                                    std::string pass = line_2;
                                    
                                    std::cout << decrypt_string(pass) << std::endl;
                                }
                                break;
                            }
                        }
                    }
                }
                file.close();
                
                break;
            }
        }  
        
        std::ofstream file;
        namespace fs = std::filesystem;
        fs::path f{ LOGIN_FILE_NAME };
        
        if (fs::exists(f))
        {
            std::cout << "\nFile exists.\n";
            file.open(LOGIN_FILE_NAME, std::ios::in | std::ios::out | std::ios::app);
        }
        else
        {
            // Create file
            std::cout << "\nFile created.\n";
            file.open(LOGIN_FILE_NAME, std::ios::in | std::ios::out | std::ios::app);
        }
        
        // Store input arguments
        title    = argv[1];
        username = argv[2];
        password = argv[3];
        
        // If there is a 4th arugmuent store it
        if (argv[4])  // 4th arg is optional
            post_cmd_argument = argv[4];
        
        if (file.is_open())
        {
            file << DATA_SEPERATOR << std::endl;
            file << "Website: " << title << std::endl;
            file << username << std::endl;
            file << encrypt_string(password) << std::endl;
        }
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
    return 0;
}

