#include <chrono>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "sgievallib/AttackComponent.h"
#include "sgievallib/Entity.h"
#include "sgievallib/EntityGrid.h"
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

    float minX = std::numeric_limits<float>::infinity();
    float maxX = std::numeric_limits<float>::lowest();
    float minY = std::numeric_limits<float>::infinity();
    float maxY = std::numeric_limits<float>::lowest();

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

        if (x + width / 2 > maxX)
        {
            maxX = x + width / 2;
        }
        if (x - width / 2 < minX)
        {
            minX = x - width / 2;
        }
        if (y + height / 2 > maxY)
        {
            maxY = y + height / 2;
        }
        if (y - height / 2 < minY)
        {
            minY = y - height / 2;
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

    // Primitive (unoptimized) algorithm with ~O(n^2) time complexity:
    // const auto entitiesSize = entities.size();
    // auto intersectionCount = 0;
    // for (auto i = 0; i < entitiesSize; ++i)
    // {
    //     for (auto j = i + 1; j < entitiesSize; ++j)
    //     {
    //         const auto &b1 = entities[i]->GetBoundingBox();
    //         const auto &b2 = entities[j]->GetBoundingBox();
    //         if (entities[i]->IntersectsWith(*entities[j]))
    //         {
    //             ++intersectionCount;
    //         }
    //     }
    // }
    // std::cout << "Number of intersections (first algorithm): " << intersectionCount << std::endl;
    // Number of intersections: 21589
    // Algorithm executed in 1960ms.

    // Optimized algorithm:

    auto yMargin = (maxY - minY) / numberOfEntities;
    auto xMargin = (maxX - minX) / numberOfEntities;

    const auto start = std::chrono::high_resolution_clock::now();

    auto grid = EntityGrid(entities.size(), minX - xMargin, maxX + xMargin, minY - yMargin, maxY + yMargin);
    grid.ImportEntites(entities);
    auto intersectionCount = grid.CountIntersections();
    std::cout << "Number of intersections: " << intersectionCount << std::endl;

    const auto end = std::chrono::high_resolution_clock::now();
    const auto runMS = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Algorithm executed in " << runMS.count() << "ms.\n" << std::endl;

    return 0;
}