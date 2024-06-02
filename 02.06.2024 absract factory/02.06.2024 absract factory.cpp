#include <iostream>
#include <string>
using namespace std;

/*
Абстрактная фабрика - порождающий паттерн проектирования,
который предоставляет интерфейс для создания семейств взаимосвязанных или взаимозависимых объектов,
не специфицируя их конкретных классов.

Применимость
- система не должна зависеть от того, как создаются, компонуются и представляются входящие в нее объекты;
- входящие в семейство взаимосвязанные объекты должны использоваться вместе и необходимо обеспечить выполнение этого ограничения;
- система должна конфигурироваться одним из семейств составляющих ее объектов;

Паттерн абстрактная фабрика обладает следующими плюсами и минусами:
 * изолирует конкретные классы.
 * упрощает замену семейств продуктов.
 * гарантирует сочетаемость продуктов.
*/

class Herbivore abstract //Травоядное животное 
{
public:
    virtual string GetName() abstract;
    virtual void eatGrass() abstract; 
    virtual double GetWeight() abstract;
    virtual bool IsAlive() abstract;
    virtual void SetAlive(bool Alive) abstract;
};

class Wildebeest : public Herbivore //Антилопа Гну
{
    double weight;
    bool alive;
public:
    Wildebeest() : weight(200), alive(true) {}

    void eatGrass() override 
    {
        weight += 10; 
    }
    double GetWeight() override
    {
        return weight;
    }
    bool IsAlive() override 
    {
        return alive;
    }
    void SetAlive(bool Alive) override
    {
        alive = Alive;
    }
    string GetName() override
    {
        return "Wildebeest";
    }
};

class Bison : public Herbivore //Бизон
{
private:
    double weight;
    bool alive;
public:
    Bison() : weight(100), alive(true) {}

    void eatGrass() override
    {
        weight += 10;
    }
    double GetWeight() override
    {
        return weight;
    }
    bool IsAlive() override 
    {   
        return alive;
    }
    void SetAlive(bool Alive) override
    {
        alive = Alive;
    }
    string GetName() override
    {
        return "Bison";
    }
};

class Elk : public Herbivore //Лось
{
private:
    double weight;
    bool alive;
public:
    Elk() : weight(500), alive(true) {}

    void eatGrass() override
    {
        weight += 10;
    }
    double GetWeight() override
    {
        return weight;
    }
    bool IsAlive() override
    {
        return alive;
    }
    void SetAlive(bool Alive) override
    {
        alive = Alive;
    }
    string GetName() override
    {
        return "Elk";
    }
};

class Carnivore abstract //Плотоядное животное
{
public:
    virtual void Eat(Herbivore* obj) abstract;
    virtual double GetPower() abstract;
};

class Lion : public Carnivore
{   
    double power;
public:
    double GetPower() override 
    {
        return power;
    }
    void Eat(Herbivore* obj) override
    {
        if (power > obj->GetWeight())
        {
            power += 10;
            obj->SetAlive(false);
            cout << "Lion eats " << obj->GetName() << " and gains power " << endl;
        }
        else 
        {
            power -= 10;
            cout << "Lion fails to eat " << obj->GetName() << " and loses power\n";
        }
    }
};

class Wolf : public Carnivore
{
    double power;
public:
    double GetPower() override
    {
        return power;
    }
    void Eat(Herbivore* obj) override
    {
        if (power > obj->GetWeight())
        {
            power += 10;
            obj->SetAlive(false);
            cout << "Wolf eats " << obj->GetName() << " and gains power " << endl;
        }
        else
        {
            power -= 10;
            cout << "Wolf fails to eat " << obj->GetName() << " and loses power\n";
        }
    }
};

class Tiger : public Carnivore
{
    double power;
public:
    double GetPower() override
    {
        return power;
    }
    void Eat(Herbivore* obj) override
    {
        if (power > obj->GetWeight())
        {
            power += 10;
            obj->SetAlive(false);
            cout << "Tiger eats " << obj->GetName() << " and gains power " << endl;
        }
        else
        {
            power -= 10;
            cout << "Tiger fails to eat " << obj->GetName() << " and loses power\n";
        }
    }
};

class Continent abstract
{
public:
    virtual Herbivore* CreateHerbivore() abstract;
    virtual Carnivore* CreateCarnivore() abstract;
};

class Africa : public Continent
{
public:
    Herbivore* CreateHerbivore() override
    {
        return new Wildebeest;
    }
    Carnivore* CreateCarnivore() override
    {
        return new Lion;
    }
};

class NorthAmerica : public Continent
{
    Herbivore* CreateHerbivore() override
    {
        return new Bison;
    }
    Carnivore* CreateCarnivore() override
    {
        return new Wolf;
    }
};

class Eurasia : public Continent
{
    Herbivore* CreateHerbivore() override
    {
        return new Elk;
    }
    Carnivore* CreateCarnivore() override
    {
        return new Tiger;
    }
};

class AnimalWorld
{
    Herbivore* herbivore;
    Carnivore* carnivore;
public:
    AnimalWorld(Continent* factory) 
    {
        herbivore = factory->CreateHerbivore();
        carnivore = factory->CreateCarnivore();
    }
    void MealsHerbivores() {
        if (herbivore->IsAlive()) 
        {
            herbivore->eatGrass();
            cout << herbivore->GetName() << " eats grass and now weighs " << herbivore->GetWeight() << " kg\n";
        }
    }
    void NutritionCarnivores() 
    {
        if (herbivore->IsAlive()) 
        {
            carnivore->Eat(herbivore);
        }
    }
};

void PrintAnimalWorld(Continent* continent, const string& continentName) 
{
    cout << continentName << endl;
    AnimalWorld world(continent);
    world.MealsHerbivores();
    world.NutritionCarnivores();
    cout << endl;
    delete continent;
}

int main()
{
    PrintAnimalWorld(new Africa(), "Africa");
    PrintAnimalWorld(new NorthAmerica(), "North America");
    PrintAnimalWorld(new Eurasia(), "Eurasia");
}