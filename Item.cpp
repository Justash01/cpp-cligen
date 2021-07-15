#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <direct.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fstream>
#include "packages/nlohmann.json.3.9.1/build/native/include/nlohmann/json.hpp" // required lib for JSON
using json = nlohmann::ordered_json; // used to output JSON in order

int main() {
    // Get values here
    std::string identifier, displayName, cooldownDur;
    std::cout << "Identifier: ";
    std::getline(std::cin, identifier);

    std::cout << "Display Name: ";
    std::getline(std::cin, displayName);

    std::cout << "Cooldown Duration: ";
    std::getline(std::cin, cooldownDur);

    // Split name and namespace from the identifier
    std::string str = identifier;
    std::string e = ":";
    std::int64_t pos = str.find(":");
    std::string idNamespace = str.substr(0, pos);
    std::string idName = str.substr(pos + 1);

    // create JSON
    json itemMain = {
        { "format_version", "1.16.100" },
        { "minecraft:item", {
            { "description", {
                { "identifier", identifier },
                { "category", "Items" }
            }},
            { "components", {
                { "minecraft:icon", {
                    { "texture", idName + ".texture" }
                }},
                { "minecraft:display_name", {
                    { "value", idNamespace + "." + idName }
                }},
                { "minecraft:max_stack_size", 1 },
                { "minecraft:use_duration", 999999999 },
                { "minecraft:stacked_by_data", true },
                { "minecraft:hand_equipped", true },
                { "minecraft:creative_category", {
                    { "parent", "itemGroup.name.tools" }
                }},
                { "minecraft:food", {
                    { "can_always_eat", true }
                }},
                { "minecraft:cooldown", {
                    { "category", idNamespace },
                    { "duration", std::stof(cooldownDur) }
                }},
                { "minecraft:render_offsets", {
                    { "main_hand", {
                        { "first_person", {
                            { "scale", { 0, 0, 0 }}
                        }},
                        { "third_person", {
                            { "scale", { 0, 0, 0 }}
                        }}
                    }}
                }}
            }}
        }}
    };

    // create dir
    const std::string outputPath = "output/" + idName;
    if (_mkdir(outputPath.c_str()) == -1) 
    {
        // throw error if file already exists
        std::cerr << "Error :" << strerror(errno) << std::endl;
    }
    else
    {
        std::ofstream itemFile("output/" + idName + "/" + idName + ".json");
        itemFile << itemMain.dump(4) << std::endl;

        std::ofstream itemLangFile("output/" + idName + "/en_US.lang");
        itemLangFile << idNamespace + "." + idName + "=" + displayName << std::endl;
    }
};