/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2023, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
*  following conditions are met:
*
*  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
*  disclaimer.
*
*  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
*  disclaimer in the documentation and/or other materials provided with the distribution.
*
*  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote products
*  derived from this software without specific prior written permission from the respective party.
*
*  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative works
*  may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without specific prior
*  written permission from Alliance for Sustainable Energy, LLC.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND ANY CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
*  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S), ANY CONTRIBUTORS, THE UNITED STATES GOVERNMENT, OR THE UNITED
*  STATES DEPARTMENT OF ENERGY, NOR ANY OF THEIR EMPLOYEES, BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
*  USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
*  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
*  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_FAN_SYSTEMMODEL_FIELDENUMS_HXX
#define UTILITIES_IDD_FAN_SYSTEMMODEL_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Fan_SystemModelFields
 *  \brief Enumeration of Fan:SystemModel's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Fan_SystemModelFields, )
#else
class Fan_SystemModelFields: public ::EnumBase<Fan_SystemModelFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, AirInletNodeName, AirOutletNodeName, DesignMaximumAirFlowRate, SpeedControlMethod, ElectricPowerMinimumFlowRateFraction, DesignPressureRise, MotorEfficiency, MotorInAirStreamFraction, DesignElectricPowerConsumption, DesignPowerSizingMethod, ElectricPowerPerUnitFlowRate, ElectricPowerPerUnitFlowRatePerUnitPressure, FanTotalEfficiency, ElectricPowerFunctionofFlowFractionCurveName, NightVentilationModePressureRise, NightVentilationModeFlowFraction, MotorLossZoneName, MotorLossRadiativeFraction, EndUseSubcategory, NumberofSpeeds,   };
  Fan_SystemModelFields()
   : EnumBase<Fan_SystemModelFields>(Name) {} 
  Fan_SystemModelFields(const std::string &t_name) 
   : EnumBase<Fan_SystemModelFields>(t_name) {} 
  Fan_SystemModelFields(int t_value) 
   : EnumBase<Fan_SystemModelFields>(t_value) {} 
  static std::string enumName() 
  { return "Fan_SystemModelFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Fan_SystemModelFields>::value()); }
   private:
    friend class EnumBase<Fan_SystemModelFields>;
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
{ Fan_SystemModelFields::Name, "Name", "Name"},
{ Fan_SystemModelFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ Fan_SystemModelFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ Fan_SystemModelFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ Fan_SystemModelFields::DesignMaximumAirFlowRate, "DesignMaximumAirFlowRate", "Design Maximum Air Flow Rate"},
{ Fan_SystemModelFields::SpeedControlMethod, "SpeedControlMethod", "Speed Control Method"},
{ Fan_SystemModelFields::ElectricPowerMinimumFlowRateFraction, "ElectricPowerMinimumFlowRateFraction", "Electric Power Minimum Flow Rate Fraction"},
{ Fan_SystemModelFields::DesignPressureRise, "DesignPressureRise", "Design Pressure Rise"},
{ Fan_SystemModelFields::MotorEfficiency, "MotorEfficiency", "Motor Efficiency"},
{ Fan_SystemModelFields::MotorInAirStreamFraction, "MotorInAirStreamFraction", "Motor In Air Stream Fraction"},
{ Fan_SystemModelFields::DesignElectricPowerConsumption, "DesignElectricPowerConsumption", "Design Electric Power Consumption"},
{ Fan_SystemModelFields::DesignPowerSizingMethod, "DesignPowerSizingMethod", "Design Power Sizing Method"},
{ Fan_SystemModelFields::ElectricPowerPerUnitFlowRate, "ElectricPowerPerUnitFlowRate", "Electric Power Per Unit Flow Rate"},
{ Fan_SystemModelFields::ElectricPowerPerUnitFlowRatePerUnitPressure, "ElectricPowerPerUnitFlowRatePerUnitPressure", "Electric Power Per Unit Flow Rate Per Unit Pressure"},
{ Fan_SystemModelFields::FanTotalEfficiency, "FanTotalEfficiency", "Fan Total Efficiency"},
{ Fan_SystemModelFields::ElectricPowerFunctionofFlowFractionCurveName, "ElectricPowerFunctionofFlowFractionCurveName", "Electric Power Function of Flow Fraction Curve Name"},
{ Fan_SystemModelFields::NightVentilationModePressureRise, "NightVentilationModePressureRise", "Night Ventilation Mode Pressure Rise"},
{ Fan_SystemModelFields::NightVentilationModeFlowFraction, "NightVentilationModeFlowFraction", "Night Ventilation Mode Flow Fraction"},
{ Fan_SystemModelFields::MotorLossZoneName, "MotorLossZoneName", "Motor Loss Zone Name"},
{ Fan_SystemModelFields::MotorLossRadiativeFraction, "MotorLossRadiativeFraction", "Motor Loss Radiative Fraction"},
{ Fan_SystemModelFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
{ Fan_SystemModelFields::NumberofSpeeds, "NumberofSpeeds", "Number of Speeds"},
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
  inline std::ostream &operator<<(std::ostream &os, const Fan_SystemModelFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Fan_SystemModelFields> OptionalFan_SystemModelFields ;
#endif

/** \class Fan_SystemModelExtensibleFields
 *  \brief Enumeration of Fan:SystemModel's Idd and Idf extensible fields
 *  to be used in conjunction with ExtensibleIndex and ExtensibleGroup.
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer ExtensibleIndex.field indices. (The enumeration value names
 *  are more likely to be valid across EnergyPlus and OpenStudio releases, and will break
 *  if they become invalid.)See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Fan_SystemModelExtensibleFields, )
#else
class Fan_SystemModelExtensibleFields: public ::EnumBase<Fan_SystemModelExtensibleFields> {
 public: 
  enum domain 
  {
SpeedFlowFraction, SpeedElectricPowerFraction,   };
  Fan_SystemModelExtensibleFields()
   : EnumBase<Fan_SystemModelExtensibleFields>(SpeedFlowFraction) {} 
  Fan_SystemModelExtensibleFields(const std::string &t_name) 
   : EnumBase<Fan_SystemModelExtensibleFields>(t_name) {} 
  Fan_SystemModelExtensibleFields(int t_value) 
   : EnumBase<Fan_SystemModelExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "Fan_SystemModelExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Fan_SystemModelExtensibleFields>::value()); }
   private:
    friend class EnumBase<Fan_SystemModelExtensibleFields>;
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
{ Fan_SystemModelExtensibleFields::SpeedFlowFraction, "SpeedFlowFraction", "Speed Flow Fraction"},
{ Fan_SystemModelExtensibleFields::SpeedElectricPowerFraction, "SpeedElectricPowerFraction", "Speed Electric Power Fraction"},
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
  inline std::ostream &operator<<(std::ostream &os, const Fan_SystemModelExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Fan_SystemModelExtensibleFields> OptionalFan_SystemModelExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_FAN_SYSTEMMODEL_FIELDENUMS_HXX
