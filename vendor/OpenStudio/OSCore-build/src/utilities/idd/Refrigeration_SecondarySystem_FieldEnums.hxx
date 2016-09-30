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

#ifndef UTILITIES_IDD_REFRIGERATION_SECONDARYSYSTEM_FIELDENUMS_HXX
#define UTILITIES_IDD_REFRIGERATION_SECONDARYSYSTEM_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Refrigeration_SecondarySystemFields
 *  \brief Enumeration of Refrigeration:SecondarySystem's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Refrigeration_SecondarySystemFields, )
#else
class Refrigeration_SecondarySystemFields: public ::EnumBase<Refrigeration_SecondarySystemFields> {
 public: 
  enum domain 
  {
Name, RefrigeratedCaseorWalkinorCaseAndWalkInListName, CirculatingFluidType, CirculatingFluidName, EvaporatorCapacity, EvaporatorFlowRateforSecondaryFluid, EvaporatorEvaporatingTemperature, EvaporatorApproachTemperatureDifference, EvaporatorRangeTemperatureDifference, NumberofPumpsinLoop, TotalPumpFlowRate, TotalPumpPower, TotalPumpHead, PhaseChangeCirculatingRate, PumpDriveType, VariableSpeedPumpCubicCurveName, PumpMotorHeattoFluid, SumUADistributionPiping, DistributionPipingZoneName, SumUAReceiver_SeparatorShell, Receiver_SeparatorZoneName, EvaporatorRefrigerantInventory, EndUseSubcategory,   };
  Refrigeration_SecondarySystemFields()
   : EnumBase<Refrigeration_SecondarySystemFields>(Name) {} 
  Refrigeration_SecondarySystemFields(const std::string &t_name) 
   : EnumBase<Refrigeration_SecondarySystemFields>(t_name) {} 
  Refrigeration_SecondarySystemFields(int t_value) 
   : EnumBase<Refrigeration_SecondarySystemFields>(t_value) {} 
  static std::string enumName() 
  { return "Refrigeration_SecondarySystemFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Refrigeration_SecondarySystemFields>::value()); }
   private:
    friend class EnumBase<Refrigeration_SecondarySystemFields>;
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
{ Refrigeration_SecondarySystemFields::Name, "Name", "Name"},
{ Refrigeration_SecondarySystemFields::RefrigeratedCaseorWalkinorCaseAndWalkInListName, "RefrigeratedCaseorWalkinorCaseAndWalkInListName", "Refrigerated Case or Walkin or CaseAndWalkInList Name"},
{ Refrigeration_SecondarySystemFields::CirculatingFluidType, "CirculatingFluidType", "Circulating Fluid Type"},
{ Refrigeration_SecondarySystemFields::CirculatingFluidName, "CirculatingFluidName", "Circulating Fluid Name"},
{ Refrigeration_SecondarySystemFields::EvaporatorCapacity, "EvaporatorCapacity", "Evaporator Capacity"},
{ Refrigeration_SecondarySystemFields::EvaporatorFlowRateforSecondaryFluid, "EvaporatorFlowRateforSecondaryFluid", "Evaporator Flow Rate for Secondary Fluid"},
{ Refrigeration_SecondarySystemFields::EvaporatorEvaporatingTemperature, "EvaporatorEvaporatingTemperature", "Evaporator Evaporating Temperature"},
{ Refrigeration_SecondarySystemFields::EvaporatorApproachTemperatureDifference, "EvaporatorApproachTemperatureDifference", "Evaporator Approach Temperature Difference"},
{ Refrigeration_SecondarySystemFields::EvaporatorRangeTemperatureDifference, "EvaporatorRangeTemperatureDifference", "Evaporator Range Temperature Difference"},
{ Refrigeration_SecondarySystemFields::NumberofPumpsinLoop, "NumberofPumpsinLoop", "Number of Pumps in Loop"},
{ Refrigeration_SecondarySystemFields::TotalPumpFlowRate, "TotalPumpFlowRate", "Total Pump Flow Rate"},
{ Refrigeration_SecondarySystemFields::TotalPumpPower, "TotalPumpPower", "Total Pump Power"},
{ Refrigeration_SecondarySystemFields::TotalPumpHead, "TotalPumpHead", "Total Pump Head"},
{ Refrigeration_SecondarySystemFields::PhaseChangeCirculatingRate, "PhaseChangeCirculatingRate", "PhaseChange Circulating Rate"},
{ Refrigeration_SecondarySystemFields::PumpDriveType, "PumpDriveType", "Pump Drive Type"},
{ Refrigeration_SecondarySystemFields::VariableSpeedPumpCubicCurveName, "VariableSpeedPumpCubicCurveName", "Variable Speed Pump Cubic Curve Name"},
{ Refrigeration_SecondarySystemFields::PumpMotorHeattoFluid, "PumpMotorHeattoFluid", "Pump Motor Heat to Fluid"},
{ Refrigeration_SecondarySystemFields::SumUADistributionPiping, "SumUADistributionPiping", "Sum UA Distribution Piping"},
{ Refrigeration_SecondarySystemFields::DistributionPipingZoneName, "DistributionPipingZoneName", "Distribution Piping Zone Name"},
{ Refrigeration_SecondarySystemFields::SumUAReceiver_SeparatorShell, "SumUAReceiver_SeparatorShell", "Sum UA Receiver/Separator Shell"},
{ Refrigeration_SecondarySystemFields::Receiver_SeparatorZoneName, "Receiver_SeparatorZoneName", "Receiver/Separator Zone Name"},
{ Refrigeration_SecondarySystemFields::EvaporatorRefrigerantInventory, "EvaporatorRefrigerantInventory", "Evaporator Refrigerant Inventory"},
{ Refrigeration_SecondarySystemFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
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
  inline std::ostream &operator<<(std::ostream &os, const Refrigeration_SecondarySystemFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Refrigeration_SecondarySystemFields> OptionalRefrigeration_SecondarySystemFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_REFRIGERATION_SECONDARYSYSTEM_FIELDENUMS_HXX
