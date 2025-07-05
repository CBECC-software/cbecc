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

#ifndef UTILITIES_IDD_SWIMMINGPOOL_INDOOR_FIELDENUMS_HXX
#define UTILITIES_IDD_SWIMMINGPOOL_INDOOR_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class SwimmingPool_IndoorFields
 *  \brief Enumeration of SwimmingPool:Indoor's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(SwimmingPool_IndoorFields, )
#else
class SwimmingPool_IndoorFields: public ::EnumBase<SwimmingPool_IndoorFields> {
 public: 
  enum domain 
  {
Name, SurfaceName, AverageDepth, ActivityFactorScheduleName, MakeupWaterSupplyScheduleName, CoverScheduleName, CoverEvaporationFactor, CoverConvectionFactor, CoverShortWavelengthRadiationFactor, CoverLongWavelengthRadiationFactor, PoolWaterInletNode, PoolWaterOutletNode, PoolHeatingSystemMaximumWaterFlowRate, PoolMiscellaneousEquipmentPower, SetpointTemperatureSchedule, MaximumNumberofPeople, PeopleSchedule, PeopleHeatGainSchedule,   };
  SwimmingPool_IndoorFields()
   : EnumBase<SwimmingPool_IndoorFields>(Name) {} 
  SwimmingPool_IndoorFields(const std::string &t_name) 
   : EnumBase<SwimmingPool_IndoorFields>(t_name) {} 
  SwimmingPool_IndoorFields(int t_value) 
   : EnumBase<SwimmingPool_IndoorFields>(t_value) {} 
  static std::string enumName() 
  { return "SwimmingPool_IndoorFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SwimmingPool_IndoorFields>::value()); }
   private:
    friend class EnumBase<SwimmingPool_IndoorFields>;
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
{ SwimmingPool_IndoorFields::Name, "Name", "Name"},
{ SwimmingPool_IndoorFields::SurfaceName, "SurfaceName", "Surface Name"},
{ SwimmingPool_IndoorFields::AverageDepth, "AverageDepth", "Average Depth"},
{ SwimmingPool_IndoorFields::ActivityFactorScheduleName, "ActivityFactorScheduleName", "Activity Factor Schedule Name"},
{ SwimmingPool_IndoorFields::MakeupWaterSupplyScheduleName, "MakeupWaterSupplyScheduleName", "Make-up Water Supply Schedule Name"},
{ SwimmingPool_IndoorFields::CoverScheduleName, "CoverScheduleName", "Cover Schedule Name"},
{ SwimmingPool_IndoorFields::CoverEvaporationFactor, "CoverEvaporationFactor", "Cover Evaporation Factor"},
{ SwimmingPool_IndoorFields::CoverConvectionFactor, "CoverConvectionFactor", "Cover Convection Factor"},
{ SwimmingPool_IndoorFields::CoverShortWavelengthRadiationFactor, "CoverShortWavelengthRadiationFactor", "Cover Short-Wavelength Radiation Factor"},
{ SwimmingPool_IndoorFields::CoverLongWavelengthRadiationFactor, "CoverLongWavelengthRadiationFactor", "Cover Long-Wavelength Radiation Factor"},
{ SwimmingPool_IndoorFields::PoolWaterInletNode, "PoolWaterInletNode", "Pool Water Inlet Node"},
{ SwimmingPool_IndoorFields::PoolWaterOutletNode, "PoolWaterOutletNode", "Pool Water Outlet Node"},
{ SwimmingPool_IndoorFields::PoolHeatingSystemMaximumWaterFlowRate, "PoolHeatingSystemMaximumWaterFlowRate", "Pool Heating System Maximum Water Flow Rate"},
{ SwimmingPool_IndoorFields::PoolMiscellaneousEquipmentPower, "PoolMiscellaneousEquipmentPower", "Pool Miscellaneous Equipment Power"},
{ SwimmingPool_IndoorFields::SetpointTemperatureSchedule, "SetpointTemperatureSchedule", "Setpoint Temperature Schedule"},
{ SwimmingPool_IndoorFields::MaximumNumberofPeople, "MaximumNumberofPeople", "Maximum Number of People"},
{ SwimmingPool_IndoorFields::PeopleSchedule, "PeopleSchedule", "People Schedule"},
{ SwimmingPool_IndoorFields::PeopleHeatGainSchedule, "PeopleHeatGainSchedule", "People Heat Gain Schedule"},
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
  inline std::ostream &operator<<(std::ostream &os, const SwimmingPool_IndoorFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SwimmingPool_IndoorFields> OptionalSwimmingPool_IndoorFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SWIMMINGPOOL_INDOOR_FIELDENUMS_HXX
