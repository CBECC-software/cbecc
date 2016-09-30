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

#ifndef UTILITIES_IDD_ROOMAIRSETTINGS_UNDERFLOORAIRDISTRIBUTIONEXTERIOR_FIELDENUMS_HXX
#define UTILITIES_IDD_ROOMAIRSETTINGS_UNDERFLOORAIRDISTRIBUTIONEXTERIOR_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class RoomAirSettings_UnderFloorAirDistributionExteriorFields
 *  \brief Enumeration of RoomAirSettings:UnderFloorAirDistributionExterior's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(RoomAirSettings_UnderFloorAirDistributionExteriorFields, )
#else
class RoomAirSettings_UnderFloorAirDistributionExteriorFields: public ::EnumBase<RoomAirSettings_UnderFloorAirDistributionExteriorFields> {
 public: 
  enum domain 
  {
ZoneName, NumberofDiffusersperZone, PowerperPlume, DesignEffectiveAreaofDiffuser, DiffuserSlotAnglefromVertical, ThermostatHeight, ComfortHeight, TemperatureDifferenceThresholdforReporting, FloorDiffuserType, TransitionHeight, CoefficientAinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2, CoefficientBinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2, CoefficientCinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2, CoefficientDinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2, CoefficientEinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2,   };
  RoomAirSettings_UnderFloorAirDistributionExteriorFields()
   : EnumBase<RoomAirSettings_UnderFloorAirDistributionExteriorFields>(ZoneName) {} 
  RoomAirSettings_UnderFloorAirDistributionExteriorFields(const std::string &t_name) 
   : EnumBase<RoomAirSettings_UnderFloorAirDistributionExteriorFields>(t_name) {} 
  RoomAirSettings_UnderFloorAirDistributionExteriorFields(int t_value) 
   : EnumBase<RoomAirSettings_UnderFloorAirDistributionExteriorFields>(t_value) {} 
  static std::string enumName() 
  { return "RoomAirSettings_UnderFloorAirDistributionExteriorFields"; }
  domain value() const { return static_cast<domain>(EnumBase<RoomAirSettings_UnderFloorAirDistributionExteriorFields>::value()); }
   private:
    friend class EnumBase<RoomAirSettings_UnderFloorAirDistributionExteriorFields>;
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
{ RoomAirSettings_UnderFloorAirDistributionExteriorFields::ZoneName, "ZoneName", "Zone Name"},
{ RoomAirSettings_UnderFloorAirDistributionExteriorFields::NumberofDiffusersperZone, "NumberofDiffusersperZone", "Number of Diffusers per Zone"},
{ RoomAirSettings_UnderFloorAirDistributionExteriorFields::PowerperPlume, "PowerperPlume", "Power per Plume"},
{ RoomAirSettings_UnderFloorAirDistributionExteriorFields::DesignEffectiveAreaofDiffuser, "DesignEffectiveAreaofDiffuser", "Design Effective Area of Diffuser"},
{ RoomAirSettings_UnderFloorAirDistributionExteriorFields::DiffuserSlotAnglefromVertical, "DiffuserSlotAnglefromVertical", "Diffuser Slot Angle from Vertical"},
{ RoomAirSettings_UnderFloorAirDistributionExteriorFields::ThermostatHeight, "ThermostatHeight", "Thermostat Height"},
{ RoomAirSettings_UnderFloorAirDistributionExteriorFields::ComfortHeight, "ComfortHeight", "Comfort Height"},
{ RoomAirSettings_UnderFloorAirDistributionExteriorFields::TemperatureDifferenceThresholdforReporting, "TemperatureDifferenceThresholdforReporting", "Temperature Difference Threshold for Reporting"},
{ RoomAirSettings_UnderFloorAirDistributionExteriorFields::FloorDiffuserType, "FloorDiffuserType", "Floor Diffuser Type"},
{ RoomAirSettings_UnderFloorAirDistributionExteriorFields::TransitionHeight, "TransitionHeight", "Transition Height"},
{ RoomAirSettings_UnderFloorAirDistributionExteriorFields::CoefficientAinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2, "CoefficientAinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2", "Coefficient A in formula Kc = A*Gamma**B + C + D*Gamma + E*Gamma**2"},
{ RoomAirSettings_UnderFloorAirDistributionExteriorFields::CoefficientBinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2, "CoefficientBinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2", "Coefficient B in formula Kc = A*Gamma**B + C + D*Gamma + E*Gamma**2"},
{ RoomAirSettings_UnderFloorAirDistributionExteriorFields::CoefficientCinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2, "CoefficientCinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2", "Coefficient C in formula Kc = A*Gamma**B + C + D*Gamma + E*Gamma**2"},
{ RoomAirSettings_UnderFloorAirDistributionExteriorFields::CoefficientDinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2, "CoefficientDinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2", "Coefficient D in formula Kc = A*Gamma**B + C + D*Gamma + E*Gamma**2"},
{ RoomAirSettings_UnderFloorAirDistributionExteriorFields::CoefficientEinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2, "CoefficientEinformulaKc_EQUAL_A_TIMES_Gamma_POW_B_PLUS_C_PLUS_D_TIMES_Gamma_PLUS_E_TIMES_Gamma_POW_2", "Coefficient E in formula Kc = A*Gamma**B + C + D*Gamma + E*Gamma**2"},
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
  inline std::ostream &operator<<(std::ostream &os, const RoomAirSettings_UnderFloorAirDistributionExteriorFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<RoomAirSettings_UnderFloorAirDistributionExteriorFields> OptionalRoomAirSettings_UnderFloorAirDistributionExteriorFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ROOMAIRSETTINGS_UNDERFLOORAIRDISTRIBUTIONEXTERIOR_FIELDENUMS_HXX
