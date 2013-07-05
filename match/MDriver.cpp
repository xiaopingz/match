#include "MDriver.h"
#include<algorithm>	//std::find
#include<iostream>

BGPairsPtr	MDriver::makeAllPairs(PersonGroupPtr boys, PersonGroupPtr girls)
{
	BGPairsPtr	pBGPairs	=	std::make_shared<BGPairs>();
	while( boys->size() && girls->size() )
	{
		BGPair	onePair	=	makeOnePair(boys,girls);	//	一次配对
		pBGPairs->push_back(onePair);					//将结果放入BGPairs当中
		PersonGroup::iterator	it	=	std::find(boys->begin(),boys->end(),onePair.first);	//查找已配对的男性的位置
		boys->erase(it);		//删除该男性信息
		it	=	std::find(girls->begin(),girls->end(),onePair.second);		//查找已配对的女性的位置
		girls->erase(it);		//	删除该女性信息
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
		//遍历男性，给女士投票
		PersonInfoPtr	girlToVote	=	(*itBoys)->selectTheBestOne(girls);
		(*pMapGB)[girlToVote]->push_back(*itBoys);	
	}
	for( itMap = pMapGB->begin(); itMap!=pMapGB->end();++itMap )
	{
		int iSumOfBest=0, iSumNow=0, iIdOfBest=100, iIdNow=100;
		iSumNow		=	(itMap->first)->sumOfInfo();
		iIdNow		=	(itMap->first)->getUsrid();
		//选出票数最多的女性
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
	PersonInfoPtr	boyMatched	=	girlMatched->selectTheBestOne(itMax->second);	//配对成功
	//std::cout<<boyMatched->getUsrid()<<" & "<<girlMatched->getUsrid()<<std::endl;
	return std::make_pair(boyMatched,girlMatched);
}
