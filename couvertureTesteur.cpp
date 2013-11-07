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
  tp2::Couverture fcouv;

  CouvertureTest();
};

CouvertureTest::CouvertureTest()
{
  std::ifstream ifs("couverture.txt", std::ifstream::in);
  std::ifstream ifs2("couverture_fail.txt", std::ifstream::in);
  couv = tp2::Couverture(ifs);
  fcouv = tp2::Couverture(ifs2);
}

TEST_F(CouvertureTest, constructeurFichier)
{
  EXPECT_FALSE(couv.reqGraphe().estVide());
}

TEST_F(CouvertureTest, villesAccessibles)
{
  EXPECT_TRUE(couv.villesAccessibles());
  EXPECT_FALSE(fcouv.villesAccessibles());
}

TEST_F(CouvertureTest, villesCritiques)
{
  EXPECT_FALSE(couv.villesCritiques().empty());
}

TEST_F(CouvertureTest, dureeMinParcours)
{
  tp2::Ville depart("ville1", "a1");
  tp2::Ville arrivee("ville4", "d4");
  int duree;
  couv.determinerMinParcours(depart, arrivee, duree);
  EXPECT_EQ(duree, 90);
}

TEST_F(CouvertureTest, dureeMinParcoursImpossible)
{
  tp2::Ville depart("ville1", "a1");
  tp2::Ville arrivee("ville4", "d4");
  int duree;
  fcouv.determinerMinParcours(depart, arrivee, duree);
  EXPECT_EQ(duree, -1);
}

TEST_F(CouvertureTest, dureeMinParcoursException)
{
  tp2::Ville depart("ville1", "a1");
  tp2::Ville arrivee("ville7", "g7");
  int duree;
  EXPECT_THROW(couv.determinerMinParcours(depart, arrivee, duree), std::logic_error);
}

TEST_F(CouvertureTest, bellmanFord)
{
  tp2::Ville depart("ville1", "a1");
  tp2::Ville arrivee("ville4", "d4");
  int duree;
  couv.bellManFord(depart, arrivee, duree);
  EXPECT_EQ(duree, 90);
}

TEST_F(CouvertureTest, bellmanFordImpossible)
{
  tp2::Ville depart("ville1", "a1");
  tp2::Ville arrivee("ville4", "d4");
  int duree;
  fcouv.bellManFord(depart, arrivee, duree);
  EXPECT_EQ(duree, -1);
}

TEST_F(CouvertureTest, bellmanFordException)
{
  tp2::Ville depart("ville1", "a1");
  tp2::Ville arrivee("ville7", "g7");
  int duree;
  EXPECT_THROW(couv.bellManFord(depart, arrivee, duree), std::logic_error);
}

int main(int ac, char* av[])
{
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}
