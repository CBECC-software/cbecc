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

#ifndef UTILITIES_IDD_AIRTERMINAL_SINGLEDUCT_CONSTANTVOLUME_COOLEDBEAM_FIELDENUMS_HXX
#define UTILITIES_IDD_AIRTERMINAL_SINGLEDUCT_CONSTANTVOLUME_COOLEDBEAM_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields
 *  \brief Enumeration of AirTerminal:SingleDuct:ConstantVolume:CooledBeam's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields, )
#else
class AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields: public ::EnumBase<AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, CooledBeamType, SupplyAirInletNodeName, SupplyAirOutletNodeName, ChilledWaterInletNodeName, ChilledWaterOutletNodeName, SupplyAirVolumetricFlowRate, MaximumTotalChilledWaterVolumetricFlowRate, NumberofBeams, BeamLength, DesignInletWaterTemperature, DesignOutletWaterTemperature, CoilSurfaceAreaperCoilLength, ModelParametera, ModelParametern1, ModelParametern2, ModelParametern3, ModelParametera0, ModelParameterK1, ModelParametern, CoefficientofInductionKin, LeavingPipeInsideDiameter,   };
  AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields()
   : EnumBase<AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields>(Name) {} 
  AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields(const std::string &t_name) 
   : EnumBase<AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields>(t_name) {} 
  AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields(int t_value) 
   : EnumBase<AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields>(t_value) {} 
  static std::string enumName() 
  { return "AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields>::value()); }
   private:
    friend class EnumBase<AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields>;
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
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::Name, "Name", "Name"},
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::CooledBeamType, "CooledBeamType", "Cooled Beam Type"},
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::SupplyAirInletNodeName, "SupplyAirInletNodeName", "Supply Air Inlet Node Name"},
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::SupplyAirOutletNodeName, "SupplyAirOutletNodeName", "Supply Air Outlet Node Name"},
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::ChilledWaterInletNodeName, "ChilledWaterInletNodeName", "Chilled Water Inlet Node Name"},
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::ChilledWaterOutletNodeName, "ChilledWaterOutletNodeName", "Chilled Water Outlet Node Name"},
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::SupplyAirVolumetricFlowRate, "SupplyAirVolumetricFlowRate", "Supply Air Volumetric Flow Rate"},
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::MaximumTotalChilledWaterVolumetricFlowRate, "MaximumTotalChilledWaterVolumetricFlowRate", "Maximum Total Chilled Water Volumetric Flow Rate"},
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::NumberofBeams, "NumberofBeams", "Number of Beams"},
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::BeamLength, "BeamLength", "Beam Length"},
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::DesignInletWaterTemperature, "DesignInletWaterTemperature", "Design Inlet Water Temperature"},
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::DesignOutletWaterTemperature, "DesignOutletWaterTemperature", "Design Outlet Water Temperature"},
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::CoilSurfaceAreaperCoilLength, "CoilSurfaceAreaperCoilLength", "Coil Surface Area per Coil Length"},
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::ModelParametera, "ModelParametera", "Model Parameter a"},
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::ModelParametern1, "ModelParametern1", "Model Parameter n1"},
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::ModelParametern2, "ModelParametern2", "Model Parameter n2"},
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::ModelParametern3, "ModelParametern3", "Model Parameter n3"},
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::ModelParametera0, "ModelParametera0", "Model Parameter a0"},
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::ModelParameterK1, "ModelParameterK1", "Model Parameter K1"},
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::ModelParametern, "ModelParametern", "Model Parameter n"},
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::CoefficientofInductionKin, "CoefficientofInductionKin", "Coefficient of Induction Kin"},
{ AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::LeavingPipeInsideDiameter, "LeavingPipeInsideDiameter", "Leaving Pipe Inside Diameter"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields> OptionalAirTerminal_SingleDuct_ConstantVolume_CooledBeamFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AIRTERMINAL_SINGLEDUCT_CONSTANTVOLUME_COOLEDBEAM_FIELDENUMS_HXX
