#include"MDriver.h"
#include"PersonInfo.h"
#include<stdlib.h>	//srand,rand
#include<time.h>

void main()
{
	srand(time(NULL));
	PersonGroupPtr pPGPlayer,pPGMale,pPGFemale;
	pPGPlayer	=	PersonInfo::readFromFile("../players.txt");
	pPGMale		=	PersonInfo::/*generateRandomPersons(100,1)*/readFromFile("../male.txt");
	pPGFemale	=	PersonInfo::/*generateRandomPersons(100,0)*/readFromFile("../female.txt");
	PersonInfoPtr	pPlayer	=	(*pPGPlayer)[0];
	if(pPlayer->getPersonGenger()==1)
	{
		pPGMale->pop_back();
		pPGMale->push_back(pPlayer);
	}
	else
	{
		pPGFemale->pop_back();
		pPGFemale->push_back(pPlayer);
	}

	BGPairsPtr pPairs	=	MDriver::makeAllPairs(pPGMale,pPGFemale);
	PersonInfo::dumpPairsToFile(pPairs,"../matched.txt");
}