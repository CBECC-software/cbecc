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

#ifndef UTILITIES_IDD_REFRIGERATION_COMPRESSORRACK_FIELDENUMS_HXX
#define UTILITIES_IDD_REFRIGERATION_COMPRESSORRACK_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Refrigeration_CompressorRackFields
 *  \brief Enumeration of Refrigeration:CompressorRack's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Refrigeration_CompressorRackFields, )
#else
class Refrigeration_CompressorRackFields: public ::EnumBase<Refrigeration_CompressorRackFields> {
 public: 
  enum domain 
  {
Name, HeatRejectionLocation, DesignCompressorRackCOP, CompressorRackCOPFunctionofTemperatureCurveName, DesignCondenserFanPower, CondenserFanPowerFunctionofTemperatureCurveName, CondenserType, WaterCooledCondenserInletNodeName, WaterCooledCondenserOutletNodeName, WaterCooledLoopFlowType, WaterCooledCondenserOutletTemperatureScheduleName, WaterCooledCondenserDesignFlowRate, WaterCooledCondenserMaximumFlowRate, WaterCooledCondenserMaximumWaterOutletTemperature, WaterCooledCondenserMinimumWaterInletTemperature, EvaporativeCondenserAvailabilityScheduleName, EvaporativeCondenserEffectiveness, EvaporativeCondenserAirFlowRate, BasinHeaterCapacity, BasinHeaterSetpointTemperature, DesignEvaporativeCondenserWaterPumpPower, EvaporativeWaterSupplyTankName, CondenserAirInletNodeName, EndUseSubcategory, RefrigerationCaseNameorWalkInNameorCaseAndWalkInListName, HeatRejectionZoneName,   };
  Refrigeration_CompressorRackFields()
   : EnumBase<Refrigeration_CompressorRackFields>(Name) {} 
  Refrigeration_CompressorRackFields(const std::string &t_name) 
   : EnumBase<Refrigeration_CompressorRackFields>(t_name) {} 
  Refrigeration_CompressorRackFields(int t_value) 
   : EnumBase<Refrigeration_CompressorRackFields>(t_value) {} 
  static std::string enumName() 
  { return "Refrigeration_CompressorRackFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Refrigeration_CompressorRackFields>::value()); }
   private:
    friend class EnumBase<Refrigeration_CompressorRackFields>;
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
{ Refrigeration_CompressorRackFields::Name, "Name", "Name"},
{ Refrigeration_CompressorRackFields::HeatRejectionLocation, "HeatRejectionLocation", "Heat Rejection Location"},
{ Refrigeration_CompressorRackFields::DesignCompressorRackCOP, "DesignCompressorRackCOP", "Design Compressor Rack COP"},
{ Refrigeration_CompressorRackFields::CompressorRackCOPFunctionofTemperatureCurveName, "CompressorRackCOPFunctionofTemperatureCurveName", "Compressor Rack COP Function of Temperature Curve Name"},
{ Refrigeration_CompressorRackFields::DesignCondenserFanPower, "DesignCondenserFanPower", "Design Condenser Fan Power"},
{ Refrigeration_CompressorRackFields::CondenserFanPowerFunctionofTemperatureCurveName, "CondenserFanPowerFunctionofTemperatureCurveName", "Condenser Fan Power Function of Temperature Curve Name"},
{ Refrigeration_CompressorRackFields::CondenserType, "CondenserType", "Condenser Type"},
{ Refrigeration_CompressorRackFields::WaterCooledCondenserInletNodeName, "WaterCooledCondenserInletNodeName", "Water-Cooled Condenser Inlet Node Name"},
{ Refrigeration_CompressorRackFields::WaterCooledCondenserOutletNodeName, "WaterCooledCondenserOutletNodeName", "Water-Cooled Condenser Outlet Node Name"},
{ Refrigeration_CompressorRackFields::WaterCooledLoopFlowType, "WaterCooledLoopFlowType", "Water-Cooled Loop Flow Type"},
{ Refrigeration_CompressorRackFields::WaterCooledCondenserOutletTemperatureScheduleName, "WaterCooledCondenserOutletTemperatureScheduleName", "Water-Cooled Condenser Outlet Temperature Schedule Name"},
{ Refrigeration_CompressorRackFields::WaterCooledCondenserDesignFlowRate, "WaterCooledCondenserDesignFlowRate", "Water-Cooled Condenser Design Flow Rate"},
{ Refrigeration_CompressorRackFields::WaterCooledCondenserMaximumFlowRate, "WaterCooledCondenserMaximumFlowRate", "Water-Cooled Condenser Maximum Flow Rate"},
{ Refrigeration_CompressorRackFields::WaterCooledCondenserMaximumWaterOutletTemperature, "WaterCooledCondenserMaximumWaterOutletTemperature", "Water-Cooled Condenser Maximum Water Outlet Temperature"},
{ Refrigeration_CompressorRackFields::WaterCooledCondenserMinimumWaterInletTemperature, "WaterCooledCondenserMinimumWaterInletTemperature", "Water-Cooled Condenser Minimum Water Inlet Temperature"},
{ Refrigeration_CompressorRackFields::EvaporativeCondenserAvailabilityScheduleName, "EvaporativeCondenserAvailabilityScheduleName", "Evaporative Condenser Availability Schedule Name"},
{ Refrigeration_CompressorRackFields::EvaporativeCondenserEffectiveness, "EvaporativeCondenserEffectiveness", "Evaporative Condenser Effectiveness"},
{ Refrigeration_CompressorRackFields::EvaporativeCondenserAirFlowRate, "EvaporativeCondenserAirFlowRate", "Evaporative Condenser Air Flow Rate"},
{ Refrigeration_CompressorRackFields::BasinHeaterCapacity, "BasinHeaterCapacity", "Basin Heater Capacity"},
{ Refrigeration_CompressorRackFields::BasinHeaterSetpointTemperature, "BasinHeaterSetpointTemperature", "Basin Heater Setpoint Temperature"},
{ Refrigeration_CompressorRackFields::DesignEvaporativeCondenserWaterPumpPower, "DesignEvaporativeCondenserWaterPumpPower", "Design Evaporative Condenser Water Pump Power"},
{ Refrigeration_CompressorRackFields::EvaporativeWaterSupplyTankName, "EvaporativeWaterSupplyTankName", "Evaporative Water Supply Tank Name"},
{ Refrigeration_CompressorRackFields::CondenserAirInletNodeName, "CondenserAirInletNodeName", "Condenser Air Inlet Node Name"},
{ Refrigeration_CompressorRackFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
{ Refrigeration_CompressorRackFields::RefrigerationCaseNameorWalkInNameorCaseAndWalkInListName, "RefrigerationCaseNameorWalkInNameorCaseAndWalkInListName", "Refrigeration Case Name or WalkIn Name or CaseAndWalkInList Name"},
{ Refrigeration_CompressorRackFields::HeatRejectionZoneName, "HeatRejectionZoneName", "Heat Rejection Zone Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Refrigeration_CompressorRackFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Refrigeration_CompressorRackFields> OptionalRefrigeration_CompressorRackFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_REFRIGERATION_COMPRESSORRACK_FIELDENUMS_HXX
