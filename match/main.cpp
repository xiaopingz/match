#include"MDriver.h"
#include"PersonInfo.h"
#include<iostream>
#include<stdlib.h>	//srand,rand
#include<time.h>

void showStartInfo()
{
	std::cout<<"\n\n***************数字化婚姻配对****************"<<std::endl;
	std::cout<<"Welcome! Please choose the mode:\n1. Manual input;\n2. Auto generate:\n0. Exit!"<<std::endl;
}
 
void main()
{
	while(1)
	{
		srand(time(NULL));
		PersonGroupPtr	pPGPlayer,pPGMale,pPGFemale;
		PersonInfoPtr	pPlayer;
		int input;

		showStartInfo();
		std::cin>>input;
		if( input==1 )
		{
			pPlayer	=	PersonInfo::inputOnePerson();
			if( !pPlayer )
			{
				std::cout<<"You input of the personInfo is illigal!"<<std::endl;
				continue;
			}
			if(pPlayer->getPersonGenger()==1)
			{
				pPGMale		=	PersonInfo::generateRandomPersons(99,1);
				pPGFemale	=	PersonInfo::generateRandomPersons(100,0);
			}
			else
			{
				pPGMale		=	PersonInfo::generateRandomPersons(100,1);
				pPGFemale	=	PersonInfo::generateRandomPersons(99,0);
			}
			
		}
		else if( input==2 )
		{
			pPGMale		=	PersonInfo::readFromFile("../male.txt");
			pPGFemale	=	PersonInfo::readFromFile("../female.txt");
			pPGPlayer	=	PersonInfo::readFromFile("../players.txt");
			if( !pPGFemale || !pPGMale || !pPGPlayer )
				continue;
			int iNum;
			std::cout<<"Please choose the number of the player(1~100):"<<std::endl;
			std::cin>>iNum;
			pPlayer		=	(*pPGPlayer)[iNum-1];
			if(pPlayer->getPersonGenger()==1)
			{
				pPGMale->push_back(pPlayer);
			}
			else
			{
				pPGFemale->push_back(pPlayer);
			}
		}
		else if( input==0 )
			break;
		else
		{
			std::cout<<"Illigal input! Please choose again!"<<std::endl;
			continue;
		}

		BGPairsPtr pPairs	=	MDriver::makeAllPairs(pPGMale,pPGFemale);
		PersonInfo::showPairs(pPairs);	//	显示主角的配对情况
		PersonInfo::dumpPairsToFile(pPairs,"../matched.txt");
		std::cout<<"Please check the matched pairs in the file \"../matched.txt\"!"<<std::endl;
	}
}