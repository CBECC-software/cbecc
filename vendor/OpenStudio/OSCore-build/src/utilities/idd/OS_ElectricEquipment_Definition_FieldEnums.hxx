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

#ifndef UTILITIES_IDD_OS_ELECTRICEQUIPMENT_DEFINITION_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_ELECTRICEQUIPMENT_DEFINITION_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_ElectricEquipment_DefinitionFields
 *  \brief Enumeration of OS:ElectricEquipment:Definition's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_ElectricEquipment_DefinitionFields, )
#else
class OS_ElectricEquipment_DefinitionFields: public ::EnumBase<OS_ElectricEquipment_DefinitionFields> {
 public: 
  enum domain 
  {
Handle, Name, DesignLevelCalculationMethod, DesignLevel, WattsperSpaceFloorArea, WattsperPerson, FractionLatent, FractionRadiant, FractionLost,   };
  OS_ElectricEquipment_DefinitionFields()
   : EnumBase<OS_ElectricEquipment_DefinitionFields>(Handle) {} 
  OS_ElectricEquipment_DefinitionFields(const std::string &t_name) 
   : EnumBase<OS_ElectricEquipment_DefinitionFields>(t_name) {} 
  OS_ElectricEquipment_DefinitionFields(int t_value) 
   : EnumBase<OS_ElectricEquipment_DefinitionFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ElectricEquipment_DefinitionFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ElectricEquipment_DefinitionFields>::value()); }
   private:
    friend class EnumBase<OS_ElectricEquipment_DefinitionFields>;
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
{ OS_ElectricEquipment_DefinitionFields::Handle, "Handle", "Handle"},
{ OS_ElectricEquipment_DefinitionFields::Name, "Name", "Name"},
{ OS_ElectricEquipment_DefinitionFields::DesignLevelCalculationMethod, "DesignLevelCalculationMethod", "Design Level Calculation Method"},
{ OS_ElectricEquipment_DefinitionFields::DesignLevel, "DesignLevel", "Design Level"},
{ OS_ElectricEquipment_DefinitionFields::WattsperSpaceFloorArea, "WattsperSpaceFloorArea", "Watts per Space Floor Area"},
{ OS_ElectricEquipment_DefinitionFields::WattsperPerson, "WattsperPerson", "Watts per Person"},
{ OS_ElectricEquipment_DefinitionFields::FractionLatent, "FractionLatent", "Fraction Latent"},
{ OS_ElectricEquipment_DefinitionFields::FractionRadiant, "FractionRadiant", "Fraction Radiant"},
{ OS_ElectricEquipment_DefinitionFields::FractionLost, "FractionLost", "Fraction Lost"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ElectricEquipment_DefinitionFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ElectricEquipment_DefinitionFields> OptionalOS_ElectricEquipment_DefinitionFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_ELECTRICEQUIPMENT_DEFINITION_FIELDENUMS_HXX
