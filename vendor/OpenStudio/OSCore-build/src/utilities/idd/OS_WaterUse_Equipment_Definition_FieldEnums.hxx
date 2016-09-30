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

#ifndef UTILITIES_IDD_OS_WATERUSE_EQUIPMENT_DEFINITION_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_WATERUSE_EQUIPMENT_DEFINITION_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_WaterUse_Equipment_DefinitionFields
 *  \brief Enumeration of OS:WaterUse:Equipment:Definition's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_WaterUse_Equipment_DefinitionFields, )
#else
class OS_WaterUse_Equipment_DefinitionFields: public ::EnumBase<OS_WaterUse_Equipment_DefinitionFields> {
 public: 
  enum domain 
  {
Handle, Name, EndUseSubcategory, PeakFlowRate, TargetTemperatureScheduleName, SensibleFractionScheduleName, LatentFractionScheduleName,   };
  OS_WaterUse_Equipment_DefinitionFields()
   : EnumBase<OS_WaterUse_Equipment_DefinitionFields>(Handle) {} 
  OS_WaterUse_Equipment_DefinitionFields(const std::string &t_name) 
   : EnumBase<OS_WaterUse_Equipment_DefinitionFields>(t_name) {} 
  OS_WaterUse_Equipment_DefinitionFields(int t_value) 
   : EnumBase<OS_WaterUse_Equipment_DefinitionFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_WaterUse_Equipment_DefinitionFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_WaterUse_Equipment_DefinitionFields>::value()); }
   private:
    friend class EnumBase<OS_WaterUse_Equipment_DefinitionFields>;
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
{ OS_WaterUse_Equipment_DefinitionFields::Handle, "Handle", "Handle"},
{ OS_WaterUse_Equipment_DefinitionFields::Name, "Name", "Name"},
{ OS_WaterUse_Equipment_DefinitionFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
{ OS_WaterUse_Equipment_DefinitionFields::PeakFlowRate, "PeakFlowRate", "Peak Flow Rate"},
{ OS_WaterUse_Equipment_DefinitionFields::TargetTemperatureScheduleName, "TargetTemperatureScheduleName", "Target Temperature Schedule Name"},
{ OS_WaterUse_Equipment_DefinitionFields::SensibleFractionScheduleName, "SensibleFractionScheduleName", "Sensible Fraction Schedule Name"},
{ OS_WaterUse_Equipment_DefinitionFields::LatentFractionScheduleName, "LatentFractionScheduleName", "Latent Fraction Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_WaterUse_Equipment_DefinitionFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_WaterUse_Equipment_DefinitionFields> OptionalOS_WaterUse_Equipment_DefinitionFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_WATERUSE_EQUIPMENT_DEFINITION_FIELDENUMS_HXX
