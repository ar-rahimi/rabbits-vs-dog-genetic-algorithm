//
// Created by Ahmad Rahimi on 12/15/17.
//
#include "RabbitGenerator.h"
#include "Rabbit.h"

RabbitGenerator *RabbitGenerator::rabbitGenerator;

void RabbitGenerator::generateNewRabbitPopulation(int size) {
    geneticPopulator.clearChromosomes();
    geneticPopulator.increaseGeneration();
    if(Map::getMap()->rabbits.size() != 0 || Map::getMap()->deadrabbits.size() != 0){
        //todo genereer nieuwe aan de hand van de fitness en gooi andere weg
        for(const auto &rabbit : Map::getMap()->rabbits){
            auto rbs = dynamic_cast<Rabbit*>(rabbit.get());
            geneticPopulator.insertToPopulation(rbs->getChromosome());
        }
        for(const auto &rabbit : Map::getMap()->deadrabbits){
            auto rbs = dynamic_cast<Rabbit*>(rabbit.get());
            geneticPopulator.insertToPopulation(rbs->getChromosome());
        }
        geneticPopulator.prepareChromosomes();
    }
    clearRabbits();
    std::cout << "----- GENERATE NEW POPULATION GENERATION " + std::to_string(geneticPopulator.getGeneration()) << std::endl;
    for(int i = 0; i < size; i++){
        KmPoint spawnPoint = Map::getMap()->getRandomGrassPoint();
        std::shared_ptr<Rabbit> rabbit = geneticPopulator.generateRabbitFromParents(spawnPoint);
        Map::getMap()->addRabbit(rabbit);
    }
}

RabbitGenerator *RabbitGenerator::getRabbitGenerator() {
    if (!rabbitGenerator) {
        rabbitGenerator = new RabbitGenerator();
    }
    return rabbitGenerator;
}

void RabbitGenerator::clearRabbits() {
    Map::getMap()->deadrabbits.clear();
    for (auto it=Map::getMap()->moveables.begin();
         it!=Map::getMap()->moveables.end();)
    {
        Rabbit* mb = dynamic_cast<Rabbit*>(it->get());
        if(mb)
            it = Map::getMap()->moveables.erase(it);
        else
            ++it;
    }
    Map::getMap()->rabbits.clear();
}

void RabbitGenerator::drawGenetics() {
    geneticPopulator.drawDebug();
}
