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

#ifndef UTILITIES_IDD_UTILITYCOST_VARIABLE_FIELDENUMS_HXX
#define UTILITIES_IDD_UTILITYCOST_VARIABLE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class UtilityCost_VariableFields
 *  \brief Enumeration of UtilityCost:Variable's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(UtilityCost_VariableFields, )
#else
class UtilityCost_VariableFields: public ::EnumBase<UtilityCost_VariableFields> {
 public: 
  enum domain 
  {
Name, TariffName, VariableType, JanuaryValue, FebruaryValue, MarchValue, AprilValue, MayValue, JuneValue, JulyValue, AugustValue, SeptemberValue, OctoberValue, NovemberValue, DecemberValue,   };
  UtilityCost_VariableFields()
   : EnumBase<UtilityCost_VariableFields>(Name) {} 
  UtilityCost_VariableFields(const std::string &t_name) 
   : EnumBase<UtilityCost_VariableFields>(t_name) {} 
  UtilityCost_VariableFields(int t_value) 
   : EnumBase<UtilityCost_VariableFields>(t_value) {} 
  static std::string enumName() 
  { return "UtilityCost_VariableFields"; }
  domain value() const { return static_cast<domain>(EnumBase<UtilityCost_VariableFields>::value()); }
   private:
    friend class EnumBase<UtilityCost_VariableFields>;
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
{ UtilityCost_VariableFields::Name, "Name", "Name"},
{ UtilityCost_VariableFields::TariffName, "TariffName", "Tariff Name"},
{ UtilityCost_VariableFields::VariableType, "VariableType", "Variable Type"},
{ UtilityCost_VariableFields::JanuaryValue, "JanuaryValue", "January Value"},
{ UtilityCost_VariableFields::FebruaryValue, "FebruaryValue", "February Value"},
{ UtilityCost_VariableFields::MarchValue, "MarchValue", "March Value"},
{ UtilityCost_VariableFields::AprilValue, "AprilValue", "April Value"},
{ UtilityCost_VariableFields::MayValue, "MayValue", "May Value"},
{ UtilityCost_VariableFields::JuneValue, "JuneValue", "June Value"},
{ UtilityCost_VariableFields::JulyValue, "JulyValue", "July Value"},
{ UtilityCost_VariableFields::AugustValue, "AugustValue", "August Value"},
{ UtilityCost_VariableFields::SeptemberValue, "SeptemberValue", "September Value"},
{ UtilityCost_VariableFields::OctoberValue, "OctoberValue", "October Value"},
{ UtilityCost_VariableFields::NovemberValue, "NovemberValue", "November Value"},
{ UtilityCost_VariableFields::DecemberValue, "DecemberValue", "December Value"},
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
  inline std::ostream &operator<<(std::ostream &os, const UtilityCost_VariableFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<UtilityCost_VariableFields> OptionalUtilityCost_VariableFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_UTILITYCOST_VARIABLE_FIELDENUMS_HXX
