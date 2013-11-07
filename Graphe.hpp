//! \file Graphe.hpp
//! \brief Implémentation des méthodes définies dans Graphe.h
//! \author theud1
//! \version 0.1 graphe générique
//! \date 2013-10-03
#include "Graphe.h"
#include <limits>
//vous pouvez inclure d'autres librairies si c'est nécessaire

//! \brief		Surcharge de l'opérateur de sortie.
//! \param[in]	p_out		Le flux de sortie.
//! \param[in]	p_graphe		Le graphe à  afficher.
//! \return	Le flux de sortie.
//! \pre		l'étiquette est un objet comparable, l'opérateur << y est surchargé
//! \post		Le nombre de sommets du graphe sera affiché
//! \post		Pour chaque sommet, son numéro, son étiquette seront affichés
//! \post		Pour chaque sommet, tous ses liens, le numéro des voisins, seront affichés

template<typename Objet>
std::ostream& operator <<(std::ostream& p_out, const Graphe<Objet>& p_graphe)
{
	p_out << "Le graphe contient " << p_graphe.nbSommets << " sommet(s)" << std::endl;
	typename Graphe<Objet>::Sommet* vertex = p_graphe.listSommets;

	while (vertex != NULL)
	{
		p_out << "Sommet no " << vertex->m_numero << vertex->m_etiquette << std::endl;
		//Afficher les arcs.
		typename Graphe<Objet>::Arc* arc = vertex->m_listeDest;
		if (arc != NULL)
		{
			p_out << "Ce sommet a des liens vers le(s) sommet(s) : ";
			while (arc->m_suivDest != NULL)
			{
				p_out << arc->m_dest->m_numero << "(" << arc->m_cout << "), ";
				arc = arc->m_suivDest;
			}
			p_out << arc->m_dest->m_numero << "(" << arc->m_cout << ")";
		}
		p_out << std::endl;
		vertex = vertex->m_suivant;
	}

	return p_out;
}

template<typename Objet>
Graphe<Objet>::Sommet::Sommet(int numero, const Objet& Etiquette)
:m_numero(numero),m_etiquette(Etiquette), m_listeDest(0), m_etat(false), m_predecesseur(0),
 m_cout(0), m_precedent(0), m_suivant(0)
{

}

template<typename Objet>
Graphe<Objet>::Sommet::Sommet(Sommet * source)
{
	m_numero = source->m_numero;
	m_etiquette = source->m_etiquette;
	m_listeDest = source->m_listeDest;
	m_etat = source->m_etat;
	m_predecesseur = source->m_predecesseur;
	m_cout = source->m_cout;
	m_precedent = source->m_precedent;
	m_suivant = source->m_suivant;
}

template<typename Objet>
Graphe<Objet>::Arc::Arc(Sommet * dest, int cout)
:m_dest(dest),m_cout(cout),m_suivDest(0)
{

}

template<typename Objet>
Graphe<Objet>::Graphe()
:nbSommets(0),listSommets(0)
 {

 }

template<typename Objet>
Graphe<Objet>::Graphe(const Graphe &source)
{
	_copierGraphe(source);
}

template<typename Objet>
void Graphe<Objet>::_copierGraphe(const Graphe &source)
{
	nbSommets = source.nbSommets;
	listSommets = source.listSommets;
}

template<typename Objet>
Graphe<Objet>::~Graphe()
{

}

template<typename Objet>
typename Graphe<Objet>::Sommet * Graphe<Objet>::_getSommet(int numero) const
{
	Sommet * cur = listSommets;
	while (cur)
	{
		if (cur->m_numero == numero)
			return cur;
		cur = cur->m_suivant;
	}
	return 0;
}

template<typename Objet>
typename Graphe<Objet>::Arc * Graphe<Objet>::_getArc(int numOrigine, int numDestination) const
{
	Sommet * orig = _getSommet(numOrigine);
	Arc * cur = orig->m_listeDest;
	while (cur)
	{
		if (cur->m_dest->m_numero == numDestination)
			return cur;
		cur = cur->m_suivDest;
	}
	return 0;
}

template<typename Objet>
void Graphe<Objet>::ajouterSommet(int numero, const Objet& etiquette)
{
	Sommet *cur = listSommets;
	while (cur)
	{
		if (cur->m_numero == numero)
			throw std::logic_error("Numero deja present !");
		cur = cur->m_suivant;
	}
	Sommet *newSommet = new Sommet(numero, etiquette);
	if (listSommets)
	{
		newSommet->m_suivant = listSommets;
		listSommets->m_precedent = newSommet;
	}
	listSommets = newSommet;
	++nbSommets;
}

template<typename Objet>
void Graphe<Objet>::enleverSommet(int numero)
{
	if (this->sommetExiste(numero) == false)
		throw std::logic_error("Aucun sommet avec ce numero !");
	Sommet *curSommet = listSommets;
	Arc *curArc;
	Arc *prevArc;
	while (curSommet)
	{
		if (curSommet->m_numero == numero)
		{
			if (curSommet->m_precedent)
			{
				curSommet->m_precedent->m_suivant = curSommet->m_suivant;
				if (curSommet->m_suivant)
					curSommet->m_suivant->m_precedent = curSommet->m_precedent;
			}
			else if (curSommet->m_suivant)
			{
				listSommets = curSommet->m_suivant;
				listSommets->m_precedent = NULL;
			}
			else
				listSommets = NULL;
			while (curSommet->m_listeDest)
			{
				curArc = curSommet->m_listeDest;
				curSommet->m_listeDest = curSommet->m_listeDest->m_suivDest;
				free(curArc);
			}
		}
		else
		{
			curArc = curSommet->m_listeDest;
			prevArc = NULL;
			while (curArc)
			{
				if (curArc->m_dest->m_numero == numero)
				{
					if (prevArc)
						prevArc->m_suivDest = curArc->m_suivDest;
					else
						curSommet->m_listeDest = curArc->m_suivDest;
				}
				prevArc = curArc;
				curArc = curArc->m_suivDest;
			}
		}
		curSommet = curSommet->m_suivant;
	}
	--nbSommets;
}

template<typename Objet>
void Graphe<Objet>::ajouterArc(int numOrigine, int numDestination, int cout)
{
	if (this->sommetExiste(numOrigine) == false || sommetExiste(numDestination) == false)
		throw std::logic_error("Un de ces sommets n'existe pas !");
	if (this->arcExiste(numOrigine, numDestination))
		throw std::logic_error("Cet arc existe deja !");
	Sommet * orig = _getSommet(numOrigine);
	Sommet * dest = _getSommet(numDestination);
	Arc * newArc = new Arc(dest, cout);
	newArc->m_suivDest = orig->m_listeDest;
	orig->m_listeDest = newArc;
}

template<typename Objet>
void Graphe<Objet>::enleverArc(int numOrigine, int numDestination)
{
	if (this->sommetExiste(numOrigine) == false || sommetExiste(numDestination) == false)
		throw std::logic_error("Un de ces sommets n'existe pas !");
	if (this->arcExiste(numOrigine, numDestination) == false)
		throw std::logic_error("Cet arc n'existe pas !");
	Sommet * orig = _getSommet(numOrigine);
	Arc * curArc = orig->m_listeDest;
	Arc * prevArc = NULL;
	while (curArc)
	{
		if (curArc->m_dest->m_numero = numDestination)
		{
			if (prevArc)
				prevArc->m_suivDest = curArc->m_suivDest;
			else
				orig->m_listeDest = curArc->m_suivDest;
			return;
		}
		curArc = curArc->m_suivDest;
	}
}

template<typename Objet>
int Graphe<Objet>::nombreSommets() const
{
	return nbSommets;
}

template<typename Objet>
bool Graphe<Objet>::estVide() const
{
	return (nbSommets ? false : true);
}

template<typename Objet>
std::vector<int> Graphe<Objet>::listerSommets() const
{
	Sommet * cur = listSommets;
	std::vector<int> list;
	while (cur)
	{
		list.push_back(cur->m_numero);
		cur = cur->m_suivant;
	}
	return list;
}

template<typename Objet>
std::vector<Objet> Graphe<Objet>::listerEtiquetteSommets() const
{
	Sommet * cur = listSommets;
	std::vector<Objet> list;
	while (cur)
	{
		list.push_back(cur->m_etiquette);
		cur = cur->m_suivant;
	}
	return list;
}

template<typename Objet>
int Graphe<Objet>::getNumeroSommet(const Objet& etiquette) const
{
	Sommet * cur = listSommets;
	while (cur)
	{
		if (cur->m_etiquette == etiquette)
			return cur->m_numero;
		cur = cur->m_suivant;
	}
	throw std::logic_error("Ce sommet n'existe pas !");
}

template<typename Objet>
bool Graphe<Objet>::sommetExiste(int numero) const
{
	return _getSommet(numero) ? true : false;
}

template<typename Objet>
Objet Graphe<Objet>::getEtiquetteSommet(int numero) const
{
	if (this->sommetExiste(numero) == false)
		throw std::logic_error("Ce sommet n'existe pas !");
	return _getSommet(numero)->m_etiquette;
}

template<typename Objet>
int Graphe<Objet>::ordreSortieSommet(int numero) const
{
	return 0; // todo
}

template<typename Objet>
int Graphe<Objet>::ordreEntreeSommet(int numero) const
{
	return 0; // todo
}

template<typename Objet>
std::vector<int> Graphe<Objet>::listerSommetsAdjacents(int numeroSommetsAdjacents) const
{
	if (this->sommetExiste(numeroSommetsAdjacents) == false)
		throw std::logic_error("Ce sommet n'existe pas !");
	Sommet * sommet = _getSommet(numeroSommetsAdjacents);
	std::vector<int> list;
	Arc * cur = sommet->m_listeDest;
	while (cur)
	{
		list.push_back(cur->m_dest);
		cur = cur->m_suivDest;
	}
	return list;
}

template<typename Objet>
bool Graphe<Objet>::arcExiste(int numOrigine, int numDestination) const
{
	if (this->sommetExiste(numOrigine) == false || sommetExiste(numDestination) == false)
		throw std::logic_error("Un de ces sommets n'existe pas !");
	return _getArc(numOrigine, numDestination) ? true : false;
}

template<typename Objet>
int Graphe<Objet>::getCoutArc(int numOrigine, int numDestination) const
{
	if (this->sommetExiste(numOrigine) == false || sommetExiste(numDestination) == false)
		throw std::logic_error("Un de ces sommets n'existe pas !");
	if (this->arcExiste(numOrigine, numDestination) == false)
		throw std::logic_error("Cet arc n'existe pas !");
	return _getArc(numOrigine, numDestination)->m_cout;
}

template<typename Objet>
const Graphe<Objet>& Graphe<Objet>::operator =(const Graphe& source)
{
	_copierGraphe(source);
	return *this;
}

template<typename Objet>
Graphe<Objet> Graphe<Objet>::fermetureGraphe() const
{
	bool mat[nbSommets][nbSommets];
	std::vector<int> listeSommets = listerSommets();
	int a = 0;
	for (std::vector<int>::iterator i = listeSommets.begin(); i != listeSommets.end(); i++, a++)
	{
		int b = 0;
		for (std::vector<int>::iterator j = listeSommets.begin(); j != listeSommets.end(); j++, b++)
			mat[a][b] = arcExiste(*i, *j);
	}
	for (int k = 0; k < nbSommets; k++)
		for (int i = 0; i < nbSommets; i++)
			for (int j = 0; j < nbSommets; j++)
				mat[i][j] = mat[i][j] || (mat[i][k] && mat[k][j]);
	for (int i = 0; i < nbSommets; i++)
		std::cout << listeSommets[i] << " ";
	std::cout << std::endl;
	for (int i = 0; i < nbSommets; i++)
	{
		for (int j = 0; j < nbSommets; j++)
			std::cout << mat[i][j] << " ";
		std::cout << std::endl;
	}
	Graphe<Objet> fermeture;
	Sommet * cur = listSommets;
	while (cur)
	{
		fermeture.ajouterSommet(cur->m_numero, cur->m_etiquette);
		cur = cur->m_suivant;
	}
	for (int i = 0; i < nbSommets; i++)
	{
		for (int j = 0; j < nbSommets; j++)
		{
			if (mat[i][j])
				fermeture.ajouterArc(listeSommets[i], listeSommets[j], 0);
		}
	}
	return fermeture;
}

template<typename Objet>
bool Graphe<Objet>::estFortementConnexe() const
{
	Graphe<Objet> fermeture = fermetureGraphe();
	std::vector<int> listeSommets = fermeture.listerSommets();
	for(std::vector<int>::iterator it = listeSommets.begin(); it != listeSommets.end(); it++)
		for(std::vector<int>::iterator jt = listeSommets.begin(); jt != listeSommets.end(); jt++)
			if (!fermeture._getArc(*it, *jt))
				return false;
	return true;
}

template<typename Objet>
void Graphe<Objet>::getComposantesFortementConnexes(std::vector<std::vector<Objet> > & composantes) const
{
	Graphe<Objet> fermeture = fermetureGraphe();
	Sommet * cur = fermeture.listSommets;
	while (cur)
	{
		Arc * curArc = cur->m_listeDest;
		std::vector<Objet> curVec;
		curVec.push_back(cur->m_etiquette);
		while (curArc)
		{
			if (curArc->m_dest->m_numero != cur->m_numero && fermeture._getArc(curArc->m_dest->m_numero, cur->m_numero))
			{
				curVec.push_back(curArc->m_dest->m_etiquette);
				fermeture.enleverSommet(curArc->m_dest->m_numero);
			}
			curArc = curArc->m_suivDest;
		}
		composantes.push_back(curVec);
		cur = cur->m_suivant;
	}
}

template<typename Objet>
int Graphe<Objet>::bellmanFord(const Objet& eOrigine, const Objet& eDestination,std::vector<Objet> & chemin)
{
	if (this->sommetExiste(this->getNumeroSommet(eOrigine)) == false || sommetExiste(this->getNumeroSommet(eDestination)) == false)
		throw std::logic_error("Un de ces sommets n'existe pas !");
	Sommet * cur = listSommets;
	std::cout << "Start" << std::endl;
	while (cur)
	{
		cur->m_predecesseur = 0;
		if (cur->m_etiquette == eOrigine)
			cur->m_cout = 0;
		else
			cur->m_cout = -1;
		std::cout << cur->m_cout << std::endl;
		cur = cur->m_suivant;
	}
	std::cout << "Loop" << std::endl;
	for (int i = 0; i < nbSommets; i++)
	{
		cur = listSommets;
		while (cur)
		{
			Arc * curArc = cur->m_listeDest;
			while (curArc)
			{
				if (cur->m_cout >= 0 && (curArc->m_dest->m_cout < 0
				|| cur->m_cout + curArc->m_cout < curArc->m_dest->m_cout))
				{
					curArc->m_dest->m_cout = cur->m_cout + curArc->m_cout;
					curArc->m_dest->m_predecesseur = cur;
				}
				curArc = curArc->m_suivDest;
			}
			cur = cur->m_suivant;
		}
	}
	std::cout << *this << std::endl;
	cur = _getSommet(getNumeroSommet(eDestination));
	std::cout << cur->m_numero << " " << cur->m_cout << std::endl;
	int coutChemin = cur->m_cout;
	while (cur->m_predecesseur)
	{
		std::cout << cur->m_numero << " " << cur->m_cout << std::endl;
		chemin.push_back(cur->m_etiquette);
		cur = cur->m_predecesseur;
	}
	return coutChemin;
}

template<typename Objet>
int Graphe<Objet>::dijkstra(const Objet& eOrigine, const Objet& eDestination, std::vector<Objet> & chemin)
{
	if (this->sommetExiste(this->getNumeroSommet(eOrigine)) == false || sommetExiste(this->getNumeroSommet(eDestination)) == false)
		throw std::logic_error("Un de ces sommets n'existe pas !");
	Sommet * cur = listSommets;
	std::vector<Sommet *> queue;
	std::cout << "Start" << std::endl;
	while (cur)
	{
		cur->m_predecesseur = 0;
		cur->m_etat = false;
		if (cur->m_etiquette == eOrigine)
			cur->m_cout = 0;
		else
			cur->m_cout = -1;
		std::cout << cur->m_cout << std::endl;
		cur = cur->m_suivant;
	}
	queue.push_back(_getSommet(getNumeroSommet(eOrigine)));
	while (queue.empty() == false)
	{
		typename std::vector<Sommet *>::iterator itCur = queue.begin();
		for (typename std::vector<Sommet *>::iterator it = queue.begin(); it != queue.end(); it++)
		{
			if ((*it)->m_cout < (*itCur)->m_cout)
				itCur = it;
		}
		queue.erase(itCur);
		if ((*itCur)->m_etiquette == eDestination)
			break;
		(*itCur)->m_etat = true;
		Arc * curArc = (*itCur)->m_listeDest;
		while (curArc)
		{
			int curCout = (*itCur)->m_cout + curArc->m_cout;
			if (curArc->m_dest->m_etat == false && (curArc->m_dest->m_cout == -1 || curCout < curArc->m_dest->m_cout))
			{
				curArc->m_dest->m_cout = curCout;
				curArc->m_dest->m_predecesseur = *itCur;
				queue.push_back(curArc->m_dest);
			}
			curArc = curArc->m_suivDest;
		}
	}
	cur = _getSommet(getNumeroSommet(eDestination));
	std::cout << cur->m_numero << " " << cur->m_cout << std::endl;
	int coutChemin = cur->m_cout;
	while (cur->m_predecesseur)
	{
		std::cout << cur->m_numero << " " << cur->m_cout << std::endl;
		chemin.push_back(cur->m_etiquette);
		cur = cur->m_predecesseur;
	}
	return coutChemin;
}

template<typename Objet>
void Graphe<Objet>::getPointsArticulation(std::vector<Objet> & sommets)
{
	if (this->estFortementConnexe() == false)
		return;
	Graphe<Objet> copie(*this);
	Sommet * cur = copie.listSommets;
	while (cur)
	{
		if (_isArticulation(copie, cur))
			sommets.push_back(cur->m_etiquette);
		cur = cur->m_suivant;
	}
}

template<typename Objet>
bool Graphe<Objet>::_isArticulation(Graphe<Objet> graphe, Sommet * sommet)
{
	graphe.enleverSommet(sommet->m_numero);
	return graphe.estFortementConnexe() ? false : true;
}

//À compléter par les autres méthodes demandées sur le type Graphe
