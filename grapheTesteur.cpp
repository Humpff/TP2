/*
 * grapheTesteur.cpp
 *
 *  Created on: 2013-11-05
 *      Author: Administrateur
 */

#include <iostream>
#include <gtest/gtest.h>
#include "Graphe.h"
class GrapheTest: public ::testing::Test
{
public:
	Graphe<int> graphe;
};

TEST_F(GrapheTest, constructeurVide)
{
  EXPECT_TRUE(graphe.nombreSommets() == 0);
  EXPECT_TRUE(graphe.estVide());
}

TEST_F(GrapheTest, ajoutSommet)
{
	graphe.ajouterSommet(0, 0);
	EXPECT_EQ(graphe.nombreSommets(), 1);
	EXPECT_FALSE(graphe.estVide());
}

TEST_F(GrapheTest, enlevSommet)
{
	graphe.ajouterSommet(0, 0);
	EXPECT_TRUE(graphe.sommetExiste(0));
	graphe.enleverSommet(0);
	EXPECT_EQ(graphe.nombreSommets(), 0);
	EXPECT_FALSE(graphe.sommetExiste(0));
}

TEST_F(GrapheTest, arc)
{
	graphe.ajouterSommet(0, 0);
	graphe.ajouterSommet(1, 10);
	graphe.ajouterArc(0, 1, 3);
	EXPECT_TRUE(graphe.arcExiste(0, 1));
	EXPECT_EQ(3, graphe.getCoutArc(0, 1));
}

TEST_F(GrapheTest, fermeture)
{
	graphe.ajouterSommet(0, 0);
	graphe.ajouterSommet(1, 10);
	graphe.ajouterSommet(2, 2);
	graphe.ajouterArc(0, 1, 0);
	graphe.ajouterArc(1, 2, 0);
	graphe.ajouterArc(2, 0, 0);

	graphe.fermetureGraphe();

	EXPECT_TRUE(graphe.estFortementConnexe());
}

TEST_F(GrapheTest, composantes)
{
	graphe.ajouterSommet(0, 0);
	graphe.ajouterSommet(1, 10);
	graphe.ajouterSommet(2, 2);
	graphe.ajouterSommet(3, 4);
	graphe.ajouterSommet(4, 5);
	graphe.ajouterArc(0, 1, 0);
	graphe.ajouterArc(1, 2, 1);
	graphe.ajouterArc(2, 0, 2);
	graphe.ajouterArc(2, 4, 2);
	graphe.ajouterArc(4, 3, 2);
	graphe.ajouterArc(3, 4, 6);
	std::vector<std::vector<int> > test;
	graphe.getComposantesFortementConnexes(test);
}

TEST_F(GrapheTest, bellman)
{
	graphe.ajouterSommet(0, 0);
	graphe.ajouterSommet(1, 10);
	graphe.ajouterSommet(2, 2);
	graphe.ajouterSommet(3, 4);
	graphe.ajouterSommet(4, 5);
	graphe.ajouterArc(0, 1, 0);
	graphe.ajouterArc(1, 2, 1);
	graphe.ajouterArc(2, 0, 2);
	graphe.ajouterArc(2, 4, 2);
	graphe.ajouterArc(4, 3, 2);
	graphe.ajouterArc(3, 4, 6);
	std::vector<int> test;
	graphe.bellmanFord(0, 5, test);
	graphe.dijkstra(0, 5, test);
	graphe.getPointsArticulation(test);
}
