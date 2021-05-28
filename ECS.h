#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;  //declaration
class Entity; //declaration

using ComponentID = std::size_t;  //we're creating IDs for things like pos, physics, input handling etc

inline ComponentID getComponentTypeID()   //inline is basically like using the code wherever needed instead of calling a simple func, acts like a header file
{
    static ComponentID lastID = 0;
    return lastID++;  //everytime we call it we'll get the next ID/post increment
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
    static ComponentID typeID = getComponentTypeID();  //generates new last ID and put that in our type ID
    return typeID;
}

//to check if entity has a component attached, we need to perform the following funcs
constexpr std::size_t maxComponents = 32;   

using ComponentBitSet = std::bitset<maxComponents>; //component bitset allows us to compare whether an entity has got selection of components or not
using ComponentArray = std::array<Component* , maxComponents>;  //length of all maxComponents

class Component
{
    public:
        Entity *entity;

        virtual void init() {}
        virtual void update() {}
        virtual void draw() {}

        virtual ~Component() {}
};

class Entity
{
    private:
        bool active = true; //check if the entity is active or not
        std::vector<std::unique_ptr<Component>> components; // list of all the components that the entity is holding in the form of a vector

        ComponentArray componentArray;
        ComponentBitSet componentBitSet;
    public:
    // the entity will loop through all of its components and update and draw accordingly
    void update()
    {
        for (auto& c : components) c->update();
    }
    void draw() 
    {
        for (auto& c : components) c->draw();
    }
        bool isActive() const { return active; }
        void destroy() { active = false; }  // any entity that is not active, it'll remove it

    template <typename T> bool hasComponent() const
    {
        return componentBitSet[getComponentTypeID<T>()]; //this will return true or false if a component is attached to an ID
    }

    //to add a component in the entity
    template <typename T, typename... TArgs>
    T& addComponent(TArgs&&... mArgs)
    {
        T *c(new T(std::forward<TArgs>(mArgs)...));
        c->entity = this;
        std::unique_ptr<Component> uPtr{c};
        components.emplace_back(std::move(uPtr));

        componentArray[getComponentTypeID<T>()] = c; //index of componentArray will be equal to c
        componentBitSet[getComponentTypeID<T>()] = true;

        c->init(); //reference to the components
        return *c;
    }

    //getter function in the form of getComponent
    template <typename T> T& getComponent() const
    {
        auto ptr(componentArray[getComponentTypeID<T>()]);
        return *static_cast<T*>(ptr);
    }
};  

// to keep a list of all the entities, we will make the following Manager class
class Manager
{
    private:
        std::vector<std::unique_ptr<Entity>> entities;

    public:
    void update()
    {
        for (auto& e : entities) e->update();
    }
    void draw()
    {
        for (auto& e : entities) e->draw();
    }
    //move through the frames, through every entity and then remove the ones that are not there
    void refresh()
    {
        entities.erase(std::remove_if(std::begin(entities), std::end(entities),
            [](const std::unique_ptr<Entity> &mEntity) 
        {
            return !mEntity->isActive();
        }),
        std::end(entities)); //if they are not active, entities will then be removed
    }
    Entity& addEntity()
    {
        Entity *e = new Entity();
        std::unique_ptr<Entity> uPtr{e};
        entities.emplace_back(std::move(uPtr));
        return *e;
    }
};