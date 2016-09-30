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

#ifndef UTILITIES_IDD_FAN_CONSTANTVOLUME_FIELDENUMS_HXX
#define UTILITIES_IDD_FAN_CONSTANTVOLUME_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Fan_ConstantVolumeFields
 *  \brief Enumeration of Fan:ConstantVolume's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Fan_ConstantVolumeFields, )
#else
class Fan_ConstantVolumeFields: public ::EnumBase<Fan_ConstantVolumeFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, FanTotalEfficiency, PressureRise, MaximumFlowRate, MotorEfficiency, MotorInAirstreamFraction, AirInletNodeName, AirOutletNodeName, EndUseSubcategory,   };
  Fan_ConstantVolumeFields()
   : EnumBase<Fan_ConstantVolumeFields>(Name) {} 
  Fan_ConstantVolumeFields(const std::string &t_name) 
   : EnumBase<Fan_ConstantVolumeFields>(t_name) {} 
  Fan_ConstantVolumeFields(int t_value) 
   : EnumBase<Fan_ConstantVolumeFields>(t_value) {} 
  static std::string enumName() 
  { return "Fan_ConstantVolumeFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Fan_ConstantVolumeFields>::value()); }
   private:
    friend class EnumBase<Fan_ConstantVolumeFields>;
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
{ Fan_ConstantVolumeFields::Name, "Name", "Name"},
{ Fan_ConstantVolumeFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ Fan_ConstantVolumeFields::FanTotalEfficiency, "FanTotalEfficiency", "Fan Total Efficiency"},
{ Fan_ConstantVolumeFields::PressureRise, "PressureRise", "Pressure Rise"},
{ Fan_ConstantVolumeFields::MaximumFlowRate, "MaximumFlowRate", "Maximum Flow Rate"},
{ Fan_ConstantVolumeFields::MotorEfficiency, "MotorEfficiency", "Motor Efficiency"},
{ Fan_ConstantVolumeFields::MotorInAirstreamFraction, "MotorInAirstreamFraction", "Motor In Airstream Fraction"},
{ Fan_ConstantVolumeFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ Fan_ConstantVolumeFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ Fan_ConstantVolumeFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
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
  inline std::ostream &operator<<(std::ostream &os, const Fan_ConstantVolumeFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Fan_ConstantVolumeFields> OptionalFan_ConstantVolumeFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_FAN_CONSTANTVOLUME_FIELDENUMS_HXX
