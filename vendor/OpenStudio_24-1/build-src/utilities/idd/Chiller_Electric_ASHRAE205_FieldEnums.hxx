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

#ifndef UTILITIES_IDD_CHILLER_ELECTRIC_ASHRAE205_FIELDENUMS_HXX
#define UTILITIES_IDD_CHILLER_ELECTRIC_ASHRAE205_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Chiller_Electric_ASHRAE205Fields
 *  \brief Enumeration of Chiller:Electric:ASHRAE205's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Chiller_Electric_ASHRAE205Fields, )
#else
class Chiller_Electric_ASHRAE205Fields: public ::EnumBase<Chiller_Electric_ASHRAE205Fields> {
 public: 
  enum domain 
  {
Name, RepresentationFileName, PerformanceInterpolationMethod, RatedCapacity, SizingFactor, AmbientTemperatureIndicator, AmbientTemperatureScheduleName, AmbientTemperatureZoneName, AmbientTemperatureOutdoorAirNodeName, ChilledWaterInletNodeName, ChilledWaterOutletNodeName, ChilledWaterMaximumRequestedFlowRate, CondenserInletNodeName, CondenserOutletNodeName, CondenserMaximumRequestedFlowRate, ChillerFlowMode, OilCoolerInletNodeName, OilCoolerOutletNodeName, OilCoolerDesignFlowRate, AuxiliaryInletNodeName, AuxiliaryOutletNodeName, AuxiliaryCoolingDesignFlowRate, HeatRecoveryInletNodeName, HeatRecoveryOutletNodeName, EndUseSubcategory,   };
  Chiller_Electric_ASHRAE205Fields()
   : EnumBase<Chiller_Electric_ASHRAE205Fields>(Name) {} 
  Chiller_Electric_ASHRAE205Fields(const std::string &t_name) 
   : EnumBase<Chiller_Electric_ASHRAE205Fields>(t_name) {} 
  Chiller_Electric_ASHRAE205Fields(int t_value) 
   : EnumBase<Chiller_Electric_ASHRAE205Fields>(t_value) {} 
  static std::string enumName() 
  { return "Chiller_Electric_ASHRAE205Fields"; }
  domain value() const { return static_cast<domain>(EnumBase<Chiller_Electric_ASHRAE205Fields>::value()); }
   private:
    friend class EnumBase<Chiller_Electric_ASHRAE205Fields>;
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
{ Chiller_Electric_ASHRAE205Fields::Name, "Name", "Name"},
{ Chiller_Electric_ASHRAE205Fields::RepresentationFileName, "RepresentationFileName", "Representation File Name"},
{ Chiller_Electric_ASHRAE205Fields::PerformanceInterpolationMethod, "PerformanceInterpolationMethod", "Performance Interpolation Method"},
{ Chiller_Electric_ASHRAE205Fields::RatedCapacity, "RatedCapacity", "Rated Capacity"},
{ Chiller_Electric_ASHRAE205Fields::SizingFactor, "SizingFactor", "Sizing Factor"},
{ Chiller_Electric_ASHRAE205Fields::AmbientTemperatureIndicator, "AmbientTemperatureIndicator", "Ambient Temperature Indicator"},
{ Chiller_Electric_ASHRAE205Fields::AmbientTemperatureScheduleName, "AmbientTemperatureScheduleName", "Ambient Temperature Schedule Name"},
{ Chiller_Electric_ASHRAE205Fields::AmbientTemperatureZoneName, "AmbientTemperatureZoneName", "Ambient Temperature Zone Name"},
{ Chiller_Electric_ASHRAE205Fields::AmbientTemperatureOutdoorAirNodeName, "AmbientTemperatureOutdoorAirNodeName", "Ambient Temperature Outdoor Air Node Name"},
{ Chiller_Electric_ASHRAE205Fields::ChilledWaterInletNodeName, "ChilledWaterInletNodeName", "Chilled Water Inlet Node Name"},
{ Chiller_Electric_ASHRAE205Fields::ChilledWaterOutletNodeName, "ChilledWaterOutletNodeName", "Chilled Water Outlet Node Name"},
{ Chiller_Electric_ASHRAE205Fields::ChilledWaterMaximumRequestedFlowRate, "ChilledWaterMaximumRequestedFlowRate", "Chilled Water Maximum Requested Flow Rate"},
{ Chiller_Electric_ASHRAE205Fields::CondenserInletNodeName, "CondenserInletNodeName", "Condenser Inlet Node Name"},
{ Chiller_Electric_ASHRAE205Fields::CondenserOutletNodeName, "CondenserOutletNodeName", "Condenser Outlet Node Name"},
{ Chiller_Electric_ASHRAE205Fields::CondenserMaximumRequestedFlowRate, "CondenserMaximumRequestedFlowRate", "Condenser Maximum Requested Flow Rate"},
{ Chiller_Electric_ASHRAE205Fields::ChillerFlowMode, "ChillerFlowMode", "Chiller Flow Mode"},
{ Chiller_Electric_ASHRAE205Fields::OilCoolerInletNodeName, "OilCoolerInletNodeName", "Oil Cooler Inlet Node Name"},
{ Chiller_Electric_ASHRAE205Fields::OilCoolerOutletNodeName, "OilCoolerOutletNodeName", "Oil Cooler Outlet Node Name"},
{ Chiller_Electric_ASHRAE205Fields::OilCoolerDesignFlowRate, "OilCoolerDesignFlowRate", "Oil Cooler Design Flow Rate"},
{ Chiller_Electric_ASHRAE205Fields::AuxiliaryInletNodeName, "AuxiliaryInletNodeName", "Auxiliary Inlet Node Name"},
{ Chiller_Electric_ASHRAE205Fields::AuxiliaryOutletNodeName, "AuxiliaryOutletNodeName", "Auxiliary Outlet Node Name"},
{ Chiller_Electric_ASHRAE205Fields::AuxiliaryCoolingDesignFlowRate, "AuxiliaryCoolingDesignFlowRate", "Auxiliary Cooling Design Flow Rate"},
{ Chiller_Electric_ASHRAE205Fields::HeatRecoveryInletNodeName, "HeatRecoveryInletNodeName", "Heat Recovery Inlet Node Name"},
{ Chiller_Electric_ASHRAE205Fields::HeatRecoveryOutletNodeName, "HeatRecoveryOutletNodeName", "Heat Recovery Outlet Node Name"},
{ Chiller_Electric_ASHRAE205Fields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
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
  inline std::ostream &operator<<(std::ostream &os, const Chiller_Electric_ASHRAE205Fields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Chiller_Electric_ASHRAE205Fields> OptionalChiller_Electric_ASHRAE205Fields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_CHILLER_ELECTRIC_ASHRAE205_FIELDENUMS_HXX
