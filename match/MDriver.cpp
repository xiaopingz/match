#include "MDriver.h"
#include<algorithm>	//std::find

//make pairs for all boys and girls;
BGPairsPtr	MDriver::makeAllPairs(PersonGroupPtr boys, PersonGroupPtr girls)
{
	BGPairsPtr	pBGPairs	=	std::make_shared<BGPairs>();
	while( !boys && !girls )
	{
		BGPair	onePair	=	makeOnePair(boys,girls);
		pBGPairs->push_back(onePair);
		PersonGroup::iterator	it	=	std::find(boys->begin(),boys->end(),onePair.first);
		boys->erase(it);
		it	=	std::find(girls->begin(),girls->end(),onePair.second);
		girls->erase(it);
	}
}
	
//select the first pair for the boys and girls;
BGPair		MDriver::makeOnePair(PersonGroupPtr boys, PersonGroupPtr girls)
{
}
