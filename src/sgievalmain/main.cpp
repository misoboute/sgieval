#include <chrono>
#include <fstream>
#include <iostream>
#include <string>

#include "sgievallib/Entity.h"

using namespace sgieval;

int main(int argc, const char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Specify a file to run this program.\n";
        return 1;
    }

    std::cout << "Running program against file: " << argv[1] << "\n";

    std::ifstream file(argv[1], std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file.\n";
        return 2;
    }

    unsigned int numberOfEntities = 0;
    if (!(file >> numberOfEntities))
    {
        std::cerr << "Failed to get number of Entities from file.\n";
        return 3;
    }

    // TODO: Add a collection of Entities.

    for (unsigned int i = 0; i < numberOfEntities; ++i)
    {
        float x = 0;
        float y = 0;
        float width = 0;
        float height = 0;

        if (!(file >> x >> y >> width >> height))
        {
            std::cerr << "Error getting bounds on line " << i + 1 << ".\n";
            return 4;
        }

        // Not every Entity has Components.
        std::string componentTypes;
        const auto currentPos = file.tellg();
        file >> componentTypes;
        if (!componentTypes.empty() && !std::isalpha(componentTypes.back()))
        {
            file.seekg(currentPos);
            componentTypes.clear();
        }

        for (const char type : componentTypes)
        {
            switch (type)
            {
            case 'H':
                // TODO: This Entity has a HealthComponent.
                break;
            case 'A':
                // TODO: This Entity has an AttackComponent.
                break;
            case 'M':
                // TODO: This Entity has a MovementComponent.
                break;
            default:
                std::cerr << "Unknown Component type: " << type << "\n";
                break;
            }
        }

        // TODO: Use the above information to create an Entity with
        // a Rectangle2D bounding box and given Components.
    }
    file.close();

    const auto start = std::chrono::high_resolution_clock::now();

    // TODO: Algorithm to detect number of Entity intersections.

    const auto end = std::chrono::high_resolution_clock::now();
    const auto runMS = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Algorithm executed in " << runMS.count() << "ms.\n";
    return 0;
}