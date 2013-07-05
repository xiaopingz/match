#include "PersonInfo.h"
#include<fstream>

PersonInfo::PersonInfo(int uid, int iwealth, int ilook, int icharactor, int rwealth, int rlook, int rcharactor, int igender)
	:m_userID(uid),m_info_wealth(iwealth),m_info_look(ilook),m_info_charactor(icharactor),m_ratio_wealth(rwealth),m_ratio_look(rlook),m_ratio_charactor(rcharactor),m_gender(igender)
{
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
	int iSumOfBest, iSumNow, iIdOfBest, iIdNow;
	for( std::vector<PersonInfoPtr>::iterator it = group->begin(); it!=group->end(); ++it )
	{
		tmpDegree	=	getSatDegree(*it);
		iSumNow		=	(*it)->sumOfInfo();
		iIdNow		=	(*it)->m_userID;
		if(tmpDegree>highestDegree)
		{
			highestDegree	=	tmpDegree;
			itBest	=	it;
			iSumOfBest	=	iSumNow;
			iIdOfBest	=	iIdNow;
		}
		if(tmpDegree==highestDegree)
		{
			if( (*it)->sumOfInfo()>iSumOfBest )
			{
				itBest	=	it;
				iSumOfBest	=	iSumNow;
				iIdOfBest	=	iIdNow;
			}
			if( (*it)->sumOfInfo()==iSumOfBest )
			{
				if( (*it)->m_userID<iIdOfBest )
				{
					itBest	=	it;
					iIdOfBest	=	iIdNow;
				}
			}
		}
	}
	return *itBest;
}

PersonGroupPtr  PersonInfo::readFromFile(const std::string & file)
{
	PersonGroupPtr	pPersonGroup	=	std::make_shared<PersonGroup>();
	std::ifstream	fRead(file);
	int gender,id,w,l,c,rw,rl,rc;
	char t;		//	','
	while( !fRead.eof() )
	{
		if( file=="../players.txt")
		{
			id	=	-1;
			fRead>>gender>>t>>w>>t>>l>>t>>c>>t>>rw>>t>>rl>>t>>rc;
		}
		else
		{
			if( file=="../male.txt" )
				gender	=	1;
			if( file=="../female.txt" )
				gender	=	0;
			fRead>>id>>t>>w>>t>>l>>t>>c>>t>>rw>>t>>rl>>t>>rc;
		}
		PersonInfoPtr	pPerson	=	std::make_shared<PersonInfo>(id,w,l,c,rw,rl,rc,gender);
		pPersonGroup->push_back(pPerson);
	}
	return	pPersonGroup;
}

PersonGroupPtr	PersonInfo::generateRandomPersons(int num)
{
	PersonGroupPtr	pPersonGroup	=	std::make_shared<PersonGroup>();
	for( int i = 0;i<num;++i )
	{
		PersonInfoPtr	pPerson	=	generateOnePerson();
		pPersonGroup->push_back(pPerson);
	}
	return	pPersonGroup;
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
