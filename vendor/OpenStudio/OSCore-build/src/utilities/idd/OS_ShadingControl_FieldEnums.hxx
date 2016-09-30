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

#ifndef UTILITIES_IDD_OS_SHADINGCONTROL_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_SHADINGCONTROL_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_ShadingControlFields
 *  \brief Enumeration of OS:ShadingControl's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_ShadingControlFields, )
#else
class OS_ShadingControlFields: public ::EnumBase<OS_ShadingControlFields> {
 public: 
  enum domain 
  {
Handle, Name, ShadingType, ConstructionwithShadingName, ShadingDeviceMaterialName, ShadingControlType, ScheduleName, Setpoint, ShadingControlIsScheduled, GlareControlIsActive, TypeofSlatAngleControlforBlinds, SlatAngleScheduleName, Setpoint2,   };
  OS_ShadingControlFields()
   : EnumBase<OS_ShadingControlFields>(Handle) {} 
  OS_ShadingControlFields(const std::string &t_name) 
   : EnumBase<OS_ShadingControlFields>(t_name) {} 
  OS_ShadingControlFields(int t_value) 
   : EnumBase<OS_ShadingControlFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ShadingControlFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ShadingControlFields>::value()); }
   private:
    friend class EnumBase<OS_ShadingControlFields>;
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
{ OS_ShadingControlFields::Handle, "Handle", "Handle"},
{ OS_ShadingControlFields::Name, "Name", "Name"},
{ OS_ShadingControlFields::ShadingType, "ShadingType", "Shading Type"},
{ OS_ShadingControlFields::ConstructionwithShadingName, "ConstructionwithShadingName", "Construction with Shading Name"},
{ OS_ShadingControlFields::ShadingDeviceMaterialName, "ShadingDeviceMaterialName", "Shading Device Material Name"},
{ OS_ShadingControlFields::ShadingControlType, "ShadingControlType", "Shading Control Type"},
{ OS_ShadingControlFields::ScheduleName, "ScheduleName", "Schedule Name"},
{ OS_ShadingControlFields::Setpoint, "Setpoint", "Setpoint"},
{ OS_ShadingControlFields::ShadingControlIsScheduled, "ShadingControlIsScheduled", "Shading Control Is Scheduled"},
{ OS_ShadingControlFields::GlareControlIsActive, "GlareControlIsActive", "Glare Control Is Active"},
{ OS_ShadingControlFields::TypeofSlatAngleControlforBlinds, "TypeofSlatAngleControlforBlinds", "Type of Slat Angle Control for Blinds"},
{ OS_ShadingControlFields::SlatAngleScheduleName, "SlatAngleScheduleName", "Slat Angle Schedule Name"},
{ OS_ShadingControlFields::Setpoint2, "Setpoint2", "Setpoint 2"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ShadingControlFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ShadingControlFields> OptionalOS_ShadingControlFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_SHADINGCONTROL_FIELDENUMS_HXX
