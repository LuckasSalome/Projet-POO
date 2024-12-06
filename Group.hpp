#pragma once

#include <vector>
#include <memory>
#include <algorithm>                                            // Pour std::remove sans ca marche po
#include "Entity.hpp"

class Group {
private:
    std::vector<std::shared_ptr<Entity>> group;

public:
    void addParty(std::shared_ptr<Entity> entity) {
        group.push_back(entity);
    }

    void removeParty(std::shared_ptr<Entity> entity) {
        group.erase(std::remove(group.begin(), group.end(), entity), group.end());
    }

    std::vector<std::shared_ptr<Entity>> getGroup() const {
        return group;
    }

    bool isGroupEmpty() const {
        return group.empty();
    }
};