/**********************************************************************
*  Copyright (c) 2008-2016, Alliance for Sustainable Energy.
*  All rights reserved.
*
*  This library is free software; you can redistribute it and/or
*  modify it under the terms of the GNU Lesser General Public
*  License as published by the Free Software Foundation; either
*  version 2.1 of the License, or (at your option) any later version.
*
*  This library is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*  Lesser General Public License for more details.
*
*  You should have received a copy of the GNU Lesser General Public
*  License along with this library; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**********************************************************************/

#ifndef UTILITIES_IDD_WINDOWMATERIAL_GASMIXTURE_FIELDENUMS_HXX
#define UTILITIES_IDD_WINDOWMATERIAL_GASMIXTURE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class WindowMaterial_GasMixtureFields
 *  \brief Enumeration of WindowMaterial:GasMixture's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(WindowMaterial_GasMixtureFields, )
#else
class WindowMaterial_GasMixtureFields: public ::EnumBase<WindowMaterial_GasMixtureFields> {
 public: 
  enum domain 
  {
Name, Thickness, NumberofGasesinMixture, Gas1Type, Gas1Fraction, Gas2Type, Gas2Fraction, Gas3Type, Gas3Fraction, Gas4Type, Gas4Fraction,   };
  WindowMaterial_GasMixtureFields()
   : EnumBase<WindowMaterial_GasMixtureFields>(Name) {} 
  WindowMaterial_GasMixtureFields(const std::string &t_name) 
   : EnumBase<WindowMaterial_GasMixtureFields>(t_name) {} 
  WindowMaterial_GasMixtureFields(int t_value) 
   : EnumBase<WindowMaterial_GasMixtureFields>(t_value) {} 
  static std::string enumName() 
  { return "WindowMaterial_GasMixtureFields"; }
  domain value() const { return static_cast<domain>(EnumBase<WindowMaterial_GasMixtureFields>::value()); }
   private:
    friend class EnumBase<WindowMaterial_GasMixtureFields>;
    typedef std::pair<std::string, int> PT;
    typedef std::vector<PT> VecType;
    static VecType buildStringVec(bool isd)
    {
      struct evalue
      {
        int value; const char *name; const char *description;
      };
      const evalue a[] =
      {
{ WindowMaterial_GasMixtureFields::Name, "Name", "Name"},
{ WindowMaterial_GasMixtureFields::Thickness, "Thickness", "Thickness"},
{ WindowMaterial_GasMixtureFields::NumberofGasesinMixture, "NumberofGasesinMixture", "Number of Gases in Mixture"},
{ WindowMaterial_GasMixtureFields::Gas1Type, "Gas1Type", "Gas 1 Type"},
{ WindowMaterial_GasMixtureFields::Gas1Fraction, "Gas1Fraction", "Gas 1 Fraction"},
{ WindowMaterial_GasMixtureFields::Gas2Type, "Gas2Type", "Gas 2 Type"},
{ WindowMaterial_GasMixtureFields::Gas2Fraction, "Gas2Fraction", "Gas 2 Fraction"},
{ WindowMaterial_GasMixtureFields::Gas3Type, "Gas3Type", "Gas 3 Type"},
{ WindowMaterial_GasMixtureFields::Gas3Fraction, "Gas3Fraction", "Gas 3 Fraction"},
{ WindowMaterial_GasMixtureFields::Gas4Type, "Gas4Type", "Gas 4 Type"},
{ WindowMaterial_GasMixtureFields::Gas4Fraction, "Gas4Fraction", "Gas 4 Fraction"},
        { 0,0,0 }
      };
      VecType v;
      int i = 0;
      while (!(a[i].value == 0 && a[i].name == 0 && a[i].description == 0))
      {
        if (isd)
        {
          std::string description = a[i].description; 
          if (!description.empty())
          {
            v.push_back(PT(description, a[i].value));
          }
        } else {
          v.push_back(PT(a[i].name, a[i].value));
        }
        ++i;
      }
      return v;
    }
  
  };
  inline std::ostream &operator<<(std::ostream &os, const WindowMaterial_GasMixtureFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<WindowMaterial_GasMixtureFields> OptionalWindowMaterial_GasMixtureFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_WINDOWMATERIAL_GASMIXTURE_FIELDENUMS_HXX
