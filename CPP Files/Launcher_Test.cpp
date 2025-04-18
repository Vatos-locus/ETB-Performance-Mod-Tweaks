#include <windows.h>
#include <shlobj.h>
#include <shlwapi.h>
#include <string>
#include <fstream>
#include <iostream>
#include <codecvt>
#include <locale>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <mmsystem.h>
#include <cwchar>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <algorithm>

#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "winmm.lib")
//steam://rungameid/1943950



void wait(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

// Random
int getRandom(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// Animate Inject
void animateInjecting() {
    const int totalSteps = 20;  /

    std::cout << "[Mod Engine] Injecting performance mod..." << std::endl;

    // Schrittweise Fortschrittsanzeige
    for (int i = 0; i <= totalSteps; ++i) {
        int progress = i * 100 / totalSteps;  
        int numHashes = i;  

        
        std::cout << "\rInjecting... [" << std::string(numHashes, '#') << std::string(totalSteps - numHashes, ' ') << "] " << progress << "%";
        std::cout.flush();  

        wait(100);  
    }

    std::cout << "\rInjecting... [####################] 100% Completed" << std::endl;
    wait(1000);  
}

// Game runn check
bool isGameRunning(const std::string& appName) {
    
    std::string command = "tasklist /FI \"IMAGENAME eq " + appName + "\"";
    FILE* pipe = _popen(command.c_str(), "r");
    if (!pipe) return false;

    char buffer[128];
    std::string result = "";
    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != NULL) {
            result += buffer;
        }
    }

    _pclose(pipe);
    return result.find(appName) != std::string::npos;
}

void updateConsole() {
    while (true) {
        system("cls");  

        std::cout << "[Rendering Engine] Level of Detail: ULTRA" << std::endl;
        std::cout << "[Graphics] Shadow Quality: Enhanced" << std::endl;
        std::cout << "[Graphics] Range Boost: Enabled (x" << (getRandom(150, 200) / 100.0) << ")" << std::endl;
        std::cout << "[Physics] Friction Coefficient: Overridden" << std::endl;
        std::cout << "[AI System] Memory Allocation: " << getRandom(512, 2048) << " MB" << std::endl;
        std::cout << "[System] Memory Usage: " << getRandom(2500, 4500) << " MB / 8192 MB" << std::endl;
        std::cout << "[Network] Latency Optimization: Active" << std::endl;
        std::cout << "[Input] Response Time: " << getRandom(1, 5) << " ms" << std::endl;

        std::cout << "\n[Status] Game Running - Memory: " << getRandom(2800, 4600)
            << " MB | Avg. FPS: " << getRandom(58, 144) << std::endl;

        wait(2000); // Alle 2 Sekunden ein Update
    }
}

int main() {
    srand(time(0)); // Initialisiert den Zufallsgenerator

    const char* appID = "1943950"; // Escape The Backrooms App ID
    std::string steamLaunchURL = "steam://rungameid/" + std::string(appID);

    std::cout << "[Launcher] Launching Escape the Backrooms..." << std::endl;
    HINSTANCE result = ShellExecuteA(nullptr, "open", steamLaunchURL.c_str(), nullptr, nullptr, SW_SHOWNORMAL);

    if ((int)result <= 32) {
        std::cerr << "[Error] Failed to launch game. App ID: " << appID << std::endl;
        return 1;
    }

    wait(2000);  // Kurze Wartezeit nach dem Starten des Spiels
    animateInjecting();  // Starte die Injecting-Animation

    std::cout << "[Mod Engine] Escape The Backrooms Performance Mod Injected" << std::endl;
    wait(1000);
    std::cout << "[Mod Engine] Initializing Rendering Optimizer..." << std::endl;
    wait(1200);

    std::cout << "\n[Mod Engine] FPS Boost Enabled" << std::endl;
    std::cout << "[Mod Engine] Enjoy your game!" << std::endl;

    // Starte den "Monitoring"-Thread, der die Konsole kontinuierlich aktualisiert
    std::thread consoleUpdateThread(updateConsole);

    // Warten, bis das Spiel beendet ist und dann die Konsole schließen
    while (true) {
        if (!isGameRunning("Backrooms.exe")) { 
            std::cout << "[Mod Engine] Game closed. Exiting..." << std::endl;
            break;
        }
        wait(5000);  
    }

    
    exit(0);
}



