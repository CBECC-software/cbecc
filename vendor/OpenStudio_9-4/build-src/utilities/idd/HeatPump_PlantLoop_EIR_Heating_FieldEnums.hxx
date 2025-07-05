/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2020, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
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

#ifndef UTILITIES_IDD_HEATPUMP_PLANTLOOP_EIR_HEATING_FIELDENUMS_HXX
#define UTILITIES_IDD_HEATPUMP_PLANTLOOP_EIR_HEATING_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HeatPump_PlantLoop_EIR_HeatingFields
 *  \brief Enumeration of HeatPump:PlantLoop:EIR:Heating's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(HeatPump_PlantLoop_EIR_HeatingFields, )
#else
class HeatPump_PlantLoop_EIR_HeatingFields: public ::EnumBase<HeatPump_PlantLoop_EIR_HeatingFields> {
 public: 
  enum domain 
  {
Name, LoadSideInletNodeName, LoadSideOutletNodeName, CondenserType, SourceSideInletNodeName, SourceSideOutletNodeName, CompanionHeatPumpName, LoadSideReferenceFlowRate, SourceSideReferenceFlowRate, ReferenceCapacity, ReferenceCoefficientofPerformance, SizingFactor, CapacityModifierFunctionofTemperatureCurveName, ElectricInputtoOutputRatioModifierFunctionofTemperatureCurveName, ElectricInputtoOutputRatioModifierFunctionofPartLoadRatioCurveName,   };
  HeatPump_PlantLoop_EIR_HeatingFields()
   : EnumBase<HeatPump_PlantLoop_EIR_HeatingFields>(Name) {} 
  HeatPump_PlantLoop_EIR_HeatingFields(const std::string &t_name) 
   : EnumBase<HeatPump_PlantLoop_EIR_HeatingFields>(t_name) {} 
  HeatPump_PlantLoop_EIR_HeatingFields(int t_value) 
   : EnumBase<HeatPump_PlantLoop_EIR_HeatingFields>(t_value) {} 
  static std::string enumName() 
  { return "HeatPump_PlantLoop_EIR_HeatingFields"; }
  domain value() const { return static_cast<domain>(EnumBase<HeatPump_PlantLoop_EIR_HeatingFields>::value()); }
   private:
    friend class EnumBase<HeatPump_PlantLoop_EIR_HeatingFields>;
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
{ HeatPump_PlantLoop_EIR_HeatingFields::Name, "Name", "Name"},
{ HeatPump_PlantLoop_EIR_HeatingFields::LoadSideInletNodeName, "LoadSideInletNodeName", "Load Side Inlet Node Name"},
{ HeatPump_PlantLoop_EIR_HeatingFields::LoadSideOutletNodeName, "LoadSideOutletNodeName", "Load Side Outlet Node Name"},
{ HeatPump_PlantLoop_EIR_HeatingFields::CondenserType, "CondenserType", "Condenser Type"},
{ HeatPump_PlantLoop_EIR_HeatingFields::SourceSideInletNodeName, "SourceSideInletNodeName", "Source Side Inlet Node Name"},
{ HeatPump_PlantLoop_EIR_HeatingFields::SourceSideOutletNodeName, "SourceSideOutletNodeName", "Source Side Outlet Node Name"},
{ HeatPump_PlantLoop_EIR_HeatingFields::CompanionHeatPumpName, "CompanionHeatPumpName", "Companion Heat Pump Name"},
{ HeatPump_PlantLoop_EIR_HeatingFields::LoadSideReferenceFlowRate, "LoadSideReferenceFlowRate", "Load Side Reference Flow Rate"},
{ HeatPump_PlantLoop_EIR_HeatingFields::SourceSideReferenceFlowRate, "SourceSideReferenceFlowRate", "Source Side Reference Flow Rate"},
{ HeatPump_PlantLoop_EIR_HeatingFields::ReferenceCapacity, "ReferenceCapacity", "Reference Capacity"},
{ HeatPump_PlantLoop_EIR_HeatingFields::ReferenceCoefficientofPerformance, "ReferenceCoefficientofPerformance", "Reference Coefficient of Performance"},
{ HeatPump_PlantLoop_EIR_HeatingFields::SizingFactor, "SizingFactor", "Sizing Factor"},
{ HeatPump_PlantLoop_EIR_HeatingFields::CapacityModifierFunctionofTemperatureCurveName, "CapacityModifierFunctionofTemperatureCurveName", "Capacity Modifier Function of Temperature Curve Name"},
{ HeatPump_PlantLoop_EIR_HeatingFields::ElectricInputtoOutputRatioModifierFunctionofTemperatureCurveName, "ElectricInputtoOutputRatioModifierFunctionofTemperatureCurveName", "Electric Input to Output Ratio Modifier Function of Temperature Curve Name"},
{ HeatPump_PlantLoop_EIR_HeatingFields::ElectricInputtoOutputRatioModifierFunctionofPartLoadRatioCurveName, "ElectricInputtoOutputRatioModifierFunctionofPartLoadRatioCurveName", "Electric Input to Output Ratio Modifier Function of Part Load Ratio Curve Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const HeatPump_PlantLoop_EIR_HeatingFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<HeatPump_PlantLoop_EIR_HeatingFields> OptionalHeatPump_PlantLoop_EIR_HeatingFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HEATPUMP_PLANTLOOP_EIR_HEATING_FIELDENUMS_HXX
