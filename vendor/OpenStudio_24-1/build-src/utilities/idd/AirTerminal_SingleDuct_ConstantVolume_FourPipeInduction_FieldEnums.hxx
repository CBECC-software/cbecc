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

#ifndef UTILITIES_IDD_AIRTERMINAL_SINGLEDUCT_CONSTANTVOLUME_FOURPIPEINDUCTION_FIELDENUMS_HXX
#define UTILITIES_IDD_AIRTERMINAL_SINGLEDUCT_CONSTANTVOLUME_FOURPIPEINDUCTION_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields
 *  \brief Enumeration of AirTerminal:SingleDuct:ConstantVolume:FourPipeInduction's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields, )
#else
class AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields: public ::EnumBase<AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, MaximumTotalAirFlowRate, InductionRatio, SupplyAirInletNodeName, InducedAirInletNodeName, AirOutletNodeName, HeatingCoilObjectType, HeatingCoilName, MaximumHotWaterFlowRate, MinimumHotWaterFlowRate, HeatingConvergenceTolerance, CoolingCoilObjectType, CoolingCoilName, MaximumColdWaterFlowRate, MinimumColdWaterFlowRate, CoolingConvergenceTolerance, ZoneMixerName,   };
  AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields()
   : EnumBase<AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields>(Name) {} 
  AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields(const std::string &t_name) 
   : EnumBase<AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields>(t_name) {} 
  AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields(int t_value) 
   : EnumBase<AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields>(t_value) {} 
  static std::string enumName() 
  { return "AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields>::value()); }
   private:
    friend class EnumBase<AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields>;
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
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::Name, "Name", "Name"},
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumTotalAirFlowRate, "MaximumTotalAirFlowRate", "Maximum Total Air Flow Rate"},
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::InductionRatio, "InductionRatio", "Induction Ratio"},
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::SupplyAirInletNodeName, "SupplyAirInletNodeName", "Supply Air Inlet Node Name"},
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::InducedAirInletNodeName, "InducedAirInletNodeName", "Induced Air Inlet Node Name"},
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilObjectType, "HeatingCoilObjectType", "Heating Coil Object Type"},
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilName, "HeatingCoilName", "Heating Coil Name"},
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumHotWaterFlowRate, "MaximumHotWaterFlowRate", "Maximum Hot Water Flow Rate"},
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MinimumHotWaterFlowRate, "MinimumHotWaterFlowRate", "Minimum Hot Water Flow Rate"},
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingConvergenceTolerance, "HeatingConvergenceTolerance", "Heating Convergence Tolerance"},
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilObjectType, "CoolingCoilObjectType", "Cooling Coil Object Type"},
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilName, "CoolingCoilName", "Cooling Coil Name"},
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumColdWaterFlowRate, "MaximumColdWaterFlowRate", "Maximum Cold Water Flow Rate"},
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MinimumColdWaterFlowRate, "MinimumColdWaterFlowRate", "Minimum Cold Water Flow Rate"},
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingConvergenceTolerance, "CoolingConvergenceTolerance", "Cooling Convergence Tolerance"},
{ AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::ZoneMixerName, "ZoneMixerName", "Zone Mixer Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields> OptionalAirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AIRTERMINAL_SINGLEDUCT_CONSTANTVOLUME_FOURPIPEINDUCTION_FIELDENUMS_HXX
