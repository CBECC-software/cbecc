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

#ifndef UTILITIES_IDD_ROOMAIRSETTINGS_UNDERFLOORAIRDISTRIBUTIONINTERIOR_FIELDENUMS_HXX
#define UTILITIES_IDD_ROOMAIRSETTINGS_UNDERFLOORAIRDISTRIBUTIONINTERIOR_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class RoomAirSettings_UnderFloorAirDistributionInteriorFields
 *  \brief Enumeration of RoomAirSettings:UnderFloorAirDistributionInterior's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(RoomAirSettings_UnderFloorAirDistributionInteriorFields, )
#else
class RoomAirSettings_UnderFloorAirDistributionInteriorFields: public ::EnumBase<RoomAirSettings_UnderFloorAirDistributionInteriorFields> {
 public: 
  enum domain 
  {
ZoneName, NumberofDiffusers, PowerperPlume, DesignEffectiveAreaofDiffuser, DiffuserSlotAnglefromVertical, ThermostatHeight, ComfortHeight, TemperatureDifferenceThresholdforReporting, FloorDiffuserType, TransitionHeight, CoefficientA, CoefficientB, CoefficientC, CoefficientD, CoefficientE,   };
  RoomAirSettings_UnderFloorAirDistributionInteriorFields()
   : EnumBase<RoomAirSettings_UnderFloorAirDistributionInteriorFields>(ZoneName) {} 
  RoomAirSettings_UnderFloorAirDistributionInteriorFields(const std::string &t_name) 
   : EnumBase<RoomAirSettings_UnderFloorAirDistributionInteriorFields>(t_name) {} 
  RoomAirSettings_UnderFloorAirDistributionInteriorFields(int t_value) 
   : EnumBase<RoomAirSettings_UnderFloorAirDistributionInteriorFields>(t_value) {} 
  static std::string enumName() 
  { return "RoomAirSettings_UnderFloorAirDistributionInteriorFields"; }
  domain value() const { return static_cast<domain>(EnumBase<RoomAirSettings_UnderFloorAirDistributionInteriorFields>::value()); }
   private:
    friend class EnumBase<RoomAirSettings_UnderFloorAirDistributionInteriorFields>;
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
{ RoomAirSettings_UnderFloorAirDistributionInteriorFields::ZoneName, "ZoneName", "Zone Name"},
{ RoomAirSettings_UnderFloorAirDistributionInteriorFields::NumberofDiffusers, "NumberofDiffusers", "Number of Diffusers"},
{ RoomAirSettings_UnderFloorAirDistributionInteriorFields::PowerperPlume, "PowerperPlume", "Power per Plume"},
{ RoomAirSettings_UnderFloorAirDistributionInteriorFields::DesignEffectiveAreaofDiffuser, "DesignEffectiveAreaofDiffuser", "Design Effective Area of Diffuser"},
{ RoomAirSettings_UnderFloorAirDistributionInteriorFields::DiffuserSlotAnglefromVertical, "DiffuserSlotAnglefromVertical", "Diffuser Slot Angle from Vertical"},
{ RoomAirSettings_UnderFloorAirDistributionInteriorFields::ThermostatHeight, "ThermostatHeight", "Thermostat Height"},
{ RoomAirSettings_UnderFloorAirDistributionInteriorFields::ComfortHeight, "ComfortHeight", "Comfort Height"},
{ RoomAirSettings_UnderFloorAirDistributionInteriorFields::TemperatureDifferenceThresholdforReporting, "TemperatureDifferenceThresholdforReporting", "Temperature Difference Threshold for Reporting"},
{ RoomAirSettings_UnderFloorAirDistributionInteriorFields::FloorDiffuserType, "FloorDiffuserType", "Floor Diffuser Type"},
{ RoomAirSettings_UnderFloorAirDistributionInteriorFields::TransitionHeight, "TransitionHeight", "Transition Height"},
{ RoomAirSettings_UnderFloorAirDistributionInteriorFields::CoefficientA, "CoefficientA", "Coefficient A"},
{ RoomAirSettings_UnderFloorAirDistributionInteriorFields::CoefficientB, "CoefficientB", "Coefficient B"},
{ RoomAirSettings_UnderFloorAirDistributionInteriorFields::CoefficientC, "CoefficientC", "Coefficient C"},
{ RoomAirSettings_UnderFloorAirDistributionInteriorFields::CoefficientD, "CoefficientD", "Coefficient D"},
{ RoomAirSettings_UnderFloorAirDistributionInteriorFields::CoefficientE, "CoefficientE", "Coefficient E"},
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
  inline std::ostream &operator<<(std::ostream &os, const RoomAirSettings_UnderFloorAirDistributionInteriorFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<RoomAirSettings_UnderFloorAirDistributionInteriorFields> OptionalRoomAirSettings_UnderFloorAirDistributionInteriorFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ROOMAIRSETTINGS_UNDERFLOORAIRDISTRIBUTIONINTERIOR_FIELDENUMS_HXX
