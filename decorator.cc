#include <iostream>
#include <string>

using  std::cout;
using  std::endl;
using  std::string;


class IFamilyUnit
{
protected:
	string name;
	string sex;
	string spouseName;
	bool hasChildren;
	int numberOfMaleChild;
	int numberOfFemaleChild;
public:
	virtual void FamilyMemberNames() = 0;
	virtual ~IFamilyUnit(){};
};

class Family : public IFamilyUnit
{
public:
	virtual void FamilyMemberNames(){cout <<"Listing Family members..."<<endl;}
	virtual ~Family(){cout <<"    nuking Family..."<<endl;}
	
};

class DecoratorMembers : public IFamilyUnit
{
protected:
	IFamilyUnit* family; 
public:
	DecoratorMembers(IFamilyUnit* p):family(p){}
	
	virtual void FamilyMemberNames(){family->FamilyMemberNames();}
	virtual ~DecoratorMembers(){delete family; family = 0; cout <<"    nuking DecoratorMembers..."<<endl;}

};

class Male : public DecoratorMembers
{
public:
	Male(const string& _name, IFamilyUnit* p):DecoratorMembers(p){ name = _name;}
	virtual void FamilyMemberNames(){family->FamilyMemberNames(); cout <<"  Husband name is "<<name<<endl;}
	virtual ~Male(){cout <<"    nuking Male..."<<endl;}

};

class Female : public DecoratorMembers
{
public:
	Female(const string& _name, IFamilyUnit* p):DecoratorMembers(p){name = _name;}
	virtual void FamilyMemberNames(){family->FamilyMemberNames(); cout <<"  Wife name is "<<name<<endl;}
	virtual ~Female(){cout <<"    nuking Female..."<<endl;}

};

class MaleChild : public DecoratorMembers
{
public:
	MaleChild(const string& _name, IFamilyUnit* p):DecoratorMembers(p){name = _name;}
	virtual void FamilyMemberNames(){family->FamilyMemberNames(); cout <<"  Child name is "<<name<<endl;}
	virtual ~MaleChild(){cout <<"    nuking MaleChild..."<<endl;}

};

class FemaleChild : public DecoratorMembers
{
public:
	FemaleChild(const string& _name, IFamilyUnit* p):DecoratorMembers(p){name = _name;}
	virtual void FamilyMemberNames(){family->FamilyMemberNames(); cout <<"  Child name is "<<name<<endl;}
	virtual ~FemaleChild(){cout <<"    nuking FemaleChild..."<<endl;}

};

int main ()
{
	IFamilyUnit* newlyMarried = new Male("Dumbo", new Female("Dodo", new Family())); 
	newlyMarried->FamilyMemberNames();
	cout <<"******************************"<<endl;

	IFamilyUnit* marriedAndHadAChild = new Male("Dumbo", new Female("Dodo", new MaleChild("Dumdo", new Family())));
	marriedAndHadAChild->FamilyMemberNames();
	cout <<"******************************"<<endl;

	IFamilyUnit* marriedAndHadTwoChildren = new Male("Dumbo", new Female("Dodo", new MaleChild("Dumdo", 
									new FemaleChild("DoDum", new Family()))));
	marriedAndHadTwoChildren->FamilyMemberNames();
	cout <<"******************************"<<endl;

	delete newlyMarried;
	cout <<"******************************"<<endl;
	delete marriedAndHadAChild;
	cout <<"******************************"<<endl;
	delete marriedAndHadTwoChildren;

	return 0;
}

