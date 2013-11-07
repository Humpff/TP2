//! \file Couverture.cpp
//! \brief implémentation de l'interface pour une couverture aérienne
//! \author theud1
//! \version 0.1
//! \date 2013-10-03
#include <algorithm>
#include <stdexcept>
#include <string>
#include <fstream>
#include <iostream>
#include "Couverture.h"

namespace tp2
{
  //! \brief		Constructeur à partir d'un fichier en entrée.
  //! \param[in]	p_fichierEntree pointeur sur le fichier contenant la liste des villes à charger ainsi que les liaisons.
  //! \pre		Il y a assez de mémoire pour charger toutes les ville de la liste.
  //! \pre		Le fichier \a fichierEntree est ouvert corectement.
  //! \post		Le fichier \a fichierEntree n'est pas fermé par la fonction.
  //! \post		Si les préconditions sont respectées, les données de la couverture contenues
  //!				dans le fichier en entrée sont organisées dans un graphe en mémoire.
  //! \exception	bad_alloc si pas assez de mémoire contenir toute la liste du fichier.
  //! \exception	logic_error si le fichier \a fichierEntree n'est pas ouvert correctement.
  Couverture::Couverture(std::ifstream & p_fichierEntree)
  {
    if (p_fichierEntree == NULL)
      throw std::logic_error("Couverture: fichier non ouvert\n");

    //Lecture des données sur les villes
    std::string nom; //Pour le nom des villes
    std::string codeAeroport;
    int numero = 1;
    std::vector<std::string> tabNomVilles;

    bool sentinelle = false;

    while (!p_fichierEntree.eof() && sentinelle == false)
      {
	getline(p_fichierEntree, nom);
	if (nom == "$")//limite de la première partie du fichier
	  {
	    sentinelle = true;
	  }
	else
	  {
	    getline(p_fichierEntree, codeAeroport);
	    m_graphe.ajouterSommet(numero, Ville(nom, codeAeroport));
	    ++numero;
	    tabNomVilles.push_back(nom);
	  }
      }

    int dureeVol;
    std::string villeDestination;//nom de la ville de destination
    int indiceSource;
    int indiceDestination;
    char buff[255];
    std::vector<std::string>::iterator position;
    while (!p_fichierEntree.eof())
      {
	p_fichierEntree.getline(buff, 100);
	nom = buff;
	position = find(tabNomVilles.begin(), tabNomVilles.end(), nom);
	indiceSource = position - tabNomVilles.begin();
	p_fichierEntree.getline(buff, 100);
	villeDestination = buff;
	position = find(tabNomVilles.begin(), tabNomVilles.end(),
			villeDestination);
	indiceDestination = position - tabNomVilles.begin();
	p_fichierEntree >> dureeVol;
	p_fichierEntree.ignore();
	m_graphe.ajouterArc(indiceSource + 1, indiceDestination + 1, dureeVol);
      }
    //	cout << m_graphe;
  }

  Couverture::Couverture()
  {}

  Couverture& Couverture::operator=(Couverture const& p_couverture)
  {
    m_graphe = p_couverture.reqGraphe();

    return *this;
  }

  //! \brief		Affiche une liste de villes de la couverture à l'écran.
  //! \param[in]	p_vVilles		Une liste de villes dans un vector.
  //! \post		Le contenu de la liste p_vVilles est affiché.
  void Couverture::afficherVilles(std::vector<Ville> & p_vVilles)
  {
    if (p_vVilles.size() == 0)
      {
	std::cout << "La liste est vide\n";
      }
    else
      {
	for (unsigned int i = p_vVilles.size(); i > 0; i--)
	  {
	    std::cout << p_vVilles[i - 1] << std::endl;
	  }
      }
  }

  //! \brief		Détermine si toutes les villes de la couverture sont accessibles à partir de n'importe où.
  //! \pre		La couverture est non vide.
  //! \exception	logic_error si le graphe ne contient aucun sommet 
  //! \return		VRAI si toute ville est accessible depuis une autre, sinon FAUX dans tous les autres cas.
  bool Couverture::villesAccessibles()
  {
    if (m_graphe.estVide())
      throw std::logic_error("La couverture est vide.");
    return m_graphe.estFortementConnexe();
  }

  //! \brief		Trouve les points d'articulation de la couverture et les retourne.
  //! \pre		Il y a assez de mémoire pour retourner les points d'articulation.
  //! \post		Le graphe original reste inchangé.
  //! \return		La liste de tous les sommets d'articulation est retournée.
  //! \exception	bad_alloc s'il n'y a pas assez de mémoire pour retourner les noms des sommets.
  //! \exception	logic_error si la couverture ne contient aucune ville.
  std::vector<Ville> Couverture::villesCritiques()
  {
    if (m_graphe.estVide())
      throw std::logic_error("La couverture est vide.");
    try
      {
	std::vector<Ville> villesCritiques;
	m_graphe.getPointsArticulation(villesCritiques);

	return villesCritiques;
      }
    catch(...)
      {
	throw;
      }
  }

  //! \brief		Trouve le plus court chemin entre deux points en utilisant l'algorithme de Dijsktra et le retourne.
  //! \param[in]	p_origine la ville de l'origine.
  //! \param[in]	p_destination la ville de destination.
  //! \param[out]	p_duree le temps de vol total.
  //! \return		Un vecteur contenant la liste des villes a parcourir.
  //! \pre		Il y a assez de mémoire pour retourner les composantes du chemin.
  //! \post		Le temps de vol total est retourné, -1 s'il n'y a pas de chemin.
  //! \post		Le graphe original reste inchangé.
  //! \exception	bad_alloc s'il n'y a pas assez de mémoire pour retourner le chemin.
  //! \exception	logic_error si le sommet d'origine ou de destination n'existe pas.
  std::vector<Ville> Couverture::determinerMinParcours(const Ville & p_origine, const Ville & p_destination, int & p_duree)
  {
    if (m_graphe.estVide())
      throw std::logic_error("La couverture est vide.");
    try
      {
	std::vector<Ville> chemin;
	std::cout << "kikoo1" << std::endl;
	p_duree = m_graphe.dijkstra(p_origine, p_destination, chemin);
	std::cout << "kikoo2" << std::endl;
	if (chemin.empty())
	  p_duree = -1;

	return chemin;
      }
    catch(...)
      {
	throw;
      }
  }

  //! \brief		Trouve le plus court chemin entre deux points en utilisant l'algorithme de Bellman-Ford et le retourne.
  //! \param[in]	p_origine la ville de l'origine.
  //! \param[in]	p_destination la ville de destination.
  //! \param[out]	p_duree le temps de vol total.
  //! \return		Un vecteur contenant la liste des villes a parcourir.
  //! \pre		Il y a assez de mémoire pour retourner les composantes du chemin.
  //! \post		Le temps de vol total est retourné, -1 s'il n'y a pas de chemin.
  //! \post		Le graphe original reste inchangé.
  //! \exception	bad_alloc s'il n'y a pas assez de mémoire pour retourner le chemin.
  //! \exception	logic_error si le sommet d'origine ou de destination n'existe pas.
  std::vector<Ville> Couverture::bellManFord(const Ville & p_origine, const Ville & p_destination, int & p_duree)
  {
    if (m_graphe.estVide())
      throw std::logic_error("La couverture est vide.");
    try
      {
	std::vector<Ville> chemin;
	p_duree = m_graphe.bellmanFord(p_origine, p_destination, chemin);
	if (chemin.empty())
	  p_duree = -1;

	return chemin;
      }
    catch(...)
      {
	throw;
      }
  }

  //! \brief		Le getter du graphe des villes.
  //! \post		L'instance courante n'est pas modifiée.
  //! \return		Le graphe des villes faisant partie de la couverture.
  Graphe<Ville> const& Couverture::reqGraphe() const
  {
    return m_graphe;
  }
}//namespace tp2
