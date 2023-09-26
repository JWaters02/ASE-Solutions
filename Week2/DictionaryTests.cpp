#include <gtest/gtest.h>
#include <string>
#include "Dictionary.h"

void isPresent(Dictionary & dict, int k, const std::string& i)
{
    std::string* p_i = dict.lookup(k);
    assert(p_i);
    if (p_i)
    {
        ASSERT_EQ(*p_i, i);
    }
}

void isAbsent(Dictionary & dict, int k)
{
    ASSERT_EQ(dict.lookup(k), nullptr);
}

void insertTestData(Dictionary & dict)
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

////////////////////////////////////////////////////////////////////////////////

TEST(Lookup_Insert_Tests, EmptyLookup)
{
    Dictionary dict;
    isAbsent(dict,1);
}

TEST(Lookup_Insert_Tests, SingleInsert)
{
    Dictionary dict;
    dict.insert(22,  "Mary");
}

TEST(Lookup_Insert_Tests, SingleInsertLookup)
{
    Dictionary dict;
    dict.insert(22, "Mary");
    isPresent(dict,22,"Mary");
}

TEST(Lookup_Insert_Tests, SingleOverwriteLookup)
{
    Dictionary dict;
    dict.insert(22, "Jane");
    dict.insert(22, "Mary");
    isPresent(dict,22,"Mary");
}

TEST(Lookup_Insert_Tests, MultipleInsert)
{
    Dictionary dict;
    insertTestData(dict);
}

TEST(Lookup_Insert_Tests, MultipleInsertLookupPresent)
{
    Dictionary dict;
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
    Dictionary dict;
    insertTestData(dict);

    isAbsent(dict,2);
    isAbsent(dict,3);
    isAbsent(dict,-4);
    isAbsent(dict,56);
    isAbsent(dict,30);
}

////////////////////////////////////////////////////////////////////////////////