//! \file Graphe.hpp
//! \brief Implémentation des méthodes définies dans Graphe.h
//! \author theud1
//! \version 0.1 graphe générique
//! \date 2013-10-03

#include "Graphe.h"
#include <limits>

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

//! \brief Constructeur avec paramètres.
//! \param[in] numero Le numero du sommet.
//! \param[in] Etiquette L'etiquette du sommet.
//! \post Le graphe est construit.
template<typename Objet>
Graphe<Objet>::Sommet::Sommet(int numero, const Objet& Etiquette)
:m_numero(numero),m_etiquette(Etiquette), m_listeDest(0), m_etat(false), m_predecesseur(0),
 m_cout(0), m_precedent(0), m_suivant(0)
{

}

//! \brief Constructeur par copie.
//! \param[in] source Le graphe a copier.
//! \post Un graphe semblable a celui passe en parametre est construit.
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


//! \brief Constructeur avec paramètres.
//! \param[in] dest Le sommet de destination.
//! \param[in] cout Le poids de l'arc.
//! \post Un arc est construit.
template<typename Objet>
Graphe<Objet>::Arc::Arc(Sommet * dest, int cout)
:m_dest(dest),m_cout(cout),m_suivDest(0)
{

}

//! \brief Constructeur par defaut.
//! \post Un graphe vide est créé.
template<typename Objet>
Graphe<Objet>::Graphe()
:nbSommets(0),listSommets(0)
 {

 }

//! \brief Constructeur de copie.
//! \param[in] source La source du graphe à copier.
//! \pre Il y a assez de mémoire pour copier le graphe.
//! \exception bad_alloc Il n'y a pas assez de mémoire pour copier le graphe.
template<typename Objet>
Graphe<Objet>::Graphe(const Graphe &source)
{
	_copierGraphe(source);
}


//! \brief Copie d'un graphe
//! \post Une copie profonde à partir du graphe source a été effectuée.
//! \param[in] source Le graphe à copier.
template<typename Objet>
void Graphe<Objet>::_copierGraphe(const Graphe &source)
{
	nbSommets = 0;
	listSommets = 0;
	Sommet * cur = source.listSommets;
	while (cur)
	{
		this->ajouterSommet(cur->m_numero, cur->m_etiquette);
		cur = cur->m_suivant;
	}
	cur = source.listSommets;
	while (cur)
	{
		Arc * curArc = cur->m_listeDest;
		while (curArc)
		{
			this->ajouterArc(cur->m_numero, curArc->m_dest->m_numero, curArc->m_cout);
			curArc = curArc->m_suivDest;
		}
		cur = cur->m_suivant;
	}
}

//! \brief Destructeur
//! \post Le graphe est détruit.
template<typename Objet>
Graphe<Objet>::~Graphe()
{

}

//! \brief Trouve l'adresse d'un sommet à partir de son numéro.
//! \post L'adresse du sommet recherché est retournée.
//! \param[in] numero Le numéro du sommet.
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

//! \brief Trouve l'adresse d'un arc entre deux sommets.
//! \post L'adresse de l'arc recherché est retournée, 0 si aucun arc n'a été trouvé.
//! \param[in] origine L'adresse du sommet d'origine.
//! \param[in] destination L'adresse du sommet de destination.
//! \return L'adresse de l'arc trouvé entre le sommet d'origine et le sommet de destination.
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

//! \brief Ajout d'un sommet au graphe. 
//! \param[in] etiquette Les donnees du sommet à ajouter.
//! \param[in] numero Le numero du sommet à ajouter.
//! \pre Il y a assez de mémoire pour ajouter un sommet.
//! \pre Il n'y a aucun sommet avec le même numéro dans le graphe.
//! \post Un sommet contenant les informations passées en argument a été ajouté au Graphe.
//! \exception bad_alloc Il n'y a pas assez de mémoire pour ajouter un sommet.
//! \exception logic_error Il y a un sommet avec le même numéro dans le graphe.
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

//! \brief Enlève un sommet du graphe ainsi que tous les arcs qui vont et partent de ce sommet. 
//! \param[in] numero Le numéro du sommet à enlever.
//! \pre Il y a un sommet avec le numéro 'm_numero' dans le graphe.
//! \post Le sommet identifié par 'm_numero' a été enlevé du graphe.
//! \exception logic_error Il n'y a aucun sommet avec le numéro 'm_numero' dans le graphe.
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

//! \brief Ajout d'un arc au graphe.
//! \param[in] numOrigine Le numéro du sommet d'origine.
//! \param[in] numDestination Le numéro du sommet de destination.
//! \param[in] cout Le cout de l'arc.
//! \pre Les deux sommets doivent exister.
//! \post Un arc a été ajouté entre le sommet 'numeroOrigine' et le sommet 'numeroDestination'.
//! \exception bad_alloc Pas assez de mémoire pour alloué le nouvel arc.
//! \exception logic_error Un des deux sommets n'existe pas.
//! \exception logic_error Il y a déjà un arc orienté entre ces deux sommets.
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

//! \brief Enlève un arc du graphe.
//! \param[in] numOrigine Le numero du sommet d'origine.
//! \param[in] numDestination 	Le numéro du sommet de destination.
//! \pre Les deux sommets identifiés par leur numéro doivent appartenir au graphe.
//! \pre Un arc reliant les deux sommets doit exister.
//! \post Le graphe contient un arc en moins
//! \exception std::logic_error Un des deux sommets, ou les deux, n'existent pas.
//! \exception std::logic_error Il n'y a pas d'arc entre les 2 sommets.
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

//! \brief Retourne le nombre de sommets dans la liste des sommets. 
//! \return Le nombre de sommets dans le graphe.
//! \post Le graphe reste inchangé. 
template<typename Objet>
int Graphe<Objet>::nombreSommets() const
{
	return nbSommets;
}

//! \brief Indique si la liste des sommets est vide. 
//! \return True si le graphe ne contient pas de sommets, false autrement.
//! \post Le graphe reste inchangé.
template<typename Objet>
bool Graphe<Objet>::estVide() const
{
	return (nbSommets ? false : true);
}

//! \brief Retourne la liste des numéros des sommets dans un vecteur d'entiers.
//! \return Un vector de type int qui contient une liste de tous les numéros des sommets.
//! \post Le graphe reste inchangé.
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

//! \brief Retourne la liste des étiquettes des sommets dans un vecteur.
//! \return Un vector de type Objet qui contient une liste de toutes les étiquettes des sommets.
//! \post Le graphe reste inchangé. 
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

//! \brief Retourne le numéro d'un sommet selon son etiquette.
//! \param[in] etiquette L'étiquette d'un sommet.
//! \return Le numéro du sommet recherché 
//! \pre Le sommet doit faire partie du graphe.
//! \post Le graphe reste inchangé. 
//! \exception logic_error Le sommet n'existe pas.
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

//! \brief Retourne l'existence d'un sommet. 
//! \param[in] numero Le numéro du sommet.
//! \return True si le sommet existe, false autrement.
//! \post Le graphe reste inchangé.
template<typename Objet>
bool Graphe<Objet>::sommetExiste(int numero) const
{
	return _getSommet(numero) ? true : false;
}

//! \brief Retourne l'étiquette d'un sommet.
//! \param[in] numero Le numéro du sommet.
//! \return Le nom du sommet recherché.
//! \pre Le sommet doit exister.
//! \exception logic_error Il n'y a pas de sommets dans le graphe.
//! \exception logic_error Le sommet n'existe pas.
template<typename Objet>
Objet Graphe<Objet>::getEtiquetteSommet(int numero) const
{
	if (this->sommetExiste(numero) == false)
		throw std::logic_error("Ce sommet n'existe pas !");
	return _getSommet(numero)->m_etiquette;
}

//! \brief Le sommet n'existe pas.
//! \param[in] Le numéro du sommet.
//! \return L'odre de sortie d'un sommet.
//! \pre Le sommet doit exister.
//! \exception logic_error Le sommet n'existe pas.
template<typename Objet>
int Graphe<Objet>::ordreSortieSommet(int numero) const
{
	return 0; // todo
}

//! \brief Retourne l'ordre d'entrée d'un sommet.
//! \param[in] Le numéro du sommet.
//! \return L'odre d'entrée d'un sommet.
//! \pre Le sommet doit exister 
//! \post Le graphe reste inchangé. 
//! \exception logic_error Le sommet n'existe pas.
template<typename Objet>
int Graphe<Objet>::ordreEntreeSommet(int numero) const
{
	return 0; // todo
}

//! \brief Retourne la liste des numéros des sommets adjacents au sommet passé en argument dans un vecteur d'entiers.
//! \param[in] numeroSommetsAdjacents Le numéro du sommet dont on cherche les sommets adjacents.
//! \return Un vector de type int qui contient une liste de tous les numéros des sommets adjacents au sommet demandé.
//! \pre Le sommet doit appartenir au graphe.
//! \post Le graphe reste inchangé.
//! \exception logic_error si le sommet n'existe pas.
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

//! \brief Retourne l'existence d'un arc.
//! \param[in] numOrigine Le numéro du sommet d'origine.
//! \param[in] numDestination Le numéro du sommet de destination.
//! \return True si un arc existe entre les deux sommets, false autrement.
//! \pre Les sommets doivent appartenir au graphe.
//! \post Le graphe reste inchangé. 
//! \exception logic_error L'un ou l'autre, ou les 2 sommets ne font pas partie du graphe.
template<typename Objet>
bool Graphe<Objet>::arcExiste(int numOrigine, int numDestination) const
{
	if (this->sommetExiste(numOrigine) == false || sommetExiste(numDestination) == false)
		throw std::logic_error("Un de ces sommets n'existe pas !");
	return _getArc(numOrigine, numDestination) ? true : false;
}

//! \brief Retourne le coût d'un arc passé en argument.
//! \param[in] numOrigine Le numéro du sommet d'origine.
//! \param[in] numDestination Le numéro du sommet de destination.
//! \return Le coût de l'arc entre deux sommets.
//! \pre L'arc doit exister.
//! \post Le graphe reste inchangé. 
//! \exception logic_error Le sommet source et/ou destination n'existent pas.
//! \exception logic_error L'arc n'existe pas.
template<typename Objet>
int Graphe<Objet>::getCoutArc(int numOrigine, int numDestination) const
{
	if (this->sommetExiste(numOrigine) == false || sommetExiste(numDestination) == false)
		throw std::logic_error("Un de ces sommets n'existe pas !");
	if (this->arcExiste(numOrigine, numDestination) == false)
		throw std::logic_error("Cet arc n'existe pas !");
	return _getArc(numOrigine, numDestination)->m_cout;
}

//! \brief Surcharge de l'opérateur d'affectation.
//! \param[in] source Le graphe à copier.
//! \pre Il doit y avoir assez de mémoire.
//! \post Le graphe a un contenu identique à 'source'. 
//! \exception bad_alloc S'il n'y a pas assez de mémoire. 
template<typename Objet> 
const Graphe<Objet>& Graphe<Objet>::operator =(const Graphe& source)
{
	_copierGraphe(source);
	return *this;
}

//! \brief Déterminer la fermeture transitive du graphe.
//! \pre Le graphe est correctement initialisé.
//! \post La fermeture transitive du graphe est retournée. 
//! \post Le graphe original reste inchangé. 
//! \exception bad_alloc si pas assez de mémoire application de l'algorithme de Floyd-Warshall 
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
//	for (int i = 0; i < nbSommets; i++)
//		std::cout << listeSommets[i] << " ";
//	std::cout << std::endl;
//	for (int i = 0; i < nbSommets; i++)
//	{
//		for (int j = 0; j < nbSommets; j++)
//			std::cout << mat[i][j] << " ";
//		std::cout << std::endl;
//	}
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

//! \brief Détermine si le graphe est fortement connexe ou non.
//! \return true si le graphe est fortement connexe, false sinon 
//! \post true est retourné si le graphe est fortement connexe, false est retourné sinon.
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

//! \brief Détermine les composantes fortement connexes et les mémorise dans un conteneur passé en paramètre.
//! \param[in] composantes Les composantes du graphe.
//! \pre Il y a assez de mémoire pour placer les composantes fortements connexes dans 'composantes'.
//! \post Les composantes fortement connexes du graphe sont placées dans 'composantes'.
//! \exception Il n'y a pas assez de mémoire pour placer les composantes fortements connexes dans 'composantes'.
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

//! \brief Trouve le plus court chemin entre deux points en utilisant l'algorithme de Bellman-Ford et le retourne.
//! \param[in] eOrigine l'etiquette du sommet d'origine.
//! \param[in] eDestination l'etiquette du sommet de destination.
//! \param[out] chemin Un vector de type etiquette qui contient le chemin du parcours.
//! \return Le coût du parcours trouvé.
//! \pre Il y a assez de mémoire pour placer les composantes du chemin 'chemin'
//! \post Le cout total est retourné, -1 s'il n'y a pas de chemin
//! \post Le graphe original reste inchangé 
//! \post La liste des étiquettes des sommets à parcourir est retournée dans le vector 'chemin'
//! \exception bad_alloc Il n'y a pas assez de mémoire pour placer le chemin dans 'chemin'
//! \exception logic_error Le sommet d'origine ou de destination n'existe pas 
template<typename Objet>
int Graphe<Objet>::bellmanFord(const Objet& eOrigine, const Objet& eDestination,std::vector<Objet> & chemin)
{
	if (this->sommetExiste(this->getNumeroSommet(eOrigine)) == false || sommetExiste(this->getNumeroSommet(eDestination)) == false)
		throw std::logic_error("Un de ces sommets n'existe pas !");
	Sommet * cur = listSommets;
	while (cur)
	{
		cur->m_predecesseur = 0;
		if (cur->m_etiquette == eOrigine)
			cur->m_cout = 0;
		else
			cur->m_cout = -1;
		cur = cur->m_suivant;
	}
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
	cur = _getSommet(getNumeroSommet(eDestination));
	int coutChemin = cur->m_cout;
	while (cur->m_predecesseur)
	{
		chemin.push_back(cur->m_etiquette);
		cur = cur->m_predecesseur;
	}
	return coutChemin;
}

//! \brief Trouve le plus court chemin entre deux points en utilisant l'algorithme de Dijkstra et le retourne.
//! \param[in] eOrigine l'etiquette du sommet d'origine.
//! \param[in] eDestination l'etiquette du sommet de destination.
//! \param[out] chemin Un vector de type etiquette qui contient le chemin du parcours.
//! \return Le coût du parcours trouvé.
//! \pre Il y a assez de mémoire pour placer les composantes du chemin 'chemin'
//! \post Le cout total est retourné, -1 s'il n'y a pas de chemin
//! \post Le graphe original reste inchangé 
//! \post La liste des étiquettes des sommets à parcourir est retournée dans le vector 'chemin'
//! \exception bad_alloc Il n'y a pas assez de mémoire pour placer le chemin dans 'chemin'
//! \exception logic_error Le sommet d'origine ou de destination n'existe pas 
template<typename Objet>
int Graphe<Objet>::dijkstra(const Objet& eOrigine, const Objet& eDestination, std::vector<Objet> & chemin)
{
	if (this->sommetExiste(this->getNumeroSommet(eOrigine)) == false || sommetExiste(this->getNumeroSommet(eDestination)) == false)
		throw std::logic_error("Un de ces sommets n'existe pas !");
	Sommet * cur = listSommets;
	std::vector<Sommet *> queue;
	while (cur)
	{
		cur->m_predecesseur = 0;
		cur->m_etat = false;
		if (cur->m_etiquette == eOrigine)
			cur->m_cout = 0;
		else
			cur->m_cout = -1;
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
		Sommet * curSommet = *itCur;
		queue.erase(itCur);
		if ((curSommet)->m_etiquette == eDestination)
			break;
		(curSommet)->m_etat = true;
		Arc * curArc = (curSommet)->m_listeDest;
		while (curArc)
		{
			if (!(curSommet))
			  std::cout << "itCur est null" << std::endl;
			int curCout = (curSommet)->m_cout + curArc->m_cout;

			if (curArc->m_dest->m_etat == false && (curArc->m_dest->m_cout == -1 || curCout < curArc->m_dest->m_cout))
			{
				curArc->m_dest->m_cout = curCout;
				curArc->m_dest->m_predecesseur = curSommet;
				queue.push_back(curArc->m_dest);
			}
			curArc = curArc->m_suivDest;
		}
	}
	cur = _getSommet(getNumeroSommet(eDestination));
	int coutChemin = cur->m_cout;
	while (cur->m_predecesseur)
	{
		chemin.push_back(cur->m_etiquette);
		cur = cur->m_predecesseur;
	}
	return coutChemin;
}

//! \brief Trouve les points d'articulation du graphe et les retourne.
//! \param[out] sommets Un vector de type Objet qui contient tous les sommets d'articulation.
//! \pre Il y a assez de mémoire pour placer les sommets dans 'sommets'
//! \post La liste de tous les sommets d'articulation sont retournés dans le vector 'sommets' 
//! \post Le graphe original reste inchangé
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
