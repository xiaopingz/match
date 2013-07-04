#include "PersonInfo.h"

PersonInfo::PersonInfo(int uid, int iwealth, int ilook, int icharactor, int rwealth, int rlook, int rcharactor)
{
	m_userID		=	uid;
	m_info_wealth	=	iwealth;		
	m_info_look		=	ilook;		
	m_info_charactor	=	icharactor;
	m_ratio_wealth	=	rwealth;
	m_ratio_look	=	rlook;
	m_ratio_charactor	=	rcharactor;
}

int		PersonInfo::sumOfInfo()
{
	return m_info_charactor+m_info_look+m_info_wealth;
}

int		PersonInfo::getSatDegree(PersonInfoPtr p)
{
	return m_info_charactor * p->m_ratio_charactor + m_info_look * p->m_ratio_look + m_info_wealth * p->m_ratio_wealth;
}

PersonInfoPtr 	PersonInfo::selectTheBestOne(PersonGroupPtr group)
{
	int highestDegree=0, tmpDegree;
	std::vector<PersonInfoPtr>::iterator itBest;
	int iSumOfBest, iIdOfBest;
	for( std::vector<PersonInfoPtr>::iterator it = group->begin(); it!=group->end(); ++it )
	{
		tmpDegree	=	getSatDegree(*it);
		if(tmpDegree>highestDegree)
		{
			highestDegree	=	tmpDegree;
			itBest	=	it;
			iSumOfBest	=	(*it)->sumOfInfo();
			iIdOfBest	=	(*it)->m_userID;
		}
		if(tmpDegree==highestDegree)
		{
			if( (*it)->sumOfInfo()>iSumOfBest )
			{
				itBest	=	it;
				iSumOfBest	=	(*it)->sumOfInfo();
				iIdOfBest	=	(*it)->m_userID;
			}
			if( (*it)->sumOfInfo()==iSumOfBest )
			{
				if( (*it)->m_userID<iIdOfBest )
				{
					itBest	=	it;
					iIdOfBest	=	(*it)->m_userID;
				}
			}
		}
	}
	return *itBest;
}

PersonGroupPtr  PersonInfo::readFromFile(const std::string & file)
{
}

PersonGroupPtr	PersonInfo::generateRandomPersons(int num)
{
}

PersonInfoPtr	PersonInfo::generateOnePerson()
{
}

void			PersonInfo::showPairs(BGPairsPtr ps)
{
}

void			PersonInfo::dumpPairsToFile(BGPairsPtr ps, const std::string & file)
{
}
