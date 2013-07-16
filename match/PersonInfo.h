#ifndef PERSON_INFO_H_
#define PERSON_INFO_H_
#include <vector>
#include <map>
#include <memory>
#include <string>


class PersonInfo;
typedef std::shared_ptr<PersonInfo> PersonInfoPtr;
typedef std::vector<PersonInfoPtr> PersonGroup;
typedef std::shared_ptr<PersonGroup> PersonGroupPtr;
typedef std::map<PersonInfoPtr,PersonGroupPtr>	MapGB;	//���Ů�Ժ�ѡ����Ϣ����Ů��ͶƱ�������ԣ�
typedef std::pair<PersonInfoPtr, PersonInfoPtr> BGPair; //<Boy, Girl>
typedef std::vector<BGPair>	 BGPairs;
typedef std::shared_ptr<BGPairs>	BGPairsPtr;


class PersonInfo
{
public:
	PersonInfo();
	PersonInfo(int uid, int iwealth, int ilook, int icharactor, int rwealth, int rlook, int rcharactor, int igender);
	
	int		sumOfInfo();
	int		getSatDegree(PersonInfoPtr p);		//����һ���˶���һ���˵������
	int		getPersonGenger();
	int		getUsrid();
	
	PersonInfoPtr 	selectTheBestOne(PersonGroupPtr group);	//ѡ����һ�Ա��������������
	PersonGroupPtr	selectMaxSatDegree(PersonGroupPtr group);
	static	PersonGroupPtr	selectMaxSum(PersonGroupPtr group);
	static	PersonInfoPtr	selectMinId(PersonGroupPtr group);
	
	
	static PersonGroupPtr	readFromFile(const std::string & file);	//���ļ��ж�ȡ�û���Ϣ
	static PersonGroupPtr	generateRandomPersons(int num, int gender);	//���������Ϣ���û���numΪ������ĸ�����genderΪ�Ա�
	static PersonInfoPtr	generateOnePerson(int id, int gender);
	static PersonInfoPtr	inputOnePerson();
	
	static void			showPairs(BGPairsPtr ps);
	static void			dumpPairsToFile(BGPairsPtr ps, const std::string & file);
	
protected:
	int m_userID;
	int m_info_wealth;		//���˲Ƹ�: ȡֵ1~100
	int m_info_look;		//������ò��ȡֵ1~100
	int m_info_charactor;	//����Ʒ��ȡֵ1~100
	int m_ratio_wealth;
	int m_ratio_look;
	int m_ratio_charactor;	//����ż����ָ��������ٷֱȣ����ߺ�Ϊ100������ȡֵ1~98
	int m_gender;			//1:male; 0:female
};//end class PersonInfo;
#endif