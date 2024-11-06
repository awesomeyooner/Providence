#ifndef SERVERMANAGER_HPP
#define SERVERMANAGER_HPP

#define CROW_MAIN
#define CROW_STATIC_DIRECTORY "public/"
#include <crow.h>
#include <crow/middlewares/cors.h>
#include <fstream>
#include <string>
#include <iostream>
#include "../util/Utility.hpp"

class ServerManager{

    public:
        ServerManager();

        void initialize();

    private:


};

#endif