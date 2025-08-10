#include <iostream>
#include <string>
#include <map>
#include <vector>

// Configuration Struct to hold automation script settings
struct ScriptConfig {
    std::string scriptName;
    std::string scriptType; // e.g., Python, Bash, etc.
    int scriptInterval; // in seconds
    bool scriptEnabled;
};

// Automation Script Controller Class
class ScriptController {
private:
    std::map<std::string, ScriptConfig> scriptConfigs;
    std::vector<std::thread> scriptThreads;

public:
    ScriptController() {}

    // Add a new script configuration
    void addScriptConfig(const ScriptConfig& config) {
        scriptConfigs[config.scriptName] = config;
    }

    // Start all enabled scripts
    void startScripts() {
        for (auto& config : scriptConfigs) {
            if (config.second.scriptEnabled) {
                scriptThreads.emplace_back([this, config]() {
                    // Run the script asynchronously
                    runScript(config.second);
                });
            }
        }
    }

    // Run a single script
    void runScript(const ScriptConfig& config) {
        // TO DO: Implement script running logic based on script type
        std::cout << "Running script: " << config.scriptName << std::endl;
    }

    // Stop all scripts
    void stopScripts() {
        for (auto& thread : scriptThreads) {
            thread.join();
        }
    }
};

int main() {
    ScriptController controller;

    // Example script configurations
    ScriptConfig script1 = {"script1", "Python", 60, true};
    ScriptConfig script2 = {"script2", "Bash", 300, false};
    ScriptConfig script3 = {"script3", "Python", 10, true};

    // Add script configurations
    controller.addScriptConfig(script1);
    controller.addScriptConfig(script2);
    controller.addScriptConfig(script3);

    // Start scripts
    controller.startScripts();

    // Wait for user input to stop scripts
    std::cout << "Press Enter to stop scripts..." << std::endl;
    std::cin.get();

    // Stop scripts
    controller.stopScripts();

    return 0;
}