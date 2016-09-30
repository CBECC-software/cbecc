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

#ifndef UTILITIES_IDD_OS_UTILITYCOST_VARIABLE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_UTILITYCOST_VARIABLE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_UtilityCost_VariableFields
 *  \brief Enumeration of OS:UtilityCost:Variable's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_UtilityCost_VariableFields, )
#else
class OS_UtilityCost_VariableFields: public ::EnumBase<OS_UtilityCost_VariableFields> {
 public: 
  enum domain 
  {
Handle, Name, TariffName, VariableType, JanuaryValue, FebruaryValue, MarchValue, AprilValue, MayValue, JuneValue, JulyValue, AugustValue, SeptemberValue, OctoberValue, NovemberValue, DecemberValue,   };
  OS_UtilityCost_VariableFields()
   : EnumBase<OS_UtilityCost_VariableFields>(Handle) {} 
  OS_UtilityCost_VariableFields(const std::string &t_name) 
   : EnumBase<OS_UtilityCost_VariableFields>(t_name) {} 
  OS_UtilityCost_VariableFields(int t_value) 
   : EnumBase<OS_UtilityCost_VariableFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_UtilityCost_VariableFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_UtilityCost_VariableFields>::value()); }
   private:
    friend class EnumBase<OS_UtilityCost_VariableFields>;
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
{ OS_UtilityCost_VariableFields::Handle, "Handle", "Handle"},
{ OS_UtilityCost_VariableFields::Name, "Name", "Name"},
{ OS_UtilityCost_VariableFields::TariffName, "TariffName", "Tariff Name"},
{ OS_UtilityCost_VariableFields::VariableType, "VariableType", "Variable Type"},
{ OS_UtilityCost_VariableFields::JanuaryValue, "JanuaryValue", "January Value"},
{ OS_UtilityCost_VariableFields::FebruaryValue, "FebruaryValue", "February Value"},
{ OS_UtilityCost_VariableFields::MarchValue, "MarchValue", "March Value"},
{ OS_UtilityCost_VariableFields::AprilValue, "AprilValue", "April Value"},
{ OS_UtilityCost_VariableFields::MayValue, "MayValue", "May Value"},
{ OS_UtilityCost_VariableFields::JuneValue, "JuneValue", "June Value"},
{ OS_UtilityCost_VariableFields::JulyValue, "JulyValue", "July Value"},
{ OS_UtilityCost_VariableFields::AugustValue, "AugustValue", "August Value"},
{ OS_UtilityCost_VariableFields::SeptemberValue, "SeptemberValue", "September Value"},
{ OS_UtilityCost_VariableFields::OctoberValue, "OctoberValue", "October Value"},
{ OS_UtilityCost_VariableFields::NovemberValue, "NovemberValue", "November Value"},
{ OS_UtilityCost_VariableFields::DecemberValue, "DecemberValue", "December Value"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_UtilityCost_VariableFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_UtilityCost_VariableFields> OptionalOS_UtilityCost_VariableFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_UTILITYCOST_VARIABLE_FIELDENUMS_HXX
