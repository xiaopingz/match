#include "MDriver.h"
#include<algorithm>	//std::find
#include<iostream>

BGPairsPtr	MDriver::makeAllPairs(PersonGroupPtr boys, PersonGroupPtr girls)
{
	BGPairsPtr	pBGPairs	=	std::make_shared<BGPairs>();
	while( boys->size() && girls->size() )
	{
		BGPair	onePair	=	makeOnePair(boys,girls);	//	һ�����
		pBGPairs->push_back(onePair);					//���������BGPairs����
		PersonGroup::iterator	it	=	std::find(boys->begin(),boys->end(),onePair.first);	//��������Ե����Ե�λ��
		boys->erase(it);		//ɾ����������Ϣ
		it	=	std::find(girls->begin(),girls->end(),onePair.second);		//��������Ե�Ů�Ե�λ��
		girls->erase(it);		//	ɾ����Ů����Ϣ
	}
	return	pBGPairs;
}
	
BGPair		MDriver::makeOnePair(PersonGroupPtr boys, PersonGroupPtr girls)
{
	std::shared_ptr<MapGB>	pMapGB	=	std::make_shared<MapGB>();
	PersonGroup::size_type	ixMax	=	0, ixTmp;
	MapGB::iterator itMap, itMax;

	for( ixTmp=0;ixTmp!=(*girls).size();++ixTmp )
	{
		PersonGroupPtr	pPG	=	std::make_shared<PersonGroup>();
		PersonInfoPtr	pGirl	=	(*girls)[ixTmp];
		(*pMapGB)[pGirl]	=	pPG;
	}
	for( PersonGroup::iterator itBoys = boys->begin(); itBoys!=boys->end(); ++itBoys )
	{
		//�������ԣ���ŮʿͶƱ
		PersonInfoPtr	girlToVote	=	(*itBoys)->selectTheBestOne(girls);
		(*pMapGB)[girlToVote]->push_back(*itBoys);	
	}
	for( itMap = pMapGB->begin(); itMap!=pMapGB->end();++itMap )
	{
		int iSumOfBest=0, iSumNow=0, iIdOfBest=100, iIdNow=100;
		iSumNow		=	(itMap->first)->sumOfInfo();
		iIdNow		=	(itMap->first)->getUsrid();
		//ѡ��Ʊ������Ů��
		ixTmp	=	(itMap->second)->size();
		if( ixTmp>ixMax || (ixTmp==0 && ixMax==0) )
		{
			ixMax	=	ixTmp;
			itMax	=	itMap;
			iSumOfBest	=	iSumNow;
			iIdOfBest	=	iIdNow;
		}
		else if( ixTmp==ixMax )
		{
			if( iSumNow>iSumOfBest )
			{
				itMax	=	itMap;
				iSumOfBest	=	iSumNow;
				iIdOfBest	=	iIdNow;
			}
			else if( iSumNow==iSumOfBest )
			{
				if( iIdNow<iIdOfBest )
				{
					itMax	=	itMap;
					iIdOfBest	=	iIdNow;
				}
			}
		}
	}
	PersonInfoPtr	girlMatched	=	itMax->first;
	PersonInfoPtr	boyMatched	=	girlMatched->selectTheBestOne(itMax->second);	//��Գɹ�
	//std::cout<<boyMatched->getUsrid()<<" & "<<girlMatched->getUsrid()<<std::endl;
	return std::make_pair(boyMatched,girlMatched);
}
