#include "dna.h"

const DnaSequence& DnaSequence::operator=(const DnaSequence& dnaSequence){
	DnaSequence::Nucleotides* tmp =m_dnaSequence;
	m_dnaSequence= new DnaSequence::Nucleotides[dnaSequence.length()];
	delete[] tmp;
		
	for (size_t i=0;i<dnaSequence.length();i++)
	{
		m_dnaSequence[i]=dnaSequence.m_dnaSequence[i];
	}
	
	m_length=dnaSequence.length();
	return *this;

}

void DnaSequence::allocDna(const char* dnaSequence){
	size_t i=0;
	m_dnaSequence=new DnaSequence::Nucleotides[m_length];
	
	try
	{
		for (;i<m_length;i++)
		{
			m_dnaSequence[i]=dnaSequence[i];
		}
	}
	
	catch(invalid_inputs &e)
	{
		m_dnaSequence=NULL;
		delete[]m_dnaSequence;
		throw;
	}
}

bool operator==(const DnaSequence& dnaSequence,const DnaSequence& dnaSequence1){
	if (dnaSequence.length() != dnaSequence1.length())
	{
		return false;
	}
	size_t len=dnaSequence.length();
	
	for (size_t i=0;i<len;i++)
	{
		if (dnaSequence[i].getNucleotides() != dnaSequence1[i].getNucleotides())
		{
			return false;
		}
	}
	return true;
}


bool operator!=(const DnaSequence& dnaSequence,const DnaSequence& dnaSequence1){
	if (dnaSequence.length() != dnaSequence1.length())
	{
		return true;
	}
	size_t len=dnaSequence.length();
	for (size_t i=0;i<len;i++)
	{
		if (dnaSequence[i].getNucleotides() != dnaSequence1[i].getNucleotides())
		{
			return true;
		}
	}
	return false;
}



std::ostream& operator<<(std::ostream& os, const DnaSequence& dnaSequence){
	size_t len=dnaSequence.length();

	for (size_t i=0;i<len;i++)
	{
		os<<dnaSequence[i];
	}
	return os;
} 

inline void DnaSequence::writeToFolder(const std::string &fileName){
	std::ofstream myfile;
	myfile.open(fileName.c_str());
	if (myfile.is_open())
	{
		for(size_t i=0;i<length();i++)
		{
			myfile<<m_dnaSequence[i].getNucleotides();
		}
		myfile.close();
		return;
	}
	else
	{
		throw open_file_error(); 
	}
}
DnaSequence::DnaSequence(std::fstream& myfile):m_dnaSequence(NULL){
	std::string line;
	std::string dnaFromFile;
	if (myfile.is_open())
	{
 		while (getline(myfile,line))
  		{
			dnaFromFile += line;
    	}
		myfile.close();
  	}
	else
	{
		throw open_file_error();
	}
	size_t folderLen=dnaFromFile.length();
	m_dnaSequence = new Nucleotides[folderLen];
	try
	{
		for (size_t i=0;i<folderLen;i++)
		{
			m_dnaSequence[i]=dnaFromFile[i];
		}
	}
	
	catch(invalid_inputs &e)
	{
		m_dnaSequence=NULL;
		delete[]m_dnaSequence;
		throw;
	}
}


DnaSequence DnaSequence::slicing(size_t start, size_t end){
	std::string tmp=(*this).getAsString();
	std::string res;
	res=tmp[start];
	for(size_t i=start+1;i<end;i++)	
	{
		res+=tmp[i];
	}
	return DnaSequence(res);
}

static char getPairChar(char firstInPair)
{

		if(firstInPair=='A'){
			return 'C';
		}
		if(firstInPair=='C'){
			return 'A';
		}
		if(firstInPair=='G'){
			return 'T';
		}
		if(firstInPair=='T'){
			return 'G';
		}
	return 0;
}
DnaSequence DnaSequence::pairing(){
	
	std::string tmp=(*this).getAsString();
	std::string res; 
	for(size_t i=m_length;i>0;i--)
	{
		res+=getPairChar(tmp[m_length-i]);	
	}
	return res;
}

size_t DnaSequence::find(const std::string& subSeq){
	std::string tmp=(*this).getAsString();
	return tmp.find(subSeq);

}
size_t DnaSequence::count(const std::string& subSeq){
	return findAll(subSeq).size();
}
  
std::vector<size_t> DnaSequence::findAll(const std::string& subSeq){
	size_t i=0;
	size_t len=subSeq.length();
	size_t myLen=length();
	std::vector<size_t> subPosition;
	while(i<=myLen-len){
		if((slicing(i,m_length).find(subSeq))==-1)
		{	
			return subPosition;
		}
		else
		{
			i+=((slicing(i,m_length).find(subSeq))+1);
			subPosition.push_back(i-1);
		}
	}
	return subPosition;
}


std::vector<DnaSequence> DnaSequence::consensusSequences(){
	std::vector<size_t> first=findAll("ATG");
	std::vector<size_t> end1,end2,end3;
	end1=findAll("TAG");
	end2=findAll("TAA");
	end3=findAll("TGA");
	std::vector<DnaSequence> res={"A"};
	std::vector<size_t>::iterator i;
	std::vector<size_t>::iterator j;	
	
	for(i=first.begin();i!=first.end(); i++)
	{
		for(j=end1.begin();j!=end1.end();j++)
		{
			if ((*i<*j) && ((*j-*i)%3==0))
			{
				res.push_back(slicing(*i,(*j)+3));
			}
		}
		for(j=end2.begin();j!=end2.end(); j++)
		{
			if ((*i<*j) && ((*j-*i)%3==0))
			{
				res.push_back(slicing(*i,(*j)+3));
			}
		}
		for(j=end3.begin();j!=end3.end(); j++)
		{
			if ((*i<*j) && ((*j-*i)%3==0))
			{
				res.push_back(slicing(*i,(*j)+3));
			}
		}
	}	
	return res;
}




