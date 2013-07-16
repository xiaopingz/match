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
	PersonInfoPtr	girlMatched, boyMatched;

	for( PersonGroup::size_type ixTmp=0;ixTmp!=(*girls).size();++ixTmp )
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
	
	PersonGroupPtr	pPGHotGirls	=	getHotestGirl(pMapGB);
	if ( pPGHotGirls->size()==1 )
	{
		 girlMatched	=	*(pPGHotGirls->begin());
	}
	else
	{
		PersonGroupPtr	pPGMSGirls	=	PersonInfo::selectMaxSum(pPGHotGirls);
		if ( pPGMSGirls->size()==1 )
		{
			girlMatched	=	*(pPGMSGirls->begin());
		}
		else
		{
			girlMatched	=	PersonInfo::selectMinId(pPGMSGirls);
		}
	}
	boyMatched	=	girlMatched->selectTheBestOne((*pMapGB)[girlMatched]);	//��Գɹ�
	return std::make_pair(boyMatched,girlMatched);
}

PersonGroupPtr		MDriver::getHotestGirl(std::shared_ptr<MapGB>	pMapGB)
{
	PersonGroupPtr	pPGHotGirls	=	std::make_shared<PersonGroup>();
	MapGB::iterator	it, itBest;
	PersonGroup::size_type	ixMax	=	0, ixTmp;

	for ( it=pMapGB->begin();it!=pMapGB->end();++it )
	{
		ixTmp	=	(it->second)->size();
		if ( ixTmp>ixMax || ixMax==ixTmp )
		{
			if ( ixTmp>ixMax )
			{
				ixMax	=	ixTmp;
				pPGHotGirls->clear();
			}
			pPGHotGirls->push_back(it->first);
		}
	}
	return	pPGHotGirls;
}