//! \file Ville.h
//! \brief interface de la classe Ville modélisant des villes où sont situés des aéroports
//! \author theud1
//! \version 0.1
//! \date 2013-10-03
//! une ville est caractérisée par son nom et le code de son aéroport
#ifndef VILLE_H_
#define VILLE_H_
#include <string>
#include <iostream>

namespace tp2
{

  class Ville
  {
  public:
    Ville(const std::string& p_nom,
	  const std::string& p_codeAeroport);
    std::string reqCodeAeroport() const;
    std::string reqNom() const;
    bool operator==(const Ville& p_ville) const;
    friend std::ostream& operator <<(std::ostream& out, const Ville& p_ville);
  private:
    std::string m_nom;
    std::string m_codeAeroport;
  };

  inline std::string Ville::reqCodeAeroport() const
  {
    return m_codeAeroport;
  }


  inline std::string Ville::reqNom() const
  {
    return m_nom;
  }

}

#endif /* VILLE_H_ */
