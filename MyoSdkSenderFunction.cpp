void print()
{
    // Clear the current line
    std::cout << '\r';
    
    if (onArm) {
        
        std::string poseString = currentPose.toString();
        
        std::cout << '[' << (isUnlocked ? "unlocked" : "locked  ") << "] ";
        if(poseString == "fist")
        {
            
            std::string action = "STOP_MOVE";
            std::cout << action << "; " << lastCommand;
            lastCommand = action;
            
            if (sendto(s, action.c_str(), strlen(action.c_str()) , 0 , (struct sockaddr *) &si_other, slen)==-1)
            {
                die("sendto()");
            }
        }
        else if(poseString == "fingersSpread")
        {
            std::string action = "MOVE_FORWARD";
            std::cout << action << "; " << lastCommand;
            lastCommand = action;
            
            if (sendto(s, action.c_str(), strlen(action.c_str()) , 0 , (struct sockaddr *) &si_other, slen)==-1)
            {
                die("sendto()");
            }
        }
        else if(poseString == "waveIn")
        {
            std::string action = "LEFT_MOVE";
            std::cout << action << "; " << lastCommand;
            lastCommand = "STOP_MOVE";
            
            if (sendto(s, action.c_str(), strlen(action.c_str()) , 0 , (struct sockaddr *) &si_other, slen)==-1)
            {
                die("sendto()");
            }
        }
        else if(poseString == "waveOut")
        {
            std::string action = "RIGHT_MOVE";
            std::cout << action << "; " << lastCommand;
            lastCommand = "STOP_MOVE";
            
            if (sendto(s, action.c_str(), strlen(action.c_str()) , 0 , (struct sockaddr *) &si_other, slen)==-1)
            {
                die("sendto()");
            }
        }
        
    } else {
        // Print out a placeholder for the arm and pose when Myo doesn't currently know which arm it's on.
        std::cout << '[' << std::string(8, ' ') << ']' << "[?]" << '[' << std::string(14, ' ') << ']';
    }
    
    std::cout << std::flush;
}