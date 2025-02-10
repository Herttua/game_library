#ifndef COMPONENT_SYSTEM_HH_
#define COMPONENT_SYSTEM_HH_

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array> 

class component;
class entity;

using component_id = std::size_t;

inline component_id get_component_id()
{
    static component_id last_id = 0;
    return last_id++;
}

template <typename T> inline component_id get_component_id() noexcept
{
    static component_id type_id { get_component_id() };
    return type_id;
}

constexpr std::size_t max_components = 32;
using component_bitset = std::bitset<max_components>;
using component_array = std::array<component*, max_components>;

class component
{
public:
    entity* ent;

    virtual void init()   {}
    virtual void update(float dt) {}
    virtual void draw()   {}

    virtual ~component() {}
};

class entity
{
public:
    void update(float dt)
    {
        for(auto& c : components) c->update(dt);
    }

    void draw() 
    {
        for(auto& c : components) c->draw();
    }
    
    bool is_active() const { return active; }
    void destroy() { active = false; }

    template <typename T> bool has_component() const
    {
        return comp_bits[get_component_id<T>()];
    }

    template <typename T, typename... TArgs>
    T& add_component(TArgs&&... mArgs)
    {
        T* c(new T(std::forward<TArgs>(mArgs)...));
        c->ent = this;
        std::unique_ptr<component> u_ptr{c};
        components.emplace_back(std::move(u_ptr));

        comp_arr[get_component_id<T>()] = c;
        comp_bits[get_component_id<T>()] = true;

        c->init();
        return *c;
    }

    template <typename T> T& get_component() const
    {
        auto ptr(comp_arr[get_component_id<T>()]);
        return *static_cast<T*>(ptr);
    }

private:
    bool active = true;
    std::vector<std::unique_ptr<component>> components;
    component_array comp_arr;
    component_bitset comp_bits;
};

class master
{
public:
    void update(float dt)
    {
        for(auto& e : entities) e->update(dt);
    }
    
    void draw()
    {
        for(auto& e : entities) e->draw();   
    }

    void refresh()
    {
        entities.erase(std::remove_if(std::begin(entities), std::end(entities), 
            [](const std::unique_ptr<entity> &m_ent)
            {
                return !m_ent->is_active();
            }),
                std::end(entities));
    }

    entity& add_entity()
    {
        entity *e = new entity();
        std::unique_ptr<entity> u_ptr{e};
        entities.emplace_back(std::move(u_ptr));
        return *e;
    }

private:
    std::vector<std::unique_ptr<entity>> entities;
};

#endif //COMPONENT_SYSTEM_HH_