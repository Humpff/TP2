#include "Ville.h"

namespace tp2
{
  Ville::Ville(std::string const& p_nom, std::string const& p_codeAeroport)
    : m_nom(p_nom), m_codeAeroport(p_codeAeroport)
  {}

  bool Ville::operator==(Ville const& p_ville) const
  {
    if (p_ville.reqNom() == m_nom && p_ville.reqCodeAeroport() == m_codeAeroport)
      return true;
    return false;
  }

  std::ostream& operator<<(std::ostream& out, Ville const& p_ville)
  {
    out << p_ville.reqNom() << " " << p_ville.reqCodeAeroport();

    return out;
  }
}
