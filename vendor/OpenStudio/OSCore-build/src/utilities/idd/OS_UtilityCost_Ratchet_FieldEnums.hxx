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

#ifndef UTILITIES_IDD_OS_UTILITYCOST_RATCHET_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_UTILITYCOST_RATCHET_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_UtilityCost_RatchetFields
 *  \brief Enumeration of OS:UtilityCost:Ratchet's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_UtilityCost_RatchetFields, )
#else
class OS_UtilityCost_RatchetFields: public ::EnumBase<OS_UtilityCost_RatchetFields> {
 public: 
  enum domain 
  {
Handle, Name, TariffName, BaselineSourceVariable, AdjustmentSourceVariable, SeasonFrom, SeasonTo, MultiplierValueorVariableName, OffsetValueorVariableName,   };
  OS_UtilityCost_RatchetFields()
   : EnumBase<OS_UtilityCost_RatchetFields>(Handle) {} 
  OS_UtilityCost_RatchetFields(const std::string &t_name) 
   : EnumBase<OS_UtilityCost_RatchetFields>(t_name) {} 
  OS_UtilityCost_RatchetFields(int t_value) 
   : EnumBase<OS_UtilityCost_RatchetFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_UtilityCost_RatchetFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_UtilityCost_RatchetFields>::value()); }
   private:
    friend class EnumBase<OS_UtilityCost_RatchetFields>;
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
{ OS_UtilityCost_RatchetFields::Handle, "Handle", "Handle"},
{ OS_UtilityCost_RatchetFields::Name, "Name", "Name"},
{ OS_UtilityCost_RatchetFields::TariffName, "TariffName", "Tariff Name"},
{ OS_UtilityCost_RatchetFields::BaselineSourceVariable, "BaselineSourceVariable", "Baseline Source Variable"},
{ OS_UtilityCost_RatchetFields::AdjustmentSourceVariable, "AdjustmentSourceVariable", "Adjustment Source Variable"},
{ OS_UtilityCost_RatchetFields::SeasonFrom, "SeasonFrom", "Season From"},
{ OS_UtilityCost_RatchetFields::SeasonTo, "SeasonTo", "Season To"},
{ OS_UtilityCost_RatchetFields::MultiplierValueorVariableName, "MultiplierValueorVariableName", "Multiplier Value or Variable Name"},
{ OS_UtilityCost_RatchetFields::OffsetValueorVariableName, "OffsetValueorVariableName", "Offset Value or Variable Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_UtilityCost_RatchetFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_UtilityCost_RatchetFields> OptionalOS_UtilityCost_RatchetFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_UTILITYCOST_RATCHET_FIELDENUMS_HXX
