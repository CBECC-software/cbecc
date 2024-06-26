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

#ifndef UTILITIES_IDD_OS_REFRIGERATION_GASCOOLER_AIRCOOLED_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_REFRIGERATION_GASCOOLER_AIRCOOLED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Refrigeration_GasCooler_AirCooledFields
 *  \brief Enumeration of OS:Refrigeration:GasCooler:AirCooled's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Refrigeration_GasCooler_AirCooledFields, )
#else
class OS_Refrigeration_GasCooler_AirCooledFields: public ::EnumBase<OS_Refrigeration_GasCooler_AirCooledFields> {
 public: 
  enum domain 
  {
Handle, Name, RatedTotalHeatRejectionRateCurveName, GasCoolerFanSpeedControlType, RatedFanPower, MinimumFanAirFlowRatio, TransitionTemperature, TranscriticalApproachTemperature, SubcriticalTemperatureDifference, MinimumCondensingTemperature, AirInletNodeName, EndUseSubcategory, GasCoolerRefrigerantOperatingChargeInventory, GasCoolerReceiverRefrigerantInventory, GasCoolerOutletPipingRefrigerantInventory,   };
  OS_Refrigeration_GasCooler_AirCooledFields()
   : EnumBase<OS_Refrigeration_GasCooler_AirCooledFields>(Handle) {} 
  OS_Refrigeration_GasCooler_AirCooledFields(const std::string &t_name) 
   : EnumBase<OS_Refrigeration_GasCooler_AirCooledFields>(t_name) {} 
  OS_Refrigeration_GasCooler_AirCooledFields(int t_value) 
   : EnumBase<OS_Refrigeration_GasCooler_AirCooledFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Refrigeration_GasCooler_AirCooledFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Refrigeration_GasCooler_AirCooledFields>::value()); }
   private:
    friend class EnumBase<OS_Refrigeration_GasCooler_AirCooledFields>;
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
{ OS_Refrigeration_GasCooler_AirCooledFields::Handle, "Handle", "Handle"},
{ OS_Refrigeration_GasCooler_AirCooledFields::Name, "Name", "Name"},
{ OS_Refrigeration_GasCooler_AirCooledFields::RatedTotalHeatRejectionRateCurveName, "RatedTotalHeatRejectionRateCurveName", "Rated Total Heat Rejection Rate Curve Name"},
{ OS_Refrigeration_GasCooler_AirCooledFields::GasCoolerFanSpeedControlType, "GasCoolerFanSpeedControlType", "Gas Cooler Fan Speed Control Type"},
{ OS_Refrigeration_GasCooler_AirCooledFields::RatedFanPower, "RatedFanPower", "Rated Fan Power"},
{ OS_Refrigeration_GasCooler_AirCooledFields::MinimumFanAirFlowRatio, "MinimumFanAirFlowRatio", "Minimum Fan Air Flow Ratio"},
{ OS_Refrigeration_GasCooler_AirCooledFields::TransitionTemperature, "TransitionTemperature", "Transition Temperature"},
{ OS_Refrigeration_GasCooler_AirCooledFields::TranscriticalApproachTemperature, "TranscriticalApproachTemperature", "Transcritical Approach Temperature"},
{ OS_Refrigeration_GasCooler_AirCooledFields::SubcriticalTemperatureDifference, "SubcriticalTemperatureDifference", "Subcritical Temperature Difference"},
{ OS_Refrigeration_GasCooler_AirCooledFields::MinimumCondensingTemperature, "MinimumCondensingTemperature", "Minimum Condensing Temperature"},
{ OS_Refrigeration_GasCooler_AirCooledFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ OS_Refrigeration_GasCooler_AirCooledFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
{ OS_Refrigeration_GasCooler_AirCooledFields::GasCoolerRefrigerantOperatingChargeInventory, "GasCoolerRefrigerantOperatingChargeInventory", "Gas Cooler Refrigerant Operating Charge Inventory"},
{ OS_Refrigeration_GasCooler_AirCooledFields::GasCoolerReceiverRefrigerantInventory, "GasCoolerReceiverRefrigerantInventory", "Gas Cooler Receiver Refrigerant Inventory"},
{ OS_Refrigeration_GasCooler_AirCooledFields::GasCoolerOutletPipingRefrigerantInventory, "GasCoolerOutletPipingRefrigerantInventory", "Gas Cooler Outlet Piping Refrigerant Inventory"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Refrigeration_GasCooler_AirCooledFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Refrigeration_GasCooler_AirCooledFields> OptionalOS_Refrigeration_GasCooler_AirCooledFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_REFRIGERATION_GASCOOLER_AIRCOOLED_FIELDENUMS_HXX
