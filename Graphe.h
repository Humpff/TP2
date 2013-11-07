//! \file	Graphe.h
//! \brief	Définition de l'interface pour un graphe générique
//! \author	abder, thierry
//! \version	2.0 graphe template
//! \date	octobre 2013

#include <iostream>
#include <fstream>		// Pour les fichiers
#include <stdexcept>
#include <string>
#include <vector>

#ifndef GRAPHE__H
#define GRAPHE__H

//! \class	Graphe
//! \brief	Classe représentant un graphe orienté, coloré dont les étiquettes sont des comparables
template<typename Objet>
class Graphe
{
private:

	// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
	//	Classes internes
	// _________________________________________________________________________________________________


	class Arc;

	//! \class	Sommet
	//! \brief	Classe représentant un sommet dans un graphe
	class Sommet
	{
	public:

		//Constructeurs

		//!
		//! \brief Constructeur avec paramètres
		//!
		//! \param[in] Etiquette Les donnees d'un sommet
		//! \param[in] numero Le numero du sommet
		//! \post Le sommet est initialise avec les parametres

		Sommet(int numero, const Objet& Etiquette);

		/**
		 * \brief Constructeur par copie
		 * \param[in] source Le sommet à copier
		 * \post Copie profonde du sommet source
		 */

		Sommet(Sommet * source);

		//Destructeur
		/**
		 * \brief Destructeur
		 * \post Le sommet est detruit
		 */
		~Sommet();

		int m_numero; /**< Le numéro du sommet */
		Objet m_etiquette;

		Arc * m_listeDest; /**< La liste des arcs entre le sommet et les sommets qui lui sont adjacents */

		bool m_etat; /**< Pour marquer un routeur */
		Sommet * m_predecesseur; /**< Pour Dijkstra et Bellman-Ford */
		int m_cout; /**< Pour Dijkstra et Bellman-Ford */

		Sommet *m_precedent; /**< le sommet précédent dans la liste des sommets */
		Sommet *m_suivant; /**< Le prochain sommet dans la liste */
	};

	//! \class	Arc
	//! \brief	Classe interne représentant un arc entre deux sommets dans le graphe
	class Arc
	{
	public:

		Arc(Sommet * dest, int cout);
		~Arc();

		Sommet * m_dest; /**< Un pointeur sur le sommet de destination */
		int m_cout; /**< Le coût entre les deux sommets reliés par l'arc */
		Arc * m_suivDest; /**< Le prochain sommet de destination */
	};

public:

	// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
	//	Constructeurs et destructeur
	// _________________________________________________________________________________________________


	Graphe();
	Graphe(const Graphe &source);

	~Graphe();

	// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
	//	Ajout/suppression de sommets et d'arcs
	// _________________________________________________________________________________________________

	void ajouterSommet(int numero, const Objet& etiquette);
	void enleverSommet(int numero);

	void ajouterArc(int numOrigine, int numDestination, int cout);
	void enleverArc(int numOrigine, int numDestination);

	// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
	//	Données sur le graphe (incluant listes de sommets)
	// _________________________________________________________________________________________________

	int nombreSommets() const;
	bool estVide() const;
	std::vector<int> listerSommets() const;
	std::vector<Objet> listerEtiquetteSommets() const;

	// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
	//	Trouver numéro sommet
	// _________________________________________________________________________________________________

	int getNumeroSommet(const Objet& etiquette) const ;

	// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
	//	Données à propos des sommets
	// _________________________________________________________________________________________________

	bool sommetExiste(int numero) const;
	Objet getEtiquetteSommet(int numero) const ;
	int ordreSortieSommet(int numero) const ;
	int ordreEntreeSommet(int numero) const ;
	std::vector<int> listerSommetsAdjacents(int numeroSommetsAdjacents) const ;

	// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
	//	Données à propos des arcs
	// _________________________________________________________________________________________________

	bool arcExiste(int numOrigine, int numDestination) const;
	int getCoutArc(int numOrigine, int numDestination) const;

	// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
	//	Surcharge d'opérateurs
	// _________________________________________________________________________________________________

	const Graphe& operator =(const Graphe& source);
	template<class U> friend std::ostream& operator <<(std::ostream& out,
			const Graphe<U>& g);

	// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
	//	Fonctions plus complexes
	// _________________________________________________________________________________________________


	Graphe fermetureGraphe() const ;
	bool estFortementConnexe() const;
	void getComposantesFortementConnexes(
			std::vector<std::vector<Objet> > & composantes) const;
	int bellmanFord(const Objet& eOrigine, const Objet& eDestination,
			std::vector<Objet> & chemin);
	int dijkstra(const Objet& eOrigine, const Objet& eDestination,
			std::vector<Objet> & chemin);
	void getPointsArticulation(std::vector<Objet> & sommets);

private:

	// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
	//	Propriétés privées
	// _________________________________________________________________________________________________

	int nbSommets; /**< Le nombre de sommets dans le graphe */
	Sommet * listSommets; /**< Liste des sommets du graphe */

	// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
	//	Méthodes auxiliaires (getters)
	// _________________________________________________________________________________________________

	Sommet *_getSommet(int numero) const;
	Arc * _getArc(Sommet * sommet1, Sommet * sommet2) const;
	Arc * _getArc(int numOrigine, int numDestination) const;

	// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
	//	Méthodes auxiliaires (destruction + copie)
	// _________________________________________________________________________________________________

	void _detruireGraphe();
	void _copierGraphe(const Graphe &source);
	void _enleverSommet(Sommet * sommetAEnlever);

	// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
	//	Méthodes auxiliaires (path finding)
	// _________________________________________________________________________________________________

	void _initPathFinding(const Objet& eOrigine, const Objet& eDestination,
			Sommet * & origine, Sommet * & destination);
	void _recupererChemin(Sommet * destination, std::vector<Objet> & chemin);
	bool _isArticulation(Graphe<Objet> graphe, Sommet * sommet);

};
#include "Graphe.hpp"
#endif
