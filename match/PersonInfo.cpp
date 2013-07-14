#include "PersonInfo.h"
#include<fstream>
#include<iostream>

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
	int	sd	=	m_info_charactor * p->m_ratio_charactor + m_info_look * p->m_ratio_look + m_info_wealth * p->m_ratio_wealth;
		//std::cout<<m_userID<<"->"<<p->m_userID<<" :"<<sd<<std::endl;

	return sd;
}

int		PersonInfo::getPersonGenger()
{
	return	m_gender;
}

int		PersonInfo::getUsrid()
{
	return m_userID;
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
		{	//如果满意度相同，则找出自身各项指标和最大的一个
			if( (*it)->sumOfInfo()>iSumOfBest )
			{
				itBest	=	it;
				iSumOfBest	=	iSumNow;
				iIdOfBest	=	iIdNow;
			}
			if( (*it)->sumOfInfo()==iSumOfBest )
			{	//如果和也一样，则选择id最小的一个
				if( (*it)->m_userID<iIdOfBest )
				{
					itBest	=	it;
					iIdOfBest	=	iIdNow;
				}
			}
		}
	}
	//std::cout<<m_userID<<" choose:"<<(*itBest)->m_userID<<std::endl;
	return *itBest;
}

PersonGroupPtr  PersonInfo::readFromFile(const std::string & file)
{
	PersonGroupPtr	pPersonGroup	=	std::make_shared<PersonGroup>();
	std::ifstream	fRead;
	fRead.open(file);
	if( !fRead.good() )
	{
		std::cout<<"Open file:"<<file<<" failed!"<<std::endl;
		return NULL;
	}
	int gender,id = 0 ,w,l,c,rw,rl,rc;
	char t;		//	读取符号','

	if( file.find("players.txt")!=std::string::npos )
		id	=	-1;		//从players.txt中读取的主角id均为-1
	else if( file.find("male.txt")!=std::string::npos )
		gender	=	1;		// male
	else if( file.find("female.txt")!=std::string::npos )
		gender	=	0;		//female

	while( !fRead.eof() )
	{
		if( id==-1 )
			fRead>>gender>>t>>w>>t>>l>>t>>c>>t>>rw>>t>>rl>>t>>rc;
		else
			fRead>>id>>t>>w>>t>>l>>t>>c>>t>>rw>>t>>rl>>t>>rc;

		if(fRead.bad()||fRead.fail())
			continue;
		PersonInfoPtr	pPerson	=	std::make_shared<PersonInfo>(id,w,l,c,rw,rl,rc,gender);
		pPersonGroup->push_back(pPerson);
	}
	fRead.close();
	return	pPersonGroup;
}

PersonGroupPtr	PersonInfo::generateRandomPersons(int num,int gender)
{
	PersonGroupPtr	pPersonGroup	=	std::make_shared<PersonGroup>();
	for( int i = 0;i<num;++i )
	{
		PersonInfoPtr	pPerson	=	generateOnePerson(i,gender);
		pPersonGroup->push_back(pPerson);
	}
	return	pPersonGroup;
}

PersonInfoPtr	PersonInfo::generateOnePerson(int id, int gender)
{
	int w, l, c, rw, rl, rc;
	w	=	rand()%100 + 1;	//生成1~100的随机数
	l	=	rand()%100 + 1;
	c	=	rand()%100 + 1;
	rw	=	rand()%98  + 1;	//生成1~98的随机数
	rl	=	rand()%(99-rw) + 1;
	rc	=	100 - rw - rl;
	PersonInfoPtr	pPerson	=	std::make_shared<PersonInfo>(id,w,l,c,rw,rl,rc,gender);
	return	pPerson;
}

PersonInfoPtr	PersonInfo::inputOnePerson()
{
	PersonInfoPtr pPerson;
	int w, l, c, rw, rl, rc,gender;
	std::cout<<"Please int the person's information (7 numbers):"<<std::endl;
	std::cin>>w>>l>>c>>rw>>rl>>rc>>gender;
	if( w<100 && l<100 && c<100 && rw<99 && rl<99 && rc<98 && rw+rl+rc==100 && gender==1 || gender==0 )
		pPerson =	std::make_shared<PersonInfo>(-1,w,l,c,rw,rl,rc,gender);
	else
		pPerson	=	NULL;
	return pPerson;
}

void			PersonInfo::showPairs(BGPairsPtr ps)
{
	std::vector<BGPair>::iterator itPair;
	for( itPair=ps->begin();itPair != ps->end();++itPair )
	{
		PersonInfoPtr pBoy	=	(*itPair).first;
		PersonInfoPtr pGirl	=	(*itPair).second;
		std::cout<<"M:"<<pBoy->m_userID<<" INFO:"<<pBoy->m_info_wealth<<","<<pBoy->m_info_look<<","<<pBoy->m_info_charactor<<","<<pBoy->m_ratio_wealth<<","<<pBoy->m_ratio_look<<","<<pBoy->m_ratio_charactor;
		std::cout<<" F:"<<pGirl->m_userID<<" INFO:"<<pGirl->m_info_wealth<<","<<pGirl->m_info_look<<","<<pGirl->m_info_charactor<<","<<pGirl->m_ratio_wealth<<","<<pGirl->m_ratio_look<<","<<pGirl->m_ratio_charactor<<std::endl;
	}
}

void			PersonInfo::dumpPairsToFile(BGPairsPtr ps, const std::string & file)
{
	std::ofstream	fWrite(file);
	std::vector<BGPair>::iterator itPair;
	for( itPair=ps->begin();itPair != ps->end();++itPair )
	{
		PersonInfoPtr pBoy	=	(*itPair).first;
		PersonInfoPtr pGirl	=	(*itPair).second;
		fWrite<<"M:"<<pBoy->m_userID<<" INFO:"<<pBoy->m_info_wealth<<","<<pBoy->m_info_look<<","<<pBoy->m_info_charactor<<","<<pBoy->m_ratio_wealth<<","<<pBoy->m_ratio_look<<","<<pBoy->m_ratio_charactor;
		fWrite<<" F:"<<pGirl->m_userID<<" INFO:"<<pGirl->m_info_wealth<<","<<pGirl->m_info_look<<","<<pGirl->m_info_charactor<<","<<pGirl->m_ratio_wealth<<","<<pGirl->m_ratio_look<<","<<pGirl->m_ratio_charactor<<std::endl;
	}
	fWrite.close();
}
