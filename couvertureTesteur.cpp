/*
 * couvertureTesteur.cpp
 *
 *  Created on: 2013-11-05
 *      Author: Administrateur
 */

#include <iostream>
#include <fstream>
#include <gtest/gtest.h>
#include "Couverture.h"

class CouvertureTest: public ::testing::Test
{
public:
  tp2::Couverture couv;

  CouvertureTest();
};

CouvertureTest::CouvertureTest()
{
  std::ifstream ifs("couverture.txt", std::ifstream::in);
  couv = tp2::Couverture(ifs);
}

TEST_F(CouvertureTest, constructeurFichier)
{
  EXPECT_FALSE(couv.reqGraphe().estVide());
}

TEST_F(CouvertureTest, villesAccessibles)
{
  EXPECT_TRUE(couv.villesAccessibles());
}

TEST_F(CouvertureTest, villesCritiques)
{
  EXPECT_FALSE(couv.villesCritiques().empty());
}

int main(int ac, char* av[])
{
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}
