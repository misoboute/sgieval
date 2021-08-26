#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "sgievallib/AttackComponent.h"
#include "sgievallib/Entity.h"
#include "sgievallib/HealthComponent.h"
#include "sgievallib/MovementComponent.h"

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

    std::vector<Entity::PtrT> entities;

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

        Entity::RectT boundingBox(x, y, width, height);
        auto entity = std::make_shared<Entity>(boundingBox);

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
                entity->AddComponent(std::make_shared<HealthComponent>());
                break;
            case 'A':
                entity->AddComponent(std::make_shared<AttackComponent>());
                break;
            case 'M':
                entity->AddComponent(std::make_shared<MovementComponent>());
                break;
            default:
                std::cerr << "Unknown Component type: " << type << "\n";
                break;
            }
        }

        entities.push_back(entity);
    }
    file.close();

    const auto start = std::chrono::high_resolution_clock::now();

    auto intersectionCount = 0;
    const auto entitiesSize = entities.size();
    for (auto i = 0; i < entitiesSize; ++i)
    {
        for (auto j = i + 1; j < entitiesSize; ++j)
        {
            const auto &b1 = entities[i]->GetBoundingBox();
            const auto &b2 = entities[j]->GetBoundingBox();
            if (b1.IntersectsWith(b2))
            {
                // std::cout << "Ent #" << i << " / Ent #" << j << ": (" << b1.GetX() << ", " << b1.GetY() << ", "
                //           << b1.GetWidth() << ", " << b1.GetHeight() << ") / (" << b2.GetX() << ", " << b2.GetY()
                //           << ", " << b2.GetWidth() << ", " << b2.GetHeight() << ")" << std::endl;
                ++intersectionCount;
            }
        }
    }
    std::cout << "Number of intersections: " << intersectionCount << std::endl;

    const auto end = std::chrono::high_resolution_clock::now();
    const auto runMS = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Algorithm executed in " << runMS.count() << "ms.\n";
    return 0;
}