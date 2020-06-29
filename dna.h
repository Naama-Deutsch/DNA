#ifndef __DNA_H__
#define __DNA_H__
#include <cstring>
#include <string>
#include <iostream>
#include "myexceptoin.h"
#include <fstream>
#include <vector>
#include <iterator>
inline bool isValid(char nucleotide){
	return (nucleotide=='A' || nucleotide=='C' || nucleotide=='T' || nucleotide=='G');
	
}
class DnaSequence
{
private:	
	class Nucleotides
	{
	public:	
		
		Nucleotides() {}
		Nucleotides(char nucleotides);
		const Nucleotides& operator=(const Nucleotides& nucleotide);
		char getNucleotides() const;
		operator char();
	private:
		char m_nucleotide;
	};
	Nucleotides* m_dnaSequence;
	size_t m_length;
	void allocDna(const char* dnaSequence);
	std::string getAsString();
public:
	DnaSequence(const char* dnaSequence);
	DnaSequence(const std::string& dnaSequence);
	DnaSequence(std::fstream& myfile);
	DnaSequence(const DnaSequence &dnaSequence);
	const DnaSequence& operator=(const DnaSequence &dnaSequence);
	~DnaSequence();
	const DnaSequence::Nucleotides& operator[](size_t i) const;
	DnaSequence::Nucleotides& operator[](size_t i);
	size_t length()const;
	const Nucleotides* getDnaSequence()const;
	DnaSequence slicing(size_t start, size_t end);
	DnaSequence pairing();
	void writeToFolder(const std::string &fileName);
	size_t find(const std::string& subSeq);
	std::vector<size_t> findAll(const std::string& subSeq);
	size_t count(const std::string& subSeq);
	std::vector<DnaSequence> consensusSequences();
	friend std::ostream& operator<<(std::ostream& os, const Nucleotides& nucleotide);
};

bool operator==(const DnaSequence& dnaSequence,const DnaSequence& dnaSequence1);
bool operator!=(const DnaSequence& dnaSequence,const DnaSequence& dnaSequence1);
std::ostream& operator<<(std::ostream& os, const DnaSequence& dnaSequence);

inline DnaSequence::DnaSequence(const char* dnaSequence): m_dnaSequence(NULL),m_length(strlen(dnaSequence)) {
		allocDna(dnaSequence);
}

inline DnaSequence::DnaSequence(const std::string &dnaSequence): m_dnaSequence(NULL),m_length(dnaSequence.length()) {
		allocDna(dnaSequence.c_str());
}


	
inline DnaSequence::DnaSequence(const DnaSequence &dnaSequence) :m_dnaSequence(NULL),m_length(dnaSequence.length()){
	m_dnaSequence=new DnaSequence::Nucleotides[m_length];
	for (size_t i=0;i<m_length;i++)
	{
		m_dnaSequence[i]=dnaSequence.m_dnaSequence[i];
	}
}
	

inline DnaSequence::~DnaSequence(){
	delete[] m_dnaSequence;
	m_dnaSequence = NULL;
}

inline size_t DnaSequence::length()const{
	return m_length;
}

inline const DnaSequence::Nucleotides& DnaSequence::operator[](size_t i) const{
		/*if (i > strlen(m_dnaSequence))
		{
			throw not_matching_index();
		}*/
		return m_dnaSequence[i];
}

inline DnaSequence::Nucleotides& DnaSequence::operator[](size_t i){
		/*if (i > strlen(m_dnaSequence))
		{
			throw not_matching_index();
		}*/
		return m_dnaSequence[i];
}
inline const DnaSequence::Nucleotides* DnaSequence::getDnaSequence()const{
	return m_dnaSequence;
}

inline DnaSequence::Nucleotides::Nucleotides(char nucleotide):m_nucleotide(nucleotide){
	if(!isValid(nucleotide))
	{
		throw invalid_inputs();
	}

}
inline const DnaSequence::Nucleotides& DnaSequence::Nucleotides::operator=(const DnaSequence::Nucleotides& nucleotide){
	m_nucleotide=nucleotide.getNucleotides();
	return *this;
}

inline char DnaSequence::Nucleotides::getNucleotides()const{
	return m_nucleotide;
}

inline std::ostream& operator<<(std::ostream& os,const DnaSequence::Nucleotides& nucleotide){
	os<<nucleotide.getNucleotides();
	return os;
}
inline DnaSequence::Nucleotides::operator char(){
	return m_nucleotide;

}

inline std::string DnaSequence::getAsString(){
	std::string resStr;
	for (size_t i=0;i<m_length;i++)
	{
		resStr+=m_dnaSequence[i].getNucleotides();
	}
	return resStr;
	
}
#endif
