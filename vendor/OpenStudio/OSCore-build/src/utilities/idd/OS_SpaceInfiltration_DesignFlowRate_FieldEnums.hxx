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

#ifndef UTILITIES_IDD_OS_SPACEINFILTRATION_DESIGNFLOWRATE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_SPACEINFILTRATION_DESIGNFLOWRATE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_SpaceInfiltration_DesignFlowRateFields
 *  \brief Enumeration of OS:SpaceInfiltration:DesignFlowRate's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_SpaceInfiltration_DesignFlowRateFields, )
#else
class OS_SpaceInfiltration_DesignFlowRateFields: public ::EnumBase<OS_SpaceInfiltration_DesignFlowRateFields> {
 public: 
  enum domain 
  {
Handle, Name, SpaceorSpaceTypeName, ScheduleName, DesignFlowRateCalculationMethod, DesignFlowRate, FlowperSpaceFloorArea, FlowperExteriorSurfaceArea, AirChangesperHour, ConstantTermCoefficient, TemperatureTermCoefficient, VelocityTermCoefficient, VelocitySquaredTermCoefficient,   };
  OS_SpaceInfiltration_DesignFlowRateFields()
   : EnumBase<OS_SpaceInfiltration_DesignFlowRateFields>(Handle) {} 
  OS_SpaceInfiltration_DesignFlowRateFields(const std::string &t_name) 
   : EnumBase<OS_SpaceInfiltration_DesignFlowRateFields>(t_name) {} 
  OS_SpaceInfiltration_DesignFlowRateFields(int t_value) 
   : EnumBase<OS_SpaceInfiltration_DesignFlowRateFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_SpaceInfiltration_DesignFlowRateFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_SpaceInfiltration_DesignFlowRateFields>::value()); }
   private:
    friend class EnumBase<OS_SpaceInfiltration_DesignFlowRateFields>;
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
{ OS_SpaceInfiltration_DesignFlowRateFields::Handle, "Handle", "Handle"},
{ OS_SpaceInfiltration_DesignFlowRateFields::Name, "Name", "Name"},
{ OS_SpaceInfiltration_DesignFlowRateFields::SpaceorSpaceTypeName, "SpaceorSpaceTypeName", "Space or SpaceType Name"},
{ OS_SpaceInfiltration_DesignFlowRateFields::ScheduleName, "ScheduleName", "Schedule Name"},
{ OS_SpaceInfiltration_DesignFlowRateFields::DesignFlowRateCalculationMethod, "DesignFlowRateCalculationMethod", "Design Flow Rate Calculation Method"},
{ OS_SpaceInfiltration_DesignFlowRateFields::DesignFlowRate, "DesignFlowRate", "Design Flow Rate"},
{ OS_SpaceInfiltration_DesignFlowRateFields::FlowperSpaceFloorArea, "FlowperSpaceFloorArea", "Flow per Space Floor Area"},
{ OS_SpaceInfiltration_DesignFlowRateFields::FlowperExteriorSurfaceArea, "FlowperExteriorSurfaceArea", "Flow per Exterior Surface Area"},
{ OS_SpaceInfiltration_DesignFlowRateFields::AirChangesperHour, "AirChangesperHour", "Air Changes per Hour"},
{ OS_SpaceInfiltration_DesignFlowRateFields::ConstantTermCoefficient, "ConstantTermCoefficient", "Constant Term Coefficient"},
{ OS_SpaceInfiltration_DesignFlowRateFields::TemperatureTermCoefficient, "TemperatureTermCoefficient", "Temperature Term Coefficient"},
{ OS_SpaceInfiltration_DesignFlowRateFields::VelocityTermCoefficient, "VelocityTermCoefficient", "Velocity Term Coefficient"},
{ OS_SpaceInfiltration_DesignFlowRateFields::VelocitySquaredTermCoefficient, "VelocitySquaredTermCoefficient", "Velocity Squared Term Coefficient"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_SpaceInfiltration_DesignFlowRateFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_SpaceInfiltration_DesignFlowRateFields> OptionalOS_SpaceInfiltration_DesignFlowRateFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_SPACEINFILTRATION_DESIGNFLOWRATE_FIELDENUMS_HXX
