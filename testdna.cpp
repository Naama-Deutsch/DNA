#include <iostream>
#include "dna.h"
#include <exception>
#include <gtest/gtest.h>


int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
TEST(BasicTest, Ctor)
{
 	DnaSequence dna1("ACTG");
    ASSERT_EQ(dna1,"ACTG");
}
TEST(BasicTest, CopyCtor)
{
 	DnaSequence dna1("AAAAAA");
    DnaSequence dna2(dna1);
    
    ASSERT_EQ(dna1,dna2);
}
TEST(BasicTest, AsmtOperator)
{
 	DnaSequence dna1("AAAAAA");
    DnaSequence dna2("AA");
    dna1=dna2;
    ASSERT_EQ(dna1,dna2);
}

TEST(BasicTest, Exception)
{
    ASSERT_THROW(DnaSequence dna("Naama"),invalid_inputs);
}

TEST(BasicTest, Length)
{

	DnaSequence dna("AAAAAAAA");
    ASSERT_EQ(dna.length(),8);
}

TEST(BasicTest, Equal)
{

	DnaSequence dna1("ACTG");
    DnaSequence dna2("ACTG");
    ASSERT_TRUE(dna1==dna2);
}
TEST(BasicTest, NotEqual)
{

	DnaSequence dna1("ACTG");
    DnaSequence dna2("ACTG");
    ASSERT_FALSE(dna1!=dna2);
}
TEST(BasicTest, OsrteamOperator)
{

	DnaSequence dna1("ACTGACTG");
    ASSERT_TRUE(std::cout<<dna1<<std::endl);
}
TEST(NonMemberTest, IndexOperator)
{

	DnaSequence dna1("ACTG");
    DnaSequence dna2("ACTTT");
    ASSERT_EQ((char)dna1[2],(char)dna2[4]);
}
TEST(NonMemberTest, IndexOperator2)
{

	DnaSequence dna1("ACTG");
    ASSERT_EQ((char)dna1[2],'T');
}
TEST(NonMemberTest, Slice)
{

	DnaSequence dna1("ACTG");
    DnaSequence dna2("ACTACTGTT");
    ASSERT_EQ(dna1,dna2.slicing(3,7));
}
TEST(MoreTest, Count)
{

	DnaSequence dna1("ATGGATGATGGGCGGTATG");
    ASSERT_EQ(dna1.count("AT"),4);
}
TEST(MoreTest, Find)
{
	DnaSequence dna1("ATGGATGATGGGCGGTATG");
    ASSERT_EQ(dna1.find("ATGA"),4);
}
TEST(MoreTest, FindAll)
{
	DnaSequence dna1("ATGGATGATGGGCGGTATG");
    ASSERT_EQ(dna1.findAll("AT")[1],4);
}
/*TEST(MoreTest, ConsenSusSequences)
{
	DnaSequence dna1("ATGTTTTAATGTAA");
    ASSERT_EQ(dna1.consensusSequences()[0],"A");
}*/
