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
