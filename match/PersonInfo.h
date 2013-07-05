#ifndef PERSON_INFO_H_
#define PERSON_INFO_H_
#include <vector>
#include <memory>
#include <string>


class PersonInfo;
typedef std::shared_ptr<PersonInfo> PersonInfoPtr;
typedef std::vector<PersonInfoPtr> PersonGroup;
typedef std::shared_ptr<PersonGroup> PersonGroupPtr;
typedef std::pair<PersonInfoPtr, PersonInfoPtr> BGPair; //<Boy, Girl>
typedef std::vector<BGPair>	 BGPairs;
typedef std::shared_ptr<BGPairs>	BGPairsPtr;


class PersonInfo
{
public:
	PersonInfo(int uid, int iwealth, int ilook, int icharactor, int rwealth, int rlook, int rcharactor, int igender);
	
	int		sumOfInfo();
	int		getSatDegree(PersonInfoPtr p);
	
	PersonInfoPtr 	selectTheBestOne(PersonGroupPtr group);
	
	
	static PersonGroupPtr  readFromFile(const std::string & file);
	static PersonGroupPtr	generateRandomPersons(int num);
	static PersonInfoPtr	generateOnePerson();
	
	static void			showPairs(BGPairsPtr ps);
	static void			dumpPairsToFile(BGPairsPtr ps, const std::string & file);
	
protected:
	int m_userID;
	int m_info_wealth;		//本人财富: 取值1~100
	int m_info_look;		//本人样貌：取值1~100
	int m_info_charactor;	//本人品格：取值1~100
	int m_ratio_wealth;
	int m_ratio_look;
	int m_ratio_charactor;	//对配偶三项指标的期望百分比，三者和为100，各自取值1~98
	int m_gender;			//1:male; 0:female
};//end class PersonInfo;
#endif