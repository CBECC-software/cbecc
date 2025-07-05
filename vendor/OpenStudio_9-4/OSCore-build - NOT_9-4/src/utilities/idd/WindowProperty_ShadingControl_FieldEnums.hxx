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

#ifndef UTILITIES_IDD_WINDOWPROPERTY_SHADINGCONTROL_FIELDENUMS_HXX
#define UTILITIES_IDD_WINDOWPROPERTY_SHADINGCONTROL_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class WindowProperty_ShadingControlFields
 *  \brief Enumeration of WindowProperty:ShadingControl's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(WindowProperty_ShadingControlFields, )
#else
class WindowProperty_ShadingControlFields: public ::EnumBase<WindowProperty_ShadingControlFields> {
 public: 
  enum domain 
  {
Name, ShadingType, ConstructionwithShadingName, ShadingControlType, ScheduleName, Setpoint, ShadingControlIsScheduled, GlareControlIsActive, ShadingDeviceMaterialName, TypeofSlatAngleControlforBlinds, SlatAngleScheduleName, Setpoint2,   };
  WindowProperty_ShadingControlFields()
   : EnumBase<WindowProperty_ShadingControlFields>(Name) {} 
  WindowProperty_ShadingControlFields(const std::string &t_name) 
   : EnumBase<WindowProperty_ShadingControlFields>(t_name) {} 
  WindowProperty_ShadingControlFields(int t_value) 
   : EnumBase<WindowProperty_ShadingControlFields>(t_value) {} 
  static std::string enumName() 
  { return "WindowProperty_ShadingControlFields"; }
  domain value() const { return static_cast<domain>(EnumBase<WindowProperty_ShadingControlFields>::value()); }
   private:
    friend class EnumBase<WindowProperty_ShadingControlFields>;
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
{ WindowProperty_ShadingControlFields::Name, "Name", "Name"},
{ WindowProperty_ShadingControlFields::ShadingType, "ShadingType", "Shading Type"},
{ WindowProperty_ShadingControlFields::ConstructionwithShadingName, "ConstructionwithShadingName", "Construction with Shading Name"},
{ WindowProperty_ShadingControlFields::ShadingControlType, "ShadingControlType", "Shading Control Type"},
{ WindowProperty_ShadingControlFields::ScheduleName, "ScheduleName", "Schedule Name"},
{ WindowProperty_ShadingControlFields::Setpoint, "Setpoint", "Setpoint"},
{ WindowProperty_ShadingControlFields::ShadingControlIsScheduled, "ShadingControlIsScheduled", "Shading Control Is Scheduled"},
{ WindowProperty_ShadingControlFields::GlareControlIsActive, "GlareControlIsActive", "Glare Control Is Active"},
{ WindowProperty_ShadingControlFields::ShadingDeviceMaterialName, "ShadingDeviceMaterialName", "Shading Device Material Name"},
{ WindowProperty_ShadingControlFields::TypeofSlatAngleControlforBlinds, "TypeofSlatAngleControlforBlinds", "Type of Slat Angle Control for Blinds"},
{ WindowProperty_ShadingControlFields::SlatAngleScheduleName, "SlatAngleScheduleName", "Slat Angle Schedule Name"},
{ WindowProperty_ShadingControlFields::Setpoint2, "Setpoint2", "Setpoint 2"},
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
  inline std::ostream &operator<<(std::ostream &os, const WindowProperty_ShadingControlFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<WindowProperty_ShadingControlFields> OptionalWindowProperty_ShadingControlFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_WINDOWPROPERTY_SHADINGCONTROL_FIELDENUMS_HXX
