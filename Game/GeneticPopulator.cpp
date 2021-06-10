//
// Created by Ahmad Rahimi on 12/24/17.
//

#include "GeneticPopulator.h"

GeneticPopulator::GeneticPopulator() {
    curBaddestChromosome = Chromosome();
    curBaddestChromosome.setFitness(1000000000);
    baddestChromosome.setFitness(1000000000);
}

void GeneticPopulator::insertToPopulation(Chromosome chromosome) {
    this->chromosomes.emplace_back(chromosome);
    this->sortedChromosome.emplace_back(chromosome);
    totalSum += chromosome.getFitness();

    updateChromosomeBoard(chromosome);
}

Chromosome GeneticPopulator::getChromosome() {
    Chromosome selectedchromosome{};
    int partialSum = 0;
    int r;
    if(totalSum == 0)
        r = 0;
    else
        r = rand() % int(totalSum) + 0;
    for(auto &ch : chromosomes){
        partialSum+=ch.getFitness();
        if(partialSum >= r){
            selectedchromosome = ch;
            break;
        }
    }
    return selectedchromosome;
}

void GeneticPopulator::clearChromosomes() {
    totalSum = 0;
    chromosomes.clear();
    sortedChromosome.clear();
    generateCount = 0;
    curBestChromosome = Chromosome();
    curBestChromosome.setFitness(0);
    curBaddestChromosome = Chromosome();
    curBaddestChromosome.setFitness(100000000);
    curAvgChromosome = 0;
}

void GeneticPopulator::updateChromosomeBoard(Chromosome chromosome) {
    if(chromosome.getFitness() > curBestChromosome.getFitness()){
        curBestChromosome = chromosome;
    }
    if(chromosome.getFitness() > bestChromosome.getFitness()){
        bestChromosome = chromosome;
        bestChromosome.generation = this->generation-1;
    }
    if(chromosome.getFitness() < curBaddestChromosome.getFitness()){
        curBaddestChromosome = chromosome;
    }
    if(chromosome.getFitness() < baddestChromosome.getFitness()){
        baddestChromosome = chromosome;
        baddestChromosome.generation = this->generation-1;
    }

    curAvgChromosome = curAvgChromosome + (chromosome.getFitness()/100);
    //curAvgChromosome = chromosome.getFitness()/100;
}

void GeneticPopulator::increaseGeneration() {
    generation++;
}

std::shared_ptr<Rabbit> GeneticPopulator::generateRabbitFromParents(KmPoint generationPoint) {
    int color[3] = {252, 70, 0};
    if(generateCount < ((maxGenerate / 100) * 75)) {
        int r = rand() % 1 + 0;

        if (chromosomes.empty()) {
            Chromosome c = Chromosome(Helper::generatRandomFloat(10), Helper::generatRandomFloat(10),
                                      Helper::generatRandomFloat(10), Helper::generatRandomFloat(20),
                                      Helper::generatRandomFloat(20), 0);
            c.generation = this->generation;
            std::shared_ptr<Rabbit> rabbit(new Rabbit(generationPoint.x, generationPoint.y, 5, 5, color, c));
            if (r == 1) {
                rabbit->color[0] = 128;
                rabbit->color[1] = 10;
                rabbit->color[2] = 190;
            }
            return rabbit;
        }
        Chromosome c1 = this->getChromosome();
        Chromosome c2 = this->getChromosome();
        std::cout << "PARENTS FITNESS:" + std::to_string(c1.getFitness()) + " - " + std::to_string(c2.getFitness())
                  << std::endl;
        std::cout << "att_dog   att_wat     coh     sep     align" << std::endl;
        std::cout << std::to_string(c1.getAttractionDog()) + "  " + std::to_string(c1.getAttractionWater()) + "    " +
                     std::to_string(c1.getAffectionCohesion()) + "   " + std::to_string(c1.getAffectionSeperation()) + "     " + std::to_string(c1.getAffectionAlignment()) << std::endl;
        std::cout << std::to_string(c2.getAttractionDog()) + "  " + std::to_string(c2.getAttractionWater()) + "    " +
                     std::to_string(c2.getAffectionCohesion()) + "   " + std::to_string(c2.getAffectionSeperation()) + "     " + std::to_string(c2.getAffectionAlignment()) << std::endl;
        Chromosome merged = c1.mergeChromosome(c2);
        merged.generation = this->generation;
        std::cout << std::to_string(merged.getAttractionDog()) + "  " + std::to_string(merged.getAttractionWater()) + "    " +
                     std::to_string(merged.getAffectionCohesion()) + "   " + std::to_string(merged.getAffectionSeperation()) + "     " + std::to_string(merged.getAffectionAlignment()) << std::endl;
        std::shared_ptr<Rabbit> rabbit(new Rabbit(generationPoint.x, generationPoint.y, 5, 5, color, merged));
        generateCount++;
        return rabbit;
    }else{
        Chromosome chromosome;
        if(generateCount >= this->sortedChromosome.size())
            chromosome = this->sortedChromosome.at(this->sortedChromosome.size()-1);
        else
            chromosome = this->sortedChromosome.at(generateCount);
        std::shared_ptr<Rabbit> rabbit(new Rabbit(generationPoint.x, generationPoint.y, 5, 5, color, chromosome));
        generateCount++;
        return rabbit;
    }
}

void GeneticPopulator::drawDebug() {
    
    if((Debug::DEBUG_GENETICS || Debug::DEBUG_OPTIONS_ALL) && this->generation >= 1){
        RenderManager::getRenderManager()->DrawText("---Genetics " + std::to_string(this->generation) + "---", 800, 10, 150,
                                                    15, 0, 255, 0, 0);
        RenderManager::getRenderManager()->DrawText("Current Best: " + std::to_string(this->curBestChromosome.getFitness()), 800, 25, 150,
                                                    15, 0, 255, 255, 255);
        RenderManager::getRenderManager()->DrawText("Current Avg: " + std::to_string(this->curAvgChromosome), 800, 40, 150,
                                                    15, 0, 255, 255, 255);
        RenderManager::getRenderManager()->DrawText("Current Bad: " + std::to_string(this->curBaddestChromosome.getFitness()), 800, 55, 150,
                                                    15, 0, 255, 255, 255);
        RenderManager::getRenderManager()->DrawText("Overall Best: " + std::to_string(this->bestChromosome.getFitness()) + "|" + std::to_string(this->bestChromosome.generation), 800, 70, 150,
                                                    15, 0, 255, 255, 255);
        RenderManager::getRenderManager()->DrawText("Overall Bad: " + std::to_string(this->baddestChromosome.getFitness()) + "|" + std::to_string(this->baddestChromosome.generation), 800, 85, 150,
                                                    15, 0, 255, 255, 255);

        RenderManager::getRenderManager()->DrawText("---Best chromosoom---", 1000, 10, 150,
                                                    15, 0, 255, 0, 0);
        RenderManager::getRenderManager()->DrawText("Att. Dog: " + std::to_string(this->bestChromosome.getAttractionDog()), 1000, 25, 150,
                                                    15, 0, 255, 255, 255);
        RenderManager::getRenderManager()->DrawText("Att. Water: " + std::to_string(this->bestChromosome.getAttractionWater()), 1000, 40, 150,
                                                    15, 0, 255, 255, 255);
        RenderManager::getRenderManager()->DrawText("Cohesion: " + std::to_string(this->bestChromosome.getAffectionCohesion()), 1000, 55, 150,
                                                    15, 0, 255, 255, 255);
        RenderManager::getRenderManager()->DrawText("Separation: " + std::to_string(this->bestChromosome.getAffectionSeperation()), 1000, 70, 150,
                                                    15, 0, 255, 255, 255);
        RenderManager::getRenderManager()->DrawText("Alignment: " + std::to_string(this->bestChromosome.getAffectionAlignment()), 1000, 85, 150,
                                                    15, 0, 255, 255, 255);
    }
}

int GeneticPopulator::getGeneration() const {
    return generation;
}

void GeneticPopulator::prepareChromosomes() {
    std::sort(sortedChromosome.begin(), sortedChromosome.end());
}

void StoreChromosomes(){

}