//! \file Ville.cpp
//! \brief implémentation de l'interface pour une ville
//! \author lorine, raphael
//! \version 0.1
//! \date 2013-11-06

#include "Ville.h"

namespace tp2
{
	Ville::Ville()
	: m_nom(""), m_codeAeroport("")
	{}
  //! \brief		Constructeur a partir du nom d'une ville et d'un code d'aeroport.
  //! \param[in]	p_nom nom d'une ville.
  //! \param[in]	p_codeAeroport code d'un aeroport.
  //! \post		Une ville est créée.
  Ville::Ville(std::string const& p_nom, std::string const& p_codeAeroport)
    : m_nom(p_nom), m_codeAeroport(p_codeAeroport)
  {}

  //! \brief		Surcharge de l'opérateur == qui compare deux villes.
  //! \param[in]	Une ville a comparer avec l'instance courante.
  //! \return		vrai si les villes sont identiques, sinon faux.
  bool Ville::operator==(Ville const& p_ville) const
  {
    if (p_ville.reqNom() == m_nom && p_ville.reqCodeAeroport() == m_codeAeroport)
      return true;
    return false;
  }

  //! \brief		Surcharge de l'opérateur << qui affiche les données d'une ville.
  //! \param[in]	Un stream.
  //! \param[in]	Une ville.
  //! \post		Les données de la ville sont affichées.
  std::ostream& operator<<(std::ostream& out, Ville const& p_ville)
  {
    out << p_ville.reqNom() << " " << p_ville.reqCodeAeroport();

    return out;
  }
}
