#include <gtest/gtest.h>
#include <string>
#include "Dictionary.h"

void isPresent(Dictionary<int, std::string>& dict, int k, const std::string& i)
{
    std::string* p_i = dict.lookup(k);
    assert(p_i);
    if (p_i)
    {
        ASSERT_EQ(*p_i, i);
    }
}

void isAbsent(Dictionary<int, std::string>& dict, int k)
{
    ASSERT_EQ(dict.lookup(k), nullptr);
}

void insertTestData(Dictionary<int, std::string>& dict)
{
    dict.insert(22, "Jane");
    dict.insert(22, "Mary");
    dict.insert(0, "Harold");
    dict.insert(9, "Edward");
    dict.insert(37, "Victoria");
    dict.insert(4, "Matilda");
    dict.insert(26, "Oliver");
    dict.insert(42, "Elizabeth");
    dict.insert(19, "Henry");
    dict.insert(4, "Stephen");
    dict.insert(24, "James");
    dict.insert(-1, "Edward");
    dict.insert(31, "Anne");
    dict.insert(23, "Elizabeth");
    dict.insert(1, "William");
    dict.insert(26, "Charles");
}

void accessLeftRotator(Dictionary<int, std::string>& dictionary)
{
    dictionary.rotateLeft(dictionary.root);
}

void accessRightRotator(Dictionary<int, std::string>& dictionary)
{
    dictionary.rotateRight(dictionary.root);
}

////////////////////////////////////////////////////////////////////////////////

TEST(Lookup_Insert_Tests, EmptyLookup)
{
    Dictionary<int, std::string> dict;
    isAbsent(dict,1);
}

TEST(Lookup_Insert_Tests, SingleInsert)
{
    Dictionary<int, std::string> dict;
    dict.insert(22,  "Mary");
}

TEST(Lookup_Insert_Tests, SingleInsertLookup)
{
    Dictionary<int, std::string> dict;
    dict.insert(22, "Mary");
    isPresent(dict,22,"Mary");
}

TEST(Lookup_Insert_Tests, SingleOverwriteLookup)
{
    Dictionary<int, std::string> dict;
    dict.insert(22, "Jane");
    dict.insert(22, "Mary");
    isPresent(dict,22,"Mary");
}

TEST(Lookup_Insert_Tests, MultipleInsert)
{
    Dictionary<int, std::string> dict;
    insertTestData(dict);
}

TEST(Lookup_Insert_Tests, MultipleInsertLookupPresent)
{
    Dictionary<int, std::string> dict;
    insertTestData(dict);

    isPresent(dict,22,"Mary");
    isPresent(dict,4,"Stephen");
    isPresent(dict,9,"Edward");
    isPresent(dict,1,"William");
    isPresent(dict,0,"Harold");
    isPresent(dict,24,"James");
    isPresent(dict,26,"Charles");
    isPresent(dict,19,"Henry");
    isPresent(dict,31,"Anne");
    isPresent(dict,23,"Elizabeth");
    isPresent(dict,37,"Victoria");
    isPresent(dict,42,"Elizabeth");
    isPresent(dict,-1,"Edward");
}

TEST(Lookup_Insert_Tests, MultipleInsertLookupAbsent)
{
    Dictionary<int, std::string> dict;
    insertTestData(dict);

    isAbsent(dict,2);
    isAbsent(dict,3);
    isAbsent(dict,-4);
    isAbsent(dict,56);
    isAbsent(dict,30);
}

////////////////////////////////////////////////////////////////////////////////

TEST(Remove_Tests, EmptyRemove)
{
    Dictionary<int, std::string> dict;
    dict.remove(43);
    isAbsent(dict,43);
}

TEST(Remove_Tests, RemoveChildlessRoot)
{
    Dictionary<int, std::string> dict;
    dict.insert(7,"John");
    dict.remove(7);
    isAbsent(dict,7);
}

TEST(Remove_Tests, RemoveLeftChildOfRoot)
{
    Dictionary<int, std::string> dict;
    dict.insert(31,"Anne");
    dict.insert(7,"John");
    dict.remove(7);

    isAbsent(dict,7);
    isPresent(dict,31,"Anne");
}

TEST(Remove_Tests, RemoveRightChildOfRoot)
{
    Dictionary<int, std::string> dict;
    dict.insert(7,"John");
    dict.insert(31,"Anne");
    dict.remove(31);

    isAbsent(dict,31);
    isPresent(dict,7,"John");
}

TEST(Remove_Tests, InsertMany_RemoveChildlessNodes)
{
    Dictionary<int, std::string> dict;
    insertTestData(dict);

    dict.remove(-1);
    isAbsent(dict,-1);

    dict.remove(1);
    isAbsent(dict,1);

    dict.remove(19);
    isAbsent(dict,19);

    dict.remove(23);
    isAbsent(dict,23);

    dict.remove(31);
    isAbsent(dict,31);

    dict.remove(42);
    isAbsent(dict,42);

    dict.remove(4);
    isAbsent(dict,4);

    isPresent(dict,22,"Mary");
    isPresent(dict,9,"Edward");
    isPresent(dict,0,"Harold");
    isPresent(dict,24,"James");
    isPresent(dict,26,"Charles");
    isPresent(dict,37,"Victoria");
}

TEST(Remove_Tests, OverwriteThenRemove)
{
    Dictionary<int, std::string> dict;
    dict.insert(22,"Jane");
    dict.insert(22,"Mary");
    dict.insert(4,"Matilda");
    dict.insert(26,"Oliver");
    dict.insert(4,"Stephen");
    dict.insert(26,"Charles");

    dict.remove(4);
    isAbsent(dict,4);

    dict.remove(26);
    isAbsent(dict,26);

    dict.remove(22);
    isAbsent(dict,22);
}

TEST(Remove_Tests, RemoveRootWithLeftChild)
{
    Dictionary<int, std::string> dict;
    dict.insert(31,"Anne");
    dict.insert(7,"John");
    dict.remove(31);

    isAbsent(dict,31);
    isPresent(dict,7,"John");
}

TEST(Remove_Tests, RemoveRootWithRightChild)
{
    Dictionary<int, std::string> dict;
    dict.insert(7,"John");
    dict.insert(31,"Anne");
    dict.remove(31);

    isAbsent(dict,31);
    isPresent(dict,7,"John");
}

TEST(Remove_Tests, InsertMany_RemoveNodesWithOneChild)
{
    Dictionary<int, std::string> dict;
    insertTestData(dict);

    dict.remove(4);
    isAbsent(dict,4);

    dict.remove(1);
    isAbsent(dict,1);

    dict.remove(9);
    isAbsent(dict,9);

    isPresent(dict,22,"Mary");
    isPresent(dict,0,"Harold");
    isPresent(dict,24,"James");
    isPresent(dict,26,"Charles");
    isPresent(dict,19,"Henry");
    isPresent(dict,31,"Anne");
    isPresent(dict,23,"Elizabeth");
    isPresent(dict,37,"Victoria");
    isPresent(dict,42,"Elizabeth");
    isPresent(dict,-1,"Edward");
}

TEST(Remove_Tests, RemoveRootWithChildren)
{
    Dictionary<int, std::string> dict;
    dict.insert(31,"Anne");
    dict.insert(7,"John");
    dict.insert(42,"Elizabeth");
    dict.remove(31);

    isAbsent(dict,31);
    isPresent(dict,7,"John");
    isPresent(dict,42,"Elizabeth");
}

TEST(Remove_Tests, InsertMany_RemoveNodesWithChildren)
{
    Dictionary<int, std::string> dict;
    insertTestData(dict);

    dict.remove(0);
    isAbsent(dict,0);

    dict.remove(37);
    isAbsent(dict,37);

    dict.remove(22);
    isAbsent(dict,22);

    isPresent(dict,4,"Stephen");
    isPresent(dict,9,"Edward");
    isPresent(dict,1,"William");
    isPresent(dict,24,"James");
    isPresent(dict,26,"Charles");
    isPresent(dict,19,"Henry");
    isPresent(dict,31,"Anne");
    isPresent(dict,23,"Elizabeth");
    isPresent(dict,42,"Elizabeth");
    isPresent(dict,-1,"Edward");
}

TEST(Remove_Tests, InsertMany_RemoveAbsent)
{
    Dictionary<int, std::string> dict;
    insertTestData(dict);

    dict.remove(6);
    isAbsent(dict,6);

    isPresent(dict,22,"Mary");
    isPresent(dict,4,"Stephen");
    isPresent(dict,9,"Edward");
    isPresent(dict,1,"William");
    isPresent(dict,0,"Harold");
    isPresent(dict,24,"James");
    isPresent(dict,26,"Charles");
    isPresent(dict,19,"Henry");
    isPresent(dict,31,"Anne");
    isPresent(dict,23,"Elizabeth");
    isPresent(dict,37,"Victoria");
    isPresent(dict,42,"Elizabeth");
    isPresent(dict,-1,"Edward");
}

////////////////////////////////////////////////////////////////////////////////

TEST(Copy_Constructor_Tests, CopyConstructorFullyCopies)
{
    Dictionary<int, std::string> dict1;
    insertTestData(dict1);

    Dictionary<int, std::string> dict2(dict1);

    isPresent(dict2,22,"Mary");
    isPresent(dict2,4,"Stephen");
    isPresent(dict2,9,"Edward");
    isPresent(dict2,1,"William");
    isPresent(dict2,0,"Harold");
    isPresent(dict2,24,"James");
    isPresent(dict2,26,"Charles");
    isPresent(dict2,19,"Henry");
    isPresent(dict2,31,"Anne");
    isPresent(dict2,23,"Elizabeth");
    isPresent(dict2,37,"Victoria");
    isPresent(dict2,42,"Elizabeth");
    isPresent(dict2,-1,"Edward");
}

TEST(Copy_Constructor_Tests, CopyConstructorDoesNotDeleteSource)
{
    Dictionary<int, std::string> dict1;
    insertTestData(dict1);

    Dictionary<int, std::string> dict2(dict1);

    isPresent(dict1,22,"Mary");
    isPresent(dict1,4,"Stephen");
    isPresent(dict1,9,"Edward");
    isPresent(dict1,1,"William");
    isPresent(dict1,0,"Harold");
    isPresent(dict1,24,"James");
    isPresent(dict1,26,"Charles");
    isPresent(dict1,19,"Henry");
    isPresent(dict1,31,"Anne");
    isPresent(dict1,23,"Elizabeth");
    isPresent(dict1,37,"Victoria");
    isPresent(dict1,42,"Elizabeth");
    isPresent(dict1,-1,"Edward");
}

TEST(Copy_Constructor_Tests, CopyConstructorIsDeep)
{
    Dictionary<int, std::string> dict1;
    insertTestData(dict1);

    Dictionary<int, std::string> dict2(dict1);

    dict1.insert(2,"William");
    isPresent(dict1,2,"William");
    isAbsent(dict2,2);

    dict2.insert(3,"Henry");
    isPresent(dict2,3,"Henry");
    isAbsent(dict1,3);

    dict1.remove(24);
    isAbsent(dict1,24);
    isPresent(dict2,24,"James");

    dict2.remove(26);
    isAbsent(dict2,26);
    isPresent(dict1,26,"Charles");
}

////////////////////////////////////////////////////////////////////////////////

TEST(Display_Entries_Test, StringStreamCheck)
{
    Dictionary<int, std::string> dict;
    dict.insert(22,"Jane");
    dict.insert(4,"Mary");

    std::stringstream actualOutputStream;
    dict.displayEntries(actualOutputStream);

    std::stringstream expectedOutputStream;
    expectedOutputStream << "22 Jane"        << std::endl;
    expectedOutputStream << "4 Mary"         << std::endl;
    ASSERT_EQ(actualOutputStream.str(), expectedOutputStream.str());
}

TEST(Display_Entries_Test, DisplayDoesNotIncludeOverwrittenItems)
{
    Dictionary<int, std::string> dict;
    dict.insert(22,"Mary");
    dict.insert(-12,"Aelfwynn");
    dict.insert(-12,"Aethelstan");
    dict.insert(31,"Anne");

    std::stringstream expectedOutputStream;
    expectedOutputStream << "31 Anne"        << std::endl;
    expectedOutputStream << "22 Mary"        << std::endl;
    expectedOutputStream << "-12 Aethelstan" << std::endl;

    std::stringstream actualOutputStream;
    dict.displayEntries(actualOutputStream);

    ASSERT_EQ(expectedOutputStream.str(), actualOutputStream.str());
}

////////////////////////////////////////////////////////////////////////////////

TEST(Rotate_Tests, LeftRotator)
{
    Dictionary<int, std::string> dict;
    insertTestData(dict);

    accessLeftRotator(dict);

    std::stringstream actualOutputStream;
    dict.displayEntries(actualOutputStream);

    std::stringstream expectedOutputStream;
    expectedOutputStream << "22 Mary"        << std::endl;
    expectedOutputStream << "37 Victoria"    << std::endl;
    expectedOutputStream << "42 Elizabeth"   << std::endl;
    expectedOutputStream << "26 Charles"     << std::endl;
    expectedOutputStream << "31 Anne"        << std::endl;
    expectedOutputStream << "24 James"       << std::endl;
    expectedOutputStream << "23 Elizabeth"   << std::endl;
    expectedOutputStream << "9 Edward"       << std::endl;
    expectedOutputStream << "19 Henry"       << std::endl;
    expectedOutputStream << "4 Stephen"      << std::endl;
    expectedOutputStream << "1 William"      << std::endl;
    expectedOutputStream << "0 Harold"       << std::endl;
    expectedOutputStream << "-1 Edward"      << std::endl;

    ASSERT_EQ(actualOutputStream.str(), expectedOutputStream.str());
}

TEST(Rotate_Tests, RightRotator)
{
    Dictionary<int, std::string> dict;
    insertTestData(dict);

    accessRightRotator(dict);

    std::stringstream actualOutputStream;
    dict.displayEntries(actualOutputStream);

    std::stringstream expectedOutputStream;
    expectedOutputStream << "42 Elizabeth"   << std::endl;
    expectedOutputStream << "37 Victoria"    << std::endl;
    expectedOutputStream << "22 Mary"        << std::endl;
    expectedOutputStream << "26 Charles"     << std::endl;
    expectedOutputStream << "31 Anne"        << std::endl;
    expectedOutputStream << "24 James"       << std::endl;
    expectedOutputStream << "23 Elizabeth"   << std::endl;
    expectedOutputStream << "0 Harold"       << std::endl;
    expectedOutputStream << "9 Edward"       << std::endl;
    expectedOutputStream << "19 Henry"       << std::endl;
    expectedOutputStream << "4 Stephen"      << std::endl;
    expectedOutputStream << "1 William"      << std::endl;
    expectedOutputStream << "-1 Edward"      << std::endl;

    ASSERT_EQ(actualOutputStream.str(), expectedOutputStream.str());
}

TEST(Rotate_Tests, LeftThenRightRotator)
{
    Dictionary<int, std::string> dict;
    insertTestData(dict);

    Dictionary<int, std::string> dict2(dict);

    accessLeftRotator(dict);
    accessRightRotator(dict);

    std::stringstream actualOutputStream;
    dict.displayEntries(actualOutputStream);

    std::stringstream ss2;
    dict2.displayEntries(ss2);

    ASSERT_EQ(actualOutputStream.str(), ss2.str());
}